#include <initializer_list>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include "DoubleList.hpp"

namespace
{
    int g_passed = 0;
    int g_failed = 0;

    void disable_crash_dialogs()
    {
#ifdef _WIN32
        SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);
#endif
    }

    void pass(const std::string &name)
    {
        ++g_passed;
        std::cout << "[PASS] " << name << '\n';
    }

    void fail(const std::string &message)
    {
        ++g_failed;
        std::cout << "[FAIL] " << message << '\n';
    }

    template <typename Func>
    bool throws_out_of_range(Func func)
    {
        try
        {
            func();
            return false;
        }
        catch (const std::out_of_range &)
        {
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    template <typename Func>
    void expect_throw_out_of_range(Func func, const std::string &name)
    {
        try
        {
            func();
            fail(name + " | expected std::out_of_range");
        }
        catch (const std::out_of_range &)
        {
            pass(name);
        }
        catch (...)
        {
            fail(name + " | wrong exception type");
        }
    }

    bool list_matches_vector(const DoubleList &list, const std::vector<int> &expected)
    {
        if (list.size() != static_cast<int>(expected.size()))
        {
            return false;
        }

        for (int i = 0; i < list.size(); ++i)
        {
            if (list[i] != expected[i])
            {
                return false;
            }
        }

        return true;
    }

    void expect_bool(bool actual, bool expected, const std::string &name)
    {
        if (actual == expected)
        {
            pass(name);
        }
        else
        {
            fail(name + " | expected: " + std::string(expected ? "true" : "false") +
                 ", actual: " + std::string(actual ? "true" : "false"));
        }
    }

    void expect_int(int actual, int expected, const std::string &name)
    {
        if (actual == expected)
        {
            pass(name);
        }
        else
        {
            fail(name + " | expected: " + std::to_string(expected) +
                 ", actual: " + std::to_string(actual));
        }
    }

    void expect_list_equals_vector(const DoubleList &list, const std::vector<int> &expected,
                                   const std::string &name)
    {
        if (list_matches_vector(list, expected))
        {
            pass(name);
            return;
        }

        ++g_failed;
        std::cout << "[FAIL] " << name << " | expected: [";
        for (std::size_t i = 0; i < expected.size(); ++i)
        {
            if (i > 0)
            {
                std::cout << ", ";
            }
            std::cout << expected[i];
        }

        std::cout << "], actual: [";
        for (int i = 0; i < list.size(); ++i)
        {
            if (i > 0)
            {
                std::cout << ", ";
            }
            std::cout << list[i];
        }
        std::cout << "]\n";
    }

    void expect_list(const DoubleList &list, std::initializer_list<int> expected,
                     const std::string &name)
    {
        std::vector<int> expected_values;
        for (int value : expected)
        {
            expected_values.push_back(value);
        }
        expect_list_equals_vector(list, expected_values, name);
    }

    void expect_throw_insert(DoubleList &list, int pos, int value, const std::string &name)
    {
        try
        {
            list.insert(pos, value);
            fail(name + " | expected std::out_of_range");
        }
        catch (const std::out_of_range &)
        {
            pass(name);
        }
        catch (...)
        {
            fail(name + " | wrong exception type");
        }
    }

    void expect_throw_index(const DoubleList &list, int index, const std::string &name)
    {
        try
        {
            (void)list[index];
            fail(name + " | expected std::out_of_range");
        }
        catch (const std::out_of_range &)
        {
            pass(name);
        }
        catch (...)
        {
            fail(name + " | wrong exception type");
        }
    }

    void test_default_constructed()
    {
        DoubleList list;
        expect_int(list.size(), 0, "default size is 0");
        expect_bool(list.empty(), true, "default empty is true");
    }

    void test_push_back()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        expect_list(list, {1, 2, 3}, "push_back preserves order");
    }

    void test_push_front()
    {
        DoubleList list;
        list.push_front(1);
        list.push_front(2);
        list.push_front(3);
        expect_list(list, {3, 2, 1}, "push_front inserts at head");
    }

    void test_mixed_push()
    {
        DoubleList list;
        list.push_back(2);
        list.push_front(1);
        list.push_back(3);
        list.push_front(0);
        expect_list(list, {0, 1, 2, 3}, "mixed push_front and push_back");
    }

    void test_insert_front()
    {
        DoubleList list;
        list.push_back(2);
        list.push_back(3);
        list.insert(0, 1);
        expect_list(list, {1, 2, 3}, "insert at position 0");
    }

    void test_insert_back()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);
        list.insert(list.size(), 3);
        expect_list(list, {1, 2, 3}, "insert at tail");
    }

    void test_insert_middle_from_head_side()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(3);
        list.push_back(4);
        list.insert(1, 2);
        expect_list(list, {1, 2, 3, 4}, "insert in middle near head");
    }

    void test_insert_middle_from_tail_side()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(5);
        list.insert(3, 4);
        expect_list(list, {1, 2, 3, 4, 5}, "insert in middle near tail");
    }

    void test_insert_into_empty_list()
    {
        DoubleList list;
        list.insert(0, 42);
        expect_list(list, {42}, "insert into empty list");
    }

    void test_operator_index()
    {
        DoubleList list;
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);
        list.push_back(40);

        expect_int(list[0], 10, "operator[] head access");
        expect_int(list[1], 20, "operator[] near head access");
        expect_int(list[2], 30, "operator[] near tail access");
        expect_int(list[3], 40, "operator[] tail access");
    }

    void test_clear_and_reuse()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.clear();

        expect_int(list.size(), 0, "clear resets size");
        expect_throw_index(list, 0, "operator[] throws after clear");

        list.push_front(9);
        list.push_back(10);
        expect_list(list, {9, 10}, "list can be reused after clear");
    }

    void test_insert_out_of_range()
    {
        DoubleList list;
        expect_throw_insert(list, -1, 7, "insert rejects negative position");
        expect_throw_insert(list, 1, 7, "insert rejects position beyond size on empty list");

        list.push_back(1);
        list.push_back(2);
        expect_throw_insert(list, 3, 7, "insert rejects position beyond size");
    }

    void test_index_out_of_range()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);

        expect_throw_index(list, -1, "operator[] rejects negative index");
        expect_throw_index(list, 2, "operator[] rejects index equal to size");
    }

    void test_front_and_back()
    {
        DoubleList list;
        list.push_back(2);
        expect_int(list.front(), 2, "front returns only element");
        expect_int(list.back(), 2, "back returns only element");

        list.push_front(1);
        list.push_back(3);
        expect_int(list.front(), 1, "front updates after push_front");
        expect_int(list.back(), 3, "back updates after push_back");

        list.insert(1, 99);
        expect_int(list.front(), 1, "front is stable after middle insert");
        expect_int(list.back(), 3, "back is stable after middle insert");
    }

    void test_empty_state_transitions()
    {
        DoubleList list;
        expect_bool(list.empty(), true, "empty is true on new list");

        list.push_back(1);
        expect_bool(list.empty(), false, "empty is false after push_back");

        list.pop_back();
        expect_bool(list.empty(), true, "empty is true after removing last element");

        list.push_front(5);
        expect_bool(list.empty(), false, "empty is false after push_front");

        list.clear();
        expect_bool(list.empty(), true, "empty is true after clear");
    }

    void test_pop_front()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.pop_front();
        expect_list(list, {2, 3}, "pop_front removes first element");
        expect_int(list.front(), 2, "front updates after pop_front");
        expect_int(list.back(), 3, "back stays correct after pop_front");

        list.pop_front();
        list.pop_front();
        expect_bool(list.empty(), true, "pop_front can empty the list");
        expect_int(list.size(), 0, "size is 0 after popping all from front");
    }

    void test_pop_back()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);

        list.pop_back();
        expect_list(list, {1, 2}, "pop_back removes last element");
        expect_int(list.front(), 1, "front stays correct after pop_back");
        expect_int(list.back(), 2, "back updates after pop_back");

        list.pop_back();
        list.pop_back();
        expect_bool(list.empty(), true, "pop_back can empty the list");
        expect_int(list.size(), 0, "size is 0 after popping all from back");
    }

    void test_mixed_pop_operations()
    {
        DoubleList list;
        for (int value = 1; value <= 5; ++value)
        {
            list.push_back(value);
        }

        list.pop_front();
        list.pop_back();
        expect_list(list, {2, 3, 4}, "mixed pops keep middle elements linked");

        list.pop_back();
        expect_list(list, {2, 3}, "pop_back after mixed pops");

        list.pop_front();
        expect_list(list, {3}, "pop_front leaves single element");

        expect_int(list.front(), 3, "front is correct for single element after pops");
        expect_int(list.back(), 3, "back is correct for single element after pops");
    }

    void test_empty_list_operations_throw()
    {
        DoubleList list;
        expect_throw_out_of_range([&] { list.front(); }, "front throws on empty list");
        expect_throw_out_of_range([&] { list.back(); }, "back throws on empty list");
        expect_throw_out_of_range([&] { list.pop_front(); }, "pop_front throws on empty list");
        expect_throw_out_of_range([&] { list.pop_back(); }, "pop_back throws on empty list");
    }

    void test_erase_front()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);

        list.erase(0);
        expect_list(list, {2, 3, 4}, "erase removes first element");
        expect_int(list.front(), 2, "front updates after erase first");
        expect_int(list.back(), 4, "back stays correct after erase first");
    }

    void test_erase_middle()
    {
        DoubleList list;
        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        list.push_back(4);
        list.push_back(5);

        list.erase(2);
        expect_list(list, {1, 2, 4, 5}, "erase removes middle element");
        expect_int(list.front(), 1, "front stays correct after erase middle");
        expect_int(list.back(), 5, "back stays correct after erase middle");
    }

    void test_erase_single_element()
    {
        DoubleList list;
        list.push_back(42);

        list.erase(0);
        expect_bool(list.empty(), true, "erase can remove the only element");
        expect_int(list.size(), 0, "size is 0 after erase only element");
        expect_throw_out_of_range([&] { list.front(); }, "front throws after erase only element");
        expect_throw_out_of_range([&] { list.back(); }, "back throws after erase only element");
    }

    void test_erase_out_of_range()
    {
        DoubleList list;
        expect_throw_out_of_range([&] { list.erase(0); }, "erase rejects index 0 on empty list");
        expect_throw_out_of_range([&] { list.erase(-1); }, "erase rejects negative index");

        list.push_back(1);
        list.push_back(2);
        list.push_back(3);
        expect_throw_out_of_range([&] { list.erase(3); }, "erase rejects index equal to size");
        expect_throw_out_of_range([&] { list.erase(99); }, "erase rejects index beyond size");
    }

    void test_erase_sequence()
    {
        DoubleList list;
        for (int value = 1; value <= 6; ++value)
        {
            list.push_back(value);
        }

        list.erase(1);
        expect_list(list, {1, 3, 4, 5, 6}, "erase sequence after first middle erase");

        list.erase(2);
        expect_list(list, {1, 3, 5, 6}, "erase sequence after second middle erase");

        list.erase(0);
        expect_list(list, {3, 5, 6}, "erase sequence after erasing head");
    }

    int run_probe_erase_last_index()
    {
        DoubleList list;
        list.push_back(10);
        list.push_back(20);
        list.push_back(30);

        list.erase(2);

        if (list.size() != 2)
        {
            return 2;
        }
        if (list.front() != 10 || list.back() != 20)
        {
            return 3;
        }
        if (list[0] != 10 || list[1] != 20)
        {
            return 4;
        }

        return 0;
    }

    void test_erase_last_index(const char *self_path)
    {
        std::string command = "\"";
        command += self_path;
        command += "\" --probe-erase-last-index >nul 2>nul";

        int exit_code = std::system(command.c_str());
        if (exit_code == 0)
        {
            pass("erase removes last element");
        }
        else
        {
            fail("erase removes last element | child process crashed or returned non-zero");
        }
    }

    void test_large_push_back_sequence()
    {
        DoubleList list;
        std::vector<int> expected;

        for (int i = 0; i < 200; ++i)
        {
            list.push_back(i);
            expected.push_back(i);
        }

        expect_int(list.size(), 200, "large push_back updates size");
        expect_list_equals_vector(list, expected, "large push_back sequence");
    }

    void test_large_push_front_sequence()
    {
        DoubleList list;
        std::vector<int> expected;

        for (int i = 0; i < 200; ++i)
        {
            list.push_front(i);
            expected.insert(expected.begin(), i);
        }

        expect_int(list.size(), 200, "large push_front updates size");
        expect_list_equals_vector(list, expected, "large push_front sequence");
    }

    void test_insert_all_positions()
    {
        for (int pos = 0; pos <= 4; ++pos)
        {
            DoubleList list;
            std::vector<int> expected = {10, 20, 30, 40};

            for (int value : expected)
            {
                list.push_back(value);
            }

            list.insert(pos, 99);
            expected.insert(expected.begin() + pos, 99);
            if (!list_matches_vector(list, expected))
            {
                fail("insert at every position | first failing pos=" + std::to_string(pos));
                return;
            }
        }

        pass("insert at every position");
    }

    void test_repeated_clear_cycles()
    {
        DoubleList list;

        for (int round = 0; round < 20; ++round)
        {
            std::vector<int> expected;

            for (int i = 0; i < 25; ++i)
            {
                int value = round * 100 + i;
                if (i % 2 == 0)
                {
                    list.push_back(value);
                    expected.push_back(value);
                }
                else
                {
                    list.push_front(value);
                    expected.insert(expected.begin(), value);
                }
            }

            if (!list_matches_vector(list, expected))
            {
                fail("repeated clear cycles | content mismatch at round=" + std::to_string(round));
                return;
            }

            list.clear();
            if (list.size() != 0)
            {
                fail("repeated clear cycles | clear did not reset size at round=" +
                     std::to_string(round));
                return;
            }
        }

        pass("repeated clear cycles");
    }

    void test_stress_against_vector()
    {
        DoubleList list;
        std::vector<int> expected;
        std::mt19937 rng(20260509);
        std::uniform_int_distribution<int> op_dist(0, 11);
        std::uniform_int_distribution<int> value_dist(-1000, 1000);

        for (int step = 0; step < 1000; ++step)
        {
            int op = op_dist(rng);
            int value = value_dist(rng);

            if (expected.empty())
            {
                if (op == 11)
                {
                    list.clear();
                    expected.clear();
                }
                else
                {
                    list.push_front(value);
                    expected.insert(expected.begin(), value);
                }
            }
            else if (op <= 2)
            {
                list.push_front(value);
                expected.insert(expected.begin(), value);
            }
            else if (op <= 5)
            {
                list.push_back(value);
                expected.push_back(value);
            }
            else if (op <= 8)
            {
                std::uniform_int_distribution<int> pos_dist(0, static_cast<int>(expected.size()));
                int pos = pos_dist(rng);
                list.insert(pos, value);
                expected.insert(expected.begin() + pos, value);
            }
            else if (op == 9)
            {
                list.pop_front();
                expected.erase(expected.begin());
            }
            else if (op == 10)
            {
                list.pop_back();
                expected.pop_back();
            }
            else
            {
                list.clear();
                expected.clear();
            }

            if (list.empty() != expected.empty())
            {
                fail("stress against vector | empty mismatch at step " + std::to_string(step));
                return;
            }

            if (expected.empty())
            {
                if (!throws_out_of_range([&] { list.front(); }))
                {
                    fail("stress against vector | front should throw on empty at step " +
                         std::to_string(step));
                    return;
                }

                if (!throws_out_of_range([&] { list.back(); }))
                {
                    fail("stress against vector | back should throw on empty at step " +
                         std::to_string(step));
                    return;
                }
            }
            else
            {
                if (list.front() != expected.front())
                {
                    fail("stress against vector | front mismatch at step " + std::to_string(step));
                    return;
                }

                if (list.back() != expected.back())
                {
                    fail("stress against vector | back mismatch at step " + std::to_string(step));
                    return;
                }
            }

            bool should_check_full_content = step < 50 || step % 50 == 0 || op >= 9;
            if (should_check_full_content && !list_matches_vector(list, expected))
            {
                fail("stress against vector | content mismatch at step " + std::to_string(step));
                return;
            }

            if (list.size() != static_cast<int>(expected.size()))
            {
                fail("stress against vector | size mismatch at step " + std::to_string(step));
                return;
            }
        }

        pass("stress against vector");
    }
}

int main(int argc, char *argv[])
{
    disable_crash_dialogs();

    if (argc > 1 && std::string(argv[1]) == "--probe-erase-last-index")
    {
        return run_probe_erase_last_index();
    }

    test_default_constructed();
    test_push_back();
    test_push_front();
    test_mixed_push();
    test_insert_front();
    test_insert_back();
    test_insert_middle_from_head_side();
    test_insert_middle_from_tail_side();
    test_insert_into_empty_list();
    test_operator_index();
    test_clear_and_reuse();
    test_insert_out_of_range();
    test_index_out_of_range();
    test_front_and_back();
    test_empty_state_transitions();
    test_pop_front();
    test_pop_back();
    test_mixed_pop_operations();
    test_empty_list_operations_throw();
    test_erase_front();
    test_erase_middle();
    test_erase_single_element();
    test_erase_out_of_range();
    test_erase_sequence();
    test_erase_last_index(argv[0]);
    test_large_push_back_sequence();
    test_large_push_front_sequence();
    test_insert_all_positions();
    test_repeated_clear_cycles();
    test_stress_against_vector();

    std::cout << "\nPassed: " << g_passed << '\n';
    std::cout << "Failed: " << g_failed << '\n';

    return g_failed == 0 ? 0 : 1;
}

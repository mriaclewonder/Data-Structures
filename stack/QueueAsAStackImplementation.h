#include <iostream>

#include <queue>

namespace queue_as_a_stack_implementation {
    class MyStack {
    public:
        MyStack() {

        }

        void push(int val)
        {
            int n = q.size();
            q.push(val);
            for (int i = 0; i < n; ++i) {
                int temp = q.front();
                q.pop();
                q.push(temp);
            }
        }

        int pop()
        {
            int temp = q.front();
            q.pop();
            return temp;
        }

        int top() const
        {
            return q.front();
        }

        bool empty() const {
            return q.empty();
        }

    private:
        std::queue<int> q;
    };
}
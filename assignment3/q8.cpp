#include <iostream>
class Stack {
private:
    enum { MAX_SIZE = 5 };
    int arr[MAX_SIZE];
    int top;

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() const {
        return top == -1;
    }

    bool isFull() const {
        return top == MAX_SIZE - 1;
    }

    void push(int value) {
        if (isFull()) {
            std::cout << "Stack Overflow" << value << "." << std::endl;
            return;
        }
        arr[++top] = value;
        std::cout << "Pushed: " << value << std::endl;
    }

    int pop() {
        if (isEmpty()) {
            std::cout << "Stack Underflow" << std::endl;
            return -1;
        }
        int poppedValue = arr[top--];
        std::cout << "Popped: " << poppedValue << std::endl;
        return poppedValue;
    }
};
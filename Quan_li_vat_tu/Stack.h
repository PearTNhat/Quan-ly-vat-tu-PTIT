#pragma once
#include "Header.h"
#include "Goods_Struct.h"
template <typename T>
struct Stack {
    T** a;
    int top;
    int capacity;

    Stack(int size) {
        capacity = size;
        a = new T * [capacity];
        top = -1;
    }

    ~Stack() {
        delete[] a;
    }
};

template <typename T>
bool isEmpty(Stack<T>& s) {
    return s.top == -1;
}

template <typename T>
void push(Stack<T>& s, T* x) {
    if (s.capacity - 1 == s.top) {
        cout << " Stack is overflow";
    }
    else {
        s.a[++s.top] = x;
    }
}

template <typename T>
T* pop(Stack<T>& s) {
    if (s.top == -1) {
        cout << " Stack is empty";
        return NULL;
    }
    return s.a[s.top--];
}
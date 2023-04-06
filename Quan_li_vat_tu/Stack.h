#pragma once
#include "Header.h"
#include "Goods_Struct.h"
struct Stack {
    DS_VatTu**a;
    int top ;
    int capacity;
    Stack(int size) {       
        capacity = size;
        a = new DS_VatTu *[capacity];
        top = -1;
    }

    ~Stack() {
        delete[] a;
    }
};
bool isEmpty(Stack& s) {
    return s.top == -1;
}
void push(Stack &s, DS_VatTu* x) {
    if (s.capacity-1==s.top) {
        cout << " Stack is overflow";
    }
    else {
        s.a[++s.top] = x;
    }
}
DS_VatTu* pop(Stack& s) {
    if (s.top == -1) {
        cout << " Stack is empty";
        return NULL;
    }   
    return s.a[s.top--];
    
}

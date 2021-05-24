//
// Created by User on 24/05/2021.
//
#include <memory>
#include "Iterator.h"
#ifndef EXPERTCPP_EX2_LINKEDLIST_H
#define EXPERTCPP_EX2_LINKEDLIST_H

using namespace std;

template <class T> class LinkedList {
public:

    struct Node{
        T data;
        unique_ptr<Node> next;
        Node(T data): data{data}, next{nullptr} {}
    };

    LinkedList(): head{nullptr} {};
    ~LinkedList() {while(head) head=std::move(head->next);}
    void add(T data) {
        Node* new_node = new Node(data);
        auto temp = std::unique_ptr<Node>(new_node);
        if(head) temp->next = std::move(head);
        head = std::move(temp);
    }
    Iterator begin() const{ return Iterator(head.get());}
    Iterator end() const {
        Node* curr=head.get();
        while(curr->next){curr=curr->next.get();}
        return Iterator(curr);
    }

private:
    unique_ptr<Node> head;
};


#endif //EXPERTCPP_EX2_LINKEDLIST_H

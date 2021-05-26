//
// Created by User on 24/05/2021.
//
#include <memory>
#ifndef EXPERTCPP_EX2_LINKEDLIST_H
#define EXPERTCPP_EX2_LINKEDLIST_H

using namespace std;

template <class T> class LinkedList {
public:
    struct Node{
        T data;
        shared_ptr<Node> next;
        Node(T data): data{data}, next{nullptr} {}

        shared_ptr<Node> getNext(){return next;}
    };

    LinkedList(): head{nullptr}, cursor{}, list_size{0} {};
    ~LinkedList(){while(head) head=std::move(head->next);}
    shared_ptr<Node> getHead(){return  head;}
    weak_ptr<Node> getCursor(){return cursor;}
    void add(T data){
        Node* new_node = new Node(data);
        auto temp = std::shared_ptr<Node>(new_node);
        if(head) {
            temp->next = std::move(head);
            head = std::move(temp);
        }
        else{
            head = std::move(temp);
            tail=head;
        }
        cursor=head;
        list_size++;
    }
    bool isEmpty(){return list_size? 0:1;}
    bool hasNext(){ return cursor.lock().get()->getNext()? 1:0;}
    bool endOfLinkedList(){return getCursor().lock().get()? 0:1;}
    void setToHead(){cursor=head;}
    LinkedList<T>& operator++(){
        auto temp = cursor.lock();
        cursor = temp.get()->getNext();
        return *this;
    }

private:
    shared_ptr<Node> head;
    weak_ptr<Node> tail;
    weak_ptr<Node> cursor;
    int list_size;
};


#endif //EXPERTCPP_EX2_LINKEDLIST_H

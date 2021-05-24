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

    LinkedList(): head{nullptr}, cursor{} {};
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
    }
    bool hasNext(){ return cursor.lock().get()->getNext()? 1:0;}
    bool end(){return cursor.lock().get() == tail.lock().get();}

    LinkedList<T>& operator++(){
        auto temp = cursor.lock();
        if(hasNext()){ cursor = temp.get()->getNext(); }
        else{cursor = head;};
        return *this;
    }

private:
    shared_ptr<Node> head;
    weak_ptr<Node> tail;
    weak_ptr<Node> cursor;
};


#endif //EXPERTCPP_EX2_LINKEDLIST_H

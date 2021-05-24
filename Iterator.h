//
// Created by User on 24/05/2021.
//

#ifndef EXPERTCPP_EX2_ITERATOR_H
#define EXPERTCPP_EX2_ITERATOR_H

class Node;
class Iterator {
private:
    Node *current;
public:
    Iterator(){
        current= nullptr;
    };

    Iterator(Node *ptr){
        current=ptr;
    };

};


#endif //EXPERTCPP_EX2_ITERATOR_H

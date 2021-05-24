#include <iostream>
#include "System.h"
#include <string>


int main() {
    System s;
    s.init("inputFile");
    s.printContainersGraph();
//    s.printTimesGraph();
//    class Integer {
//        int i;
//    public:
//        Integer(int x) : i{x} {};
//
//        int getInteger() { return i; }
//    };
//    LinkedList<Integer> lnk;
//    lnk.add(Integer{2});
//    lnk.add(Integer{5});
//    lnk.add(Integer{90});
//    lnk.add(Integer{55});
////    cout << lnk.getCursor().lock().get()->data.getInteger() << endl;
////    lnk.setCursorNext();
////    ++lnk;
////    cout << lnk.getCursor().lock().get()->data.getInteger()<<endl;
////    ++lnk;
////    cout << lnk.getCursor().lock().get()->data.getInteger()<<endl;
////    ++lnk;
////    cout << lnk.getCursor().lock().get()->data.getInteger()<<endl;
////    ++lnk;
//    lnk.setToHead();
//    while(!lnk.endOfLinkedList()){
//        cout << lnk.getCursor().lock().get()->data.getInteger()<<endl;
//        ++lnk;
//    }
//    lnk.setToHead();




    return 0;
}

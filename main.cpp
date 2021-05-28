#include <iostream>
#include "System.h"
#include <string>


int main() {
    System s;
    cout<<endl;
//    s.load("inputFile");
    s.load("input");
//    s.load("input2");


    s.printTimesGraph();
    cout<<endl;
    s.printContainersGraph();
//
//
//    s.outbound(3);
//    s.inbound(3);
//    Time t = Time(19,1,9,15);
//    cout << "balance in time:"<<endl;
//    s.balance(3,t);




//class Integer{
//   int i;
//public:
//   Integer(int x):i{x}{};
//   int gati(){return i;}
//
//
//LinkedList<Inte
//};ger> lnk;
//lnk.add(Integer(5));
//lnk.add(Integer(7));
//
//    lnk.add(Integer(9));
//lnk.setToHead();
//while(!lnk.endOfLinkedList()){
//    cout<<lnk.getCursor().lock()->data.gati();
//    ++lnk;
//}

    return 0;
}

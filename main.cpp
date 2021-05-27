#include <iostream>
#include "System.h"
#include <string>


int main() {
    System s;
    cout<<endl;
//    s.load("inputFile");

    s.load("input2");
    s.printContainersGraph();
    cout<<endl;
    s.printTimesGraph();


    s.outbound(0);
//s.inbound(0);
//    cout << endl;
//    cout << "from main:"<<endl;
//



//class Integer{
//   int i;
//public:
//   Integer(int x):i{x}{};
//   int gati(){return i;}
//
//};
//
//LinkedList<Integer> lnk;
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

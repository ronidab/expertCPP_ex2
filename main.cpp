#include <iostream>
#include "System.h"
#include <string>


int main() {
    System s;
    s.load("inputFile");
    s.load("input2");
    s.printContainersGraph();
    s.outbound(0);
s.inbound(0);
    cout << endl;
    cout << "from main:"<<endl;

    s.printTimesGraph();

    return 0;
}

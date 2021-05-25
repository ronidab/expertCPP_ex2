#include <iostream>
#include "System.h"
#include <string>


int main() {
    System s;
    s.init("inputFile");
    s.printContainersGraph();
    cout << endl;
    s.printTimesGraph();

    return 0;
}

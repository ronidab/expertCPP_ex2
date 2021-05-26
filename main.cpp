#include <iostream>
#include "System.h"
#include <string>


int main() {
    System s;
    s.load("inputFile");
    s.load("input2");
    s.printContainersGraph();
    cout << endl;
    s.printTimesGraph();

    return 0;
}

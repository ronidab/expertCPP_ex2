#include <iostream>
#include "Terminal.h"
#include <string>


int main(int argc, char **argv) {
    Terminal t;
    if (argc == 1) {
        cerr << "At least one input file required.";
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        try {
            t.validInput(argv[i]);
        }
        catch (exception &e) {
            cout << e.what();
            exit(1);
        }
    }
    //if we get here - all files are valid
    for (int j = 1; j < argc; j++) {
        t.loadFile(argv[j]);
    }

    t.run();



    return 0;
}

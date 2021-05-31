#include <iostream>
#include "Terminal.h"
#include <string>


int main(int argc, char **argv) {
    ifstream f("input");
    if (!f) { cout << "cannot!"; }

    Terminal t;
//    int line;
//    if (!t.validInput("input", line)) {
//        cerr << InvalidINput("input", line).what();
//        exit(1);
//    }

    if (argc == 1) {
        cerr << "At least one input file required.";
        exit(1);
    }

    int line;
    int i = 1;
    for (; i < argc && string(argv[i])!="-o"; i++) {
        if (!t.validInput(argv[i], line)){
            cerr << InvalidINput(argv[i],line).what();
            exit(1);
        }
    }

    //output file argument exist
    if(argv[i] =="-o"){
        t.setOutputFile(argv[++i]);
    }

    //if we get here - all files are valid
    for (int j = 1; j < argc; j++) {
        t.loadFile(argv[j]);
    }

    t.run();

    return 0;
}

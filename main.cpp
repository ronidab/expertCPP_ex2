#include <iostream>
#include "Terminal.h"
#include <string>


int main(int argc, char **argv) {

    if (argc == 1) {
        cerr << "At least one input file required.\n";
        exit(1);
    }
    if ((string(argv[1])).compare("-i")){
        cerr << "-i flag required.\n";
        exit(1);
    }

    Terminal t;
    int line;
    int i = 2;
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
    for (int j = 2; j < argc; j++) {
        t.loadFile(argv[j]);
    }

    t.run();

    return 0;
}

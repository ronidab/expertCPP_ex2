#include <iostream>
#include "Terminal.h"
#include <string>


int main(int argc, char **argv) {
    bool loaded = false;
    Terminal t;

    for (int i = 0; i < argc; i++) {
        try {
            t.validInput(argv[i]);
        }
        catch (exception &e) {
            cout << e.what();
            continue;
        }
        t.loadFile(argv[i]);
        if(!loaded){loaded=true;}
    }

    t.run();


    return 0;
}

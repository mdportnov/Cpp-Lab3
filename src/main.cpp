#include "lab3.h"

using namespace lab3;

const char *msgs[] = {" 0. Exit",
                      " 1. Input new nums and perform operations"
};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

int (*functions[])(){nullptr, dialog_input};

int main() {
    int rc;
//    BigInt bigInt = BigInt(std::cin);
//    std::cout<<bigInt;
    while ((rc = dialog(msgs, NMsgs))) {
        if (!functions[rc]())
            break;
    }
}
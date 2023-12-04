#include <stdio.h>
#include <iostream>
#include "hangman.h"

int main() {

    std::cout << "Let's play Hangman!" << std::endl;
    int userInput = 0;

    while (userInput != 9) {
        EvilHangman h;

        h.startHM();

        std::cout << "Want to play again? Type '9' to stop, or anything else to go again." << std::endl;
        std::cin >> userInput;
    }

    return 0;
}
/*
* File: hangman.cpp
* ----------------------------------------
* Implements the hangman class found in 
* hangman.h, adding functionality to its methods
* Also implements a subclass called "EvilHangman"  
*
* This is a very dirty implementation. I'm also working
* on a more cleaned up version to understand how this should
* "properly" work
*/

#include "hangman.h"
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>

HangMan::HangMan() {
    /* initialize */
    maxGuesses = 7;
    currGuesses = 0;
    gameWord = "";
    progress = "";

    /* 
        Add words into vector of possible words.
        I used GfG and thispointer.com for ref on
        reading in the file. 
    */
    std::fstream wordFile;
    wordFile.open("words.txt");
    if (wordFile.is_open()) {
        /* temporary string variable to hold each word */
        std::string temp;

        /* Read in the words from "words.txt" */
        while (getline(wordFile, temp)) { wordList.push_back(temp); }   

        /* Close the file once done. */
        wordFile.close();               

    }
    else {
        /* Lets me know if opening the file didn't work. */
        std::cout << "Error opening words.txt." << std::endl; 
    }

}

/*
* Initializes and plays the game of hangman.
*/
void HangMan::startHM() {
    std::cout << "Welcome to Hangman!" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    std::cout << "Enter '4' to quit" << std::endl;
    /* Runs once at the start to choose the word */
    gameWord = chooseWord();
    std::cout << "You have " << maxGuesses << " wrong guesses remaining." << std::endl;

    /* Fill the "progress" to show blanks */
    for (int i = 0; i < gameWord.length(); i++) {
        progress += "_";
    }

    /* Print the blanks to give amount of letters */
    std::cout << progress << std::endl;

    /* Main game loop */
    while (currGuesses < maxGuesses ) {
        std::cout << "Enter a letter to guess: " << std::endl;
        
        /* Grab guess and then flush input */
        char guess;
        std::cin >> guess;
        std::cout << std::endl;
        if (guess == '4') {
            std::cout << "Closing..." << std::endl;
            exit(0);
        }

        if (isInWord(guess)) {
            std::cout << "Nice! You found a letter." << std::endl;
            updateBoard(guess);
        }
        else {
            std::cout << "Nope! That's a wrong guess." << std::endl;
            currGuesses++;
        }

        std::cout << progress << std::endl;
        std::cout << "Wrong guesses: " << currGuesses << " / " << maxGuesses << std::endl;
        if (gameWord.find(progress) != std::string::npos) { break; }
    }

    if (currGuesses >= maxGuesses) {
        std::cout << "Aw man! Looks like you lost." << std::endl;
        std::cout << "The word was '" << gameWord << "'." << std::endl;
    }
    else if (progress == gameWord) {
        std::cout << "You got it right, great job! The word was '" << gameWord << "'!" << std::endl; 
    }

}

/*
* Uses the random library to select a word at random from
* the vector of words to be the "hangman" word
*/
std::string HangMan::chooseWord() {
    srand(time(0));                                 // Seed the random gen
    int listLen = wordList.size();                  // grab the size of the vector
    std::string ret = wordList[rand() % listLen];   // Choose a random word

    // return the random word
    return ret;
}
/*
*
*/
void HangMan::updateBoard(char usrChar) {
    for (int i = 0; i < gameWord.length(); i++) {
        if (usrChar == gameWord[i]) {
            progress[i] = usrChar;
        }
    }
}
/*
* 
*/
bool HangMan::isInWord(char usrChar) {
    /* If the character was already found */
    if (progress.find(usrChar) != std::string::npos) {
        std::cout << "...But you've already found this character. Let's still call it correct." << std::endl;
    }
    
    if (gameWord.find(usrChar) != std::string::npos) {
        return true;
    }
    else {
        return false;
    }

}

EvilHangman::EvilHangman() {
    /* 
        initialize the map 
        unfortunately hardcoded (kinda?)
        Designed to use the provided "words.txt" file in the
        directory.
    */
    families = 
    {
        {std::string("_l____"), {"alaska", "altera", "altria", "planar"}},
        {std::string("_a____"), {"banned", "battle", "hangar", "panned"}},
        {std::string("a____a"), {"altera", "altria"}},
        {std::string("_____r"), {"hangar", "planar", "quasar"}},
        {std::string("____th"), {"breath", "health", "wreath"}},
        {std::string("__nned"), {"banned", "panned"}},
        {std::string("_anned"), {"banned", "panned"}},
        {std::string("alt__a"), {"altria", "altera"}},
        {std::string("__a_a_"), {"planar", "quasar"}},
        {std::string("__a_ar"), {"planar", "quasar"}},
        {std::string("__eath"), {"breath", "wreath"}}
    }; // Note: many of these keys were to test it changing the outcome

}

/* 
EvilHangman equivalent of updateBoard, changing the word if possible
Whenever the board is updated to match the guessed letters, if it can change
the word to a different one, it does so. 
*/
void EvilHangman::updateBoard(char usrChar) {
    for (int i = 0; i < gameWord.length(); i++) {
        if (usrChar == gameWord[i]) {
            progress[i] = usrChar;
        }
    }

    if (families.find(progress) != families.end()){
        wordList = families.at(progress);
        gameWord = chooseWord();


        // test if it actually changes (debug)
        // std::cout << gameWord << std::endl;
        // it did in fact change
    }

}
// debug method for testing vector
/*
void HangMan::printVector() {
    int i = 0;
    while (i < wordList.size()) {
        std::cout << wordList[i] << std::endl;
        i++;
    }
}
*/

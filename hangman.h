/*
* File: hangman.h
* ---------------------------------------
* This file outlines functions for a HangMan game class.
* 
*/

#ifndef _hangman_h
#define _hangman_h

#include <stdlib.h>
#include <string>
#include <vector>
#include <map>

class HangMan {
    protected:
    int maxGuesses;                     // max number of allowed wrong guesses
    int currGuesses;                    // current wrong guesses
    std::string gameWord;               // the hangman word
    std::string progress;               // the progress on the hangman word
    std::vector<std::string> wordList;  // list of possible words

    public:
    /* Constructor */
    HangMan();

    // Starts the game of Hangman
    void startHM();

    // Choose a random word from a list of words.                                 
    std::string chooseWord();

    // update the board
    // modified in EvilHangman
    virtual void updateBoard(char UsrChar);

    // check if letter is in the word
    bool isInWord(char usrChar);

    // debug function
    // void printVector();

};

/*
Implements Evil Hangman; the word will attempt to change as guesses are made
*/
class EvilHangman : public HangMan {
    private:
    std::map<std::string, std::vector<std::string>> families;
    public:
    void updateBoard(char usrChar) override;

    EvilHangman();

};

#endif
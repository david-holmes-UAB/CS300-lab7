# CS300-lab7
Repo for CS300 Lab 7 at UAB

Code for the implementation of HangMan and Evil Hangman. Truthfully a very dirty implementation, one that I would ideally go back to clean up. I initially had multiple issues with comparing validity of strings, due to certain strings registering as C strings instead of C++ 11 strings (an example of this can be seen the travesty of a map initialization in the EvilHangman constructor). Similarly, variables are set to protected rather than private in the base class, but realistically using setters and getters would have probably been better form.

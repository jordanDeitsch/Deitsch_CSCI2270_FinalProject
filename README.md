# Deitsch_CSCI2270_FinalProject
- Project Summary
This project is designed with the intention of enabling the playing of a realistic game of blackjack with the additional feature of assisted card counting. The program will begin with the choice of the user to decide on the number of decks to be in use within the game. The number of decks in a blackjack game greatly affects the ability of a player to count cards; one deack is easily counted, while seven or eight decks (as used in Las Vegas casinos) make for lower probability of achieving a "high count" before the dealer reshuffles. The game will then proceed as a standard game, with the player having the choice to hit or stay and place varrying bets. The dealer will be constrained to standard rules of the game, and the results of each hand in addition to the cards played that hand will be displayed for the player's convenience. At any time in the game the player will also have the ability to check on the "count" of the game. This count will be determined by the type of card counting system chosen by the player to follow at the beginning of the game. The primary type of card counting system that will be implemented in this program is the High-Low system, the most standard system of card counting. This ability to check the count can be used as either practice for the player's own attempts to count cards, or to influence their betting strategy during the game in an attempt to gauge the effectiveness of a certain system.

- How to Run
This program can be run through the terminal or in the ternimal emulator on any code platform (xCode, codeblocks, etc.). The program contains a driver file saved as FinalProject.cpp, as well as a class implementation file and associated header file saved as Blackjack.cpp and Blackjack.h, respectively. The final file required for this program to run is the text file saved as cards.txt. This text file must be saved in the same directory as the driver file so the program can open it and read the necesary information. An example of running this file in the terminal is shown below, when in the approporiate directory.

    g++ FinalProject.cpp Blackjack.cpp   (compiles the program with appropriate class file)
    ./a.out                              (runs program)

All project documentation is provided in the comment blocks before each method in the class implementation file, as per directions. These comment blocks all include a function prototype, a function description, an example of the function being called, and pre and post-conditions for the function. All functions are fairly strightforward, with descriptive names and obvious purposes.

- Dependencies
This program does not have any dependencies other than the requirements listed in the "How to Run" explanation. These requirements are that the directory containing the driver file must also contain the class implementation and text file. The program also makes use of many standard libraries within c++, including vector, string, fstream, iostream, stdlib.h, stdio.h, and time.h.

- System Requirements
This program will run on Mac OSX (developed in XCode) and Linux (tested on Ubuntu virtual machine). Windows terminal has not been tested, but the code is not tailored to any specific system and should work for all.

- Group Members
No other group members

- Contributors

- Issues/bugs and Possible Functions
--Primary bug is found in corner cases where the user must define the ace as either a 1 or 11 point card. These cases include times when the player is dealt multiple aces, or when the ace is initially allowed to be either a 1 or 11, but in later play is changed again.
--Bug in the dealer hand when multiple aces are dealt. Normally in blackjack an ace is considered soft (11) for the dealer, but when multiple aces are dealt they can be altered, an option the program does not currently handle.
--Adding to the program an option to choose between different types of card counting systems would be useful, as this could be used to compare efficiency between different card counting systems. Other possible systems to add are the Ken Uston system and Wong Halves.
--Adding an option for the user to "double down" on their bet at the beginning of the hand would be useful. The user can also be given the option to place an insurance bet and split theor cards, all adding to the realism of the game.
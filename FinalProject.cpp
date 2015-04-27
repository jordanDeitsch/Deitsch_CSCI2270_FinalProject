//
//  main.cpp
//  BlackJack
//
//  Created by Jordan Deitsch on 4/16/15.
//  Copyright (c) 2015 Jordan Deitsch. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Blackjack.h"

using namespace std;

vector<cardNode> addCard(vector<cardNode>, string);
int startMenu();

//int argc, const char * argv[]
int main(){

    ifstream inFile;   //opening file and reading cards
    string fileLine;
    string fileName = "cards.txt";
    inFile.open(fileName);
    
    vector<cardNode> singleDeck;  //create vector of all cards in one deck
    
    while(getline(inFile, fileLine)){   //add each card in file, calls function addCard
        
        singleDeck = addCard(singleDeck, fileLine);
    }
    inFile.close();  //close file
    
    ////////////////////////////////////////////////////////////
    
    int numDecks = startMenu();  //allows user to choose number of decks to play with
    vector<cardNode> allCards;   //create vector of all cards in play (size = 52 * numDecks)
    
    for(int i = 0; i < numDecks; i++){   //loop through for number of decks chosen to play with
        
        for(int j = 0; j < singleDeck.size(); j++){  //loop through each card in a single deck
            
            allCards.push_back(singleDeck[j]);  //add cards from single deck to all cards vector
        }
    }
    
    BlackJackRound game = BlackJackRound();  //initializes game
    game.shuffleDeck(numDecks, singleDeck);  //creates and shuffles deck
    
    ////////////////////////////////////////////////////////////

    bool run = true;     //boolean to keep running program
    int choice;          //integer of choice of the player
    while(run == true){
        
        choice = game.gameMenu();  //let player choose from menu
        
        if(choice == 0){           //player chooses to end game
            run = false;
            cout << "Thank you for playing!" << endl;
        }
        else if(choice == 1){      //player chooses to play a round of blackjack
            game.startRound();     //starts a round
            game.play();           //allows the player to play the round
        }
    }
    
    return 0;
}

int startMenu()   //menu to start the program
{
    cout << "Lets Play Blackjack!"<< endl;
    cout << "How many decks are you playing with?" << endl;
    
    string choiceStr;
    int choice;
    
    getline(cin, choiceStr);
    choice = atoi(choiceStr.c_str());
    
    return choice;     //returns choce of the player of how many decks to play with
}

vector<cardNode> addCard(vector<cardNode> cardList, string fullLine)
{
    //all of these lines simply take a line from the text file of possible cards and assigns the values
    //in the line as values for individual card nodes. These nodes are added to the vector of possible cards,
    //which is returned to the main method.
    
    string str1 = fullLine;
    string str2;
    string str3 = "spades";
    string str4 = "clubs";
    string str5 = "hearts";
    string str6 = "diamonds";
    
    int comma = str1.find(',');
    str2 = str1.substr(comma+1);
    str1 = str1.substr(0, comma);
    
    int value = atoi(str2.c_str());
    
    cardNode node1;
    cardNode node2;
    cardNode node3;
    cardNode node4;
    
    node1.face = str1;
    node2.face = str1;
    node3.face = str1;
    node4.face = str1;
    
    node1.value = value;
    node2.value = value;
    node3.value = value;
    node4.value = value;
    
    node1.suit = str3;
    node2.suit = str4;
    node3.suit = str5;
    node4.suit = str6;
    
    
    if(str1 == "ace"){
        node1.isAce = true;
        node2.isAce = true;
        node3.isAce = true;
        node4.isAce = true;
    }

    
    cardList.push_back(node1);
    cardList.push_back(node2);
    cardList.push_back(node3);
    cardList.push_back(node4);
    
    return cardList;
}

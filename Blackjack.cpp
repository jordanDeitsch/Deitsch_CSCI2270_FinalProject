//
//  Blackjack.cpp
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

/*
 
 Function Prototype:  BlackJackRound::BlackJackRound()
 
 Function Description:  Constructor for the blackjack game, this function will 
 create the game with set initial conditions of zero winnings, no bet, and a count of zero
 
 Example:  BlackJackRound game = BlackJackRound();
 
 Pre-condition: No pre-conditions needed, as this only constructs the framework for the game
 Post-condition: An instance of the game will becreated to play through the main method
 
 */

BlackJackRound::BlackJackRound()
{
    bet = 0;        //initialize all variables at start of game
    winnings = 0;
    count = 0;
    playerHand = NULL;
    dealerHand = NULL;
}

BlackJackRound::~BlackJackRound()
{
    //destructor
}

/*
 
 Function Prototype:  void BlackJackRound::shuffleDeck(int, std::vector<cardNode>)
 
 Function Description: This function will take the intial deck of all 52 cards and "shuffle" them into a deck of randomly
 assorted cards. The number of cards in the final deck are equal to the number of single decks used in play times 52. This deck will be 
 reshuffled at the end of a game or when the deck reaches a certain small enough size.
 
 Example: game.shuffleDeck(3, singleDeck)
 
 Pre-condition: Must have a positive integer to tell number of decks used and a vector of the original 52 cards.
 Post-condition: A deck will be full shufled and ready for use in the rest of the blackjack game
 
 */
void BlackJackRound::shuffleDeck(int deckNum, std::vector<cardNode> singleDeck)
{
    originalDeck = singleDeck;       //save single deck to the class
    numDecks = deckNum;              //save number of decks being used, for use in reshuffling
    std::vector<cardNode> tempDeck;  //temporary deck to choose from when shuffling. This deck is composed of all possible cards in order
    deck = NULL;                     //initializing the deck before shuffling
    
    for(int i = 0; i < deckNum; i++){                //repeat the number of decks that are to be used
        for(int j = 0; j < singleDeck.size(); j++){  //add next card to the temporary deck
            tempDeck.push_back(singleDeck[j]);
        }
    }
    
    while(tempDeck.size() > 0){  //while still cards to choose from in the shuffling
        
        srand (time(NULL));                         //choose random card out of what is left in a single possible deck
        int random = rand()%tempDeck.size();
        
        cardNode* newCard = new cardNode;           //empty card node
        newCard->face = tempDeck[random].face;      //values of new card to be added to top of deck (think of it as a stack)
        newCard->suit = tempDeck[random].suit;
        newCard->value = tempDeck[random].value;
        newCard->next = deck;                       //points to next card in deck, the previous head
        tempDeck.erase(tempDeck.begin() + random);  //deltes from the temp deck the card chosen to be put on full deck
        
        deck = newCard;                             //set pointer to top of deck as the new card
        
    }
}

/*
 
 Function Prototype:  void BlackJackRound::printPlayerHand()
 
 Function Description: This function will print out the hand of the player. Each hand is stored as a linked
 list, so the function starts at the head of the list and moves through each card node, printing out the face.
 
 Example:  game.printPlayerHand();
 
 Pre-condition:  The linked list head must exist, otherwise nothing will be printed.
 Post-condition: The terminal will output the entirety of the player's hand, as well as the cumulative value
 
 */
void BlackJackRound::printPlayerHand()
{
    cardNode* x = new cardNode;      //empty card node to be used to move through linked list of player hand
    x = playerHand;                  //start off at the top of the player's hand
    int total = 0;                   //initialize the player's hand value as zero
    
    while(x != NULL){
        std::cout << x->face << " " << std::endl;   //print out the card in the player's hand
        total = total + x->value;                   //add the current card being viewed to the total
        x = x->next;                                //move on to next card in the linked list
    }
    std::cout << "Total value of cards: " << total << std::endl;  //print out the total value of the player's hand
}

/*
 
 Function Prototype:  void BlackJackRound::printDealerHand()
 
 Function Description: This function will print out the hand of the dealer. Each hand is stored as a linked
 list, so the function starts at the head of the list and moves through each card node, printing out the face.
 
 Example:  game.printDealerHand();
 
 Pre-condition:  The linked list head must exist, otherwise nothing will be printed.
 Post-condition: The terminal will output the entirety of the dealer's hand
 
 */
void BlackJackRound::printDealerHand()
{
    cardNode* x = new cardNode;  //empty card to moce through linked list
    x = dealerHand;              //start at the top of the dealer's hand
    
    while(x != NULL){
        std::cout << x->face << std::endl; //print the dealer's current card being viewed
        x = x->next;                       //move to next card in dealer's hand
    }
}

/*
 
 Function Prototype:  void BlackJackRound::dealPlayer()
 
 Function Description:  This function will deal a card to the player from the top of the deck.
 
 Example:  game.dealPlayer()
 
 Pre-condition:  The head of the player hand linked list must exist, as must the head of the deck linked list.
 Post-condition: The deck will lose its top card, with appropriate pointer reassignment, 
 while the player will recieve the top card.
 
 */
void BlackJackRound::dealPlayer()
{
    cardNode* temp = deck;    //card drawn from the top of the deck
    deck = deck->next;        //top of the deck is now at the next card down
    temp->next = playerHand;  //card drawn is now pointing to the current top of the player hand
    playerHand = temp;        //top of player hand is now the new card dealt
    cardCount(*temp);         //adjust the count of the game for the card that is dealt
}

/*
 
 Function Prototype:  void BlackJackRound::dealDealer()
 
 Function Description:  This function will deal a card to the dealer from the top of the deck.
 
 Example:  game.dealDealer()
 
 Pre-condition:  The head of the dealer hand linked list must exist, as must the head of the deck linked list.
 Post-condition: The deck will lose its top card, with appropriate pointer reassignment,
 while the delaer will recieve the top card.
 
 */
void BlackJackRound::dealDealer()
{
    cardNode* temp = deck;    //card drawn from the top of the deck
    deck = deck->next;        //top of the deck is now at the next card down
    temp->next = dealerHand;  //card drawn is now pointing to the current top of the dealer hand
    dealerHand = temp;        //top of dealer hand is now the new card dealt
    cardCount(*temp);         //adjust the count of the game for the card that is dealt
}

/*
 
 Function Prototype:  void BlackJackRound::initializeHands()
 
 Function Description:  This simple function will initialize the head of each player and dealer linked lists. This function
 essentially discards the hands from the previous round of the game.
 
 Example: game.initializeHands()
 
 Pre-condition: The dealer and player heads must exist for theor respective linked lists
 Post-condition: The player and dealer heads will be set ot NULL so as to start a new round
 
 */
void BlackJackRound::initializeHands()
{
    dealerHand = NULL;   //set the player and delaer hands as empty, used at beginning of each round
    playerHand = NULL;
}

/*
 
 Function Prototype:  int BlackJackRound::gameMenu()
 
 Function Description:  This function allows the user to choose their option within the game. 
 The user can choose between playing a round (and placing a bet), checking their current winnings, 
 checking the current count of the deck, and exiting the game. This function will also check to
 reshuffle the deck if it has reached a low enough number of cards left.
 
 Example:  int j = game.gameMenu()
 
 Pre-condition: This function requires a game to have been initialized
 Post-condition: This function will return an integer to the main function depending on the choice the user makes
 
 */
int BlackJackRound::gameMenu()
{
    cardNode* x = deck; //emtpy card to move through linked list
    int numCards = 0;   //check for number of cards left in the deck
    while(x != NULL){   //count cards left in deck
        numCards++;
        x = x->next;
    }
    if(numCards < 15){   //deck must be reshuffled if there is a small number of cards left. I chose 15 as the number needed
        std::cout << "Less then 15 cards in deck. Reshuffling." << std::endl;  //tell user that deck is being resuffled
        shuffleDeck(numDecks, originalDeck);                                   //shuffle the deck with appropriate number of cards
        count = 0;       //reset the count to zero every time the deck is shuffled
    }
    
    std::string choice;  //string for the choice of the user in the following menu
    
    std::cout << "Choose option from below: " << std::endl;   //menu to choose what to du during the game
    std::cout << "1. Place bet" << std::endl;
    std::cout << "2. View current winnings" << std::endl;
    std::cout << "3. View current card count" << std::endl;
    std::cout << "4. End game" << std::endl;
    
    getline(std::cin, choice);  //get choice from the user

    if(choice == "1"){          //if user chooses to place a bet and play a round
        
        std::cout << "Enter value of current bet: " << std::endl;  //code to get the bet from the input
        std::string betStr;             //string of the user's bet
        getline(std::cin, betStr);      //get string from input
        bet = atoi(betStr.c_str());     //convert string to integer bet
        return 1;                       //return 1 to the main function, telling the choice of user to play
    }
    else if(choice == "2"){     //user want to view their current winnings in the game
        std::cout << "Your current winnings are: " << winnings << std::endl;
    }
    else if(choice == "3"){     //user wants to view the current count of the cards in the game
        std::cout << "The current count is: " << count << std::endl;
    }
    else{   //user ends game
        std::cout << "Your final winnings are: " << winnings << std::endl;  //display final winnings before exiting game
        return 0;  //returns 0 to tell main function to exit game
    }
    
    return -1;  //tells main function to redisplay the game choice menu
}

/*
 
 Function Prototype:  void BlackJackRound::startRound()
 
 Function Description:  This function is central to the playing of the game, as it will start a round of blackjack
 by dealing two cards (in alternating order) to the player and dealer. The function also checks for blackjack, as most
 casinos define blackjack as happening only on the first two cards, not any natural 21.
 
 Example:  game.startRound();
 
 Pre-condition: The function can only be run if there has already been a blackjack game initialized
 Post-condition: The function will result in a dealer hand and player hand initialized with two cards each.
 The function will also output to the terminal the cards dealt tot the player and the dealer's face up card.
 
 */
void BlackJackRound::startRound()
{
    initializeHands();  //set player and dealer hand to zero
    
    dealPlayer();       //deal two cards each to the player and dealer, alternating like in a real game
    dealDealer();
    dealPlayer();
    dealDealer();
    
    std::cout << "Your hand: " << std::endl;  //print out the players full hand
    printPlayerHand();

    std::cout << "Dealer face-up card: ";     //print out only the dealer's top card, like in a real game
    std::cout << dealerHand->face << std::endl;
    
    cardNode* x = new cardNode;  //empty card to move through linked list
    x = playerHand;              //start off at the top pf the player's hand
    int total = 0;               //set player's hand value to zero to check for initial blackjack
    
    while(x != NULL){            //lopp to check value of initial hand for blackjack
        total = total + x->value;
        x = x->next;
    }
    
    blackjack = false;      //boolean for blackjack
    if(total == 21){        //if blackjack, set to true
        blackjack = true;
    }
}

/*
 
 Function Prototype:  void BlackJackRound::play()
 
 Function Description:  This functio is the heart of the game. It wil allow the player to play through his hand until he either desires
 to stay or 21 is reached or exceeded. The method then checks the player's hand and the dealer's to determine a winner of that hand,
 and the amount either won or lost.
 
 Example:  game.play();
 
 Pre-condition: The method requires user input during the method, where the user can choose whether to hit or stay in his hand.
 Post-condition: The method will end with a winner being determined, changing the winnnings variable to reflect the impact of the 
 bet and whether the player won or lost.
 
 */
void BlackJackRound::play()
{
    bool playing = true;       //boolean to check for if the player still wants to play in that round
    bool bust = false;         //boolean to check of player has busted in that round
    int playerCount = 0;       //initialize player's hand value to zero
    std::string playerChoice;  //string of the player's choice to hit or stay
    
    while(playing == true && bust == false){  //only keep looping of the player wants to play and hasn't busted
        
        playerCount = checkPlayerHand();      //find and set the player's current hand value
        
        if(playerCount > 21){                 //check for the player busting by being over 21
            bust = true;
        }
        else if(playerCount == 21){           //stop playing if the player is already at 21
            playing = false;
        }
        else{
            //menu to check if the player wants to hit or stay on ther hand
            std::cout << "Your current hand has a value of: " << playerCount << std::endl;
            std::cout << "Would you like to hit or stay? " << std::endl;
            std::cout << "1. Hit" << std::endl;
            std::cout << "2. Stay" << std::endl;
            getline(std::cin, playerChoice);
            
            if(playerChoice == "1"){  //player wants a card
                dealPlayer();         //deal player a card
                std::cout << "You have been dealt: " << playerHand->value << std::endl;
            }
            else{
                playing = false;     //player chooses to end hand
            }
        }
    }
    
    bool dealerBlackJack = false;         //initilize dealer as not having blackjack
    int dealerCount = checkDealerHand();  //check dealer's hand
    if(dealerCount == -1){                //if blackjack, set it as true
        dealerBlackJack = true;
        dealerCount = 21;                 //set the hand value as 21
    }
    
    std::cout << "The dealer's full hand: " << std::endl;  //print out the dealer's final hand
    printDealerHand();
    
    std::cout << "Your final hand value is: " << playerCount << std::endl;    //print out your final hand value
    std::cout << "Dealer final hand value is: " << dealerCount << std::endl;  //print out dealer's final hand value
    
    //all different possibilities of the round with appropriate effect on the bet
    if(playerCount > 21){
        //bust, lose regardless of dealer hand
        bet = -1 * bet;
        std::cout << "You have lost this hand." << std::endl;
    }
    else{
        if(blackjack == true && dealerBlackJack == true){
            //push, both blackjack
            bet = 0;  //lose all of bet
            std::cout << "You have tied this hand." << std::endl;
        }
        else if(blackjack == true){
            //you have blackjack and the dealer does not
            bet = bet * 1.5;  //win 3:2 odds, or 1.5 times your bet
            std::cout << "You have blackjack!" << std::endl;
        }
        else if(dealerBlackJack == true){
            //player loses, dealer had blackjack
            bet = -1 * bet;  //lose all of bet
            std::cout << "You have lost this hand." << std::endl;
        }
        else if(dealerCount > 21 || playerCount > dealerCount){
            //player wins original bet, so bet is unchanged
            std::cout << "You have won this hand!" << std::endl;
        }
        else{
            //player loses
            bet = -1 * bet;  //lose all of bet
            std::cout << "You have lost this hand." << std::endl;
            
        }
    }
    
    winnings = winnings + bet;  //adjust final winnings by adding result of bet (bet can be negative if player lost)
}

/*
 
 Function Prototype:  int BlackJackRound::checkPlayerHand();
 
 Function Description: This function checks the hand of the player for being over or under 21. It also contains functionality
 to account for aces being worth either 1 or 11 at the player's choice.
 
 Example:  int playerHand = checkPlayerHand();
 
 Pre-condition: The function requires a player hand to already be created, with cards
 Post-condition: The function returns the integer value of the player's hand, and potentially alters the value of
 the ace in the player's hand.
 
 */
int BlackJackRound::checkPlayerHand()
{
    //return value of hand
    
    cardNode* x = new cardNode;  //empty node to go through linked list
    x = playerHand;              //start at the top of the player hand
    int total = 0;               //initialize player hand value as zero
    bool aceInPlay = false;      //boolean to check for if ace is in play
    std::string aceChoice;       //string for user to choose whether ace is 1 or 11 points
    
    while(x != NULL){            //loop through the linked list to check for aces in the player's hand
        
        if(x->isAce == true ){   //check for the card being viewed as an ace
            aceInPlay = true;
        }
        total = total + x->value;  //update total of the hand
        x = x->next;
    }
    
    if(aceInPlay == false){        //if ace not in hand, simply return the total
        return total;
    }
    else{
        x = playerHand;            //once again, go through player hand to find the ace
        while(x->isAce != true){
            x = x->next;
        }
        //conditionals for what can be done with the ace
        if(x->value == 11 && total > 21 && total < 32){  //ace must be changed to a 1 in this range
            x->value = 1;        //change ace value to a 1
            total = total - 10;  //remove ten from the total as ace is now a 1, not an 11
        }
        else if(x->value == 11 && total >= 32){  //does not matter if ace is changed to 1, still a bust
            return total;                        //simply return the total
        }
        else if(x->value == 1 && total < 12){  //the option to make ace an 11 or 1 is available
            //menu to choose the value of the ace
            std::cout << "Choose value for your ace (currently 1), with a current card total of: " << total << std::endl;
            std::cout << "1. Ace = 1" << std::endl;
            std::cout << "2. Ace = 11" << std::endl;
            getline(std::cin, aceChoice);
            
            if(aceChoice == "1"){
                x->value = 1;        //change the ace value to a 1;
            }
            else{
                x->value = 11;       //changed to a value of 11
                total = total + 10;  //update total
            }

        }
        
        return total;  //return the total of the player's hand
    }
}

/*
 
 Function Prototype:  int BlackJackRound::checkDealerHand();
 
 Function Description: This function checks the initial value of the dealer hand, then plays through the dealer's hand in accordance
 with the rules of blackjack. These rules are to hit on anything less than a 17 and stay on anything above.
 
 Example:  int dealerHand = checkDealerHand();
 
 Pre-condition: The function requires a dealer hand to already be created, with cards
 Post-condition: The function returns the integer value of the dealer's hand
 
 */
int BlackJackRound::checkDealerHand()
{
    //returns the value of the dealer's hand, with value of -1 for blackjack
    
    cardNode* x = new cardNode;  //empty card to go through linked list
    x = dealerHand;              //start at the top of the dealer's hand
    int total = 0;               //initialize dealer's hand to zero
    
    while(x != NULL){            //loop to go through dealer's hand and count totals
        total = total + x->value;
        x = x->next;
    }
    
    if(total == 21){
        return -1;
    }
    bool end = false;   //boolean to check for end condition of dealer's turn
    while(end == false){
        
        if(total > 17){  //dealer stays above a 17
            end = true;
            return total;
        }
        else{                                   //dealer must hit anything below or equal to a 17
            dealDealer();                       //deal card to the dealer
            total = total + dealerHand->value;  //update dealer total
        }
    }
    return total;  //return the dealer's hand value
}

/*
 
 Function Prototype:  void BlackJackRound::cardCount(cardNode);
 
 Function Description: This function takes a card and will adjust the count of the deck based on this card's value. The current
 counting system implemented in this system is the High-Low system, the most simple.
 
 Example:  cardCount(newCard);
 
 Pre-condition: This function requires a card to be passed into the function, or else it will not work
 Post-condition:  This function will not return a value, but will alter the count of the deck based on the card passed in
 
 */
void BlackJackRound::cardCount(cardNode newCard)
{
    //using traditional high-low system of card counting
    
    if(newCard.value > 1 && newCard.value < 7){          //add +1 for 2,3,4,5,6
        count ++;
    }
    else if(newCard.value == 1 || newCard.value == 10){  //subtract 1 for A,10,J,Q,K
        count --;
    }
}
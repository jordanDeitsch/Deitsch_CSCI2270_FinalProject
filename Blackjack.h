//
//  Blackjack.h
//  BlackJack
//
//  Created by Jordan Deitsch on 4/16/15.
//  Copyright (c) 2015 Jordan Deitsch. All rights reserved.
//

#ifndef __BlackJack__Blackjack__
#define __BlackJack__Blackjack__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cardNode{
    
    int value;
    bool isAce;
    std::string face;
    std::string suit;
    cardNode* next;
};


class BlackJackRound
{
public:
    BlackJackRound();
    virtual ~BlackJackRound();
    
    void shuffleDeck(int deckNum, std::vector<cardNode> singleDeck);
    void printPlayerHand();
    void printDealerHand();
    void dealPlayer();
    void dealDealer();
    void initializeHands();
    void startRound();
    void cardCount(cardNode newCard);
    void play();
    int checkPlayerHand();
    int checkDealerHand();
    int gameMenu();
    
protected:
private:
    int count;
    int bet;
    int winnings;
    int numDecks;
    bool blackjack;
    cardNode* playerHand;
    cardNode* dealerHand;
    cardNode* deck;
    std::vector<cardNode> originalDeck;

};

#endif /* defined(__BlackJack__Blackjack__) */

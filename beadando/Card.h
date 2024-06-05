#ifndef CARD_H
#define CARD_H

#include <string>

enum Suit{
    CLUBS = 0,
    DIAMONDS = 1,
    HEARTS = 2,
    SPADES = 3
};

enum Value{
    _2 = 2,
    _3,
    _4,
    _5,
    _6,
    _7,
    _8,
    _9,
    T,
    J,
    Q,
    K,
    A
};

class Card{
    private:
        Suit suit;
        Value value;

    public:
        Card(char v, char s);

        ~Card();
        
        void Print();

        Value getValue();
        int faceValue();
        Suit getSuit();
};

#endif
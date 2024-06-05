#include <iostream>
#include "Card.h"

Card::Card(char v, char s){
    switch (s)
    {
    case 'H':
        suit=HEARTS;
        break;
    
    case 'S':
        suit=SPADES;
        break;

    case 'C':
        suit=CLUBS;
        break;

    case 'D':
        suit=DIAMONDS;
        break;

    default:
        break;
    }

    switch (v)
    {
    case 'T':
        value=Value::T;
        break;

    case 'J':
        value=Value::J;
        break;

    case 'Q':
        value=Value::Q;
        break;

    case 'K':
        value=Value::K;
        break;

    case 'A':
        value=Value::A; 
        break;
    
    default:
        value=Value(v-'0');
    }

}

Card::~Card()
{
}

//overload kellene, de ehhhh, igy is jo
void Card::Print(){
    switch (value) {
        case Value::T:
            std::cout << 'T';
            break;
        case Value::J:
            std::cout << 'J';
            break;
        case Value::Q:
            std::cout << 'Q';
            break;
        case Value::K:
            std::cout << 'K';
            break;
        case Value::A:
            std::cout << 'A';
            break;
        default:
            std::cout << static_cast<int>(value);
            break;
    }

    switch (suit)
    {
    case Suit::HEARTS:
        std::cout<<'H';
        break;

    case Suit::SPADES:
        std::cout<<'S';
        break;

    case Suit::CLUBS:
        std::cout<<'C';
        break;

    case Suit::DIAMONDS:
        std::cout<<'D';
        break;

    default:
        break;
    }

    std::cout<<" ";

}

Suit Card::getSuit(){
    return suit;
}

Value Card::getValue(){
    return value;
}

int Card::faceValue(){
    return value;
}
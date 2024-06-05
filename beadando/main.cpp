#include <iostream>
#include "Hand.h"

int main(){

    std::vector<Hand> hands;
    std::string line;
    while(std::getline(std::cin, line)){
        std::vector<Card> cards;
        int i=0;
        while(i<(int)line.size()){
            cards.push_back(Card(line[i],line[i+1]));
            i+=3;
        }
        hands.push_back(Hand(cards));
    }
    for(Hand& h : hands){
        h.Print();
    }
    for(Hand& h : hands){
        h.evaluate_hand();
    }

    return 0;
}
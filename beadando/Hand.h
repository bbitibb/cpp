#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>

class Hand{
    private:
        std::vector<Card> cards;

    public:
        Hand(const std::vector<Card> &c);

        ~Hand();

        void Print();
        void sort_cards();
        void evaluate_hand();
        bool is_high_card();
        bool is_pair();
        bool is_two_pairs();
        bool is_drill();
        bool is_straight();
        bool is_flush();
        bool is_full_house();
        bool is_poker();
        bool is_straight_flush();
        bool is_royal_flush();
};



#endif
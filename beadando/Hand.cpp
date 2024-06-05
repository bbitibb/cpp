#include "Hand.h"
#include <algorithm>
#include <unordered_map>
#include <iostream>

Hand::Hand(const std::vector<Card>& c): cards(c){}

Hand::~Hand(){}

void Hand::Print()
{
    for(Card& card : cards){
        card.Card::Print();
    }
    std::cout<<std::endl;
}

void Hand::sort_cards()
{
    std::sort(cards.begin(), cards.end(), [](Card& a, Card& b)
    {
        return a.faceValue() < b.faceValue();
    }
    );
}

void Hand::evaluate_hand(){
    if(is_royal_flush()){ std::cout<<"Royal flush"<<std::endl; return;}
    if(is_straight_flush()){ std::cout<<"Straight flush"<<std::endl; return;}
    if(is_poker()){ std::cout<<"Four of a kind"<<std::endl; return;}
    if(is_full_house()){ std::cout<<"Full house"<<std::endl; return;}
    if(is_flush()){ std::cout<<"Flush"<<std::endl; return;}
    if(is_straight()){ std::cout<<"Straight"<<std::endl; return;}
    if(is_drill()){ std::cout<<"Three of a kind"<<std::endl; return;}
    if(is_two_pairs()){ std::cout<<"Two pairs"<<std::endl; return;}
    if(is_pair()){ std::cout<<"One pair"<<std::endl; return;}
    if(is_high_card()){ std::cout<<"High card"<<std::endl; return;}
}

bool Hand::is_high_card(){
    return !(is_pair() || is_two_pairs() || is_drill() || is_straight() || is_flush() || is_full_house() || is_poker() || is_straight_flush() || is_royal_flush());
}

bool Hand::is_pair(){
    std::unordered_map<char, int> count;
    for(Card& card : cards){
        count[card.getValue()]++;
    }
    
    for(int i=0; i<(int)count.size(); ++i){
        if(count[i]==2) return true;
    }

    return false;
}

bool Hand::is_two_pairs(){
    std::unordered_map<char, int> count;
    for(Card& card : cards){
        count[card.getValue()]++;
    }
    return count.size()==3;
}

bool Hand::is_drill(){
    std::unordered_map<char, int> count;
    for (Card& card : cards) {
        count[card.getValue()]++;
    }
    for(int i=0; i<(int)count.size(); ++i){
        if(count[i]==3) return true;
    }
    return false;
}

bool Hand::is_straight(){
    sort_cards();
    
    //na, ez ilyen
    if(cards[0].getValue()==_2 && cards[1].getValue()==_3 && cards[2].getValue()==_4 && cards[3].getValue()==_5 && cards[4].getValue()==A) return true;
    for(int i=0; i<(int)cards.size()-1; i++){
        if(cards[i].faceValue()!=cards[i+1].faceValue()-1){
            return false;
        }
    }
    return true;
}

bool Hand::is_flush(){
    for(int i=0; i<(int)cards.size()-1; ++i){
        if(cards[i].getSuit()!=cards[i+1].getSuit()) return false;
    }
        return true;
}

bool Hand::is_full_house(){
    return is_drill() && is_pair();
}

bool Hand::is_poker(){
    std::unordered_map<char, int> count;
    for(Card& card : cards){
        count[card.getValue()]++;
    }
    
    for(int i=0; i<(int)count.size(); ++i){
        if(count[i]==4) return true;
    }

    return false;
}

bool Hand::is_straight_flush(){
    return is_straight() && is_flush();
}

bool Hand::is_royal_flush(){
    sort_cards();
    return is_straight_flush() && cards[0].faceValue()==10;
}
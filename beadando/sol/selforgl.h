#ifndef SELFORGL_H
#define SELFORGL_H

#include <list>
#include <algorithm>
#include <iostream>
#include <unordered_map>

template<typename T>
class self_organizing_list{
    private:
    
    public:
        virtual ~self_organizing_list(){}
        virtual bool contains(const T &e) = 0;    
};


template<typename T>
class move_to_front : public self_organizing_list<T> {
    private:
        std::list<T> &container;
    public:
        move_to_front(std::list<T>& list) : container(list){
        }

        bool contains (const T &e) override {

            typename std::list<T>::iterator e_place = std::find(container.begin(), container.end(), e);


            if(e_place != container.end()){
            /*
            */
                T front_e = *e_place;
                container.erase(e_place);
                container.push_front(front_e);
            } 
            else{
                return false;
            }


            return true;
        }

};

template<typename T>
class frequency_list : public self_organizing_list<T>{
    private:
        std::list<T> &container;
        std::unordered_map<T, int> freq;

    public:
        frequency_list(std::list<T>& list) : container(list){
            for(const auto& item : container){
                freq[item]=0;
            }
        }

        bool contains (const T &e) override{
            for(typename std::list<T>::iterator it=container.begin(); it!=container.end(); ++it){    
                if(*it==e){
                    freq[e]++;
                    container.sort([this](const T& a, const T& b){
                        return freq[a]>freq[b];
                    });
                    return true;
                }          
            }
            return false;
        }

};
/*
*/


#endif
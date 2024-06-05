#ifndef MM_VEC_H
#define MM_VEC_H

#include <vector>
#include <limits>
#include <algorithm>

template<typename T>
class MinMaxVector{
    private:
        std::vector<T> vec;
        mutable T minim;
        mutable T maxim;
        mutable bool min_valid;
        mutable bool max_valid;
    public:
        MinMaxVector() : min_valid(false), max_valid(false){}

        MinMaxVector<T>& push_back(T e){
            vec.push_back(e);
            invalidate();
            return *this;
        }
        T min() const{
            if(!min_valid) calculate_min();
            return minim;
        }
        T max() const{
            if(!max_valid) calculate_max();
            return maxim;
        }
        T& at(size_t index) {
            invalidate();
            return vec.at(index);
        }
        const T& at(size_t index) const {
            return vec.at(index);
        }
        int size() const {
            return vec.size();
        }
        void calculate_min() const {
            if (!min_valid) {
                minim = *std::min_element(vec.begin(), vec.end());
                min_valid = true;
            }
        }
        void calculate_max() const {
            if (!max_valid) {
                maxim = *std::max_element(vec.begin(), vec.end());
                max_valid = true;
            }
        }
        T& operator[](size_t index){
            invalidate();
            return vec[index];
        }
        const T& operator[](size_t index)const{
            return vec[index];
        }
        void invalidate(){
            min_valid=false;
            max_valid=false;
        }

        using iterator = typename std::vector<T>::iterator;
        using const_iterator = typename std::vector<T>::const_iterator;

        iterator end(){
            invalidate();
            return vec.end();
        }
        const_iterator end() const{
            return vec.end();
        }
        iterator begin(){
            invalidate();
            return vec.begin();
        }
        const_iterator begin() const{
            return vec.begin();
        }


        
};

#endif
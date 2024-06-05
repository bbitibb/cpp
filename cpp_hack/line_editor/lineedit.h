#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <list>

template<typename Cont, typename CharT = typename Cont::value_type>
class line_editor{
    private:
        std::list<CharT> line;
        typename std::list<CharT>::iterator cursor;
        bool isInsert;
    
    public:
        line_editor() : cursor(line.end()), isInsert(false){}

        void press(CharT c){
            if(isInsert && cursor != line.end()){
                *cursor = c;
            }
            else{
                cursor = line.insert(cursor, c);
            }
            cursor++;
        }
        
        void home(){
            cursor = line.begin();
        }

        Cont enter(){
            Cont ret(line.begin(), line.end());
            line.clear();
            cursor = line.end();
            return ret;
        }

        void insert(){ isInsert = !isInsert; }

        void backspace(){
            cursor--;
            del();
        }

        void del(){
            cursor = line.erase(cursor);
        }
};


#endif
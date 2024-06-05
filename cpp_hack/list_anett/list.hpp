#ifndef LIST_HPP_INCLUDED
#define LIST_HPP_INCLUDED

#include "listexception.hpp"
#include <iostream>

/**
 * Kétszeresen láncolt lista implementáció
 */

template<class T>    /// Jelezzük, hogy ez egy "T" típusú template osztály lesz
class List
{
    private:
        /** 
		 * A szerkezetet felépítő belső osztály, kívülről nem látszik
         * A láncoláshoz minden elem tartalmaz egy a következőre, és egy az
         * előzőre mutató pointert, valamint magát az adatot.
         */
        struct Node
        {
            public:
                T data;           //Azt szeretnénk, hogy az eltárolt érték típusát megadhassuk
                Node *prev;       //Az előző elemre mutató pointer
                Node *next;       //A következő elemre mutató pointer

                Node(const T& data0) : data(data0), prev(NULL), next(NULL) {} //Konstruktor, ami beállít egy értéket, és lenullázza a mutatókat
                Node(const T& data0, Node* prev0,Node* next0)
                 : data(data0),prev(prev0),next(next0) {}   //Konstuktor, ami beállítja az értéket, és beállítja a mutatókat
        };
        Node *head;               //A lista elejére mutató pointer
        Node *tail;               //A lista végére mutató pointer
        Node *act;                //A lista aktuális elemére mutató pointer

    public:
        /**
         * Iterátor a listához - belső osztály
         * Ez az osztály teszi lehetővé a listánk bejárását
         */
        class Iterator {
            friend class List;      //A listának hozzá kell férnie az iterátor privát adattagjához (pl. keresés esetén)
            private:
                Node* current;      //Az aktuális listelem, amelyre az iterátor mutat
            public:
                Iterator();         //Iterátor üres konstruktor
                Iterator(Node*);    //Iterátor konstruktor, amit ráállítunk egy csomópontra

                bool operator!=(const Iterator& it) const;  //Iteratorok összehasonlítása (Különbözőek-e?)
                bool operator==(const Iterator& it) const;  //Iteratorok összehasonlítása (Egyenlőek-e?)

                // Klasszikus iterátoraritmetika. Vegyük észre, hogy nagyon hasonló a pointeréhez
                Iterator& operator++();     //Prefix következőre léptetés Iteratorokra
                Iterator operator++(int);   //Postfix következőre léptetés Iteratorokra
                Iterator& operator--();     //Prefix előzőre léptetés Iteratorokra
                Iterator operator--(int);   //Postfix előzőre léptetés Iteratorokra
                T& operator*() const;       //Dereferencia Iterátorokra
        }; // Iterator vége

        List();                         //Üres lista konstruktor
        List(const List<T> &list);      //Bevezetünk egy új úgynevezett másoló konstruktort
        List& operator= (const List<T> &list);   //Valamint egy értékadó operátort
        ~List();                        //Lista destruktor
        void clear();                   //A lista törléséhez egy segéd metódus

        /// Az aktuális (act) elemet befolyásoló metódusok
        void toFirst();           //Az első elemre ugrik
        void toLast();            //Az utolsó elemre ugrik
        void stepNext();          //Hátra lép egy elemet  (A lista vége felé halad)
        void stepPrev();          //Előre lép egy elemet  (A lista eleje felé halad)
        T getValue() const;       //Az aktuális elemben tárolt T típusú értéket adja vissza
        void setValue(T e);       //Az aktuális elem értékét módosítja
        Iterator find(const T& e);  //A keresett elemre mutató iterátort adja vissza

        /// A lista állapotát lekérdező metódusok
        bool isEmpty() const;     //Üres-e a lista?
        bool isLast() const;      //A lista aktuális mutatója az utolsó elemen áll-e?
        bool isFirst() const;     //A lista aktuális mutatója az első helyen áll-e?
        bool isActNull() const;   //A lista aktuális mutatója mutat-e elemre?

        /// Beszúró metódusok
        void insertFirst(T e);    //Új T típusú elem hozzáfűzése a lista elejéhez
        void insertLast(T e);     //Új T típusú elem hozzáfűzése a lista végéhez
        void insertBefore(T e);   //T típusú elem beszúrása az aktuális elem elé
        void insertAfter(T e);    //T típusú elem beszúrása az aktuális elem mögé

        /// Törlő metódusok
        void removeFirst();       //A lista első elemének törlése
        void removeLast();        //A lista utolsó elemének törlése
        void removeAct();         //Az aktuális elem törlése

        /// Iterátor függvények
        Iterator begin() const;
        Iterator end() const;
        Iterator last() const;

        /// Kiegészítő eljárások
        void print() const;     //kiíratás
        ///Iterátoros kiiratás (lásd fájl vége)
        //Nem részei a lista adatszerkezetnek, csak nekünk segítség!
};

/// ----- Most következnek a metódus implementációk ----- ///

    /// Először nézzük az Iterátor osztály metódusait
    //Az iterátor osztály paraméter nélküli konstruktora
    template<class T>
    List<T>::Iterator::Iterator() : current(NULL){}

    //Az iterátor osztály konstruktora
    //Az iterátor egy megadott csomópontra fog mutatni, így elérhetővé válnak a műveletek
    template<class T>
    List<T>::Iterator::Iterator(Node* current0) : current(current0){}

    //Összehasonlítás Iteratorokra
    //Két iterátor akkor és csak akkor lesz egyenlő, ha ugyanazon a listán haladnak és ugyanarra a csúcsra mutatnak.
    //Az alábbi műveletek mind két feltételt ellenőrzik
    //Különbözőek-e az iterátorok?
    template<class T>
    inline bool List<T>::Iterator::operator!=(const List<T>::Iterator& it) const
    {
        return current != it.current;
    }
    //Egyenlőek-e az iterátorok?
    template<class T>
    inline bool List<T>::Iterator::operator==(const List<T>::Iterator& it) const
    {
        return current == it.current;
    }

    //Prefix következőre léptetés Iteratorokra
    template<class T>
    typename List<T>::Iterator& List<T>::Iterator::operator++()
    {
        if (!current) {                   //Ha az iterátor nem NULL iterátor
            throw InvalidIterator();
        }
        current = current->next;          //Akkor a következő elemre lépünk a listában
        return *this;                     //Majd visszatérünk az erre az elemre mutató iterátorral
    }

    //Postfix következőre léptetés Iteratorokra
    template<class T>
    typename List<T>::Iterator List<T>::Iterator::operator++(int)
    {
        if (!current) {                   //Ha az iterátor nem NULL iterátor
            throw InvalidIterator();
        }
        Iterator it(current);             //Elmentjük egy másik iterátorba a jelenlegi helyzetünket a listában
        current = current->next;          //Léptetjük az eredeti iterátort
        return it;                        //Visszatérünk a léptetés előtti helyzettel
    }

    //Prefix előzőre léptetés Iteratorokra
    template<class T>
    typename List<T>::Iterator& List<T>::Iterator::operator--()
    {
        if (!current) {                   //Ha az iterátor nem NULL iterátor
            throw InvalidIterator();
        }
        current = current->prev;          //Akkor az előző elemre lépünk a listában
        return *this;                     //Majd visszatérünk az erre az elemre mutató iterátorral
    }

    //Postfix előzőre léptetés Iteratorokra
    template<class T>
    typename List<T>::Iterator List<T>::Iterator::operator--(int)
    {
        if (!current) {                   //Ha az iterátor nem NULL iterátor
            throw InvalidIterator();
        }
        Iterator it(current);             //Elmentjük egy másik iterátorba a jelenlegi helyzetünket a listában
        current = current->prev;          //Léptetjük az eredeti iterátort
        return it;                        //Visszatérünk a léptetés előtti helyzettel
    }

    //Dereferencia operátor iterátorra (visszaadja az iterátor által mutatott elem értékét)
    template<class T>
    T& List<T>::Iterator::operator*() const
    {
        if (!current) {                   //Ha az iterátor nem NULL iterátor
            throw InvalidIterator();
        }
        return current->data;             //Visszatérünk az aktuális elem értékével
    }


/// Jöhetnek a List osztály metódusai
//Alap konstruktor, üres listát hoz létre
template<class T>
List<T>::List()
{
    head = tail = act = NULL; //A mutatókat mind NULL-ra állítjuk
}

//Másoló konstruktor: Új lista létrehozása egy már meglévő alapján. (klónozás)
//A másoláshoz át kell tenni az elemeket, egy másik memóriaterületre
template<class T>
List<T>::List(const List<T> &list)
{
    head = tail = act = NULL; //A mutatókat mind NULL-ra állítjuk
    //Egy i pointer fut végig az elemeken, amíg a tail után ki nem fut a listából
    for(Node* i = list.head;i != NULL;i = i->next)
        insertLast(i->data);
}

//Értékadó operátor: Az eredeti lista elemeit cseréli le
template<class T>
List<T>& List<T>::operator=(const List<T>& list) {
    if(&list == this)          //Ha a kapott lista megegyezik az eredetivel, akkor készen vagyunk
    {
        return *this;
    }
    if(!isEmpty())            //Egyébként ki kell ürítenünk a már meglévő listánkat, ha nem üres
    {
        clear();
    }
    for(Node* i=list.head; i!=NULL; i=i->next)
    {
        insertLast(i->data);     //Sorba belemásoljuk az elemeket
    }
    return *this;
}

//Destructor
template<class T>
List<T>::~List()
{
    //while(!isEmpty())     //Amíg van elem a listában,
    //    removeLast();     //addig kiszedjük az utolsó elemet
    clear();                ///Miután implementáltuk a clear() eljárást, nyugodtan felhasználhatjuk itt
}

//A lista kiürítése
template<class T>
void List<T>::clear()
{
    if(isEmpty())        //Ha üres a lista akkor nincsen dolgunk
    {
        return;
    }
    for(Node* i=head; i!=NULL; /*A ciklus változó inkrementálása nem itt lesz*/)
    {
        Node* tmp = i;
        i = i->next;    //Itt inkrementálunk, mivel most még meg van a törlendő elem, rá tudunk lépni a rákövetkezőre
        delete tmp;
    }
    head = tail = NULL;
}

/// Az aktuális (act) elemet befolyásoló metódusok implementációi
//Az aktuális elemet az első lista elemre állítja
template<class T>
void List<T>::toFirst()
{
    act = head;         // Az aktuális mutasson az első elemre
}

//Az aktuális elemet az utolsó lista elemre állítja
template<class T>
void List<T>::toLast()
{
    act = tail;         // Az aktuálsi mutasson az utolsó elemre
}

//Az aktuális mutatót (ha nem NULL az értéke) egy elemmel hátrébb állítja
//Vegyük észre, hogy ez az eljárás NULL-á teheti az act-ot! (Ha act = tail volt)
template<class T>
void List<T>::stepNext()
{
    if(act)             // Ha az aktuális mutató érvényes elemre mutat
        act = act->next; // Akkor az aktuálist egyel hátrább léptetjük
}

//Az aktuális mutatót (ha nem NULL az értéke) egy elemmel előrébb állítja
//Vegyük észre, hogy ez az eljárás NULL-á teheti az act-ot! (Ha act = head volt)
template<class T>
void List<T>::stepPrev()
{
    if(act)             // Ha az aktuális mutató érvényes elemre mutat
        act = act->prev; // Akkor az aktuálist egyel előrébb léptetjük
}

//Visszaadja az aktuális elem értékét
template<class T>
T List<T>::getValue() const
{
    if(isEmpty())       // Ha üres a lista
        throw(UnderFlowException()); // Akkor egy UnderFlowException-t dobunk
    if(!act)            // Ha nem üres, mert nem dobtunk kivételt, de az act = NULL
        throw(ActNullException()); // Akkor egy ActNullException-t dobunk
    return act->data;   // Ha minden rendbe, mert nem volt kivétel, akkor visszadjuk az aktuális elem értékét
}

//Beállítjuk az aktuális elem értékét
template<class T>
void List<T>::setValue(T e)
{
    if(isEmpty())       // Ha üres a lista
        throw(UnderFlowException()); // Akkor egy UnderFlowException-t dobunk
    if(!act)            // Ha nem üres, mert nem dobtunk kivételt, de az act = NULL
        throw(ActNullException()); //Akkor egy ActNullExceptiont dobunk
    act->data = e;      // Ha minden rendben, akkor be tudjuk állítani az aktuális elem értékét
}


//Keresés a listában (Az adaton értelmezett == operátort használjuk)
template<class T>
typename List<T>::Iterator List<T>::find(const T& e)
{
    Node* p;
    for (p = head; p != NULL && !(p->data == e); p = p->next);
    return Iterator(p);
}

/// A lista állapotát lekérdező metódusok implementációi
//Megvizsgálja, hogy üres-e a lista (TRUE: ha üres, FALSE: ha nem üres)
template<class T>
bool List<T>::isEmpty() const
{
    return head == NULL;    //Visszaadjuk, hogy a head NULL-e, mert az csak akkor NULL, ha üres a lista.
}

//Megvizsgálja, hogy az aktuális elem-e az utolsó (TRUE: ha igen, FALSE: ha nem)
template<class T>
bool List<T>::isLast() const
{
    return act == tail;    //Ha a két mutató megegyezik, akkor az aktuális elem az utolsó
}

//Megvizsgálja, hogy az aktuális elem-e az első (TRUE: ha igen, FALSE: ha nem)
template<class T>
bool List<T>::isFirst() const
{
    return act == head;    //Ha a két mutató megyegyezik, akkor az aktuális elem az első
}

//Megvizsgáljuk, hogy a lista végén vagyunk-e (TRUE: ha igen, FALSE: ha nem)
template<class T>
bool List<T>::isActNull() const
{
    return act == NULL;    //Visszaadjuk, hogy az act == NULL igaz-e
}

/// Beszúró metódusok implementálása
//A lista elejére szúrja be a paraméterben kapott új értéket
template<class T>
void List<T>::insertFirst(T e)
{
    Node* p = new Node(e);  //Létrehozzuk az új elemet,

    if(isEmpty())           //Ha üres a lista...
    {
        act = head = tail = p; //...akkor ez az új elem lesz az első, utolsó, és aktuális
    }
    else // Ha már van elem a listában
    {
        p->next = head;     //Az új elem rákövetkezője lesz a régi, első elem
        head->prev = p;     //A régi, első elem megelőzője lesz az új elem
        act = head = p;     //Az új elem lesz az első, és az aktuális is
    }
}

//A lista végére szúrja be a paraméterben kapott új értéket
template<class T>
void List<T>::insertLast(T e)
{
    Node* p = new Node(e);  //Létrehozzuk az új elemet

    if(isEmpty())           //Ha a lista üres...
    {
        act = head = tail = p; //...akkor ez az új elem lesz az első, utolsó, és aktuális
    }
    else                    //Ha már van elem a listában
    {
        p->prev = tail;     //Az új elem megelőzője lesz a régi, utolsó elem
        tail->next = p;     //A régi, utolsó elem rákövetkezője lesz az új elem
        act = tail = p;     //Az új elem lesz az utolsó, és az aktuális is
    }
}

//Az aktuális elem elé szúrja be a paraméterben kapott új értéket
template<class T>
void List<T>::insertBefore(T e)
{
    if(!act)                //Ha nincs aktuális elem
        throw(ActNullException());      //Akkor ActNullException-t dobunk
    if(isFirst())           //Ha az aktuális az első, akkor az elészúrás ua. mint az első helyre beszúrás
        insertFirst(e);     //Tehát szúrjuk simán az elejére
    else                    //Ha nem az act az első
    {
        Node* p = new Node(e,act->prev,act); //Létrehozzuk az új elemet, és egyben beállítjuk a mutatóit az act-ra, és az act megelőzőjére
        act->prev->next = p; //act megelőzőjének rákövetkezője innentől az új elem
        act->prev = p;      //Az act megelőzője is az új elem
        act = p;            //Mivel az átláncolás megvan, innetől az új elem az aktuális
    }
}

//Az aktuális elem után szúrja be a paraméterben kapott új értéket
template<class T>
void List<T>::insertAfter(T e)
{
    if(!act)                //Ha nincs aktuális elem
        throw(ActNullException());      //Akkor ActNullException-t dobunk
    if(isLast())            //Ha az aktuális az utolsó, akkor az utána szúrás ua. mint az utolsó helyre szúrás
        insertLast(e);      //Tehát szúrjuk simán a végére
    else                    //Ha nem az act az utolsó
    {
        Node* p = new Node(e,act,act->next); //Létrehozzuk az új elemet, és beállítjuk a mutatóit az act-ra, és az act rákövetkezőjére
        act->next->prev = p; //Az act rákövetkezőjének megelőzője innentől az új elem
        act->next = p;      //Az act rákövetkezője is az új elem
        act = p;            //Mivel az átláncolás megvan, innentől az új elem az aktuális
    }
}

/// Törlő metódusok implementálása
//Törli a lista első elemét
template<class T>
void List<T>::removeFirst()
{
    if(isEmpty())               //Ha üres a lista, akkor nem lehet törölni
        throw(UnderFlowException());    //Tehát dobunk egy UnderFlowException-t
    if(head == tail)            //Ha csak 1 darab elem van a listában
    {
        delete head;            //Kitöröljük azt az egyet
        act = head = tail = NULL;       //Mivel a lista így kiürült, a mutatókat lenullázzuk
    }
    else                        //Ha több elem van
    {
        head = head->next;      //A head eggyel hátrébb kerül
        delete head->prev;      //Az első elemet töröljük
        head->prev = NULL;      //Majd a rá mutató mutatót lenullázzuk
        act = head;             //Az első lesz az aktuális elem
    }
}

//Törli a lista utolsó elemét
template<class T>
void List<T>::removeLast()
{
    if(isEmpty())               //Ha üres a lista, akkor nem lehet törölni
        throw(UnderFlowException());    //Tehát dobunk egy UnderFlowException-t
    if(head == tail)            //Ha csak 1 darab elem van a listában
    {
        delete tail;            //Kitöröljük azt az egyet
        act = head = tail = NULL;       //Mivel a lista így kiürült, a mutatókat lenullázzuk
    }
    else // Ha van több elem
    {
        tail = tail->prev;      //A tail eggyel előrébb kerül
        delete tail->next;      //Az utolsó elemet töröljük
        tail->next = NULL;      //Majd a rá mutató mutatót lenullázzuk
        act = tail;             //Az utolsó lesz az aktuális
    }
}

//Törli a lista aktuális elemét
template<class T>
void List<T>::removeAct()
{
    if(isEmpty())               //Ha üres a lista, nincs mit törölni
        throw(UnderFlowException());    //Dobunk egy UnderFlowException-t
    if(!act)                    //Ha nem üres, de az act NULL
        throw(ActNullException());      //Dobunk egy ActNullException-t
    if(isFirst())               //Ha az act az első
        removeFirst();          //Akkor simán töröljük az elsőt
    else if(isLast())           //Ha az act az utolsó
        removeLast();           //Akkor simán töröljük az utolsót
    else                        //Ha köztes elem
    {
        Node *p = act;          //Egy ideiglenes pointerrel rámutatunk az act-ra
        act = act->next;        //Az act-ot eggyel hátrébb toljuk (lehetne előre is, de mi most így valósítjuk meg a törlést)
        p->next->prev = p->prev; //A p(régi act) rákövetkezőjének megelőzője a törlendő elem megelőzője lesz lesz
        p->prev->next = p->next; // és a p megelőzőjének rákövetkezője a törlendő elem rákövetkezője lesz
        delete p;               //Ezek után kitöröljük a törlendő elemet
    }
}

/// Iterátor függvények implementálása
//Lista kezdetének lekérdezése
template<class T>
inline typename List<T>::Iterator List<T>::begin() const {
    return Iterator(head);
}

//Lista végének lekérdezése
//VIGYÁZAT! A visszaadott iterátort nem tudjuk már visszaléptetni!
template<class T>
inline typename List<T>::Iterator List<T>::end() const {
  return Iterator(NULL);
}

//Lista utolsó elemének lekérdezése
template<class T>
inline typename List<T>::Iterator List<T>::last() const {
  return Iterator(tail);
}

/// Kiegészítő eljárások implementálása
//Kiírja konzolra a lista tartalmát az elejéről a végéig haladva
template<class T>
void List<T>::print() const
{
    //Egy i pointer fut végig az elemeken, amíg a tail után ki nem fut a listából
    for(Node* i=head; i!=NULL; i=i->next)
        cout << i->data << ", ";   // és kiírja az aktuális elem értékét
    cout << endl;
}

//Iterátor segítségével írja ki konzolra a lista tartalmát az elejéről a végéig haladva
template<typename T>
void operator<<(ostream& out, const List<T>& list)
{
    typename List<T>::Iterator it;
    //Egy it iterátor fut végig az elemeken, a lista elejértől addig, amíg el nem érjük a lista végét
    for(it=list.begin(); it!=list.end(); it++)        //Implementáltuk a "!=" és "++" műveleteket; használhatjuk
        out << *it << " ";   // és kiírja az aktuális elem értékét
    out << endl;
}

#endif // LIST_HPP_INCLUDED


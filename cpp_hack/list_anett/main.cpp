#include "list.hpp"
#include <iostream>

int main() {

    try
    {
        List<int> list;
        cout << "--- Toltsuk fel a listat szamokkal 10-1-ig ---\n";
        for (int i=1; i<=10; ++i) {
            list.insertFirst(i);
        }
        cout << list;   // Készítettünk egy kiírató operátort a belső iterátor osztály segítségével (list.hpp fájl legvége)

        cout << "\nSzurjuk be a 0-t is a megfelelo helyre\n";
        list.insertLast(0);
        cout << list;

        cout << "\nToroljuk ki a 7-et\n";
        list.find(7);   // Új lista metódus! Az adott értékre állítja az aktuális mutatót
        list.removeAct();
        cout << list;

        cout << "\nKeressunk ra egy elemre es irassuk ki!\n";
        List<int>::Iterator it = list.find(6);
        cout << *it;

        cout << "\nIrassuk ki a kovetkezo elemet!\n";
        ++it;
        cout << *it;

        cout << "\nIrassuk ki a listat!\n";
        cout << list;

        cout << "\nIrjuk ki forditva a listat!\n";
        for (List<int>::Iterator it = list.last(); it != list.end(); --it) {
            cout << *it << ' ';
        }
        cout << endl;
    }
    catch(std::exception& e)
    {
        cout << "\n***HIBA tortent!*** " << e.what() << endl;
    }

    //A program vége
    cout << "\n\nA program befejezte a futasat!" << endl;

    return 0;
}

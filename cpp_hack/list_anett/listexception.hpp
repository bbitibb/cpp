#ifndef LISTEXCEPTION_HPP_INCLUDED
#define LISTEXCEPTION_HPP_INCLUDED

#include <exception>

using namespace std;

class UnderFlowException : public exception
{
    public:
        const char* what() const throw() { return "Alulcsordulas!"; }
};

class ActNullException : public exception
{
    public:
        const char* what() const throw() { return "Nincs aktualis elem kivalasztva!"; }
};

//Kiv�tel, ha nulliter�toron akarunk m�veletet v�gezni
class InvalidIterator : public exception
{
    public:
        const char* what() const throw() { return "Ervenytelen iterator!"; }
};

#endif // LISTEXCEPTION_HPP_INCLUDED

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

//Kivétel, ha nulliterátoron akarunk mûveletet végezni
class InvalidIterator : public exception
{
    public:
        const char* what() const throw() { return "Ervenytelen iterator!"; }
};

#endif // LISTEXCEPTION_HPP_INCLUDED

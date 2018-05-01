#ifndef DATE_HPP_INCLUDED
#define DATE_HPP_INCLUDED
#include <iostream>

class Date
{
    friend std::istream& operator>> (std::istream&, Date&);
    int d; //dd
    int m; //mm
    int y; //yyyy
public:
    Date(int d = 1, int m = 1, int y = 1990):d(d), m(m), y(y){};
    int getD();
    int getM();
    int getY();
    std::string ToString();
    bool isValid();
};

#endif // DATE_HPP_INCLUDED

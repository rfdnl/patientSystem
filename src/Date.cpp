#include "Date.hpp"
#include <iostream>
#include <sstream>
#include <string>

int Date::getD(){ return this->d; }

int Date::getM(){ return this->m; }

int Date::getY(){ return this->y; }

std::string Date::ToString(){
    std::stringstream ss;
    ss << this->d << "/" << this->m << "/" << this->y;
    return ss.str();
}

bool Date::isValid()
{
    if (this->d > 0 && this->d < 32 && this->m > 0 && this->m < 13 && this->y > 1800 && this->y < 2100)
        return true;
    else
    {
        std::cout << "Not a valid date.\n";
        return false;
    }
}

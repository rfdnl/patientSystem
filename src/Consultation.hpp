#ifndef CONSULTATION_HPP_INCLUDED
#define CONSULTATION_HPP_INCLUDED
#include "Date.hpp"

class Consultation{
    friend bool SortByName(const Consultation&, const Consultation&);
    Date date;
    std::string name;
    std::string ic;
    double fee;
public:
    Consultation(Date date=Date(), std::string name = "name", std::string ic="00000000000", double fee = 0.00)
    :date(date), name(name), ic(ic), fee(fee){}
    Date getDate();
    std::string getName() const;
    std::string getIc();
    double getFee();
    std::string toString();
    std::string toDetail();
};


#endif // CONSULTATION_HPP_INCLUDED

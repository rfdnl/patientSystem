#include "Consultation.hpp"
#include "Date.hpp"
#include <sstream>

using std::string;

Date Consultation::getDate(){
    return date;
}

string Consultation::getName() const{
    return name;
}

string Consultation::getIc(){
    return ic;
}

double Consultation::getFee(){
    return fee;
}

string Consultation::toString(){
    std::stringstream ss;
    ss << "c~" << this->date.ToString() << "~" <<
    name << "~" << this->ic << "~" << this->fee << "~\n";
    string s = ss.str();
    return s;
}

string Consultation::toDetail(){
    std::stringstream ss;
    ss << "\nName:\t\t" << name
    << "\nIC:\t\t" << ic
    <<"\nFee: RM\t\t" << fee;
    string s = ss.str();
    return s;
}

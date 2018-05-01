#include "Patient.hpp"
#include "Visit.hpp"
#include <sstream>
#include <string>
#include <vector>

std::string Patient::getName(){ return this->name;}
std::string Patient::getAddress(){return this->address;}
std::string Patient::getIc() {return this->ic;}
std::string Patient::getTelno(){return this->telno;}
Date Patient::getDOB(){return this->birth;}

std::string Patient::ToString(){
    std::stringstream ss;
    ss << "np~" << this->name << "~" << this->ic << "~" << this->telno << "~"
    << this->address << "~" << this->birth.ToString()<< "~";

    std::string s = ss.str();

    if (records.empty())
        return s;
    else{
        std::stringstream totalstream, recordstream;
        for(unsigned int i=0; i<records.size(); i++){
            recordstream << records[i].ToString() << "\n";
        }
        totalstream << s << "\n" << recordstream.str();
        std::string total = totalstream.str();
        return total;
    }
}

std::string Patient::ToDetail(){
    std::stringstream detailstream;
    detailstream << "\n\nName : \t\t\t\t" <<this->getName()
    << "\nIC: \t\t\t\t" <<this->getIc()
    << "\nAddress: \t\t\t" <<this->getAddress()
    << "\nPhone number: \t\t\t" <<this->getTelno()
    << "\nBirthday: \t\t\t" <<this->getDOB().ToString()
    << "\n\n";
    std::string detail = detailstream.str();

    if (records.empty())
        return detail;
    else{
        std::stringstream recordstream;
        for(unsigned int i=0; i<records.size();i++){
            recordstream << i+1 <<". "<< records[i].ToDetail() << "\n";
        }

        std::stringstream totalstream;
        totalstream << detail << recordstream.str();
        std::string total = totalstream.str();
        return total;
    }
}

void Patient::Add(Visit v){
    records.push_back(v);
}



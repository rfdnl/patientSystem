#include "PanelPatient.hpp"
#include <iostream>
#include <sstream>

std::string Panel::ToString(){
    std::stringstream ss;
    ss << "pp~" << getName() << "~" << getIc() << "~" << getTelno() << "~"
    << getAddress() << "~" << getDOB().ToString()<< "~"
    << getEmployerName() << "~" << getMaxSponsor() << "~";

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

std::string Panel::ToDetail(){
    std::stringstream detailstream;
    detailstream << "\n\nName : \t\t\t\t" << getName()
    << "\nIC: \t\t\t\t" << getIc()
    << "\nAddress: \t\t\t" << getAddress()
    << "\nPhone number: \t\t\t" << getTelno()
    << "\nBirthday: \t\t\t" << getDOB().ToString()
    << "\nEmployer's name: \t\t" <<  employerName
    << "\nMaximum amount sponsored: \t"<< maxSponsor
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

std::string Panel::getEmployerName(){
    return this->employerName;
}


double Panel::getMaxSponsor(){
    return this->maxSponsor;
}

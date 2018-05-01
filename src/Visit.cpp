#include "Visit.hpp"
#include "Date.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

Date Visit::getDate(){ return this->date; }

std::string Visit::getDiagnose() { return this->diagnose; }

std::string Visit::getPrescription() { return this->prescription; }

double Visit::getFee(){ return this->fee; }

std::string Visit::ToString(){
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << "+~" << this->date.ToString()
    << "~" << this->getDiagnose() << "~"+this->getPrescription() << "~"
    << this->getFee() << "~";
    std::string s = ss.str();
    return s;
}

std::string Visit::ToDetail(){
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << this->date.ToString()
    << " Diagnose: " << this->getDiagnose() << "\tPrescription: "+this->getPrescription() << "\tRM"
    << this->getFee() << "\n";
    std::string s = ss.str();
    return s;
}


#ifndef PANELPATIENT_HPP_INCLUDED
#define PANELPATIENT_HPP_INCLUDED
#include <iostream>
#include "Patient.hpp"
#include "Visit.hpp"

using std::string;
class Panel : public Patient
{
    string employerName;
    double maxSponsor;
public:
    Panel(string name = "Anonymous", string address = "Nowhere",
          string ic = "121212121212", string telno = "1234567890",
          Date birth = Date(), string employerName = "N/A",
          double maxSponsor = 0.00)
    :Patient(name, address, ic, telno, birth),
    employerName(employerName), maxSponsor(maxSponsor){}
    virtual ~Panel(){}

    virtual string ToString();
    virtual string ToDetail();
    string getEmployerName();
    double getMaxSponsor();
};

#endif // PANELPATIENT_HPP_INCLUDED

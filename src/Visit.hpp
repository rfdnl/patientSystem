#ifndef VISIT_HPP_INCLUDED
#define VISIT_HPP_INCLUDED
#include "Date.hpp"

using std::string;

class Visit
{
    Date date;
    string diagnose;
    string prescription;
    double fee;
public:
    Visit(Date date = Date(), string diagnose = "Sickness", string prescription = "Medicine", double fee = 0.00)
    :date(date), diagnose(diagnose), prescription(prescription), fee(fee){}
    string getDiagnose();
    string getPrescription();
    double getFee();
    Date getDate();
    string ToString();
    string ToDetail();
};

#endif // VISIT_HPP_INCLUDED

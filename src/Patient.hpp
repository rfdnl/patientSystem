#ifndef PATIENT_HPP_INCLUDED
#define PATIENT_HPP_INCLUDED
#include <iostream>
#include <vector>
#include "Date.hpp"
#include "Visit.hpp"

using std::string;

class Patient // Non-Panel Patient
{
    string name, address, ic, telno;
    Date birth;
protected:
    std::vector<Visit> records;
public:
    Patient(string name = "Anonymous", string address = "Nowhere", string ic = "121212121212", string telno = "1234567890", Date birth = Date())
    :name(name), address(address), ic(ic), telno(telno), birth(birth){
    }

    virtual ~Patient(){}

    string getName();
    string getAddress();
    string getIc();
    string getTelno();
    Date getDOB();

    virtual string ToString();
    virtual string ToDetail();
    void Add(Visit);
};

#endif // PATIENT_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

#include "Date.hpp"
#include "Visit.hpp"
#include "Patient.hpp"
#include "PanelPatient.hpp"
#include "Consultation.hpp"

using std::cout;
using std::cin;
using std::ostream;
using std::istream;
using std::string;
using std::getline;
using std::vector;

istream& operator>> (istream& is, Date& d){
    is >> d.d >> d.m >> d.y; // dd mm yyyy
    return is;
}

struct SortByName{
    bool operator()(const Consultation& a, const Consultation& b)
    { return a.getName() < b.getName(); }
};

bool SortByNaym(const Consultation& a, const Consultation& b)
{ return a.getName() < b.getName(); }

bool SetStr(string& str){
    cin.clear(); cin.sync();
    getline(cin, str);
    if (str.length() > 0) return true;
    else return false;
}

bool SetNum(string&str, unsigned int len){
    cin.clear(); cin.sync();
    getline(cin, str);

    if ((str.find_first_not_of("0123456789") == std::string::npos) && (str.length() == len))
        return true;
    else return false;
}

vector<string> Split(const string &s, char delim){
    vector<string> strings;
    std::stringstream ss(s);
    string str;
    while (getline(ss, str, delim)){
        strings.push_back(str);
    }
    return strings;
}

Date ToDate(string& str){
    vector<string> v = Split(str, '/');
    int d, m, y;
    std::istringstream ds(v[0]);
    ds >> d;
    std::istringstream ms(v[1]);
    ms >> m;
    std::istringstream ys(v[2]);
    ys >> y;

    Date date(d, m, y);
    return date;
}

double ToDouble(string& str){
    std::istringstream ds(str);
    double d;
    ds >> d;
    return d;
}

void SetBasicInfo(string& name, string& address, string& ic, string& telno, Date& birth){
    cout << "\nName: \n";
    while (!SetStr(name))
    { cout << "Name cannot be empty! Please try again: \n"; }

    cout << "\nAddress: \n";
    while (!SetStr(address))
    { cout << "Address cannot be empty! Please try again: \n"; }

    cout << "\nNRIC: (12-numbers, no spaces)\n";
    while (!SetNum(ic, 12))
    { cout << "\nIC should contain 12 numbers! Please try again: \n"; }

    cout << "\nPhone number: (10-numbers, no space)\n";
    while (!SetNum(telno, 10))
    {cout << "\nPhone number should contain 10 numbers! Please try again: \n";}

    cout << "\nDate of Birth: (dd mm yyyy)\n";
    do{
        cin.clear(); cin.sync();
        cin >> birth;
    }while(!birth.isValid());
}

string AddVisit(Patient& patient, vector<Consultation>& consults){ // visit record, daily consultation, receipt
    Date date;
    cout << "\nDate visited: (dd mm yyyy)\n";
    do{
        cin.clear(); cin.sync();
        cin >> date;
    }while(!date.isValid());

    cout << "\nDiagnose: \n";
    string diagnose;
    while (!SetStr(diagnose))
        cout << "Diagnose cannot be empty! Please try again: \n";

    cout << "\nPrescription: \n";
    string prescription;
    while (!SetStr(prescription))
        cout << "Prescription cannot be empty! Please try again: \n";

    cout << "\nFee:\n";
    cin.clear(); cin.sync();
    double fee;
    cin >> fee;

    Visit visit(date, diagnose, prescription, fee);
    patient.Add(visit);

    Consultation consult(date, patient.getName(), patient.getIc(), fee);
    consults.push_back(consult);

    vector<string> properties = Split(patient.ToString(),'~');

    //print receipt
    cout
    << "\n====================================\n\n\tRECEIPT:\n\n====================================\n"
    << "\nNAME: \t\t" << patient.getName()
    << "\nDIAGNOSE: \t" << visit.getDiagnose()
    << "\nPRESCRIPTION: \t" << visit.getPrescription();


    if(properties[0] == "pp"){
        cout << "\n\nAmount sponsored by " << properties[6] << ": \n\tRM " << properties[7];
        cout << "\nBill amount:\n\tRM " << visit.getFee();
        if (visit.getFee() > ToDouble(properties[7])){
            cout << "\nYou need to pay:\n\tRM " << visit.getFee() - ToDouble(properties[7]);
        }
    }
    else{
        cout << "\nBill amount:\n\tRM " << visit.getFee();
        cout << "\nYou need to pay:\n\tRM " << visit.getFee();
    }

    return "\n\n====================================\n";
}

bool SearchConsultation(vector<Consultation>& consults){
    vector<Consultation> consultSearch;

    Date date;
    cout << "\nConsultation list for date: (dd mm yyyy)\n";
    do{
        cin.clear(); cin.sync();
        cin >> date;
    }while(!date.isValid());

    cout << "\n\n\n\nDATE: " << date.ToString() << "\n";
    for(unsigned int i=0; i<consults.size();i++){
        if (date.ToString() == consults[i].getDate().ToString()){
            consultSearch.push_back(consults[i]);
        }
    }

    if (consultSearch.empty())
        cout << "\nNo consultation(s) found for this date!\n";
    else
    {
        double total = 0;
        std::sort(consultSearch.begin(), consultSearch.end(), SortByNaym);
        for(unsigned int i=0; i < consultSearch.size();i++){
            cout << i+1 << ")" << consults[i].toDetail() << "\n\n";
            total = total + consults[i].getFee();
        }
        cout << "\nTotal collection of this date: RM " << total << "\n";
    }

    return true;
}

bool NewPatient(vector<Patient*>& patients, vector<Consultation>& consults){
    int opr = 0;

    cout << "\nYou have selected 'Create a new Patient record'.\nPlease key in . . .\n"
    << "0. to Go Back,\n"
    << "1. to create a PANEL patient record,\n"
    << "2. to create a NON-PANEL patient record,\n"
    << "Else, to exit the program\n\n->";
    cin.clear(); cin.sync();
    cin >> opr;

    switch(opr){
    case 0:
        return true;
        break;
    case 1: // Panel
        {
            string name, address, employerName, ic, telno;
            double maxSponsor = 0;
            Date birth;

            SetBasicInfo(name, address, ic, telno, birth);

            cout << "\nEmployer's name:\n";
            while (!SetStr(employerName))
            { cout << "Employer's name cannot be empty! Please try again: \n";}

            cout << "\nMaximum amount sponsored by '" << employerName << "':\n";
            cin.clear(); cin.sync();
            cin >> maxSponsor;

            Panel* panelPtr = new Panel(name, address, ic, telno, birth, employerName, maxSponsor);

            cout << panelPtr->ToDetail();
            cout << "\nPatient created, what do you want to do with it?\n1. Add new visit record,\nElse. Proceed.\n->";
            int option;
            cin.clear(); cin.sync();
            cin >> option;

            if (option == 1)// add visit
                cout << AddVisit(*panelPtr, consults);

            patients.push_back(panelPtr);

            return true;
            break;
        }
    case 2: // NonPanel
        {
            string name, address, ic, telno;
            Date birth;

            SetBasicInfo(name, address, ic, telno, birth);

            Patient* patientPtr = new Patient(name, address, ic, telno, birth);

            cout << patientPtr->ToDetail();
            cout << "\nPatient created, what do you want to do with it?\n1. Add new visit record,\nElse. Cancel and abort.\n->";
            int option;
            cin.clear(); cin.sync();
            cin >> option;

            if (option == 1)// add visit
                cout << AddVisit(*patientPtr, consults);

            patients.push_back(patientPtr);

            return true;
            break;
        }
    default:
        return false;
        break;
    }
}

bool SearchPatient(vector<Patient*>& patients, Patient* &p){
    string ic;
    cout << "\nPlease key in the IC of the patient that you want to retrieve.";
    cout << "\nNRIC: (12-numbers, no spaces)\n";
    while (!SetNum(ic, 12))
    { cout << "\nIC should contain 12 numbers! Please try again: \n"; }

    for(unsigned int i=0; i<patients.size();i++){
        if (patients[i]->getIc() == ic){
            p = patients[i];
            return true;
        }
    }

    return false;
}

bool RetrievePatient(vector<Patient*>& patients, vector<Consultation>& consults){

    Patient* p = NULL;
    bool exist = SearchPatient(patients, p);
    if (exist){
        cout << p->ToDetail();
        cout << "\nWhat do you want to do with it?\n1.Add new Visit Record,\nElse. Abort\n->";
        int option;
        cin >> option;
        if (option == 1)
            cout << AddVisit(*p, consults);
        else
            cout << "\nCancelled\n";
    }
    else
        cout << "Patient with the respective IC does not exist!";

    return true;
}

vector<Patient*> LoadPatients(){
    string line;
    vector<string> lines;
    vector<string> strs;
    vector<Patient*> patients;
    std::ifstream file("Patient_List.txt");
    if (file.is_open()){
        while(getline(file, line)){
            lines.push_back(line);
        }
        file.close();
    }
    else cout << "Patient_List.txt does not exist\n";

    for(unsigned int i=0;i<lines.size();i++){
        strs = Split(lines[i], '~');
        if (!strs.empty()){
            if (strs[0] == "+"){
                Visit vs(ToDate(strs[1]), strs[2], strs[3], ToDouble(strs[4]));
                patients[patients.size()-1]->Add(vs);
            }
            else if (strs[0] == "pp"){
                patients.push_back(new Panel(strs[1], strs[4], strs[2], strs[3], ToDate(strs[5]), strs[6], ToDouble(strs[7])));
            }
            else if (strs[0] == "np"){
                patients.push_back(new Patient(strs[1], strs[4], strs[2], strs[3], ToDate(strs[5])));
            }
        }
    }

    return patients;
}

vector<Consultation> LoadConsults(){
    string line;
    vector<string> lines;
    vector<string> strs;
    vector<Consultation> consults;
    std::ifstream file("Consultation_List.txt");
    if (file.is_open()){
        while(getline(file, line)){
            lines.push_back(line);
        }
        file.close();
    }
    else cout << "Consultation_List.txt does not exist.\n";

    for(unsigned int i=0;i<lines.size();i++){
        strs = Split(lines[i], '~');
        if (!strs.empty()){
            if(strs[0] == "c"){
                consults.push_back(Consultation(ToDate(strs[1]),strs[2], strs[3], ToDouble(strs[4])));
            }
        }
    }

    return consults;
}

int main()
{
    vector<Patient*> patients = LoadPatients();
    vector<Consultation> consults = LoadConsults();

    bool alive = true;
    cout << "\nTCP 1201 - Assignment 1\n"
         << "MOHD ARIF DANIAL BIN ABDUL AZIZ\n"
         << "1142702426\n"
         << "TC01 TT01\n"
         << "Patient Management System\n\n";

    do{
        int opr = 0;
        cout << "\n\nPlease key in the number that is respective to the choices below.\n"
        << "1. Create a new patient record,\n"
        << "2. Retrieve a patient's record,\n"
        << "3. Search a consultation for a specific date,\n"
        << "Else, to exit the program.\n\n->";
        cin.clear(); cin.sync();
        cin >> opr;
        switch(opr){
        case 1:
            alive = NewPatient(patients, consults);
            break;
        case 2:
            alive = RetrievePatient(patients, consults);
            break;
        case 3:
            alive = SearchConsultation(consults);
            break;
        default:
            alive = false;
            break;
        }
    }while(alive);

    cout << "\nHave a nice day!\n\n";

    // save Patients List
    std::ofstream pfile("Patient_List.txt");
    if (pfile.is_open()){
        for(unsigned int i=0; i < patients.size(); i++){
            pfile << patients[i]->ToString();
        }
        cout << "\nAll patients saved!\n";
    }
    else cout << "\nUnable to save patients.\n";

    // save Daily Consultations
    std::ofstream cfile("Consultation_List.txt");
    if (cfile.is_open()){
        for(unsigned int i=0; i < consults.size(); i++){
            cfile << consults[i].toString();
        }
        cout << "\nAll consultations saved!\n";
    }
    else cout << "\nUnable to save consultations.\n";
    return 0;
}





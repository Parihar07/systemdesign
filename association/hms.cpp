/*
Hospital Management System - Interview Problem
Task
Implement a Hospital Management System in C++ demonstrating all 4 OOP relationships.

Entities
Person (Base): name, age, contact
Doctor (IS-A Person): specialization, empID → can examine(Patient)
Patient (IS-A Person): patientID, condition
MedicalRecord: diagnosis, treatment (owned by Patient - dies with it)
Department: name, list of doctors (doctors survive if dept is destroyed)

Relationships Required
Inheritance (IS-A): Doctor IS-A Person, Patient IS-A Person
Composition (Dies together): Patient HAS MedicalRecord (use direct member or unique_ptr)
Aggregation (Independent): Department HAS Doctors (use shared_ptr)
Association (Temporary): Doctor examines Patient (pass as function parameter)
*/

/*
Solution approach

1) Will have all entities Person(-name, -Address, -age, -contact)
2) Adress(-hno, -street,, -area)
3) Patient(Person, Address, MedicalInfo, info())
4) Doctor(Person, Adress, patientList, Department)
5) Department(dept_id, name, listof doctors)
6) Medical Record(string diagnosis, treatement)
*/

#include<iostream>
#include<vector>
#include<string>
using namespace std;

// COMPOSITION: Address is owned by Person - dies with Person
class Address{
    string hno, street, area;
public:
    Address(string h, string st, string ar) : hno(h), street(st), area(ar) {
        cout << "Address Constructor\n";
    };
    ~Address(){
        cout << "Address destructor\n";
    }
    void showInfo()
    {
        cout << "H No : " << hno << endl;
        cout << "Street : " << street << endl;
        cout << "Area : " << area << endl;
    }
};
// COMPOSITION: MedicalRecord is owned by Patient - dies with Patient
class MedicalRecord{
    private:
        string diagnosis;
        string treatment;
    public:
    MedicalRecord(string diag, string treat):diagnosis(diag),treatment(treat){
        cout << "Medical Record Constructor\n";
    }
    ~MedicalRecord(){
        cout << "Medical Record Destructor\n";
    }
    void showInfo()
    {
        cout << "Diagnosis : " << diagnosis << endl;
        cout << "Treatment : " << treatment << endl;
    }
};
// BASE CLASS: Person contains Address (Composition)
class Person
{
    private:
        string name;
        int age;
        string contact;
        Address addr;  // Composition: Person HAS Address (dies together)

    public:
        // Constructor: Initialize Address in member initialization list
        Person(string p, int a, string con, string hno="something", string stret="something,", string area="something") : addr(hno, stret, area),
                                                                                     name(p), age(a), contact(con)
        {
            cout << "Person Constructor\n";
        }
        virtual ~Person() {  // Virtual destructor for proper cleanup in inheritance
            cout << "Person Destructor\n";
        }
        void showInfo()
        {
            cout << "Name : " << name << endl;
            cout << "Age : " << age << endl;
            cout << "contact : " << contact << endl;
            cout << "Address : " << endl;
            addr.showInfo();
        }
};
// INHERITANCE: Patient IS-A Person
class Patient : public Person {
private:
    MedicalRecord record;  // COMPOSITION: Patient owns MedicalRecord (dies together)
public:
    // Constructor: name, age, contact, hno, street, area, diagnosis, treatment
    Patient(string pName, int pAge, string pCon, string hno, string street, string area, string diag, string treat)
        : Person(pName, pAge, pCon, hno, street, area), record(diag, treat)
    {
        cout << "Patient Constructor\n";
    }
    ~Patient(){
        cout << "Patient Destructor\n";
    }
    void showInfo()
    {
        Person::showInfo();
        record.showInfo();
    }
};
// INHERITANCE: Doctor IS-A Person
class Doctor : public Person {
private:
    vector<Patient *> patList;  // ASSOCIATION: Doctor interacts with Patients (no ownership)
    string specialization;
public:
    Doctor(string nme, int ag, string dCon, string spec) : Person(nme, ag, dCon), specialization(spec)
    {
        cout << "Doctor Constructor\n";
    }
    ~Doctor(){
        cout << "Doctor Destructor\n";
    }
    // ASSOCIATION: Add patient reference (temporary relationship, no ownership)
    void addPatient(Patient *p){
        patList.push_back(p);
    }
    void showInfo(){
        cout << "Doctor details : ";
        Person::showInfo();
        cout << specialization << endl;
    }
    void showPatients(){
        for(auto i : patList){
            i->showInfo();
        }
    }
    // ASSOCIATION: Doctor examines Patient (temporary interaction, no ownership)
    void examine(Patient *p){
        cout << "\nDoctor examining Patient:\n";
        cout << "Specialization: " << specialization << endl;
        p->showInfo();
    }
};
// AGGREGATION: Department HAS Doctors (doctors can exist independently)
class Department
{
private:
    vector<Doctor *> docs;  // AGGREGATION: Using raw pointers (TODO: use shared_ptr after learning RAII)
    string depName;
public:
    Department(string nm):depName(nm){
        cout << "Department Constructor\n";
    }
    ~Department(){
        cout << "Department Destructor\n";
    }
    // AGGREGATION: Add doctor reference (doctors survive if department is destroyed)
    void addDoc(Doctor *doc){
        docs.push_back(doc);
    }
    void showInfo(){
        cout << "Department Details\n";
        cout << "Department Name : " << depName << endl;
        for (auto i : docs)
        {
            i->showInfo();
        }
    }
};

// UML Representation (Corrected)
/*
INHERITANCE (IS-A):
    Person ◁--- Doctor
    Person ◁--- Patient

COMPOSITION (Dies Together - filled diamond):
    Person ◆--- Address
    Patient ◆--- MedicalRecord

AGGREGATION (Independent Lifetime - hollow diamond):
    Department ◇--- Doctor

ASSOCIATION (Temporary Relationship):
    Doctor ---- Patient (via examine() and addPatient())
*/

int main()
{
    // Create Patient: name, age, contact, hno, street, area, diagnosis, treatment
    Patient p1("madhu", 21, "79932789473", "h no 404", "gully road", "reypally", "fracture", "plaster cast");
    
    // Create Doctor: name, age, contact, specialization
    Doctor kamla("kamal", 34, "64723863827", "Orthopedics");

    // Create Department (AGGREGATION)
    Department orthDep("Orthopedics Department");
    orthDep.addDoc(&kamla);  // AGGREGATION: Department has Doctor

    kamla.addPatient(&p1);  // ASSOCIATION: Doctor adds Patient to list
    
    cout << "\n========== PATIENT INFO ==========\n";
    p1.showInfo();
    
    cout << "\n========== DEPARTMENT INFO ==========\n";
    orthDep.showInfo();
    
    cout << "\n========== DOCTOR INFO ==========\n";
    kamla.showInfo();
    
    cout << "\n========== DOCTOR'S PATIENTS ==========\n";
    kamla.showPatients();
    
    cout << "\n========== ASSOCIATION DEMO ==========\n";
    kamla.examine(&p1);  // ASSOCIATION: Doctor examines Patient
    
    cout << "\n========== END ==========\n";
    return 0;
}
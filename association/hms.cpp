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

class Address{
    string hno, street, area;
public:  // Make constructor public!
    Address(string h, string st, string ar) : hno(h), street(st), area(ar) {
        cout << "Address Constructor\n";
    };
    ~Address(){
        cout << "Address destructor\n";
    }
};

class MedicalRecord{
    private:
        string diagnosis;
        string treatment;
    public:
    MedicalRecord(string diag, string treat):diagnosis(diag),treatment(treat){
        cout << "Medical Record COnstructor\n";
    }
    ~MedicalRecord(){
        cout << "medical record Desctucot\n";
    }
};

class Person
{
    private:
        string name;
        int age;
        string contact;
        
    public:
        // Initialize Address in member initialization list BEFORE constructor body
        Person(string p, int a, string con) :
        name(p), age(a), contact(con) {  // <- Initialize addr here!
            cout << "Person Constructor\n";
        }
        ~Person() {
            cout << "Person destructor\n";
        }
};

class Patient{
    private:
    Person person; //Patient is compossition here
    MedicalRecord record; //COMPOSITION
    Address addr;         // Composition: Address is part of Person
public:
    Patient(string p, int a, string con, string hno, string street, string area, string diag, string treat) 
    : person(p, a, con), addr(hno, street, area), record(diag, treat)
    {
        cout << "Patient contructor\n";
    }
    ~Patient(){
        cout << "Patient Destrucot\n";
    }
}

int
main()
{
    cout<<"Hello, Hotel Managemtn Sytems.\n";
    return 0;
}
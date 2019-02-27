#include "person.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <vector>

using namespace std;

void readData(const char* f, vector<Person> &e);
void getCompanies(vector<string> &c, vector<Person> &e);
void printHighestPaid(vector<Person> &e);
void separateAndSave(vector<string> &c, vector<Person> &e);

int main() {

  vector <Person> employees;
  vector <string> companyNames;
  
  cout << fixed << showpoint << setprecision(2);
  readData("input.txt", employees);
  getCompanies(companyNames, employees);
  printHighestPaid(employees);
  separateAndSave(companyNames, employees);
  return 0;
}

void readData(const char* f, vector<Person> &e){
  ifstream inData;
  inData.open(f);
  string fname;
  string lname;
  int id;
  string coName;
  float pay;
  float hours;
  string line;
  Person p;
  while (!inData.eof()) {
    inData >> fname;
    inData >> lname;
    inData >> id;
    inData >> coName;
    inData >> pay;
    inData >> hours;
    p.setFirstName(fname);
    p.setLastName(lname);
    p.setEmployeeId(id);
    p.setCompanyName(coName);
    p.setPayRate(pay);
    p.setHoursWorked(hours);
    e.push_back(p);
    getline(inData, line);
  }
  inData.close();
}

void getCompanies(vector<string> &c, vector<Person> &e) {
  for (int i = 0; i < e.size(); i++) {
    bool existing = false;
    for (int x = 0; x < c.size(); x++) {
      if (e[i].getCompanyName() == c[x]) {
        existing = true;
      }
    }
    if (existing == false) {
      c.push_back(e[i].getCompanyName());
    }
  }
}

void printHighestPaid(vector<Person> &e) {
  float highestPay = 0.0;
  float indexOfHighest = 0;
  for (int i = 0; i < e.size(); i++) {
    if (e[i].totalPay() > highestPay) {
      highestPay = e[i].totalPay();
      indexOfHighest = i;
    }
  }
  cout << "Highest paid: " << e[indexOfHighest].fullName() << endl;
  cout << "Employee ID: " << e[indexOfHighest].getEmployeeId() << endl;
  cout << "Employer: " << e[indexOfHighest].getCompanyName() << endl;
  cout << "Total Pay: $" << e[indexOfHighest].totalPay() << endl; 
}

void separateAndSave(vector<string> &c, vector<Person> &e) {
  for (int i = 0; i < c.size(); i++) {
    string sfile = c[i] + ".txt";
    const char* f = sfile.c_str();
    ofstream file (f);
    float total = 0;
    for (int x = 0; x < e.size(); x++) {
      if (e[x].getCompanyName() == c[i]) {
        total += e[x].totalPay();
        file << fixed << showpoint << setprecision(2);
        file << e[x].getFirstName() << "    \t" << e[x].getLastName() << "     \t" << c[i] << "\t$" << e[x].totalPay() << endl;
      }
    } 
  }
}

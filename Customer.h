// NAME: Leonardo Alfaro
// WISC ID: 9082565608
#include <string>
#include "Drink.h"
// if you need any additional includes, add them here.
#ifndef CUSTOMER_HEADER
#define CUSTOMER_HEADER
const int DRINK_LIMIT = 10;
const float TAX_PCT = 0.05;
class Customer {
private:
    Drink drinks[DRINK_LIMIT];
    int drink_count;
	string name;
public:
    Customer() { drink_count = 0; } // just writing the constructor inline, since 
   // it's a one-liner.
    void Serve(Drink & drink, const STYLE style);
	Customer(string name);
    float TotalTab(const float tip);
    void Print(const float tip);
    bool ReachedLimit(); // adding an extra function to let us print a message when
  //  we reach the limit, NOT required.
	friend ostream& operator<<(ostream& out, const Customer c) {
		out << c.name << " " << c.drink_count << endl;
		for (int i = 0; i < c.drink_count; i++) {
			out << c.drinks[i] << endl;
		}
		return out;
	}
	friend istream& operator>> (istream& in, Customer& c) {
		string new_name;
		int new_amount;
		in >> new_name >> new_amount;
		for (int i = 0; i < new_amount; i++) {
			in >> c.drinks[i];
		}
		c.name = new_name;
		c.drink_count = new_amount;
		return in;
	}
	string GetName();
};
#endif

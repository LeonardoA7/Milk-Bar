// NAME: Leonardo Alfaro
// WISC ID: 9082565608
#include <string>
// if you need any additional includes, add them here.
#ifndef DRINK_HEADER
#define DRINK_HEADER
using namespace std;
enum STYLE { NEAT = 1, ROCKS = 2, DOUBLE = 3, TALL = 4 };
struct Drink {
    string name;
    float base_price;
    STYLE style;
    Drink(); // default constructor to make compiler happy when we create array.
    Drink(string _name, float _price, STYLE _style = NEAT);
    Drink(const Drink& copy_from);
    void Prepare(const STYLE serving_style);
    float TotalPrice();
    void Print();
    // data and functions should be added here
    // you can add a private section for data if desired.
	friend ostream& operator<<(ostream& out, const Drink d) {
		string kind;
		switch (d.style) {
		case NEAT:
			kind = "STRAIGHT";
			break;
		case ROCKS:
			kind = "ROCKS";
			break;
		case DOUBLE:
			kind = "DOUBLE";
			break;
		case TALL:
			kind = "TALL";
			break;
		}
		out << d.name << " " << d.base_price << " " << kind << endl;
		return out;
	}
	friend istream& operator>>(istream& in, Drink& d) {
		string new_name;
		string new_style;
		float new_price;
		in >> new_name >> new_price >> new_style;
		d.name = new_name;
		d.base_price = new_price;
		if (new_style == "STRAIGHT") {
			d.style = NEAT;
		}
		if (new_style == "ROCKS") {
			d.style = ROCKS;
		}
		if (new_style == "DOUBLE") {
			d.style = DOUBLE;
		}
		if (new_style == "TALL") {
			d.style = TALL;
		}
		return in;
	}
};
#endif

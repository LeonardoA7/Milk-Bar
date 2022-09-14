// NAME: Leonardo Alfaro
// WISC ID: 9082565608
#include <iostream>
#include "Customer.h"
#include "Drink.h"
#include <fstream>
using namespace std;
enum MAIN_MENU { ORDER = 1, PAY = 2, SAVE = 3, LOAD = 4, EXIT = 5 };
enum DRINK_MENU { WHOLE = 1, TWO = 2, HEAVY = 3, MILKSHAKE = 4, MALT = 5, SKIM = 6, RETURN = 7 };
void PrintMain();
void PrintDrinks(Drink menu[], int count);
void PrintStyles();
void prompt();
void SaveTab(Customer c);
Customer LoadTab();
int main() {
    int input = 0;
    int drink_choice = 0;
    int style_choice = 0;
    float tip;
    prompt();
    string name;
    cin >> name;
    Customer customer = Customer(name);
    fstream f;
    f.open("menu.txt");
    int amount;
    f >> amount;
    Drink* menu = new Drink[10];
    for (int i = 0; i < amount; i++) {
        f >> menu[i];
    }
    Drink next_drink;
    do {
        PrintMain();
        cin >> input;
        while (!cin || input < 1 || input > 5) {
            if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
            cout << "Please enter a valid menu item: ";
            cin >> input;
        }
        // now we have good input, handle the cases:
        switch (input) {
        case ORDER:
            if (customer.ReachedLimit()) {
                cout << "You've reached your limit!" << endl;
            }
            else {
                PrintDrinks(menu, amount);
                cin >> drink_choice;
                if (drink_choice == amount + 1) {
                    break;
                }
                while (!cin || drink_choice < 1 || drink_choice > amount + 1) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid menu item: ";
                    cin >> drink_choice;
                }
                PrintStyles();
                cin >> style_choice;
                while (!cin || style_choice < 1 || style_choice > 4) {
                    if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                    cout << "Please enter a valid menu item: ";
                    cin >> style_choice;
                }
                next_drink = Drink(menu[drink_choice - 1]); // copy a drink from the 
               // menu.
                    switch (style_choice) {
                    case NEAT:
                        customer.Serve(next_drink, NEAT);
                        break;
                    case ROCKS:
                        customer.Serve(next_drink, ROCKS);
                        break;
                    case DOUBLE:
                        customer.Serve(next_drink, DOUBLE);
                        break;
                    case TALL:
                        customer.Serve(next_drink, TALL);
                        break;
                    }
            }
            break;
        case PAY:
            cout << "Please enter your tip percent (%): ";
            cin >> tip;
            while (!cin || tip < 0.0) {
                if (!cin) { cin.clear(); cin.ignore(100, '\n'); }
                cout << "Please enter a valid tip percent (%): ";
                cin >> tip;
            }
            customer.Print(tip); 
            prompt();
            cin >> name;
            customer = Customer(name); 
            break;
        case SAVE:
            SaveTab(customer);
            prompt();
            cin >> name;
            customer = Customer(name);
            break;
        case LOAD:
            customer = LoadTab();
            break;
        case EXIT:
            break;
        }
    } while (input != EXIT);
    return 0;
}
void PrintMain() {
    cout << "[" << ORDER << "] Order a Drink" << endl
        << "[" << PAY << "] Pay Your Tab" << endl
        << "[" << SAVE << "] Save Your Tab for later" << endl
        << "[" << LOAD << "] Load previous tab" << endl
        << "[" << EXIT << "] Exit" << endl
        << "Please enter a menu item: ";
}
void PrintDrinks(Drink menu[], int count) {
    cout << "What Drink Would You Like to Order?" << endl;
    for (int i = 0; i < count; i++) {
        cout << "[" << i+1 << "] " << menu[i].name << endl;
    }
    cout << "[" << count + 1 << "] " << "Return to main menu" << endl;
    cout << "Please entere a menu item: " << endl;
}
void PrintStyles() {
    cout << "[" << NEAT << "] Neat" << endl
        << "[" << ROCKS << "] On the Rocks" << endl
        << "[" << DOUBLE << "] Double" << endl
        << "[" << TALL << "] Tall" << endl
        << "Please enter a menu item: ";
}
void prompt() {
    cout << "Please Enter Your Name: " << endl;
}
void SaveTab(Customer c) {
    ofstream outputfile(c.GetName() + ".txt");
    outputfile << c;
    outputfile.close();
}
Customer LoadTab() {
    cout << "Whose Tab Would You Like to Load?" << endl;
    string name;
    cin >> name;
    fstream f;
    f.open(name + ".txt");
    Customer c = Customer();
    f >> c;
    f.close();
    return c;
}

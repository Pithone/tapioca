#include <iostream>

#include "termdisplay.h"

using namespace std;

TermDisplay::TermDisplay() {

}

TermDisplay::~TermDisplay() {

}

void TermDisplay::init(Config config) { }

void TermDisplay::print_header(Config config) {
    cout << "  tapioca" << endl;
}

void TermDisplay::print_journey(Config config, Journey journey) {
    for (auto leg : journey.legs) {
        cout << leg.mode << " " << leg.name << " - ";
    }
    cout << endl;
}

void TermDisplay::print_footer(Config config) {
    cout << "--------" << endl;
}

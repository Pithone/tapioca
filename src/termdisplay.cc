#include <iostream>

#include "termdisplay.h"

TermDisplay::TermDisplay() {

}

TermDisplay::~TermDisplay() {

}

void TermDisplay::init(Config config) { }

void TermDisplay::print_header(Config config) {
    std::cout << "HEADER" << std::endl;
}

void TermDisplay::print_journey(Config config, Journey journey) {
    std::cout << "CONTENT" << std::endl;
}

void TermDisplay::print_footer(Config config) {
    std::cout << "FOOTER" << std::endl;
}

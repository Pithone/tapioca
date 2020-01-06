#include <iostream>
#include "termdisplay.h"

using namespace std;
using namespace std::chrono;


// Debug function to print time to stdout
template<typename Clock, typename Duration>
ostream &operator<<(std::ostream &stream,
    const time_point<Clock, Duration> &time_point) {
    const time_t time = Clock::to_time_t(time_point);
    struct tm tm;
    localtime_r(&time, &tm);
    return stream << put_time(&tm, "%c");
}

void clear_screen() {
    cout << "\033[2J";
}

TermDisplay::TermDisplay() {

}

TermDisplay::~TermDisplay() {

}

void TermDisplay::init(Config config) {
    ;
}

void TermDisplay::clear(Config config) {
    clear_screen();
}

void TermDisplay::print_header(Config config) {
    cout << "  tapioca" << endl;
}

void TermDisplay::print_journey(Config config, Journey journey) {
    // Print remaining time in minutes and seconds
    // FIXME: when the deadline is passed the time counter breaks
    auto remaining_time = journey.departure_limit - system_clock::now();
    auto m = duration_cast<minutes>(remaining_time);
    remaining_time -= m;
    auto s = duration_cast<seconds>(remaining_time);
    cout << m.count() << ":" << setfill('0') << setw(2) << s.count() << " ";
    for (const auto leg : journey.legs) {
        switch (leg.mode) {
            case TRAIN:
                cout << "R";
                break;
            case WALK:
                cout << "W";
                break;
            case TRAM:
                cout << "T";
                break;
            case CAR:
                cout << "C";
                break;
            case BUS:
                cout << "U";
                break;
            case BIKE:
                cout << "B";
                break;
        }
        cout << " " << leg.name;
        if (&leg != &journey.legs.back())
            cout << " - ";
    }
    cout << endl;
}

void TermDisplay::print_footer(Config config) {
    cout << "--------" << endl;
}

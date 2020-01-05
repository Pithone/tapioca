#include <cpr/cpr.h>
#include <graphics.h>
#include <iostream>
#include <led-matrix.h>
#include <memory>
#include <nlohmann/json.hpp>
#include <toml.hpp>

#include "tapioca.h"
#include "display.h"
#include "rgbdisplay.h"
#include "termdisplay.h"

using namespace std;

vector<Journey> get_journeys(Config config) {
    vector<Journey> journeys;

    /* TODO: Use only SUGGESTED journeys, that can be found at
     * json["sections"][0]["journeys"] */
    auto response = cpr::Get(cpr::Url{"https://it-milan-api.citymapper.com/7/journeys"},
                             cpr::Parameters{{"start", config.start_point},
                                             {"end", config.end_point}});

    auto json = nlohmann::json::parse(response.text);
    for(auto journey : json["journeys"]) {
        Journey j;
        for(auto leg : journey["legs"]) {
            /* Match route type */
            leg_mode mode;
            string name, colorstr;
            if (leg["mode"].get<string>().compare("transit") == 0) {
                name = leg["routes"][0]["display_name"].get<string>();
                string modestr = leg["routes"][0]["affinities"][0].get<string>();
                if (modestr.compare("rail") == 0)
                    mode = TRAIN;
                // TODO: Add other matches for TRAM, CAR, BUS, BIKE
                /* Extract color */
                colorstr = leg["routes"][0]["color"].get<string>();
            } else if (leg["mode"].get<string>().compare("walk") == 0) {
                mode = WALK;
                name = "Walk";
                colorstr = "#000000";
            }
            if (colorstr.compare("") == 0)
                colorstr = "#000000";
            colorstr.erase(0, 1);
            int colornum = stoi(colorstr, 0, 16);
            int r = colornum / 0x10000;
            int g = (colornum / 0x100) % 0x100;
            int b = colornum % 0x100;
            j.legs.push_back(Leg(mode, name, Color(r,g,b)));
        }
        journeys.push_back(j);
    }
    return journeys;
}

int main(int argc, char** argv) {
    unique_ptr<Display> display;

    /* Load configuration file */
    Config config = Config();

    if (config.terminal) {
        display = make_unique<TermDisplay>();
    } else {
        display = make_unique<RgbDisplay>();
    }

    /* Continue until SIGSTOP is received */
    for(;;) {
        vector<Journey> journeys = get_journeys(config);

        /* Print data to matrix */
        display.get()->print_header(config);
        for(auto journey : journeys) {
            display.get()->print_journey(config, journey);
        }
        display.get()->print_footer(config);

        /* Wait for one minute before refreshing */
        this_thread::sleep_for(chrono::minutes(1));
    }

    return 0;
}

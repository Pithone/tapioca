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

std::vector<Journey> get_journeys(Config config) {
    /* TODO: Use only SUGGESTED journeys, that can be found at
     * json["sections"][0]["journeys"] */
    auto response = cpr::Get(cpr::Url{"https://it-milan-api.citymapper.com/7/journeys"},
                             cpr::Parameters{{"start", config.start_point},
                                             {"end", config.end_point}});

    auto json = nlohmann::json::parse(response.text);
    int j_idx = 0;
    for(auto journey : json["journeys"]) {
        j_idx++;
        std::cout << "Journey number " << j_idx << ": ";
        for(auto leg : journey["legs"]) {
            if (leg["mode"] == "transit") {
                std::cout << leg["routes"][0]["affinities"][0].get<std::string>();
                std::cout << " |" << leg["routes"][0]["display_name"].get<std::string>() << " ";
            } else
                std::cout << leg["mode"].get<std::string>() << " ";
        }
        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    std::unique_ptr<Display> display;

    /* Load configuration file */
    Config config = Config();

    if (config.terminal) {
        display = std::make_unique<TermDisplay>();
    } else {
        display = std::make_unique<RgbDisplay>();
    }

    /* Continue until SIGSTOP is received */
    for(;;) {
        std::vector<Journey> journeys = get_journeys(config);

        /* Print data to matrix */
        display.get()->print_header(config);
        for(auto journey : journeys) {
            display.get()->print_journey(config, journey);
        }
        display.get()->print_footer(config);

        /* Wait for one minute before refreshing */
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }

    return 0;
}

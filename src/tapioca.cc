#include <iostream>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <graphics.h>

enum leg_mode { TRAIN, WALK, TRAM, CAR, BUS, BIKE };

/* TODO: Load configuration from toml */
class Config {
    public:
        std::string start_point;
        std::string end_point;
        std::string region;
        bool got_bike;
};

class Color {
    public:
        unsigned char r;
        unsigned char g;
        unsigned char b;
};

class Leg {
    public:
        enum leg_mode mode;
        std::string name;
        Color color;
};

class Journey {
    public:
        std::chrono::steady_clock::time_point departure_limit;
        std::vector<Leg> legs;
};

std::vector<Journey> get_journeys(Config config) {
    /* TODO: Use only SUGGESTED journeys, that can be found at
     * json["sections"][0]["journeys"] */
    auto response = cpr::Get(cpr::Url{"https://it-milan-api.citymapper.com/7/journeys"},
                             cpr::Parameters{{"start", "45.496014,9.375752"},
                                             {"end", "45.479091,9.233966"}});

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

void print_header() {
    ;
}

void print_journey(Journey journey) {
    ;
}

void print_footer() {
    ;
}

Config load_config() {
    ;
}

int main(int argc, char** argv) {
    /* Load configuration file */
    Config config = load_config();

    /* Continue until SIGSTOP is received */
    for(;;) {
        std::vector<Journey> journeys = get_journeys(config);

        /* Print data to matrix */
        print_header();
        for(auto journey : journeys) {
            print_journey(journey);
        }
        print_footer();

        /* Wait for one minute before refreshing */
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
}

#include <iostream>

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include <graphics.h>
#include <toml.hpp>
#include <led-matrix.h>

enum leg_mode { TRAIN, WALK, TRAM, CAR, BUS, BIKE };

class Config {
    public:
        std::string start_point;
        std::string end_point;
        std::string region;
        bool got_bike;
        bool terminal;

        Config() {
            const auto config = toml::parse("../config.toml");
            start_point = toml::find<std::string>(config, "start");
            end_point = toml::find<std::string>(config, "end");
            region = toml::find<std::string>(config, "region");
            got_bike = toml::find<bool>(config, "bike");
            got_bike = toml::find<bool>(config, "terminal");
        }
};

class Color {
    public:
        unsigned char r;
        unsigned char g;
        unsigned char b;

        Color(int r, int g, int b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }
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

void print_header(Config config) {
    ;
}

void print_journey(Config config, Journey journey) {
    ;
}

void print_footer(Config config) {
    ;
}

int main(int argc, char** argv) {
    /* Load configuration file */
    Config config = Config();

    rgb_matrix::RGBMatrix::Options matrix_options;
    rgb_matrix::RuntimeOptions runtime_opt;
    rgb_matrix::ParseOptionsFromFlags(&argc,
                                      &argv,
                                      &matrix_options,
                                      &runtime_opt);

    rgb_matrix::RGBMatrix *matrix = rgb_matrix::CreateMatrixFromOptions(matrix_options,
                                                            runtime_opt);

    // TODO: implement brightness control
    //matrix->SetBrightness(brightness);

    /* Continue until SIGSTOP is received */
    for(;;) {
        std::vector<Journey> journeys = get_journeys(config);

        /* Print data to matrix */
        print_header(config);
        for(auto journey : journeys) {
            print_journey(config, journey);
        }
        print_footer(config);

        /* Wait for one minute before refreshing */
        std::this_thread::sleep_for(std::chrono::minutes(1));
    }
}

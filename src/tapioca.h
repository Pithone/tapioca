#ifndef TAPIOCA_H_
#define TAPIOCA_H_

#include <string>
#include <toml.hpp>

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
            terminal = toml::find<bool>(config, "terminal");
        }
};

class Color {
    public:
        Color(int r, int g, int b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        unsigned char r;
        unsigned char g;
        unsigned char b;
};

class Leg {
    public:
        Leg(enum leg_mode mode,
            std::string name,
            Color color) : mode(mode),
                           name(name),
                           color(color) {}
        enum leg_mode mode;
        std::string name;
        Color color;
};

class Journey {
    public:
        std::chrono::steady_clock::time_point departure_limit;
        std::vector<Leg> legs;
};

#endif // TAPIOCA_H_

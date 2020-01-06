#ifndef TAPIOCA_H_
#define TAPIOCA_H_
#define MAX_ARGC 32

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
        std::string panel_font;
        std::string panel_config;
        int panel_brightness;
        char *rgb_argv[MAX_ARGC];
        int rgb_argc;

        Config() {
            // Parse options from configuration file
            const auto config = toml::parse("../config.toml");
            start_point = toml::find<std::string>(config, "start");
            end_point = toml::find<std::string>(config, "end");
            region = toml::find<std::string>(config, "region");
            got_bike = toml::find<bool>(config, "bike");
            terminal = toml::find<bool>(config, "terminal");
            panel_font = toml::find<std::string>(config, "panel_font");
            panel_config = toml::find<std::string>(config, "panel_config");
            panel_brightness = toml::find<int>(config, "panel_brightness");
            // Compute argument count from configuration string
            rgb_argv[0] = strndup("tapioca", 8);
            rgb_argc = 1;
            size_t old_delim = 0;
            for(auto delim = panel_config.find(" ");
                delim != std::string::npos;
                delim = panel_config.find(" ", delim+1)) {
                // If we have found a delimited substring
                if(delim > old_delim + 1) {
                    rgb_argv[rgb_argc] = strndup(panel_config.c_str() + old_delim,
                                                 delim - old_delim);
                    rgb_argc++;
                }
                old_delim = delim;
            }
            // Add last argument
            rgb_argv[rgb_argc] = strndup(panel_config.c_str() + old_delim,
                                         panel_config.size() - old_delim);
            rgb_argc++;
            std::cout << "Parsed arguments: " << std::endl;
            for(int i = 0; i < rgb_argc; i++) {
                std::cout << rgb_argv[i] << std::endl;
            }
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
        std::vector<Leg> legs;
        std::chrono::system_clock::time_point departure_limit;
};

#endif // TAPIOCA_H_

#define TXTBUF_SIZE 256

#include <iostream>
#include "rgbdisplay.h"

using namespace std;
using namespace rgb_matrix;

RgbDisplay::RgbDisplay() {

}

RgbDisplay::~RgbDisplay() {

}

void RgbDisplay::init(Config config) {
    // Load font from file
    font.LoadFont(config.panel_font.c_str());

    // Initialize panel
    RGBMatrix::Options matrix_options;
    RuntimeOptions runtime_opt;
    ParseOptionsFromFlags(&config.rgb_argc,
                          (char ***)&config.rgb_argv,
                          &matrix_options,
                          &runtime_opt);

    matrix = rgb_matrix::CreateMatrixFromOptions(matrix_options,
                                                 runtime_opt);

    // TODO: implement automatic brightness control
    matrix->SetBrightness(config.panel_brightness);

    canvas = matrix->CreateFrameCanvas();
}

void RgbDisplay::clear(Config config) {
    canvas->Fill(0, 0, 0);
}

void RgbDisplay::print_header(Config config) {
    int x = 0, y = 0, letter_spacing = 0;
    char text_buffer[TXTBUF_SIZE];
    struct timespec next_time;
    next_time.tv_sec = time(NULL);
    next_time.tv_nsec = 0;
    struct tm tm;
    rgb_matrix::Color outline_color(255, 255, 255);
    localtime_r(&next_time.tv_sec, &tm);
    strftime(text_buffer, sizeof(text_buffer), "%H:%M", &tm);
    rgb_matrix::DrawText(canvas, font,
                         x - 1, y + font.baseline(),
                         outline_color, NULL, text_buffer,
                         letter_spacing - 2);
}

void RgbDisplay::print_journey(Config config, Journey journey) {
    // TODO: For each journey print in the following format
    // MM:SS W |S6 |R
    // ^     ^ legs logos, colored pipe, name of the line
    // | minutes and seconds till the deadline
    
    //rgb_matrix::DrawText(offscreen, *outline_font,
    //                     x - 1, y + font.baseline(),
    //                     outline_color, NULL, text_buffer,
    //                     letter_spacing - 2);
}

void RgbDisplay::print_footer(Config config) {
}

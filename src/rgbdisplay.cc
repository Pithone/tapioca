#include "rgbdisplay.h"

using namespace std;

RgbDisplay::RgbDisplay() {

}

RgbDisplay::~RgbDisplay() {

}

void RgbDisplay::init(Config config) {
    //rgb_matrix::RGBMatrix::Options matrix_options;
    //rgb_matrix::RuntimeOptions runtime_opt;
    //rgb_matrix::ParseOptionsFromFlags(&argc,
    //                                  &argv,
    //                                  &matrix_options,
    //                                  &runtime_opt);

    //rgb_matrix::RGBMatrix *matrix = rgb_matrix::CreateMatrixFromOptions(matrix_options,
    //                                                        runtime_opt);

    // TODO: implement brightness control
    //matrix->SetBrightness(brightness);
}

void RgbDisplay::print_header(Config config) {
    // TODO: Print clock here MM:SS, white centered
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

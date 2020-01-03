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
}

void RgbDisplay::print_journey(Config config, Journey journey) {
}

void RgbDisplay::print_footer(Config config) {
}

#ifndef RGBDISPLAY_H_
#define RGBDISPLAY_H_

#include <led-matrix.h>
#include <graphics.h>
#include "display.h"

class RgbDisplay : public Display
{
    rgb_matrix::Font font;
    rgb_matrix::RGBMatrix *matrix;
    rgb_matrix::FrameCanvas *canvas;

  public:
    RgbDisplay();
    ~RgbDisplay();

    virtual void init(Config config);
    virtual void clear(Config config);
    virtual void print_header(Config config);
    virtual void print_journey(Config config, Journey journey);
    virtual void print_footer(Config config);
};

#endif // RGBDISPLAY_H_

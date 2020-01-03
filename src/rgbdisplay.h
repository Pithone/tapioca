#ifndef RGBDISPLAY_H_
#define RGBDISPLAY_H_

#include "display.h"

class RgbDisplay : public Display
{
  public:
    RgbDisplay();
    ~RgbDisplay();

    virtual void init(Config config);
    virtual void print_header(Config config);
    virtual void print_journey(Config config, Journey journey);
    virtual void print_footer(Config config);
};

#endif // RGBDISPLAY_H_

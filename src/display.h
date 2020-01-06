#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "tapioca.h"

class Display
{
  public:
    Display() {}
    virtual ~Display() {}

    virtual void init(Config config) = 0;
    virtual void clear(Config config) = 0;
    virtual void print_header(Config config) = 0;
    virtual void print_journey(Config config, Journey journey) = 0;
    virtual void print_footer(Config config) = 0;
};

#endif // DISPLAY_H_

#ifndef TERMDISPLAY_H_
#define TERMDISPLAY_H_

#include "display.h"

class TermDisplay : public Display
{
  public:
    TermDisplay();
    ~TermDisplay();

    virtual void init(Config config);
    virtual void clear(Config config);
    virtual void print_header(Config config);
    virtual void print_journey(Config config, Journey journey);
    virtual void print_footer(Config config);
};

#endif // TERMDISPLAY_H_

#include "Legend.h"

#include <Fl/fl_draw.h>

Legend::Legend()
{
    //ctor
    top = 5;
    left = 100;
    height = 20;
    width = 300;
    isVisible = true;
}

Legend::~Legend()
{
    //dtor
}

void Legend::draw()
{
    if (!isVisible) return;

    fl_draw_box(FL_ENGRAVED_BOX, left, top, width, height, FL_BACKGROUND_COLOR);
}

void Legend::calcSize()
{

}



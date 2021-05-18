#include "DChartBase.h"

#include <FL/fl_draw.H>

DChartBase::DChartBase(int x, int y, int w, int h, const char *label) :
    Fl_Widget(x,y,w,h,label)
{
    //ctor
}

DChartBase::~DChartBase()
{
    //dtor
}

void DChartBase::draw()
{
    fl_draw_box(FL_ENGRAVED_BOX, this->x(), this->y(), this->w(), this->h(),
                 FL_BACKGROUND_COLOR);
    draw_label();
}

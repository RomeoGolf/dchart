#include "DChartBase.h"

#include <FL/fl_draw.H>
#include <string>

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
    test();
}

void DChartBase::test()
{
    std::string s = "Икс -> " + std::to_string(this->x());
    fl_draw(s.data(), 15, this->x() + 30, this->y() + 50);
}



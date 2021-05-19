#include "Series.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <math.h>

Series::Series()
{
    //ctor
}

Series::~Series()
{
    //dtor
}

void Series::addXY(double x, double y)
{
    data.push_back(new SeriesData<double>(x, y));
}

void Series::draw()
{
    fl_color(FL_BLUE);
    fl_line_style(0);

    fl_begin_line();
    for (int i = 0; i < data.size(); i++) {
        fl_vertex(data[i]->xValue, data[i]->yValue);
    }

    fl_end_line();
}



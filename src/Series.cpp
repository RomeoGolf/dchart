#include "Series.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <math.h>

Series::Series(ChartHelper &chartHelper) : chartHelper(chartHelper)
{
    //ctor
}

Series::~Series()
{
    //dtor
}

void Series::addXY(double x, double y)
{
    data.push_back(SeriesData<double>(x, y));
}

void Series::draw()
{
    fl_color(FL_BLUE);
    fl_line_style(0);

    fl_begin_line();
    for (int i = 0; i < data.size(); i++) {
        double x = data[i].xValue - horizAxis->visibleMinimum;
        double y = data[i].yValue;

        int cx = ceil(x * horizAxis->sizeCoeff) + chartHelper.marginLeft;
        int cy = chartHelper.chartRectBottom - ceil(y * (chartHelper.chartRectBottom - chartHelper.chartRectTop) / 100);

        fl_vertex(cx, cy);
    }

    fl_end_line();
}



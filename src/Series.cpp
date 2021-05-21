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
        double x = data[i].xValue;
        double y = data[i].yValue;

        int cx = ceil(x * (chartHelper.chartRectRight - chartHelper.chartRectLeft) / 10);
        int cy = ceil(y * (chartHelper.chartRectBottom - chartHelper.chartRectTop) / 100);

        fl_vertex(cx + chartHelper.chartRectLeft, chartHelper.chartRectBottom - cy);
    }

    fl_end_line();
}



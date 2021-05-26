#include "Series.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <math.h>
#include <iostream>

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

    int xStart = getFloorIndexOfX(horizAxis->visibleMinimum);
    int xEnd = getFloorIndexOfX(horizAxis->visibleMaximum);
    if (xEnd + 1 < data.size()) xEnd++;

    for (int i = xStart; i <= xEnd; i++) {
        double x = data[i].xValue - horizAxis->visibleMinimum;
        double y = data[i].yValue - vertAxis->visibleMinimum;

        int cx = ceil(x * horizAxis->sizeCoeff) + chartHelper.marginLeft;
        int cy = ceil(chartHelper.chartRectBottom - y * vertAxis->sizeCoeff);

        fl_vertex(cx, cy);
    }

    fl_end_line();
}

int Series::getFloorIndexOfX(double x)
{
    if (x >= data.back().xValue)
        return data.size() - 1;
    if (x <= data.front().xValue)
        return 0;

    int xStart = 0;
    int xEnd = data.size() - 1;

    while ((xEnd - xStart) > 1) {
        int i = xStart + (xEnd - xStart) / 2;
        auto &item = data[i];
        if (item.xValue > x) {
            xEnd = i;
        } else {
            xStart = i;
        }
    }

    return xStart;
}


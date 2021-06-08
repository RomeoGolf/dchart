#include "LineSeries.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <Fl/Enumerations.h>

#include <math.h>

LineSeries::LineSeries(ChartHelper &chartHelper) : BasicSeries(chartHelper)
{
    //ctor
}

LineSeries::~LineSeries()
{
    //dtor
}

void LineSeries::draw()
{
    fl_color(color);
    fl_line_style(0);

    fl_begin_line();

    int xStart = getFloorIndexOfX(horizAxis->getVisibleMinimum());
    int xEnd = getFloorIndexOfX(horizAxis->getVisibleMaximum());
    if (xEnd + 1 < data.size()) xEnd++;

    for (int i = xStart; i <= xEnd; i++) {
        double x = data[i].xValue - horizAxis->getVisibleMinimum();
        double y = data[i].yValue - vertAxis->getVisibleMinimum();

        int cx = ceil(x * horizAxis->getSizeCoeff()) + chartHelper.marginLeft;
        int cy = ceil(chartHelper.chartRectBottom - y * vertAxis->getSizeCoeff());

        fl_vertex(cx, cy);
    }

    fl_end_line();
}

void LineSeries::addXY(double x, double y)
{
    data.push_back(SeriesData<double>(x, y));
    isSorted = false;

    minX = x < minX ? x : minX;
    minY = y < minY ? y : minY;
    maxX = x > maxX ? x : maxX;
    maxY = y > maxY ? y : maxY;

    horizAxis->doAutoSize(minX, maxX);
    vertAxis->doAutoSize(minY, maxY);
}

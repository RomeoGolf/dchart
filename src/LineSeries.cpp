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

    int xStart = getFloorIndexOfX(horizAxis->getVisibleMinimum());
    int xEnd = getFloorIndexOfX(horizAxis->getVisibleMaximum());
    if (xEnd + 1 < data.size()) xEnd++;
    /*
    fl_begin_line();
    double vMinimum = vertAxis->getVisibleMinimum();
    double hMinimum = horizAxis->getVisibleMinimum();
    for (int i = xStart; i <= xEnd; i++) {
        double x = data[i].xValue - hMinimum;
        double y = data[i].yValue - vMinimum;

        int cx = ceil(x * horizAxis->getSizeCoeff()) + chartHelper.marginLeft;
        int cy = ceil(chartHelper.chartRectBottom - y * vertAxis->getSizeCoeff());

        fl_vertex(cx, cy);
    }
    fl_end_line();
    */
    /**/
    double vMinimum = vertAxis->getVisibleMinimum();
    double hMinimum = horizAxis->getVisibleMinimum();
    for (int i = xStart + 1; i <= xEnd; i++) {
        double x1 = data[i - 1].xValue - hMinimum;
        double y1 = data[i - 1].yValue - vMinimum;
        double x2 = data[i].xValue - hMinimum;
        double y2 = data[i].yValue - vMinimum;

        int cx1 = ceil(x1 * horizAxis->getSizeCoeff()) + chartHelper.marginLeft;
        int cy1 = ceil(chartHelper.chartRectBottom - y1 * vertAxis->getSizeCoeff());
        int cx2 = ceil(x2 * horizAxis->getSizeCoeff()) + chartHelper.marginLeft;
        int cy2 = ceil(chartHelper.chartRectBottom - y2 * vertAxis->getSizeCoeff());

        fl_line(cx1, cy1, cx2, cy2);
    }

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

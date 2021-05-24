#include "HorizAxis.h"

#include <math.h>
#include <Fl/fl_draw.h>

#include <iostream>

HorizAxis::HorizAxis(ChartHelper &chartHelper) : BasicAxis(chartHelper)
{
    //ctor
    visibleMinimum = -0.5;
    visibleMaximum = 15;
}

HorizAxis::~HorizAxis()
{
    //dtor
}

void HorizAxis::draw()
{
    pixelSize = (chartHelper.chartRectRight - chartHelper.chartRectLeft);
    if (pixelSize < 5) return;

    setSizeCoeff();
    calcStep();
    calcStartMarkUnit();

    double nextX = startMarkUnit;
    std::cout << "axis draw | nextX = " << nextX << "\n";

    double x = chartHelper.chartRectLeft + ceil(startMarkUnit * sizeCoeff);
    while (x <= chartHelper.chartRectRight) {
        fl_line(x, chartHelper.chartRectTop, x, chartHelper.chartRectBottom);
        nextX += step;
        x = chartHelper.chartRectLeft + ceil(nextX * sizeCoeff);
    }


}

void HorizAxis::calcStep()
{
    double gap = visibleMaximum - visibleMinimum;
    if (gap == 0) {
        step = 0;
        return;
    }
    double maxLabelNum = 10;
    step = ceil(gap / maxLabelNum);
}


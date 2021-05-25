#include "HorizAxis.h"

#include <math.h>
#include <Fl/fl_draw.h>

#include <iostream>
#include <string>
#include <sstream>

HorizAxis::HorizAxis(ChartHelper &chartHelper) : BasicAxis(chartHelper)
{
    //ctor
    visibleMinimum = 3.75;
    visibleMaximum = 4.5;
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

    std::cout << "axis draw | startMarkUnit = " << startMarkUnit << "\n";
    std::cout << "axis draw | startMarkUnit = " << startMarkUnit << "\n";

    startlabelValue = round((visibleMinimum + startMarkUnit) * 10) / 10;

    std::cout << "axis draw | startlabelValue = " << startlabelValue << "\n";

    double xlabelValue = startlabelValue;
    std::stringstream ss;
    ss << xlabelValue;
    std::string xLabelString = ss.str();

    double nextX = startMarkUnit;

    double x = chartHelper.chartRectLeft + ceil(startMarkUnit * sizeCoeff);
    while (x <= chartHelper.chartRectRight) {
        int labelWidth = fl_width(xLabelString.data());
        fl_draw(xLabelString.data(), x - (labelWidth / 2), chartHelper.chartRectBottom + 20);
        xlabelValue = round((xlabelValue + step) * 10) / 10;
        std::stringstream ss;
        ss << xlabelValue;
        xLabelString = ss.str();

        fl_line(x, chartHelper.chartRectTop, x, chartHelper.chartRectBottom);
        nextX += step;
        x = chartHelper.chartRectLeft + ceil(nextX * sizeCoeff);
    }


}

void HorizAxis::calcStep()
{
    double gap = visibleMaximum - visibleMinimum;

    int degree = 1;

    if (gap == 0) {
        step = 10;
        return;
    } else {
        degree = ceil(log10(gap)) - 2;
    }
    int multipl = ceil(pow(10, degree));

    std::cout << "axis draw | gap = " << gap << "\n";
    std::cout << "axis draw | degree = " << degree << "\n";
    std::cout << "axis draw | multipl = " << multipl << "\n";

    step = div(ceil(gap), 7).quot;

    std::cout << "axis draw | step = " << step << "\n";

    if (step > 1) {
        step = (div(ceil(step), multipl).quot + 1) * multipl;
        step = round(step / 5) * 5;
    } else {
        step = 0.5;
        //step = pow(10, degree - 0);
        step = pow(10, floor(log10(gap)) - 0);
        //step = round(step * 10) / 10;
    }

    std::cout << "axis draw | step (2) = " << step << "\n";

    //if ((step > 1) && (step < 10)) step = 5;
}

void HorizAxis::zoomByMouse()
{
    double oldCoeff;
    double oldVisibleMax;
    double oldVisibleMin;

    if (sizeCoeff != 0) {
        oldCoeff = sizeCoeff;
        oldVisibleMax = oldVisibleMaximum;
        oldVisibleMin = oldVisibleMinimum;
        visibleMaximum = visibleMinimum + (mouseNowX - chartHelper.chartRectLeft) / oldCoeff;
        visibleMinimum = visibleMinimum + (mouseStartX - chartHelper.chartRectLeft) / oldCoeff;
    } else {
        // exception?
    }
}


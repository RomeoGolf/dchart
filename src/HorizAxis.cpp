#include "HorizAxis.h"

#include <math.h>
#include <Fl/fl_draw.h>

//#include <iostream>
#include <string>
#include <sstream>

HorizAxis::HorizAxis(ChartHelper &chartHelper) : BasicAxis(chartHelper)
{
    //ctor
    minimum = -3.75;
    maximum = 20.5;
    visibleMinimum = -3.75;
    visibleMaximum = 20.5;
}

HorizAxis::~HorizAxis()
{
    //dtor
}

void HorizAxis::draw()
{
    pixelSize = (chartHelper.chartRectRight - chartHelper.chartRectLeft);
    if (pixelSize < 5) return;

    visibleMinimum = /*round*/(visibleMinimum * 1) / 1;
    visibleMaximum = /*round*/(visibleMaximum * 1) / 1;

    setSizeCoeff();
    calcStep();
    calcStartMarkUnit();

    if (!isVisible) return;

    startlabelValue = /*round*/((visibleMinimum + startMarkUnit) * 1) / 1;

    double xLabelValue = startlabelValue;
    double nextX = startMarkUnit;

    int x = chartHelper.chartRectLeft + ceil(startMarkUnit * sizeCoeff);
    while (x <= chartHelper.chartRectRight) {
        std::stringstream ss;
        double val = round(xLabelValue * 1000) / 1000;
        val = (fabs(val) < std::numeric_limits<double>::epsilon() ? 0 : val);
        ss << val;        std::string xLabelString = ss.str();
        int labelWidth = fl_width(xLabelString.data());

        fl_font(0, fontSize);
        fl_color(fontColor);
        fl_draw(xLabelString.data(), x - (labelWidth / 2), chartHelper.chartRectBottom + 20);
        xLabelValue = /*round*/((xLabelValue + step) * 1) / 1;

        fl_color(gridColor);
        fl_line_style(gridStyle, gridWidth, gridDashes);
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

    step = div(ceil(gap), 7).quot;

    if (step > 1) {
        step = (div(ceil(step), multipl).quot + 1) * multipl;
        //step = round(step / 5) * 5;
    } else {
        step = 0.5;
        //step = pow(10, degree - 0);
        step = pow(10, floor(log10(gap)) - 0);
        //step = round(step * 10) / 10;
    }

    if ((step > 1) && (step < 10)) step = 5;
}

void HorizAxis::zoomByMouse()
{
    if (isFixed) return;
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
        axisShift = 0;
        // exception?
    }
}

void HorizAxis::shiftByMouse()
{
    if (isFixed) return;
    if (sizeCoeff != 0) {
        axisShift = (mouseNowX - mouseStartX) / sizeCoeff;
    } else {
        axisShift = 0;
        // exception?
    }
    visibleMaximum = /*round*/((oldVisibleMaximum - axisShift) * 1) / 1;
    visibleMinimum = /*round*/((oldVisibleMinimum - axisShift) * 1) / 1;
}


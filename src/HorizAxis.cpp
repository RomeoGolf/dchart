#include "HorizAxis.h"

#include <math.h>
#include <Fl/fl_draw.h>

//#include <iostream>
#include <string>
#include <sstream>
#include <limits>

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

void HorizAxis::prepareNotches()
{
    pixelSize = (chartHelper.chartRectRight - chartHelper.chartRectLeft);

    setSizeCoeff();
    calcStep();
    calcStartMarkUnit();
    calcThickness();
}

void HorizAxis::draw(int delta)
{
    if (pixelSize < 5) return;
    if (!isVisible) return;

    startlabelValue = visibleMinimum + startMarkUnit;

    double xLabelValue = startlabelValue;
    double nextX = startMarkUnit;

    int x = chartHelper.chartRectLeft + ceil(startMarkUnit * sizeCoeff);
    while (x <= chartHelper.chartRectRight) {
        std::stringstream ss;
        //double val = round(xLabelValue * 1000) / 1000;
        double val = xLabelValue;
        val = (fabs(val) < std::numeric_limits<double>::epsilon() ? 0 : val);
        ss << val;
        std::string xLabelString = ss.str();
        int labelWidth = fl_width(xLabelString.data());

        fl_font(fontFace, fontSize);
        fl_color(fontColor);
        fl_draw(xLabelString.data(), x - (labelWidth / 2),
                chartHelper.chartRectBottom + margin + (fl_height() - fl_descent()) + delta);
        xLabelValue = xLabelValue + step;

        fl_color(gridColor);
        fl_line_style(gridStyle, gridWidth, gridDashes);
        fl_line(x, chartHelper.chartRectTop, x, chartHelper.chartRectBottom);
        nextX += step;
        x = chartHelper.chartRectLeft + ceil(nextX * sizeCoeff);
    }
}

void HorizAxis::calcStep()
{
    double gap = fabs(visibleMaximum - visibleMinimum);
    double absMax = std::max(fabs(visibleMinimum), fabs(visibleMaximum));

    int degree = ceil(log10(fabs(absMax)));
    if (gap <= std::numeric_limits<double>::epsilon()) {
        step = 10;
        return;
    } else if (gap >= 1) {
        fl_font(fontFace, fontSize);
        int labelWidth = fl_width("W") * (degree + 1);
        int maxLines = (chartHelper.chartRectRight - chartHelper.chartRectLeft)
                         / (labelWidth + labelWidth / 2) + 2;
        if (maxLines <= 0) maxLines = 1;
        step = gap / maxLines;

        double coeff = pow(10, floor(log10(gap)) - 1);
        if (coeff < std::numeric_limits<double>::epsilon()) coeff = 1;
        if (step / coeff < 1) {
            coeff = pow(10, floor(log10(step)) - 0);
        }
        step = round(step / coeff) * coeff;
    } else {
        double gapDegree = ceil(log10(gap));
        int labelWidth = fl_width("W") * (degree + 2 + (-gapDegree + 2));
        int maxLines = (chartHelper.chartRectRight - chartHelper.chartRectLeft)
                         / (labelWidth + labelWidth) + 3;
        if (maxLines <= 0) maxLines = 1;

        step = gap / maxLines;
        double coeff = pow(10, floor(log10(gap)) - 1);
        if (coeff < std::numeric_limits<double>::epsilon()) coeff = 1;
        if (step / coeff < 1) {
            coeff = pow(10, floor(log10(step)) - 0);
        }
        step = round(step / coeff) * coeff;
    }
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
    visibleMaximum = oldVisibleMaximum - axisShift;
    visibleMinimum = oldVisibleMinimum - axisShift;
}

void HorizAxis::calcThickness()
{
    fl_font(fontFace, fontSize);
    fieldThickness = fl_height() + margin * 2;
}


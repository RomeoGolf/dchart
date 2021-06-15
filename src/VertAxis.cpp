#include "VertAxis.h"

#include <Fl/fl_draw.h>

#include <math.h>
#include <string>
#include <sstream>
#include <vector>

#include <iostream>

struct Notch {
    std::string label;
    int x, y;
    int h, w;
};

VertAxis::VertAxis(ChartHelper &chartHelper) : BasicAxis(chartHelper)
{
    //ctor
    minimum = -10.7;
    maximum = 110.5;
    visibleMinimum = -10.7;
    visibleMaximum = 110.5;
}

VertAxis::~VertAxis()
{
    //dtor
}

void VertAxis::calcStep()
{
    pixelSize = chartHelper.chartRectBottom - chartHelper.chartRectTop;
    int labelSize = fl_height();

    double gap = fabs(visibleMaximum - visibleMinimum);
    double absMax = std::max(fabs(visibleMinimum), fabs(visibleMaximum));
    int degree = ceil(log10(fabs(absMax)));

    if (gap <= std::numeric_limits<double>::epsilon()) {
        step = 10;
        return;
    } else {
        int maxLines = (pixelSize) / (labelSize * 4) + 2;
        if (maxLines <= 0) maxLines = 1;
        step = gap / maxLines;

        double coeff = pow(10, floor(log10(gap)) - 1);
        if (coeff < std::numeric_limits<double>::epsilon()) coeff = 1;
        step = round(step / coeff) * coeff;
    }
}

void VertAxis::draw()
{
    pixelSize = (chartHelper.chartRectBottom - chartHelper.chartRectTop);
    if (pixelSize < 5) return;

    fl_font(fontFace, fontSize);
    setSizeCoeff();
    calcStep();
    calcStartMarkUnit();

    if (!isVisible) return;

    startlabelValue = ((visibleMinimum + startMarkUnit) * 10) / 10;

    double yLabelValue = startlabelValue;
    double nextY = startMarkUnit;
    int y = ceil(startMarkUnit * sizeCoeff);

    int b_bottom = chartHelper.chartRectBottom + 0;
    int b_top = chartHelper.chartRectTop;
    std::vector<Notch> notches;

    while (y <= (b_bottom - b_top)) {
        Notch n;
        std::stringstream ss;
        double val = round(yLabelValue * 1000) / 1000;
        val = (fabs(val) < std::numeric_limits<double>::epsilon() ? 0 : val);
        ss << val;
        n.label = ss.str();
        int labelHeight = fl_height();
        int labelWidth = fl_width(n.label.c_str());
        n.w = labelWidth + 10;
        n.h = y - (labelHeight - fl_descent()) / 2;
        n.y = y;
        notches.push_back(n);
        yLabelValue = ((yLabelValue + step) * 10) / 10;
        nextY = nextY + step;
        y = ceil(nextY * sizeCoeff);
    }

    for (int i = 0; i < notches.size(); i++) {
        fl_font(fontFace, fontSize);
        fl_color(fontColor);
        fl_draw(notches[i].label.c_str(),
                chartHelper.chartRectLeft - notches[i].w,
                b_bottom - notches[i].h);
        fl_color(gridColor);
        fl_line_style(gridStyle, gridWidth, gridDashes);
        fl_line(chartHelper.chartRectLeft - 5, b_bottom - notches[i].y,
                chartHelper.chartRectRight, b_bottom - notches[i].y);
    }
}

void VertAxis::zoomByMouse()
{
    if (isFixed) return;

    double oldCoeff;
    int height1;
    int height2;

    if (sizeCoeff != 0) {
        oldCoeff = sizeCoeff;
        height1 = chartHelper.chartRectBottom - chartHelper.chartRectTop;
        height2 = chartHelper.chartRectTop;
        visibleMaximum = visibleMinimum + (height1 - mouseStartY + height2) / oldCoeff;
        visibleMinimum = visibleMinimum + (height1 - mouseNowY + height2) / oldCoeff;
    } else {
        axisShift = 0;
        // exception?
    }
}

void VertAxis::shiftByMouse()
{
    if (isFixed) return;

    if (sizeCoeff != 0) {
        axisShift = (mouseNowY - mouseStartY) / sizeCoeff;
    } else {
        axisShift = 0;
        // exception?
    }
    visibleMaximum = ((oldVisibleMaximum + axisShift) * 10) / 10;
    visibleMinimum = /*round*/((oldVisibleMinimum + axisShift) * 10) / 10;
}

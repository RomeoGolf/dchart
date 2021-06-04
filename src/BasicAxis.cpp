#include "BasicAxis.h"

#include <math.h>

#include <iostream>

BasicAxis::BasicAxis(ChartHelper &chartHelper) : chartHelper(chartHelper)
{
    //ctor
    minimum = 0;
    maximum = 10;
    visibleMinimum = minimum;
    visibleMaximum = maximum;
    seriesNum = 0;

}

BasicAxis::~BasicAxis()
{
    //dtor
}

void BasicAxis::unZoom()
{
    visibleMaximum = maximum;
    visibleMinimum = minimum;
}

void BasicAxis::setSizeCoeff()
{
    visibleUnitSize = visibleMaximum - visibleMinimum;
    if (fabs(visibleUnitSize) < 2.2250738585072014e-308) {
        sizeCoeff = 1;
    } else {
        sizeCoeff = pixelSize / visibleUnitSize;
    }
}

void BasicAxis::calcStartMarkUnit()
{
    if (fabs(step) > 2.2250738585072014e-308) {
        startMarkUnit = step - modf(visibleMinimum / step, nullptr) * step;
        startMarkUnit = /*round*/((modf(startMarkUnit / step, nullptr) * step) * 1) / 1;
    } else {
        startMarkUnit = 0;
    }
}

void BasicAxis::setVisible(bool value)
{
    isVisible = value;
}

bool BasicAxis::getVisible()
{
    return isVisible;
}

void BasicAxis::setAutoSize(bool value)
{
    isAutoSize = value;
}

bool BasicAxis::getAutoSize()
{
    return isAutoSize;
}

void BasicAxis::setAutoZoom(bool value)
{
    isAutoZoom = value;
}

bool BasicAxis::getAutoZoom()
{
    return isAutoZoom;
}

void BasicAxis::doAutoSize(double minVal, double maxVal)
{
    if (!getAutoSize()) return;
    if (seriesNum < 1) return;
    if (seriesNum == 1) {
        setMinimum(minVal);
        setMaximum(maxVal);
    } else {
        if (minVal < minimum) setMinimum(minVal);
        if (maxVal > maximum) setMaximum(maxVal);
    }
    if (getAutoZoom() & !chartHelper.isZoomed) {
        visibleMinimum = minimum;
        visibleMaximum = maximum;
    }
}


void BasicAxis::setMinimum(double value)
{
    minimum = value;
    if (maximum < minimum) {
        maximum = minimum + std::numeric_limits<double>::epsilon();
    }
}

double BasicAxis::getMinimum()
{
    return minimum;
}

void BasicAxis::setMaximum(double value)
{
    maximum = value;
    if (minimum > maximum) {
        minimum = maximum - std::numeric_limits<double>::epsilon();
    }
}

double BasicAxis::getMaximum()
{
    return maximum;
}


void BasicAxis::incSeriesNum()
{
    seriesNum++;
    //std::cout << " (++) series num = " << seriesNum << std::endl;
}

void BasicAxis::decSeriesNum()
{
    if (seriesNum > 0) seriesNum--;

}


int BasicAxis::getSeriesNum()
{
   return seriesNum;
}




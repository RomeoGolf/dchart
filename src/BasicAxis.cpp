#include "BasicAxis.h"

#include <math.h>

BasicAxis::BasicAxis(ChartHelper &chartHelper) : chartHelper(chartHelper)
{
    //ctor
    minimun = 0;
    maximum = 10;
    visibleMinimum = minimun;
    visibleMaximum = maximum;
}

BasicAxis::~BasicAxis()
{
    //dtor
}

void BasicAxis::unZoom()
{
    visibleMaximum = maximum;
    visibleMinimum = minimun;
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


#include "BasicAxis.h"

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


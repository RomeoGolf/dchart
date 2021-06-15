#include "BasicAxis.h"

#include <Fl/Fl_Draw.h>

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

    gridColor = FL_BLUE;
    gridDashes = nullptr;
    gridStyle = FL_DOT;
    gridWidth = 1;
    fontColor = FL_BLACK;
    fontSize = 14;
    fontFace = 0;

    isFixed = false;
    isAutoZoom = true;
    isAutoSize = true;
    isAutoStep = true;
    isVisible = true;
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
    if (fabs(visibleUnitSize) < std::numeric_limits<double>::epsilon()) {
        sizeCoeff = 1;
    } else {
        sizeCoeff = pixelSize / visibleUnitSize;
    }
}

void BasicAxis::calcStartMarkUnit()
{
    if (fabs(step) > std::numeric_limits<double>::epsilon()) {
        startMarkUnit = step - modf(visibleMinimum / step, nullptr) * step;
        startMarkUnit = ((modf(startMarkUnit / step, nullptr) * step) * 1) / 1;
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
    if (!getAutoSize() || getIsFixed()) return;
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
}

void BasicAxis::decSeriesNum()
{
    if (seriesNum > 0) seriesNum--;
}


int BasicAxis::getSeriesNum()
{
   return seriesNum;
}

void BasicAxis::setMouseStartX(int value)
{
    mouseStartX = value;
}

void BasicAxis::setMouseStartY(int value)
{
    mouseStartY = value;
}

void BasicAxis::setMouseNowX(int value)
{
    mouseNowX = value;
}

void BasicAxis::setMouseNowY(int value)
{
    mouseNowY = value;
}

double BasicAxis::getVisibleMaximum()
{
    return visibleMaximum;
}

double BasicAxis::getVisibleMinimum()
{
    return visibleMinimum;
}

void BasicAxis::setVisibleMaximum(double value)
{
    visibleMaximum = value;
}

void BasicAxis::setVisibleMinimum(double value)
{
    visibleMinimum = value;
}

void BasicAxis::setOldVisibleMaximum(double value)
{
    oldVisibleMaximum = value;
}

void BasicAxis::setOldVisibleMinimum(double value)
{
    oldVisibleMinimum = value;
}

double BasicAxis::getSizeCoeff()
{
    return sizeCoeff;
}

bool BasicAxis::getIsFixed()
{
    return isFixed;
}

void BasicAxis::setIsFixed(bool value)
{
    isFixed = value;
}

int BasicAxis::getFontSize()
{
    return fontSize;
}

Fl_Color BasicAxis::getGridColor()
{
    return gridColor;
}

Fl_Color BasicAxis::getFontColor()
{
    return fontColor;
}

void BasicAxis::setFontSize(int value)
{
    fontSize = value;
}

void BasicAxis::setGridColor(Fl_Color value)
{
    gridColor = value;
}

void BasicAxis::setFontColor(Fl_Color value)
{
    fontColor = value;
}

int BasicAxis::getGridStyle()
{
    return gridStyle;
}

void BasicAxis::setGridStyle(int value)
{
    gridStyle = value;
}

int BasicAxis::getGridWidth()
{
    return gridWidth;
}

void BasicAxis::setGridWidth(int value)
{
    gridWidth = value;
}

void BasicAxis::setGridDashes(char* const value)
{
    gridDashes = value;
}

int BasicAxis::getFontFace()
{
    return fontFace;
}

void BasicAxis::setFontFace(int value)
{
    fontFace = value;
}


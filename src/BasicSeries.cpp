#include "BasicSeries.h"



#include <math.h>
#include <iostream>
#include <algorithm>

BasicSeries::BasicSeries(ChartHelper &chartHelper) : chartHelper(chartHelper)
{
    //ctor
    minX = std::numeric_limits<double>::max();
    minY = std::numeric_limits<double>::max();
    maxX = -std::numeric_limits<double>::max();
    maxY = -std::numeric_limits<double>::max();
}

BasicSeries::~BasicSeries()
{
    //dtor
}

void BasicSeries::addXY(double x, double y)
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

int BasicSeries::getFloorIndexOfX(double x)
{
    if (x >= data.back().xValue)
        return data.size() - 1;
    if (x <= data.front().xValue)
        return 0;

    int xStart = 0;
    int xEnd = data.size() - 1;

    while ((xEnd - xStart) > 1) {
        int i = xStart + (xEnd - xStart) / 2;
        auto &item = data[i];
        if (item.xValue > x) {
            xEnd = i;
        } else {
            xStart = i;
        }
    }

    return xStart;
}

void BasicSeries::sortByX()
{
    std::sort(data.begin(), data.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
       return lhs.xValue < rhs.xValue;
    });
    isSorted = true;
}

void BasicSeries::setHorizAxis(std::shared_ptr<BasicAxis> value)
{
    this->horizAxis = value;
    horizAxis->incSeriesNum();
}

void BasicSeries::setVertAxis(std::shared_ptr<BasicAxis> value)
{
    this->vertAxis = value;
    this->vertAxis->incSeriesNum();
}

std::shared_ptr<BasicAxis> BasicSeries::getHorizAxis()
{
    return horizAxis;
}

std::shared_ptr<BasicAxis> BasicSeries::getVertAxis()
{
    return vertAxis;
}

double BasicSeries::getMaxX()
{
    return maxX;
}

double BasicSeries::getMaxY()
{
    return maxY;
}

double BasicSeries::getMinX()
{
    return minX;
}

double BasicSeries::getMinY()
{
    return minY;
}

std::string BasicSeries::getCaption()
{
    return caption;
}

Fl_Color BasicSeries::getColor()
{
    return color;
}

void BasicSeries::setCaption(std::string value)
{
    caption = value;
    onPropertyChangedSignal();
}

void BasicSeries::setColor(Fl_Color value)
{
    int colorIndex = chartHelper.getColorIndex(color);
    if (colorIndex >= 0 && chartHelper.colorIndicesUsing[colorIndex] > 0) {
        chartHelper.colorIndicesUsing[colorIndex]--;
    }
    color = value;
    colorIndex = chartHelper.getColorIndex(value);
    if (colorIndex >= 0) {
        chartHelper.colorIndicesUsing[colorIndex]++;
    }
    onPropertyChangedSignal();
}

void BasicSeries::registerOnPropertyChanged(std::function<void()>handler)
{
    onPropertyChangedSignal.connect(handler);
}




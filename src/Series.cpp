#include "Series.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <math.h>
#include <iostream>
#include <algorithm>

Series::Series(ChartHelper &chartHelper) : chartHelper(chartHelper)
{
    //ctor
    minX = std::numeric_limits<double>::max();
    minY = std::numeric_limits<double>::max();
    maxX = -std::numeric_limits<double>::max();
    maxY = -std::numeric_limits<double>::max();
}

Series::~Series()
{
    //dtor
}

void Series::addXY(double x, double y)
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

void Series::draw()
{
    fl_color(color);
    fl_line_style(0);

    fl_begin_line();

    int xStart = getFloorIndexOfX(horizAxis->getVisibleMinimum());
    int xEnd = getFloorIndexOfX(horizAxis->getVisibleMaximum());
    if (xEnd + 1 < data.size()) xEnd++;

    for (int i = xStart; i <= xEnd; i++) {
        double x = data[i].xValue - horizAxis->getVisibleMinimum();
        double y = data[i].yValue - vertAxis->getVisibleMinimum();

        int cx = ceil(x * horizAxis->getSizeCoeff()) + chartHelper.marginLeft;
        int cy = ceil(chartHelper.chartRectBottom - y * vertAxis->getSizeCoeff());

        fl_vertex(cx, cy);
    }

    fl_end_line();
}

int Series::getFloorIndexOfX(double x)
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

void Series::sortByX()
{
    std::sort(data.begin(), data.end( ), [ ]( const auto& lhs, const auto& rhs )
    {
       return lhs.xValue < rhs.xValue;
    });
    isSorted = true;
}

void Series::setHorizAxis(std::shared_ptr<BasicAxis> value)
{
    this->horizAxis = value;
    horizAxis->incSeriesNum();
}

void Series::setVertAxis(std::shared_ptr<BasicAxis> value)
{
    this->vertAxis = value;
    this->vertAxis->incSeriesNum();
}

std::shared_ptr<BasicAxis> Series::getHorizAxis()
{
    return horizAxis;
}

std::shared_ptr<BasicAxis> Series::getVertAxis()
{
    return vertAxis;
}

double Series::getMaxX()
{
    return maxX;
}

double Series::getMaxY()
{
    return maxY;
}

double Series::getMinX()
{
    return minX;
}

double Series::getMinY()
{
    return minY;
}

std::string Series::getCaption()
{
    return caption;
}

Fl_Color Series::getColor()
{
    return color;
}

void Series::setCaption(std::string value)
{
    caption = value;
    onPropertyChangedSignal();
}

void Series::setColor(Fl_Color value)
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

void Series::registerOnPropertyChanged(std::function<void()>handler)
{
    onPropertyChangedSignal.connect(handler);
}




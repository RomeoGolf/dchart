#include "Legend.h"

#include <Fl/fl_draw.h>

#include <iostream>

Legend::Legend(ChartHelper &chartHelper) : chartHelper(chartHelper)
{
    //ctor
    top = 5;
    left = 100;
    height = 30;
    width = 300;
    isVisible = true;
    fontSize = 16;
    fontFace = FL_HELVETICA_ITALIC;
    fontColor = FL_BLACK;
    backColor = FL_WHITE;

    sampleGap = 5;
    sampleLength = 10;
    sampleWidth = 3;
    itemGap = 15;
    margin = 10;
    isAutoSize = true;
    isAutoPosition = true;
}

Legend::~Legend()
{
    //dtor
}

void Legend::draw()
{
    if (!isVisible) return;
    if (legendData.empty()) return;

    fl_font(fontFace, fontSize);
    fl_draw_box(FL_ENGRAVED_BOX, left, top, width, height, backColor);

    int y = top + margin + fl_height() - fl_descent();
    for (int i = 0; i < legendData.size(); i++) {
        for (int j = 0; j < legendData[i].size(); j++) {
            int startX = left + margin + legendData[i][j].startX;
            fl_color(fontColor);
            fl_draw(legendData[i][j].caption.c_str(), startX + sampleLength + sampleGap, y);
            fl_color(legendData[i][j].color);
            fl_line_style(FL_SOLID, sampleWidth);
            fl_line(startX, y + fl_descent() - fl_height() / 2,
                    startX + sampleLength, y + fl_descent() - fl_height() / 2);
        }
        y += margin + fl_height() - fl_descent();
    }
}

void Legend::calcSize(std::vector<std::shared_ptr<BasicSeries>>& series)
{
    if (!isVisible) {
        return;
    }

    int widthLimit = chartHelper.chartRectRight - chartHelper.chartRectLeft;

    legendData.clear();
    legendData.push_back(std::vector<LegendData>());

    fl_font(fontFace, fontSize);
    int maxWidth = 0;
    int x = 0;
    std::string caption;

    for (int i = 0; i < series.size(); i++)
    {
        if (!series[i]->getCaption().empty())
        {
            caption = series[i]->getCaption();
        }
        else
        {
            caption = "NoName";
        }
        int item_width = fl_width(caption.c_str()) + sampleGap + itemGap + sampleLength;

        if ((x + item_width > widthLimit - (margin * 2) + 4) & isAutoSize)
            if (!legendData.back().empty())
            {
                x = 0;
                legendData.push_back(std::vector<LegendData>());
            }
        legendData.back().push_back(LegendData(x, series[i]->getColor(), series[i]->getCaption()));
        x += item_width;
        if (maxWidth < x) maxWidth = x;
    }

    if (isAutoSize)
    {
        width = maxWidth + margin * 2 - itemGap;
        height = (fl_height() - fl_descent() + margin ) * legendData.size() + margin;
    }

    chartHelper.legendHeight = height;

    if (isAutoPosition) {
        left = chartHelper.chartRectLeft + (widthLimit - width) / 2;
        if (chartHelper.isAutoMarginTop) {
            chartHelper.chartRectTop = top + height + chartHelper.marginTop;
        }
    }
}

void Legend::setTop(int value)
{
    top = value;
}

void Legend::setLeft(int value)
{
    left = value;
}

void Legend::setHeight(int value)
{
    height = value;
}

void Legend::setWidth(int value)
{
    width = value;
}

void Legend::setVisible(bool value)
{
    isVisible = value;
}

void Legend::setFontSize(int value)
{
    fontSize = value;
}

void Legend::setSampleGap(int value)
{
    sampleGap = value;
}

void Legend::setSampleLength(int value)
{
    sampleLength = value;
}

void Legend::setSampleWidth(int value)
{
    sampleWidth = value;
}

void Legend::setItemGap(int value)
{
    itemGap = value;
}

void Legend::setMargin(int value)
{
    margin = value;
}

void Legend::setAutoSize(bool value)
{
    isAutoSize = value;
}

void Legend::setAutoPosition(bool value)
{
    isAutoPosition = value;
}

int Legend::getTop()
{
    return top;
}

int Legend::getLeft()
{
    return left;
}

int Legend::getHeight()
{
    return height;
}

int Legend::getWidth()
{
    return width;
}

bool Legend::getVisible()
{
    return isVisible;
}

int Legend::getFontSize()
{
    return fontSize;
}

int Legend::getSampleGap()
{
    return sampleGap;
}

int Legend::getSampleLength()
{
    return sampleLength;
}

int Legend::getSampleWidth()
{
    return sampleWidth;
}

int Legend::getItemGap()
{
    return itemGap;
}

int Legend::getMargin()
{
    return margin;
}

bool Legend::getAutoSize()
{
    return isAutoSize;
}

bool Legend::getAutoPosition()
{
    return isAutoPosition;
}

void Legend::setFontColor(Fl_Color value)
{
    fontColor = value;
}

void Legend::setFontFace(int value)
{
    fontFace = value;
}

Fl_Color Legend::getFontColor()
{
    return fontColor;
}

int Legend::getFontFace()
{
    return fontFace;
}

void Legend::setBackColor(Fl_Color value)
{
    backColor = value;
}

Fl_Color Legend::getBackColor()
{
    return backColor;
}


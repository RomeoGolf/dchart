#include "Legend.h"

#include <Fl/fl_draw.h>

#include <iostream>

Legend::Legend(ChartHelper &chartHelper) : chartHelper(chartHelper)
{
    //ctor
    top = 5;
    left = 100;
    height = 40;
    width = 500;
    isVisible = true;
    fontSize = 16;

    sampleGap = 5;
    sampleLength = 10;
    sampleWidth = 3;
    itemGap = 15;
    margin = 15;
}

Legend::~Legend()
{
    //dtor
}

void Legend::draw()
{
    if (!isVisible) return;
    if (legendData.empty()) return;

    fl_font(2, fontSize);
    fl_draw_box(FL_ENGRAVED_BOX, left, top, width, height, FL_BACKGROUND_COLOR);

    int y = top + margin + fl_height() - fl_descent();
    for (int i = 0; i < legendData.size(); i++) {
        for (int j = 0; j < legendData[i].size(); j++) {
            int startX = left + margin + legendData[i][j].startX;
            fl_color(FL_BLACK);
            fl_draw(legendData[i][j].caption.c_str(), startX + sampleLength + sampleGap, y);
            //std::cout << "[legend draw] caption: " << legendData[i][j].caption
            //    << " x: " << legendData[i][j].startX << std::endl;
            fl_color(legendData[i][j].color);
            fl_line_style(FL_SOLID, sampleWidth);
            fl_line(startX, y + fl_descent() - fl_height() / 2,
                    startX + sampleLength, y + fl_descent() - fl_height() / 2);
            //fl_line(startX , y + fl_descent() - fl_height() / 2 + 5,
            //        startX + sampleLength + sampleGap + itemGap + fl_width("Series_3"), y + fl_descent() - fl_height() / 2 + 5);

        }
        y += margin + fl_height() - fl_descent();
    }
}

void Legend::calcSize(std::vector<std::unique_ptr<Series>>& series)
{
    if (!isVisible) {
        return;
    }
    legendData.clear();
    legendData.push_back(std::vector<LegendData>());

    fl_font(2, fontSize);

    int widthLimit = chartHelper.chartRectRight - chartHelper.chartRectLeft;
    int maxWidth = 0;
    int x = 0;
    std::string caption;

    for (int i = 0; i < series.size(); i++) {
        if (!series[i]->caption.empty()) {
            caption = series[i]->caption;
        } else {
            caption = "NoName";
        }
        int item_width = fl_width(caption.c_str()) + sampleGap + itemGap + sampleLength;

        if (x + item_width > widthLimit - (margin * 2) + 4)
            if (!legendData.back().empty()) {
            x = 0;
            legendData.push_back(std::vector<LegendData>());
            }
        legendData.back().push_back(LegendData(x, series[i]->color, series[i]->caption));
        x += item_width;
        if (maxWidth < x) maxWidth = x;
    }

    width = maxWidth + margin * 2 - itemGap;
    height = (fl_height() - fl_descent() + margin ) * legendData.size() + margin;
    left = chartHelper.chartRectLeft + (widthLimit - width) / 2;
    chartHelper.legendHeight = height;
    if (chartHelper.isAutoMarginTop) {
        chartHelper.chartRectTop = top + height + chartHelper.marginTop;
    }
}



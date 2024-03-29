#include "DChartBase.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include <iostream>

DChartBase::DChartBase(int x, int y, int w, int h, const char *label) :
    Fl_Widget(x,y,w,h,label), legend(chartHelper)
{
    //ctor
    chartHelper.marginTop = 10;
    chartHelper.marginBottom = 50;
    chartHelper.marginLeft = 70;
    chartHelper.marginRight = 20;
    chartHelper.isAutoMarginTop = true;
    chartHelper.isAutoMarginLeft = true;
    chartHelper.isAutoMarginBottom = true;

    needWidgetBorder = true;
    needChartBorder = true;

    horizAxes.push_back(std::make_shared<HorizAxis>(this->chartHelper));
    vertAxes.push_back(std::make_shared<VertAxis>(this->chartHelper));
}

DChartBase::~DChartBase()
{
    //dtor
}

void DChartBase::draw()
{
    Fl_Offscreen oscr = fl_create_offscreen(w(), h());
    {
        fl_begin_offscreen(oscr);

        if (chartHelper.isAutoMarginLeft) {
            int leftSpace = 0;
            std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
            for (axisItem = vertAxes.begin(); axisItem != vertAxes.end(); ++axisItem) {
                if ((*axisItem)->getVisible()) {
                    (*axisItem)->prepareNotches();
                    leftSpace += (*axisItem)->getFieldThickness();
                }
            }
            chartHelper.chartRectLeft = leftSpace;
        }

        if (chartHelper.isAutoMarginBottom) {
            int bottomSpace = 0;
            std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
            for (axisItem = horizAxes.begin(); axisItem != horizAxes.end(); ++axisItem) {
                if ((*axisItem)->getVisible()) {
                    (*axisItem)->prepareNotches();
                    bottomSpace += (*axisItem)->getFieldThickness();
                }
            }
            chartHelper.chartRectBottom = h() - bottomSpace;
        }

        drawWidgetBorder();
        drawChartBorder();
        draw_label();

        int delta = 0;
        std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
        for (axisItem = vertAxes.begin(); axisItem != vertAxes.end(); ++axisItem) {
            if ((*axisItem)->getVisible()) {
                (*axisItem)->prepareNotches();
                (*axisItem)->draw(delta);
                delta += (*axisItem)->getFieldThickness();
            }
        }

        delta = 0;
        for (axisItem = horizAxes.begin(); axisItem != horizAxes.end(); ++axisItem) {
            if ((*axisItem)->getVisible()) {
                (*axisItem)->prepareNotches();
                (*axisItem)->draw(delta);
                delta += (*axisItem)->getFieldThickness();
            }
        }

        if(isZoom) {
            drawZoomRect();
        }

        std::vector<std::shared_ptr<BasicSeries>>::const_iterator item;
        for (item = series.begin(); item != series.end(); ++item) {
            (*item)->draw();
        }

        legend.draw();

        fl_end_offscreen();

        fl_copy_offscreen(x(), y(), w(), h(), oscr, 0, 0);
    }
    fl_delete_offscreen(oscr);
}

void DChartBase::test()
{
    std::string s = "Икс -> " + std::to_string(mouseStartX);
    fl_draw(s.data(), 15, this->x() + 30, this->y() + 50);

    fl_color(FL_BLUE);
    fl_line_style(FL_DASH, 2, 0);

    fl_begin_line();
    fl_vertex(50.3, 200);
    fl_vertex(150, 150);
    fl_vertex(70, 80);
    fl_vertex(170, 70);
    fl_end_line();
}

void DChartBase::drawZoomRect()
{
    fl_color(FL_BLACK);
    fl_line_style(FL_DASH, 1, 0);
    if ((zoomX >= mouseStartX) && (zoomY >= mouseStartY))
    {
        fl_rect(mouseStartX, mouseStartY, zoomX - mouseStartX, zoomY - mouseStartY);
    }
    if ((zoomX < mouseStartX) && (zoomY < mouseStartY))
    {
        fl_rect(zoomX, zoomY, mouseStartX - zoomX, mouseStartY - zoomY);
    }

    fl_line_style(0);

}

int DChartBase::handle(int event)
{
    mouseNowX = Fl::event_x() - x();
    mouseNowY = Fl::event_y() - y();
    switch (event)
    {
    case FL_PUSH :
        mouseStartX = Fl::event_x() - x();
        mouseStartY = Fl::event_y() - y();

        {
            std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
            for (axisItem = vertAxes.begin(); axisItem != vertAxes.end(); ++axisItem)
            {
                (*axisItem)->setMouseStartX(mouseStartX);
                (*axisItem)->setMouseStartY(mouseStartY);
            }
            for (axisItem = horizAxes.begin(); axisItem != horizAxes.end(); ++axisItem)
            {
                (*axisItem)->setMouseStartX(mouseStartX);
                (*axisItem)->setMouseStartY(mouseStartY);
            }
        }

        switch (Fl::event_button())
        {
            case FL_LEFT_MOUSE :
                isZoom = true;
                break;
            case FL_RIGHT_MOUSE :
                {
                    std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
                    for (axisItem = vertAxes.begin(); axisItem != vertAxes.end(); ++axisItem)
                    {
                        (*axisItem)->setOldVisibleMaximum((*axisItem)->getVisibleMaximum());
                        (*axisItem)->setOldVisibleMinimum((*axisItem)->getVisibleMinimum());
                    }
                    for (axisItem = horizAxes.begin(); axisItem != horizAxes.end(); ++axisItem)
                    {
                        (*axisItem)->setOldVisibleMaximum((*axisItem)->getVisibleMaximum());
                        (*axisItem)->setOldVisibleMinimum((*axisItem)->getVisibleMinimum());
                    }
                }

                isRightMouseButtonDown = true;
            break;
        }
        return 1;
    case FL_RELEASE :
        switch (Fl::event_button())
        {
            case FL_LEFT_MOUSE :
                isZoom = false;
                if ((mouseStartX > mouseNowX) && (mouseStartY > mouseNowY)) {
                    unZoom();
                }
                if ((mouseStartX < mouseNowX) && (mouseStartY < mouseNowY)) {
                    // zoom
                    if ((mouseNowX - mouseStartX < 25)
                        && (mouseNowY - mouseStartY < 25)) {
                        redraw();
                        break;
                    }
                    {
                        std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
                        for (axisItem = vertAxes.begin(); axisItem != vertAxes.end(); ++axisItem)
                        {
                            (*axisItem)->setMouseNowX(mouseNowX);
                            (*axisItem)->setMouseNowY(mouseNowY);
                            (*axisItem)->zoomByMouse();
                        }
                        for (axisItem = horizAxes.begin(); axisItem != horizAxes.end(); ++axisItem)
                        {
                            (*axisItem)->setMouseNowX(mouseNowX);
                            (*axisItem)->setMouseNowY(mouseNowY);
                            (*axisItem)->zoomByMouse();
                        }
                    }
                    chartHelper.isZoomed = true;
                }
                redraw();
                break;
            case FL_RIGHT_MOUSE :
                isRightMouseButtonDown = false;
                break;
        }
        return 1;
    case FL_DRAG :
        zoomX = mouseNowX;
        zoomY = mouseNowY;
        if (isZoom) {
            redraw();
        }
        if (isRightMouseButtonDown) {
            {
                std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
                for (axisItem = vertAxes.begin(); axisItem != vertAxes.end(); ++axisItem)
                {
                    (*axisItem)->setMouseNowX(mouseNowX);
                    (*axisItem)->setMouseNowY(mouseNowY);
                    (*axisItem)->shiftByMouse();
                }
                for (axisItem = horizAxes.begin(); axisItem != horizAxes.end(); ++axisItem)
                {
                    (*axisItem)->setMouseNowX(mouseNowX);
                    (*axisItem)->setMouseNowY(mouseNowY);
                    (*axisItem)->shiftByMouse();
                }
            }
            redraw();
        }
        return 1;
    default :
        return Fl_Widget::handle(event);
    }
}

void DChartBase::drawWidgetBorder()
{
    if (needWidgetBorder) {
        fl_draw_box(FL_ENGRAVED_BOX, 0, 0, w(), h(),
                 FL_BACKGROUND_COLOR);
    }
}

void DChartBase::drawChartBorder()
{
    if (needChartBorder) {
        fl_draw_box(FL_EMBOSSED_BOX,
                    chartHelper.chartRectLeft,
                    chartHelper.chartRectTop,
                    chartHelper.chartRectRight - chartHelper.chartRectLeft,
                    chartHelper.chartRectBottom - chartHelper.chartRectTop,
                    FL_BACKGROUND_COLOR);
    }
}

void DChartBase::addLineSeries()
{
    series.push_back(std::make_shared<LineSeries>(chartHelper));

    series.back()->setHorizAxis(horizAxes[0]);
    series.back()->setVertAxis(vertAxes[0]);

    series.back()->setCaption("Series_" + std::to_string(series.size()));
    int colorIndex = chartHelper.getRarestColorIndex();
    series.back()->setColor(ChartHelper::colors[colorIndex]);

    setChartRectSize(w(), h());
    legend.calcSize(series);
    series.back()->registerOnPropertyChanged([this](){return onSeriesPropertyChanged();});
}

void DChartBase::unZoom()
{
    std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
    for (axisItem = vertAxes.begin(); axisItem != vertAxes.end(); ++axisItem)
    {
        (*axisItem)->unZoom();
    }
    for (axisItem = horizAxes.begin(); axisItem != horizAxes.end(); ++axisItem)
    {
        (*axisItem)->unZoom();
    }
    chartHelper.isZoomed = false;
}

void DChartBase::resize(int x, int y, int w, int h)
{
    Fl_Widget::resize(x, y, w, h);
    setChartRectSize(w, h);
    legend.calcSize(series);
}

void DChartBase::setChartRectSize(int w, int h)
{
    if (chartHelper.isAutoMarginLeft) {
        int leftSpace = 0;
        std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
        for (axisItem = vertAxes.begin(); axisItem != vertAxes.end(); ++axisItem) {
            if ((*axisItem)->getVisible()) {
                (*axisItem)->prepareNotches();
                leftSpace += (*axisItem)->getFieldThickness();
            }
        }
        chartHelper.chartRectLeft = leftSpace;
    } else {
        chartHelper.chartRectLeft = chartHelper.marginLeft;
    }

    if (chartHelper.isAutoMarginBottom) {
        int bottomSpace = 0;
        std::vector<std::shared_ptr<BasicAxis>>::const_iterator axisItem;
        for (axisItem = horizAxes.begin(); axisItem != horizAxes.end(); ++axisItem) {
            if ((*axisItem)->getVisible()) {
                (*axisItem)->prepareNotches();
                bottomSpace += (*axisItem)->getFieldThickness();
            }
        }
        chartHelper.chartRectBottom = h - bottomSpace;
    } else {
        chartHelper.chartRectBottom = h - chartHelper.marginBottom;
    }

    chartHelper.chartRectTop = chartHelper.marginTop;
    chartHelper.chartRectRight = w - chartHelper.marginRight;
}

void DChartBase::onSeriesPropertyChanged()
{
    setChartRectSize(w(), h());
    legend.calcSize(series);
}

void DChartBase::addVertAxis()
{
    vertAxes.push_back(std::make_shared<VertAxis>(this->chartHelper));
}

void DChartBase::addHorizAxis()
{
    horizAxes.push_back(std::make_shared<HorizAxis>(this->chartHelper));
}


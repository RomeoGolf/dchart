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

    needWidgetBorder = true;
    needChartBorder = true;

    defaultHorizAxis = std::make_shared<HorizAxis>(this->chartHelper);
    defaultVertAxis = std::make_shared<VertAxis>(this->chartHelper);

    defaultHorizAxis->setVisible(true);
    defaultVertAxis->setVisible(true);

    defaultHorizAxis->setAutoSize(true);
    defaultVertAxis->setAutoSize(true);
    defaultHorizAxis->setAutoZoom(true);
    defaultVertAxis->setAutoZoom(true);
}

DChartBase::~DChartBase()
{
    //dtor
}

void DChartBase::draw()
{
    //chartHelper.chartRectTop = chartHelper.marginTop;
    //chartHelper.chartRectBottom = h() - chartHelper.marginBottom;
    //chartHelper.chartRectLeft = chartHelper.marginLeft;
    //chartHelper.chartRectRight = w() - chartHelper.marginRight;

    Fl_Offscreen oscr = fl_create_offscreen(w(), h());
    {
        fl_begin_offscreen(oscr);

        drawWidgetBorder();
        drawChartBorder();
        draw_label();

        defaultHorizAxis->draw();
        defaultVertAxis->draw();

        if(isZoom) {
            drawZoomRect();
        }

        std::vector<std::unique_ptr<Series>>::const_iterator item;
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
    //std::string s = "Икс -> " + std::to_string(this->x());
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

        defaultHorizAxis->setMouseStartX(mouseStartX);
        defaultHorizAxis->setMouseStartY(mouseStartY);
        defaultVertAxis->setMouseStartX(mouseStartX);
        defaultVertAxis->setMouseStartY(mouseStartY);

        switch (Fl::event_button())
        {
            case FL_LEFT_MOUSE :
                isZoom = true;
                break;
            case FL_RIGHT_MOUSE :
                defaultHorizAxis->setOldVisibleMaximum(defaultHorizAxis->getVisibleMaximum());
                defaultHorizAxis->setOldVisibleMinimum(defaultHorizAxis->getVisibleMinimum());
                defaultVertAxis->setOldVisibleMaximum(defaultVertAxis->getVisibleMaximum());
                defaultVertAxis->setOldVisibleMinimum(defaultVertAxis->getVisibleMinimum());
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
                    defaultHorizAxis->setMouseNowX(mouseNowX);
                    defaultHorizAxis->setMouseNowY(mouseNowY);
                    defaultHorizAxis->zoomByMouse();

                    defaultVertAxis->setMouseNowX(mouseNowX);
                    defaultVertAxis->setMouseNowY(mouseNowY);
                    defaultVertAxis->zoomByMouse();

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
            defaultHorizAxis->setMouseNowX(mouseNowX);
            defaultHorizAxis->setMouseNowY(mouseNowY);
            defaultHorizAxis->shiftByMouse();

            defaultVertAxis->setMouseNowX(mouseNowX);
            defaultVertAxis->setMouseNowY(mouseNowY);
            defaultVertAxis->shiftByMouse();
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
                    /*x() + chartHelper.marginLeft,
                    y() + chartHelper.marginTop,
                    w() - chartHelper.marginRight - chartHelper.marginLeft,
                    h() - chartHelper.marginBottom - chartHelper.marginTop,*/
                    chartHelper.chartRectLeft,
                    chartHelper.chartRectTop,
                    chartHelper.chartRectRight - chartHelper.chartRectLeft,
                    chartHelper.chartRectBottom - chartHelper.chartRectTop,
                 FL_BACKGROUND_COLOR);
    }

}

/*void DChartBase::addSeries(Series* s)
{
    series = s;
    s->horizAxis = defaultHorizAxis;
    s->vertAxis = defaultVertAxis;
}*/

void DChartBase::addSeries()
{
    series.push_back(std::make_unique<Series>(chartHelper));
    series.back()->setHorizAxis(defaultHorizAxis);
    series.back()->setVertAxis(defaultVertAxis);
    series.back()->setCaption("Series_" + std::to_string(series.size()));
    int colorIndex = chartHelper.getRarestColorIndex();
    series.back()->setColor(ChartHelper::colors[colorIndex]);
    //chartHelper.colorIndicesUsing[colorIndex]++;

    setChartRectSize(w(), h());
    legend.calcSize(series);
    series.back()->registerOnPropertyChanged([this](){return onSeriesPropertyChanged();});
}

void DChartBase::unZoom()
{
    defaultHorizAxis->unZoom();
    defaultVertAxis->unZoom();
    chartHelper.isZoomed = false;
}

void DChartBase::resize(int x, int y, int w, int h)
{
    //std::cout << "[resize before] w " << this->w() << std::endl;
    Fl_Widget::resize(x, y, w, h);
    //std::cout << "[resize after] w " << this->w() << std::endl;

    setChartRectSize(w, h);
    legend.calcSize(series);
}

void DChartBase::setChartRectSize(int w, int h)
{
    chartHelper.chartRectTop = chartHelper.marginTop;
    chartHelper.chartRectBottom = h - chartHelper.marginBottom;
    chartHelper.chartRectLeft = chartHelper.marginLeft;
    chartHelper.chartRectRight = w - chartHelper.marginRight;
}

void DChartBase::onSeriesPropertyChanged()
{
    setChartRectSize(w(), h());
    legend.calcSize(series);
}


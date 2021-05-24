#include "DChartBase.h"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <string>
#include <iostream>

DChartBase::DChartBase(int x, int y, int w, int h, const char *label) :
    Fl_Widget(x,y,w,h,label)
{
    //ctor

    chartHelper.marginTop = 40;
    chartHelper.marginBottom = 50;
    chartHelper.marginLeft = 70;
    chartHelper.marginRight = 20;

    needWidgetBorder = true;
    needChartBorder = true;

    defaultHorizAxis = std::make_unique<HorizAxis>(this->chartHelper);
}

DChartBase::~DChartBase()
{
    //dtor
}

void DChartBase::draw()
{
    chartHelper.chartRectTop = chartHelper.marginTop;
    chartHelper.chartRectBottom = h() - chartHelper.marginBottom;
    chartHelper.chartRectLeft = chartHelper.marginLeft;
    chartHelper.chartRectRight = w() - chartHelper.marginRight;

    Fl_Offscreen oscr = fl_create_offscreen(w(), h());
    {
        fl_begin_offscreen(oscr);
        drawWidgetBorder();
        drawChartBorder();
        draw_label();

        defaultHorizAxis->draw();

        if(isZoom)
            drawZoomRect();
        series->draw();
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
    fl_rect(mouseStartX, mouseStartY, zoomX - mouseStartX, zoomY - mouseStartY);
    fl_line_style(0);

}

int DChartBase::handle(int event)
{
    switch (event)
    {
    case FL_PUSH :
        mouseStartX = Fl::event_x() - x();
        mouseNowX = Fl::event_x() - x();
        mouseStartY = Fl::event_y() - y();
        mouseNowY = Fl::event_y() - y();

        switch (Fl::event_button())
        {
            case FL_LEFT_MOUSE :
                isZoom = true;
                break;
            case FL_RIGHT_MOUSE :
                isRightMouseButtonDown = true;
                break;
        }
        return 1;
    case FL_RELEASE :
        switch (Fl::event_button())
        {
            case FL_LEFT_MOUSE :
                isZoom = false;
                redraw();
                break;
            case FL_RIGHT_MOUSE :
                isRightMouseButtonDown = false;
                break;
        }
        return 1;
    case FL_DRAG :
        if (isZoom) {
            zoomX = Fl::event_x() - x();
            zoomY = Fl::event_y() - y();
            redraw();
            mouseNowX = zoomX;
            mouseNowY = zoomY;
            return 1;
        }
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
                    /*x() +*/ chartHelper.marginLeft,
                    /*y() +*/ chartHelper.marginTop,
                    w() - chartHelper.marginRight - chartHelper.marginLeft,
                    h() - chartHelper.marginBottom - chartHelper.marginTop,
                 FL_BACKGROUND_COLOR);
    }

}

void DChartBase::addSeries(Series* s)
{
    series = s;
}




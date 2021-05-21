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
    chartHelper.marginBottom = 10;
    chartHelper.marginLeft = 20;
    chartHelper.marginRight = 20;

    needWidgetBorder = true;
    needChartBorder = true;
}

DChartBase::~DChartBase()
{
    //dtor
}

void DChartBase::draw()
{
    chartHelper.chartRectTop = y() + chartHelper.marginTop;
    chartHelper.chartRectBottom = y() + h() - chartHelper.marginBottom;
    chartHelper.chartRectLeft = x() + chartHelper.marginLeft;
    chartHelper.chartRectRight = x() + w() - chartHelper.marginRight;

    drawWidgetBorder();
    drawChartBorder();
    draw_label();
    test();
    drawZoomRect();
    series->draw();
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
        mouseStartX = Fl::event_x();
        mouseNowX = Fl::event_x();
        mouseStartY = Fl::event_y();
        mouseNowY = Fl::event_y();

        switch (Fl::event_button())
        {
            case FL_LEFT_MOUSE :
                isZoom = true;
            case FL_RIGHT_MOUSE :
                isRightMouseButtonDown = true;
        }
        return 1;
    case FL_RELEASE :
        isRightMouseButtonDown = false;
        return 1;
    case FL_DRAG :
        if (isZoom) {
            zoomX = mouseNowX;
            zoomY = mouseNowY;
            redraw();

            zoomX = Fl::event_x();
            zoomY = Fl::event_y();
            redraw();

            mouseNowX = zoomX;
            mouseNowY = zoomY;

            std::cout << zoomX << " " << mouseStartX << '\n';
        }

    default :
        return Fl_Widget::handle(event);
    }
}

void DChartBase::drawWidgetBorder()
{
    if (needWidgetBorder) {
        fl_draw_box(FL_ENGRAVED_BOX, this->x(), this->y(), this->w(), this->h(),
                 FL_BACKGROUND_COLOR);
    }
}

void DChartBase::drawChartBorder()
{
    if (needChartBorder) {
        fl_draw_box(FL_EMBOSSED_BOX,
                    x() + chartHelper.marginLeft,
                    y() + chartHelper.marginTop,
                    w() - chartHelper.marginRight - chartHelper.marginLeft,
                    h() - chartHelper.marginBottom - chartHelper.marginTop,
                 FL_BACKGROUND_COLOR);
    }

}

void DChartBase::addSeries(Series* s)
{
    series = s;
}




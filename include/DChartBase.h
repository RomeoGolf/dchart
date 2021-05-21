#ifndef DCHARTBASE_H
#define DCHARTBASE_H

#include <FL/Fl_Widget.H>
#include <Series.h>

#include "ChartHelper.h"

class DChartBase : public Fl_Widget
{
    public:
        DChartBase(int x, int y, int w, int h, const char *label);
        virtual ~DChartBase();

        ChartHelper chartHelper;

        void test();
        void drawZoomRect();

        int mouseStartX;
        int mouseStartY;
        int mouseNowX;
        int mouseNowY;
        bool isZoom;
        bool isRightMouseButtonDown;

        bool needWidgetBorder;
        bool needChartBorder;
        void drawWidgetBorder();
        void drawChartBorder();

        Series *series;
        void addSeries(Series *s);


        virtual int handle(int event) override;

    protected:
        void draw();


    private:
        int zoomX;
        int zoomY;
};

#endif // DCHARTBASE_H

#ifndef DCHARTBASE_H
#define DCHARTBASE_H

#include <FL/Fl_Widget.H>
#include <BasicSeries.h>
#include <LineSeries.h>
#include <BasicAxis.h>
#include <HorizAxis.h>
#include <VertAxis.h>
#include <Legend.h>

#include "ChartHelper.h"
#include <memory>

class DChartBase : public Fl_Widget
{
    public:
        DChartBase(int x, int y, int w, int h, const char *label);
        virtual ~DChartBase();

        void test();
        void drawZoomRect();

        void drawWidgetBorder();
        void drawChartBorder();
        void unZoom();

        std::vector<std::shared_ptr<BasicSeries>> series;
        void addLineSeries();

        std::vector<std::shared_ptr <BasicAxis>> horizAxes;
        std::vector<std::shared_ptr <BasicAxis>> vertAxes;

        void addVertAxis();
        void addHorizAxis();

        virtual int handle(int event) override;
        virtual void resize(int x, int y, int w, int h) override;

    protected:
        void draw();

    private:
        int zoomX;
        int zoomY;

        int mouseStartX;
        int mouseStartY;
        int mouseNowX;
        int mouseNowY;

        bool isZoom;
        bool isRightMouseButtonDown;

        bool needWidgetBorder;
        bool needChartBorder;

        ChartHelper chartHelper;
        Legend legend;

        void setChartRectSize(int w, int h);
        void onSeriesPropertyChanged();
};

#endif // DCHARTBASE_H

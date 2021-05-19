#ifndef DCHARTBASE_H
#define DCHARTBASE_H

#include <FL/Fl_Widget.H>

class DChartBase : public Fl_Widget
{
    public:
        DChartBase(int x, int y, int w, int h, const char *label);
        virtual ~DChartBase();

        void test();
        void drawZoomRect();

        int mouseStartX;
        int mouseStartY;
        int mouseNowX;
        int mouseNowY;
        bool isZoom;
        bool isRightMouseButtonDown;

        virtual int handle(int event);

    protected:
        void draw();


    private:
        int zoomX;
        int zoomY;
};

#endif // DCHARTBASE_H

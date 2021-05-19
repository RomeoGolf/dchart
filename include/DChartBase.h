#ifndef DCHARTBASE_H
#define DCHARTBASE_H

//#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

class DChartBase : public Fl_Widget
{
    public:
        DChartBase(int x, int y, int w, int h, const char *label);
        virtual ~DChartBase();

        void test();
        void drawZoomRect();

    protected:
        void draw();

    private:
};

#endif // DCHARTBASE_H

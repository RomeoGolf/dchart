#ifndef VERTAXIS_H
#define VERTAXIS_H

#include <BasicAxis.h>


class VertAxis : public BasicAxis
{
    public:
        VertAxis(ChartHelper &chartHelper);
        virtual ~VertAxis();

        void draw() override;
        void zoomByMouse() override;
        void shiftByMouse() override;
        void calcStep();

    protected:

    private:
};

#endif // VERTAXIS_H

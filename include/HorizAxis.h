#ifndef HORIZAXIS_H
#define HORIZAXIS_H

#include <BasicAxis.h>


class HorizAxis : public BasicAxis
{
    public:
        HorizAxis(ChartHelper &chartHelper);
        virtual ~HorizAxis();

        void draw(int delta) override;
        void zoomByMouse() override;
        void shiftByMouse() override;
        void calcStep();
        virtual void prepareNotches() override;

    protected:
        void calcThickness();

    private:
};

#endif // HORIZAXIS_H

#ifndef HORIZAXIS_H
#define HORIZAXIS_H

#include <BasicAxis.h>


class HorizAxis : public BasicAxis
{
    public:
        HorizAxis(ChartHelper &chartHelper);
        virtual ~HorizAxis();

        void draw() override;
        void calcStep();

    protected:

    private:
};

#endif // HORIZAXIS_H

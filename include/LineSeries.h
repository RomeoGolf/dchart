#ifndef LINESERIES_H
#define LINESERIES_H

#include <BasicSeries.h>


class LineSeries : public BasicSeries
{
    public:
        LineSeries(ChartHelper &chartHelper);
        virtual ~LineSeries();

        virtual void draw() override;


    protected:

    private:
};

#endif // LINESERIES_H

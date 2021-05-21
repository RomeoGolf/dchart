#ifndef SERIES_H
#define SERIES_H

#include <vector>

#include "ChartHelper.h"

template<typename T> struct SeriesData
{
    double xValue;
    T yValue;
    SeriesData(double x, T y) : xValue(x), yValue(y) {}
};

class Series
{
    public:
        Series(ChartHelper &chartHelper);
        virtual ~Series();

        std::vector<SeriesData<double>> data;

        void addXY(double x, double y);
        void draw();

    protected:

    private:
        ChartHelper &chartHelper;
};

#endif // SERIES_H

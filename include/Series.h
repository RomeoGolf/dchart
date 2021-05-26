#ifndef SERIES_H
#define SERIES_H

#include <vector>
#include <memory>

#include "ChartHelper.h"
#include "BasicAxis.h"

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
        std::shared_ptr <BasicAxis> horizAxis;
        std::shared_ptr <BasicAxis> vertAxis;

        void addXY(double x, double y);
        void draw();
        int getFloorIndexOfX(double x);

    protected:

    private:
        ChartHelper &chartHelper;
};

#endif // SERIES_H

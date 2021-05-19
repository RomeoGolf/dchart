#ifndef SERIES_H
#define SERIES_H

#include <vector>

template<typename T> struct SeriesData
{
    double xValue;
    T yValue;
    SeriesData(double x, T y) : xValue(x), yValue(y) {}
};

class Series
{
    public:
        Series();
        virtual ~Series();

        std::vector<SeriesData<double>*> data;

        void addXY(double x, double y);
        void draw();

    protected:

    private:
};

#endif // SERIES_H

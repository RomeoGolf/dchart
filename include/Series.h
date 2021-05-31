#ifndef SERIES_H
#define SERIES_H

#include <Fl/Enumerations.h>

#include <vector>
#include <memory>
#include <string>

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
        void setHorizAxis(std::shared_ptr <BasicAxis> value);
        void setVertAxis(std::shared_ptr <BasicAxis> value);

        std::shared_ptr<BasicAxis> getHorizAxis();
        std::shared_ptr<BasicAxis> getVertAxis();

        void addXY(double x, double y);
        void draw();
        int getFloorIndexOfX(double x);
        void sortByX();
        double getMaxX();
        double getMaxY();
        double getMinX();
        double getMinY();
        //void setColor(Fl_Color color);

        std::string caption;
        Fl_Color color;

    protected:
        std::shared_ptr <BasicAxis> horizAxis;
        std::shared_ptr <BasicAxis> vertAxis;
        bool isSorted;
        double maxX;
        double minX;
        double maxY;
        double minY;

    private:
        ChartHelper &chartHelper;
};

#endif // SERIES_H

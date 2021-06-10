#ifndef SERIES_H
#define SERIES_H

#include <Fl/Enumerations.h>

#include <vector>
#include <memory>
#include <string>
#include <functional>

#include "ChartHelper.h"
#include "BasicAxis.h"

#include "boost/signals2.hpp"

template<typename T> struct SeriesData
{
    double xValue;
    T yValue;
    SeriesData(double x, T y) : xValue(x), yValue(y) {}
};

class BasicSeries
{
    public:
        BasicSeries(ChartHelper &chartHelper);
        virtual ~BasicSeries();

        virtual void draw() = 0;

        std::vector<SeriesData<double>> data;
        void setHorizAxis(std::shared_ptr <BasicAxis> value);
        void setVertAxis(std::shared_ptr <BasicAxis> value);

        std::shared_ptr<BasicAxis> getHorizAxis();
        std::shared_ptr<BasicAxis> getVertAxis();

        int getFloorIndexOfX(double x);
        void sortByX();
        double getMaxX();
        double getMaxY();
        double getMinX();
        double getMinY();

        std::string getCaption();
        Fl_Color getColor();
        void setCaption(std::string value);
        void setColor(Fl_Color value);
        void registerOnPropertyChanged(std::function<void()> handler);

    protected:
        ChartHelper &chartHelper;
        std::shared_ptr <BasicAxis> horizAxis;
        std::shared_ptr <BasicAxis> vertAxis;
        bool isSorted;
        Fl_Color color;
        std::string caption;
        double maxX;
        double minX;
        double maxY;
        double minY;

    private:
        boost::signals2::signal<void()> onPropertyChangedSignal;
};

#endif // SERIES_H

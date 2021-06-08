#ifndef CHARTHELPER_H
#define CHARTHELPER_H

#include <Fl/Enumerations.h>

#include <vector>




class ChartHelper
{
    public:
        ChartHelper();
        virtual ~ChartHelper();

        static constexpr Fl_Color colors[] = {FL_RED, FL_GREEN, FL_BLUE, FL_MAGENTA, FL_BLACK,
        FL_DARK_RED, FL_DARK_GREEN, 176, FL_DARK_CYAN,  FL_DARK_MAGENTA,
        FL_DARK_YELLOW, 181, 91, 243, 235, 162, 115, 200, 212, 83, FL_CYAN, FL_YELLOW};

        // margins from a widget border to a chart area
        int marginLeft;
        int marginRight;
        int marginTop;
        int marginBottom;
        int legendHeight;
        // coordinates from a widget border to a chart area
        int chartRectLeft;
        int chartRectRight;
        int chartRectTop;
        int chartRectBottom;
        bool isZoomed;

        bool isAutoMarginTop;

        int getRarestColorIndex();
        std::vector<int> colorIndicesUsing;
        int getColorIndex(Fl_Color color);

    protected:

    private:
};

#endif // CHARTHELPER_H

#ifndef BASICAXIS_H
#define BASICAXIS_H

#include "ChartHelper.h"

class BasicAxis
{
    public:
        BasicAxis(ChartHelper &chartHelper);
        virtual ~BasicAxis();

        void setMouseStartX(int value);
        void setMouseStartY(int value);
        void setMouseNowX(int value);
        void setMouseNowY(int value);

        double getVisibleMaximum();
        double getVisibleMinimum();
        void setVisibleMaximum(double value);
        void setVisibleMinimum(double value);
        void setOldVisibleMaximum(double value);
        void setOldVisibleMinimum(double value);

        double getSizeCoeff();

        void setVisible(bool value);
        bool getVisible();

        void setAutoSize(bool value);
        bool getAutoSize();
        void setAutoZoom(bool value);
        bool getAutoZoom();
        void doAutoSize(double minVal, double maxVal);

        void incSeriesNum();
        void decSeriesNum();
        int getSeriesNum();

        void setMinimum(double value);
        double getMinimum();
        void setMaximum(double value);
        double getMaximum();

        bool getIsFixed();
        void setIsFixed(bool value);

        int getFontSize();
        void setFontSize(int value);
        int getFontFace();
        void setFontFace(int value);
        Fl_Color getGridColor();
        void setGridColor(Fl_Color value);
        Fl_Color getFontColor();
        void setFontColor(Fl_Color value);
        int getGridStyle();
        void setGridStyle(int value);
        int getGridWidth();
        void setGridWidth(int value);
        void setGridDashes(char* const value);

        int getMargin();
        void setMargin(int value);
        int getNotchLength();
        void setNotchLength(int value);
        int getFieldThickness();

        virtual void draw(int delta) = 0;
        virtual void zoomByMouse() = 0;
        virtual void shiftByMouse() = 0;
        virtual void prepareNotches() = 0;
        void unZoom();

    protected:
        ChartHelper &chartHelper;

        bool isFixed;

        int mouseStartX;
        int mouseStartY;
        int mouseNowX;
        int mouseNowY;

        double oldVisibleMaximum;
        double oldVisibleMinimum;
        double visibleMaximum;
        double visibleMinimum;
        double sizeCoeff;

        double maximum;
        double minimum;

        double step;
        bool isAutoZoom;
        bool isAutoSize;
        bool isAutoStep;
        bool isVisible;

        double unitSize;
        double visibleUnitSize;
        int pixelSize;
        double startMarkUnit;
        double startlabelValue;
        double axisShift;

        int fontSize;
        int fontFace;
        Fl_Color fontColor;
        Fl_Color gridColor;
        int gridStyle;
        int gridWidth;
        char* gridDashes;

        int fieldThickness;
        int margin;
        int notchLength;

        void setSizeCoeff();
        void calcStartMarkUnit();
        virtual void calcThickness() = 0;

    private:
        int seriesNum;
};

#endif // BASICAXIS_H

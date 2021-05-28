#ifndef BASICAXIS_H
#define BASICAXIS_H

#include "ChartHelper.h"

class BasicAxis
{
    public:
        BasicAxis(ChartHelper &chartHelper);
        virtual ~BasicAxis();
        /*
    property GridPen : TPen read FGridPen write SetGridPen;
    property MarginSpacing : boolean read FMarginSpacing write SetMarginSpacing;
    property DateTime : boolean read FDateTime write SetDateTime;

    property InMargin : boolean read FInMargin write SetInMargin;

    // (max - min), при котором появляются дробные значения шкалы (0 - никогда)
    property MinDeltaForIntegerScale : real read FMinDeltaForIntegerScale write SetMinDeltaForIntegerScale;
    property ZoomDeny : boolean read FZoomDeny write SetZoomDeny;

    procedure CalcStartMarkUnit();
    procedure GetStartLabelValue();
        */

        int mouseStartX;
        int mouseStartY;
        int mouseNowX;
        int mouseNowY;
        double oldVisibleMaximum;
        double oldVisibleMinimum;
        double visibleMaximum;
        double visibleMinimum;
        double sizeCoeff;

        void setVisible(bool value);
        bool getVisible();

        void setAutoSize(bool value);
        bool getAutoSize();
        void doAutoSize(double minVal, double maxVal);

        void incSeriesNum();
        void decSeriesNum();
        int getSeriesNum();

        void setMinimum(double value);
        double getMinimum();
        void setMaximum(double value);
        double getMaximum();


        virtual void draw() = 0;
        virtual void zoomByMouse() = 0;
        virtual void shiftByMouse() = 0;
        void unZoom();

    protected:
        ChartHelper &chartHelper;

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

        void setSizeCoeff();
        void calcStartMarkUnit();

    private:
        int seriesNum;
};

#endif // BASICAXIS_H

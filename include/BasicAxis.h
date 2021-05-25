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
        double maximum;
        double minimun;
        double visibleMaximum;
        double visibleMinimum;
        double oldVisibleMaximum;
        double oldVisibleMinimum;
        double step;
        bool isAutoZoom;
        bool isAutoSize;
        bool isAutoStep;
        bool isVisible;
        double unitSize;
        double visibleUnitSize;
        double sizeCoeff;
        int pixelSize;
        double startMarkUnit;
        double startlabelValue;
        double axisShift;

        int mouseStartX;
        int mouseStartY;
        int mouseNowX;
        int mouseNowY;

        virtual void draw() = 0;
        virtual void zoomByMouse() = 0;
        virtual void shiftByMouse() = 0;
        void unZoom();


    protected:
        ChartHelper &chartHelper;

        void setSizeCoeff();
        void calcStartMarkUnit();

    private:
};

#endif // BASICAXIS_H

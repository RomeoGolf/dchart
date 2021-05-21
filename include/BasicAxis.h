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
    property StartMarkUnit : real read FStartMarkUnit write SetStartMarkUnit;
    property StartLabelValue : real read FStartLabelValue write SetStartLabelValue;

    // (max - min), при котором появляются дробные значения шкалы (0 - никогда)
    property MinDeltaForIntegerScale : real read FMinDeltaForIntegerScale write SetMinDeltaForIntegerScale;
    property ZoomDeny : boolean read FZoomDeny write SetZoomDeny;

    procedure CalcStartMarkUnit();
    procedure GetStartLabelValue();

    // для обработки сдвига и зума мышью
    property AxisShift : real read FAxisShift write SetAxisShift;
    procedure FixStartXY(X, Y : integer); virtual;
    procedure FixNowXY(X, Y : integer); virtual;
    procedure FixMaxMin(); virtual;
    procedure IfMouseShift(); virtual; abstract;
    procedure IfMouseZoom(); virtual; abstract;
    procedure UnZoom();
    property MouseXStart : integer read FMouseXStart write SetMouseXStart;
    property MouseXNow : integer read FMouseXNow write SetMouseXNow;
    property MouseYStart : integer read FMouseYStart write SetMouseYStart;
    property MouseYNow : integer read FMouseYNow write SetMouseYNow;
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

        virtual void draw() = 0;
        void unZoom();


    protected:
        ChartHelper &chartHelper;

    private:
};

#endif // BASICAXIS_H

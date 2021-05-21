#ifndef CHARTHELPER_H
#define CHARTHELPER_H


class ChartHelper
{
    public:
        ChartHelper();
        virtual ~ChartHelper();

        /*
    property Chart : TWinControl read FChart;

    property SeriesColorIndex : integer read FSeriesColorIndex write SetSeriesColorIndex;
    property ColorIndexSet :TColorIndexSet read FColorIndexSet write SetColorIndexSet;
    property SeriesList : TList read FSeriesList;

    property MarginSpace : integer read FMarginSpace;

    property AutoMarginLeft : integer read FAutoMarginLeft;
    property AutoMarginRight : integer read FAutoMarginRight;
    property AutoMarginTop : integer read FAutoMarginTop;
    property AutoMarginBottom : integer read FAutoMarginBottom;

    property LegendHeight : integer read FLegendHeight write SetLegendHeight;

    function GetNextColorIndex() : integer;
    procedure DelSeriesIndex(SIndex : integer);
    procedure DeleteColorIndex(Index : integer);
    function GetLimit(PAxis : TPersistent) : TAxisLimit;
        */

        // margins from a widget border to a chart area
        int marginLeft;
        int marginRight;
        int marginTop;
        int marginBottom;
        // coordinates from a widget border to a chart area
        int chartRectLeft;
        int chartRectRight;
        int chartRectTop;
        int chartRectBottom;
        bool isZoomed;

    protected:

    private:
};

#endif // CHARTHELPER_H

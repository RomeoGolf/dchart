#ifndef CHARTHELPER_H
#define CHARTHELPER_H


class ChartHelper
{
    public:
        ChartHelper();
        virtual ~ChartHelper();

        /*
    property MarginSpace : integer read FMarginSpace;
    property AutoMarginLeft : integer read FAutoMarginLeft;
    property AutoMarginRight : integer read FAutoMarginRight;
    property AutoMarginTop : integer read FAutoMarginTop;
    property AutoMarginBottom : integer read FAutoMarginBottom;

    function GetNextColorIndex() : integer;
        */

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


    protected:

    private:
};

#endif // CHARTHELPER_H

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

        virtual void draw() = 0;
        virtual void zoomByMouse() = 0;
        virtual void shiftByMouse() = 0;
        void unZoom();

    protected:
        ChartHelper &chartHelper;

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

        void setSizeCoeff();
        void calcStartMarkUnit();

    private:
        int seriesNum;
};

#endif // BASICAXIS_H

#ifndef LEGEND_H
#define LEGEND_H

#include <Fl/Enumerations.h>

#include <vector>
#include <memory>
#include <string>

#include <Series.h>

struct LegendData {
    int startX;
    Fl_Color color;
    std::string caption;
    LegendData(int x, Fl_Color color, std::string caption) : startX(x), color(color), caption(caption) {}
};


class Legend
{
    public:
        Legend(ChartHelper &chartHelper);
        virtual ~Legend();

        void draw();
        void calcSize(std::vector<std::unique_ptr<Series>>& series);

        void setTop(int value);
        void setLeft (int value);
        void setHeight (int value);
        void setWidth (int value);
        void setVisible (bool value);
        void setFontSize (int value);
        void setSampleGap (int value);
        void setSampleLength (int value);
        void setSampleWidth (int value);
        void setItemGap (int value);
        void setMargin (int value);
        void setAutoSize (bool value);
        void setAutoPosition (bool value);

        int getTop();
        int getLeft();
        int getHeight();
        int getWidth();
        bool getVisible();
        int getFontSize();
        int getSampleGap();
        int getSampleLength();
        int getSampleWidth();
        int getItemGap();
        int getMargin();
        bool getAutoSize();
        bool getAutoPosition();
    protected:

    private:
        ChartHelper &chartHelper;
        std::vector<std::vector<LegendData>> legendData;
        int top;
        int left;
        int height;
        int width;
        bool isVisible;
        int fontSize;

        int sampleGap;
        int sampleLength;
        int sampleWidth;
        int itemGap;
        int margin;
        bool isAutoSize;
        bool isAutoPosition;
};

#endif // LEGEND_H

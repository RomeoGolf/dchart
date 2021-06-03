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
};

#endif // LEGEND_H

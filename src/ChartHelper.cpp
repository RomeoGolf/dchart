#include "ChartHelper.h"


#include <math.h>



ChartHelper::ChartHelper()
{
    //ctor
    colorIndicesUsing.resize(sizeof(colors) / sizeof(Fl_Color));
}

ChartHelper::~ChartHelper()
{
    //dtor
}

int ChartHelper::getRarestColorIndex()
{
    int result = 0;
    int minimum = std::numeric_limits<int>::max();
    for (int i = 0; i < colorIndicesUsing.size(); i++) {
        if (colorIndicesUsing[i] < minimum) {
            minimum = colorIndicesUsing[i];
            result = i;
        }
    }
    return result;
}

int ChartHelper::getColorIndex(Fl_Color color)
{
    int result = -1;
    for (int i = 0; i < (sizeof(colors)/sizeof(Fl_Color)); i++) {
        if (color == colors[i]) {
            result = i;
            break;
        }
    }
    return result;
}


#ifndef VERTAXIS_H
#define VERTAXIS_H

#include <BasicAxis.h>
#include <string>
#include <vector>

struct Notch {
    std::string label;
    int x, y;
    int h, w;
};

class VertAxis : public BasicAxis
{
    public:
        VertAxis(ChartHelper &chartHelper);
        virtual ~VertAxis();

        void draw(int delta) override;
        void zoomByMouse() override;
        void shiftByMouse() override;
        void calcStep();
        virtual void prepareNotches() override;

    protected:
        void calcThickness();

    private:
        std::vector<Notch> notches;

};

#endif // VERTAXIS_H

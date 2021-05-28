#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include <DChartBase.h>
#include <Series.h>

#include <math.h>
//#include <iostream>

int main (int argc, char ** argv)
{
  Fl_Window *window;
  Fl_Box *box;

  window = new Fl_Window (1000, 800);

  DChartBase *dcb = new DChartBase(20, 20,
                                   window->w() - 40,
                                   window->h() - 40, "");
  dcb->labelsize(21);
  window->resizable(dcb);

  window->end ();
  window->show (argc, argv);

  dcb->addSeries();
  dcb->series.back()->addXY(0,0);
  dcb->series.back()->addXY(1,10);
  dcb->series.back()->addXY(3,30);
  dcb->series.back()->addXY(2,70);
  dcb->series.back()->addXY(4,50);
  dcb->series.back()->addXY(5,20);
  dcb->series.back()->addXY(10,100);
  dcb->series.back()->sortByX();

  //std::cout << "max x = " << dcb->series.back()->getMaxX() << std::endl;

  dcb->addSeries();
  for (double t = 0; t < 15; t += 0.05) {
      double val = sin(t) * 10.0;
      dcb->series.back()->addXY(t, val);
  }

  dcb->addSeries();
  for (double t = 5; t < 25; t += 0.1) {
      double val = cos(t - 5) * 5.0;
      dcb->series.back()->addXY(t, val);
  }

  dcb->unZoom();

  return(Fl::run());
}

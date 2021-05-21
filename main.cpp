#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include <DChartBase.h>
#include <Series.h>

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

  Series *s1 = new Series(dcb->chartHelper);
  s1->addXY(0,0);
  s1->addXY(1,10);
  s1->addXY(2,70);
  s1->addXY(3,30);
  s1->addXY(4,50);
  s1->addXY(5,20);
  s1->addXY(10,100);
  dcb->addSeries(s1);

  return(Fl::run());
}

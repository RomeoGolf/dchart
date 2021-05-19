#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include <DChartBase.h>
#include <Series.h>

int main (int argc, char ** argv)
{
  Fl_Window *window;
  Fl_Box *box;

  window = new Fl_Window (300, 300);
  box = new Fl_Box (10, 10, 150, 30, "Hello World!");

  box->box (FL_UP_BOX);
  box->labelsize (21);
  box->labelfont (FL_BOLD+FL_ITALIC);
  box->labeltype (FL_SHADOW_LABEL);

  DChartBase *dcb = new DChartBase(10, 50, 200, 200, "test");
  dcb->labelsize(21);

  window->end ();
  window->show (argc, argv);

  Series *s1 = new Series();
  s1->addXY(1,10);
  s1->addXY(2,70);
  s1->addXY(3,30);
  s1->addXY(4,50);
  s1->addXY(5,20);
  dcb->addSeries(s1);

  return(Fl::run());
}

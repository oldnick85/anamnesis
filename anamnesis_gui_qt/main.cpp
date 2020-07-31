#include <QApplication>
#include <QMainWindow>
#include "common.h"
#include "gui/cguiqtmain.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QMainWindow main_window;
  main_window.setWindowTitle(text.PrintProgramName().c_str());
  main_window.setMinimumSize(600, 600);
  main_window.show();
  CGuiQtMain* gui_main = new CGuiQtMain(&main_window);
  gui_main->Begin();
  return app.exec();
}

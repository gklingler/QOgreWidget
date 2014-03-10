#include <QApplication>

#include "QOgreWidgetDemo.hpp"

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  QOgreWidgetDemo window;

  // the call to exec will block until the last GUI window has been closed
  app.connect( &app, SIGNAL( lastWindowClosed() ), &app, SLOT( quit() ) );
  app.exec();

  return 0;
}
#include "server.h"
#include <QApplication>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  Server server;
  return app.exec();
}

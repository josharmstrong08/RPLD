#include "server.h"
#include <QCoreApplication>

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);
  Server server;
  return app.exec();
}

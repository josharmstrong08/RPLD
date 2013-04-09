#include "client.h"
#include <QCoreApplication>

int main(int argc, char** argv)
{
  QCoreApplication app(argc, argv);

  Client client;
  client.start("127.0.0.1", 8888);

  return app.exec();
}

#include <QCoreApplication>
#include "ledmatrixdriver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    LEDMatrixDriver driver;
    driver.OutputFrame(NULL, 0, 0);

    return a.exec();
}

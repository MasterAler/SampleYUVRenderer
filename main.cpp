#include "TestWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestWidget w;
    w.show();
    w.readAllSampleFile();

    return a.exec();
}

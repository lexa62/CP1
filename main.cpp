#include <QApplication>
#include "hashcount.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HashCount h;
    h.show();
    return a.exec();
}

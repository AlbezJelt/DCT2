#include "include/mainwindow.h"
#include "include/test.h"

#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

//    test::test_project_matrix();
    test::compare_DCT2_algorithms();
    return 0;

}

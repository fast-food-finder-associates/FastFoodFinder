#include <QApplication>
#include "windows/login.hpp"
#include "windows/mainwindow.hpp"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    return a.exec();
}

#include <QApplication>
#include "windows/login.hpp"
#include "windows/mainwindow.hpp"
#include "windows/navitem.hpp"
#include <QDebug>
int main(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QApplication a(argc, argv);
    MainWindow w;

    return a.exec();
}

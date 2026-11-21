#include "heads/mainwindow.h"
#include"heads/main_ui.h"
#include<heads/normal_mode.h>
#include<heads/normal_mode.h>
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    main_ui* mu=new main_ui();
    MainWindow* startW=new MainWindow();
    Normal_mode* nm = new Normal_mode();
    QObject::connect(startW,&MainWindow::startsignal,nm,&Normal_mode::start);
    startW->show();
    

    int result = app.exec();
    delete mu;
    delete startW;
    delete nm;

    return result;
}

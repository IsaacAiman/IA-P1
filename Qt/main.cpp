#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QString>
#include <iostream>
#include <string>
#include <sstream>
#include <QDebug>


int main(int argc, char *argv[])
{




   /* QString program = " /Users/Isaac/Desktop/IA-P1/menu/coche ";
    QProcess myProcess;
    myProcess.execute(program);
    qDebug()<< myProcess.exitCode();*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    a.exec();


    QString program = " /Users/Isaac/Desktop/IA-P1/./coche ";
    QProcess myProcess;
    QString s = QString::number(w.get_width());
    program = program   +s;
    s = QString::number(w.get_height());
    program = program + " " + s;
    s = QString::number(w.get_obs());
    program = program + " "+ s;
    s = QString::number(w.get_scratch());
    program = program + " " + s;

    myProcess.execute(program);

}

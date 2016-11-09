#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "iostream"
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    scratch = 0;
    width = 0;
    height = 0;
    obs = 0;
    QString alto_;
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_cancelok_accepted()
{
    this->close();

}

void MainWindow::on_cancelok_rejected()
{
    exit(0);
}



void MainWindow::on_checkbox_toggled(bool checked)
{
    if (checked){
        scratch=1;
    }
    if (!checked){
        scratch=0;
    }
}

void MainWindow::on_ancho_valueChanged(int arg1)
{
    width=arg1;
}

void MainWindow::on_alto_valueChanged(int arg1)
{
    height = arg1;
}


void MainWindow::on_porcentaje_obs_valueChanged(int arg1)
{
    obs = arg1;
}

int MainWindow::get_scratch(void){
    return scratch;
}

int MainWindow::get_width(void){
    return width;
}

int MainWindow::get_height(void){
    return height;
}

int MainWindow::get_obs(void){
    return obs;
}

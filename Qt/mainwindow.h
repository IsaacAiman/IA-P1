#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCheckBox>
#include <QDialogButtonBox>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int get_scratch(void);
    int get_width(void);
    int get_height(void);
    int get_obs(void);

private slots:
    void on_cancelok_accepted();

    void on_cancelok_rejected();

    void on_checkbox_toggled(bool checked);

    void on_ancho_valueChanged(int arg1);

    void on_alto_valueChanged(int arg1);

    void on_porcentaje_obs_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    int scratch;
    int width;
    int height;
    int obs;
};

#endif // MAINWINDOW_H

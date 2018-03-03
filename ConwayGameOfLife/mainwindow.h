#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "meshwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionAbout_triggered();

    void on_actionRandom_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

private:
    void resizeEvent(QResizeEvent *event);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

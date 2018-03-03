#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QtGlobal>
#include<QResizeEvent>
#include<QDebug>
#include<QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->meshWidget->setSize(10,10);
    ui->meshWidget->reset();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent * /*event*/)
{

}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox *box = new QMessageBox(this);
    box->setText("Stephen Krol 2018");
    box->show();
    box->exec();
}

void MainWindow::on_actionRandom_triggered()
{
    ui->meshWidget->reset();
    int m = ui->meshWidget->getM();
    int n = ui->meshWidget->getN();

    for(unsigned int i = 0; i <= n; i++ ){
        for(unsigned int j = 0; j <= m; j++ ){
            ui->meshWidget->setCell(i,j,(qrand()%2));
        }
    }
}

void MainWindow::on_actionOpen_triggered()
{
    //TODO: lol
}

void MainWindow::on_actionSave_triggered()
{
    //TODO: too hard
}

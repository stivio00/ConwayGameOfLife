#include "meshwidget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>


MeshWidget::MeshWidget(QWidget *parent) : QWidget(parent),
    m(10), n(10)
{
    timer = new QTimer(this);
    timer->setInterval(1000);
    QObject::connect(timer, &QTimer::timeout, this, &MeshWidget::nextStep);
    mat[5][5] = true;
}

void MeshWidget::setSize(unsigned int m_, unsigned int n_)
{
    setM(m_);
    setN(n_);
}

void MeshWidget::reset()
{
    for(unsigned int i = 0; i <= n; i++ ){
        for(unsigned int j = 0; j <= m; j++ ){
            mat[i][j]=false;
        }
    }
    STATE = 0;
    setStepNumber(0);
    timer->stop();
    repaint();
}

void MeshWidget::nextStep()
{
    /* copy state */
    std::array<std::array<bool,100>,100> mat_past(mat);
    for(unsigned int i = 0; i <= n; i++ ){
        for(unsigned int j = 0; j <= m; j++ ){
            /*Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
Any live cell with two or three live neighbours lives on to the next generation.
Any live cell with more than three live neighbours dies, as if by overpopulation.
Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.*/
            int arround = neighborhood(mat_past, i, j, n, m);
            if(arround < 2 ){ //underpopulation
                mat[i][j] = false;
            }
            if(arround == 2 || arround == 3){//survive
            }
            if(arround > 3){//overpopulation
                mat[i][j] = false;
            }
            if(arround == 3){//reproduction
                mat[i][j] = true;
            }
        }
    }
    setStepNumber(getStepNumber()+1);
    this->repaint();
}

void MeshWidget::setN(int n_)
{
    this->n = static_cast<unsigned int>(n_);
    repaint();
}

void MeshWidget::setM(int m_)
{
    this->m = static_cast<unsigned int>(m_);
    repaint();
}

void MeshWidget::setTimeStep(double timeStep_)
{
    timeStep = timeStep_;
    timer->setInterval(timeStep);
}

void MeshWidget::setStepNumber(int sn)
{
    stepNumber = sn;
    emit stepNumberChanged(sn);
}

void MeshWidget::setCell(int i, int j, bool state)
{
    mat[i][j] = state;
    repaint();
}

int neighborhood(MATRIX mat, int i, int j , int m, int n)
{
    /*check corner*/
    if(i==0 && j ==0){ //Top left Corner
        return RIGHT(i,j) + DOWN(i,j) + DOWN_RIGHT(i,j);
    }else if(i == m && j == 0){   //top right corner
        return LEFT(i,j) + DOWN_LEFT(i,j) + DOWN(i,j);
    }else if(i==0 && j ==n){ //left down corner
        return UP(i,j) + UP_RIGHT(i,j) + RIGHT(i,j);
    }else if(i==m &&j==n){ //right down corner
        return  UP(i,j) + UP_LEFT(i,j) + LEFT(i,j);
    }

    /*check if in the boundary*/
    if(i==0){ //left
        return UP(i,j) + DOWN(i,j)  + RIGHT(i,j)+ UP_RIGHT(i,j) + DOWN_RIGHT(i,j);
    }else if(i==m){ //Right
        return UP(i,j) + DOWN(i,j) + LEFT(i,j) + UP_LEFT(i,j) + DOWN_LEFT(i,j);
    }else if(j==0){ //up
        return + DOWN(i,j) + LEFT(i,j) + RIGHT(i,j)+ DOWN_LEFT(i,j) + DOWN_RIGHT(i,j);
    }else if(j==n){ //DOWN
        return UP(i,j) + LEFT(i,j) + RIGHT(i,j) + UP_LEFT(i,j) + UP_RIGHT(i,j);
    }

    /*count*/
    return UP(i,j) + DOWN(i,j) + LEFT(i,j) + RIGHT(i,j)
            + UP_LEFT(i,j) + UP_RIGHT(i,j) + DOWN_LEFT(i,j) + DOWN_RIGHT(i,j);
}

void MeshWidget::paintEvent(QPaintEvent * /*event*/)
{
    const unsigned int w=10,h=10;

    QPainter painter(this);
    /* Paint lines (verticals then horizontals)*/
    for(unsigned int i = 0; i <= n; i++ ){
        painter.drawLine(i*w,0,i*w,m*h);
    }
    for(unsigned int j = 0; j <= m; j++ ){
        painter.drawLine(0,j*h,n*w,j*h);
    }
    /* Paint pixels */
    for(unsigned int i = 0; i <= n; i++ ){
        for(unsigned int j = 0; j <= m; j++ ){
            if(mat[i][j]){
                painter.setBrush(QBrush(QColor("blue"),Qt::BrushStyle::SolidPattern));
            }else{
                painter.setBrush(QBrush(QColor("white"),Qt::BrushStyle::SolidPattern));
            }
            painter.drawRect(i*w,j*h, w,h);
        }
    }
}

void MeshWidget::mousePressEvent(QMouseEvent *event)
{
    int x = event->localPos().x();
    int y = event->localPos().y();
    int i = x/10;
    int j = y/10;
    mat[i][j] = !mat[i][j]; //Flip point
    repaint();
}

void MeshWidget::start()
{
    //STATE 0:init(or reset) 1:running 2:paused
    if(STATE==0)  { //START
        timer->start();
        STATE=1;
    }else if(STATE == 1) { //PAUSE
        timer->stop();
        STATE=2;
    }else if(STATE == 2) { //RESUME
        timer->start();
        STATE=1;
    }
}

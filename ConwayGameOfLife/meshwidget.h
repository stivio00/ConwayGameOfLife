#ifndef MESHWIDGET_H
#define MESHWIDGET_H

#include <array>
#include <QWidget>
#include <QTimer>

#define UP(x,y) mat[x][y+1]
#define DOWN(x,y) mat[x][y-1]
#define LEFT(x,y) mat[x-1][y]
#define RIGHT(x,y) mat[x+1][y]

#define UP_LEFT(x,y) mat[x-1][y-1]
#define UP_RIGHT(x,y) mat[x+1][y-1]
#define DOWN_LEFT(x,y) mat[x-1][y+1]
#define DOWN_RIGHT(x,y) mat[x+1][y+1]

typedef std::array<std::array<bool,100>,100> MATRIX;

int neighborhood(MATRIX mat, int i, int j, int n, int m);

/** Mesh Widget Declaration */

class MeshWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int n  READ getN WRITE setN )
    Q_PROPERTY(int m  READ getM WRITE setM )
    Q_PROPERTY(double timeStep READ getTimeStep WRITE setTimeStep NOTIFY timeStepChanged)
    Q_PROPERTY(int stepNumber READ getStepNumber WRITE setStepNumber NOTIFY stepNumberChanged)

public:
    explicit MeshWidget(QWidget *parent = nullptr);
    unsigned int getN() {return n;}
    unsigned int getM() {return m;}
    double getTimeStep() {return timeStep;}
    int getStepNumber() {return stepNumber;}

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void timeStepChanged();
    void stepNumberChanged(int);

public slots:
    void start();
    void setSize(unsigned int m_, unsigned int n_);
    void reset();
    void nextStep();
    void setN(int n_);
    void setM(int m_);
    void setTimeStep(double timeStep);
    void setStepNumber(int sn);
    void setCell(int i, int j, bool state);

private:
    MATRIX mat;
    unsigned int m,n;
    double timeStep;
    int stepNumber;
    QTimer *timer;
    int STATE;

};

#endif // MESHWIDGET_H

#ifndef QPSK_H
#define QPSK_H


#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glut.h>

class QPSK : public QGLWidget
{

public:
    explicit QPSK(QWidget *parent = 0);
    int *pdata;
    void wallplot();


    void timerEvent(QTimerEvent *event);
    int id1;
    void InputManagement();
    void myDrawCircle(double x, double y, double z, double r);
    void myDrawPoint(double x, double y, double z, double r);
    int char2int(char *str);
    void myDrawStars();
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
private:
    GLfloat translate, xRot, yRot, zRot;

signals:

public slots:

};


#endif // QPSK_H

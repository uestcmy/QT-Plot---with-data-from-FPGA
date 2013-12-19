#ifndef MYGL_H
#define MYGL_H
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>

class mygl2 : public QGLWidget
{

public:
    explicit mygl2(QWidget *parent = 0);

    void wallplot();
    void histoPlot1();
    void histoPlot2();
    void histoPlot3();
    void histoPlot4();

    void timerEvent(QTimerEvent *event);
    int id1;
    void InputManagement();
    void histoPlot41();
    void histoPlot42();
    void histoPlot43();
    void histoPlot44();
    void histoPlot31();
    void histoPlot32();
    void histoPlot33();
    void histoPlot34();
    void histoPlot23();
    void histoPlot22();
    void histoPlot21();
    void histoPlot24();
    void histoPlot11();
    void histoPlot12();
    void histoPlot13();
    void histoPlot14();
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

#endif // MYGL_H

#ifndef NETWORKLINK_H
#define NETWORKLINK_H

#include <QWidget>

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glut.h>

namespace Ui {
class NetworkLink;
}

class NetworkLink : public QGLWidget
{

    
public:
    explicit NetworkLink(QWidget *parent = 0);


    int *pdata;
    void wallplot();


    void timerEvent(QTimerEvent *event);
    int id1;
    void InputManagement();
    void myDrawCircle(double x, double y, double z, double r);
    void myDrawPoint(double x, double y, double z, double r);
    int char2int(char *str);
    void myDrawStars();
    void FlatMeshPlot();
    void SwitchPlot();

    void myDrawPlate(double R, double x, double y, double z, double r, double g, double b, double alpha);

    void myDrawPlate2(double R, double x, double y, double z, double r, double g, double b, double alpha, int pos);

    void flowplot(double x, double y, double z);
    void rectTube(double x, double y, double z);
    void horizontalTube(double x, double y, double z);
    void FPGAtransparent(double x, double y, double z, double alpha);

    void flowplot2(double x, double y, double z, double num, double width, int flag);
    void flowplot3(double x, double y, double z, double num, double width, int flag);
    void rectTube(double x, double y, double z, double alpha);
    void horizontalTube(double x, double y, double z, double alpha);
    void flowh11(double east, double north, double west, double south);
    void flowh33(double east, double north, double west, double south);
    void flowh34(double east, double north, double west, double south);
    void flowh32(double east, double north, double west, double south);
    void flowh31(double east, double north, double west, double south);
    void flowh41(double east, double north, double west, double south);
    void flowh42(double east, double north, double west, double south);
    void flowh43(double east, double north, double west, double south);
    void flowh44(double east, double north, double west, double south);
    void flowh13(double east, double north, double west, double south);
    void flowh14(double east, double north, double west, double south);
    void flowh12(double east, double north, double west, double south);
    void flowh21(double east, double north, double west, double south);
    void flowh22(double east, double north, double west, double south);
    void flowh23(double east, double north, double west, double south);
    void flowh24(double east, double north, double west, double south);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void keyPressEvent(QKeyEvent *);
private:
    GLfloat translate, xRot, yRot, zRot;

signals:

public slots:


private:
    Ui::NetworkLink *ui;
};

#endif // NETWORKLINK_H

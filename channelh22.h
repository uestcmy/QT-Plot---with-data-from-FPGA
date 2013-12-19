#ifndef CHANNELH22_H
#define CHANNELH22_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glut.h>

namespace Ui {
class ChannelH22;
}

class ChannelH22 : public QGLWidget
{


public:
    explicit ChannelH22(QWidget *parent = 0);
    ~ChannelH22();
    void wallplot();
    void histoPlot1();
    void histoPlot2();
    void histoPlot3();
    void histoPlot4();

    void timerEvent(QTimerEvent *event);
    int id1;
    double *pdata;
    double *pdata2;
    void InputManagement();
    void edgeplot();
    double char2double(char *str);
    void unitmeshplot(int i, int j, double xstart, double zstart, double xstep, double zstep, int dx, int dz);
    void meshplot(int jstart);
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
    Ui::ChannelH22 *ui;
};

#endif // CHANNELH22_H

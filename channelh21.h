#ifndef CHANNELH21_H
#define CHANNELH21_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glut.h>

namespace Ui {
class ChannelH21;
}

class ChannelH21 : public QGLWidget
{


public:
    explicit ChannelH21(QWidget *parent = 0);
    ~ChannelH21();
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
    Ui::ChannelH21 *ui;
};

#endif // CHANNELH21_H

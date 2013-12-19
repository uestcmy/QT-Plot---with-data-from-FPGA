#ifndef CHANNELH12_H
#define CHANNELH12_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glut.h>

namespace Ui {
class ChannelH12;
}

class ChannelH12 : public QGLWidget
{


public:
    explicit ChannelH12(QWidget *parent = 0);
    ~ChannelH12();
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
    Ui::ChannelH12 *ui;
};

#endif // CHANNELH12_H

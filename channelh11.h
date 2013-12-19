#ifndef CHANNELH11_H
#define CHANNELH11_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glut.h>

namespace Ui {
class ChannelH11;
}

class ChannelH11 : public QGLWidget
{

    
public:
    explicit ChannelH11(QWidget *parent = 0);
    ~ChannelH11();
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
    Ui::ChannelH11 *ui;
};

#endif // CHANNELH11_H

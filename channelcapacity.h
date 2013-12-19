#ifndef CHANNELCAPACITY_H
#define CHANNELCAPACITY_H

#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>

class ChannelCapacity : public QGLWidget
{

public:
    explicit ChannelCapacity(QWidget *parent = 0);

    void wallplot();
    void histoPlot1();
    void histoPlot2();
    void histoPlot3();
    void histoPlot4();

    void timerEvent(QTimerEvent *event);
    int id1;
    void InputManagement();
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



#endif // CHANNELCAPACITY_H

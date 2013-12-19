#ifndef CHANNEL_H
#define CHANNEL_H

#include <QWidget>
#include <QGLWidget>
#include <QKeyEvent>
#include <GL/glu.h>

namespace Ui {
class Channel;
}

class Channel : public QGLWidget
{

    
public:
    explicit Channel(QWidget *parent = 0);
    ~Channel();

    void wallplot();
    void histoPlot1();
    void histoPlot2();
    void histoPlot3();
    void histoPlot4();

    void timerEvent(QTimerEvent *event);
    int id1;
    double *pdata;
    void InputManagement();
    void edgeplot();
    double char2double(char *str);
    void meshplot();
    void unitmeshplot(int i, int j, double xstart, double zstart, double xstep, double zstep, int dx, int dz);
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
    Ui::Channel *ui;
};

#endif // CHANNEL_H

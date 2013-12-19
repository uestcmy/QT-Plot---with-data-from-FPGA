#include "channelcapacity.h"


ChannelCapacity::ChannelCapacity(QWidget *parent) :
    QGLWidget(parent)
{
     setWindowTitle("Channel Capacity");
    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 300;
    id1 = startTimer(100);
}

void ChannelCapacity::initializeGL()
{
    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}
void ChannelCapacity::resizeGL(int w, int h)
{
    glViewport(-10, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    //glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, -15.0, 15.0);
     glFrustum (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, 4.3, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Ⱦ
void ChannelCapacity::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glTranslatef(0.0, 0.0, translate);// translate is included in <QKeyEvent>
    glTranslatef(0.0, -0.5, 0.3);// translate is included in <QKeyEvent>

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);

    //histoPlot1();
    histoPlot2();
    //histoPlot3();
    //histoPlot4();
    //floor
    wallplot();
    glEnd();
}

void ChannelCapacity::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,2},{-2,-1,2},{-2,-1,-4},{2,-1,-4}};
    glColor4f(0, 0, 0,0.2);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
}
void ChannelCapacity::histoPlot1(){
    double point[8][3] = {{0.5-0.05,1,-2},{0.5-0.05,1,-3+0.05},{-0.5,1,-3+0.05},{-0.5,1,-2},
                          {0.5-0.05,-1,-2},{0.5-0.05,-1,-3+0.05},{-0.5,-1,-3+0.05},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};

    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] -= 0.3;
    }


    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(0.588235,0.313725,0.117647);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(0.588235,0.313725,0.117647);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(0.529412,0.254902,0.058824);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0.470588, 0.215686, 0.058824);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
     glColor3f(0.529412,0.254902,0.058824);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
     glColor3f(0.529412,0.254902,0.058824);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}

void ChannelCapacity::histoPlot2(){
    double point[8][3] = {{0.5-0.05,1,-2},{0.5-0.05,1,-3+0.05},{-0.5,1,-3+0.05},{-0.5,1,-2},
                          {0.5-0.05,-1,-2},{0.5-0.05,-1,-3+0.05},{-0.5,-1,-3+0.05},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};

    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 2;

    }
    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(0.698039,0.227451,0.937255);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(0.698039,0.227451,0.937255);
      //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(0.507843, 0.13333, 0.745098);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0.507843, 0.13333, 0.745098);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(0.603922, 0.196078, 0.803922);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0.603922, 0.196078, 0.803922);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void ChannelCapacity::histoPlot3(){
    double point[8][3] = {{0.5-0.05,1,-2},{0.5-0.05,1,-3+0.05},{-0.5,1,-3+0.05},{-0.5,1,-2},
                          {0.5-0.05,-1,-2},{0.5-0.05,-1,-3+0.05},{-0.5,-1,-3+0.05},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};

    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 2;

    }
    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(0, 0.7490, 1);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(0, 0.7490, 1);
     //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(0.1176, 0.5647, 1);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0.1176, 0.5647, 1);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(0, 0.7490, 1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0, 0.7490, 1);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void ChannelCapacity::histoPlot4(){
    double point[8][3] = {{0.5-0.05,1,-2},{0.5-0.05,1,-3+0.05},{-0.5,1,-3+0.05},{-0.5,1,-2},
                          {0.5-0.05,-1,-2},{0.5-0.05,-1,-3+0.05},{-0.5,-1,-3+0.05},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    int rand1 = qrand() % 10;

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += 0.7;
    }

    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 3;

    }
    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(0.980392,0.745098,0.019608);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(0.980392,0.745098,0.019608);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(0.72549, 0.529412, 0.137255);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0.72549, 0.529412, 0.137255);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(0.862745, 0.627451, 0.098039);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(0.862745, 0.627451, 0.098039);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void ChannelCapacity::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Up :
        xRot += 10;
        break;
    case Qt::Key_Left :
        yRot += 10;
        break;
    case Qt::Key_Right :
        zRot += 10;
        break;
    case Qt::Key_Down :
        translate -= 1;
        if (translate <= -20)
            translate = -1;
        break;
    }
    updateGL();
    QGLWidget::keyPressEvent(event);
}

void ChannelCapacity::timerEvent(QTimerEvent *event){
    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);

    //histoPlot1();
    histoPlot2();
    //histoPlot3();
    //histoPlot4();
    //floor
    wallplot();
    glEnd();
    updateGL();
    //qDebug()<< "timer event in mygl2 Class!" << endl;
}

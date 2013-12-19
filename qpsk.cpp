#include "qpsk.h"
#include <math.h>
#include <QDebug>
#include <stdio.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QtGui/QApplication>
#include <QFileInfo>
#include <QTextCodec>
#include <QDateTime>


QPSK::QPSK(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("QPSK Stars");
    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 90;
    zRot += 340;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    id1 = startTimer(100);
    InputManagement();

}

void QPSK::initializeGL()
{
    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}
void QPSK::resizeGL(int w, int h)
{
    glViewport(-10, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    //glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, -15.0, 15.0);
     glFrustum (-3* ( GLfloat ) w / ( GLfloat ) h, 3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, 5, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//
void QPSK::paintGL()
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

    wallplot();
    glEnd();
    /*
    glBegin(GL_LINE);
    glColor4f(0, 0, 0,0.5);//black
    glVertex3f(-0.2,0.5,3);
    glVertex3f(-0.2,0.5,-3);
    glEnd();

    glBegin(GL_LINE);
    glColor4f(1, 0, 0,0.5);//red
    glPointSize(10);
    glVertex3f(0,0.5,0);
    glVertex3f(-0.2,0.5,0);
    glEnd();

    glBegin(GL_POINT);
    glColor4f(1, 0, 0,0.5);
    glPointSize(100);
    glVertex3f(0,0.5,-1);
    glEnd();
*/


    myDrawPoint(-0.2,0.5,0,0.03);
    myDrawStars();
    glColor4f(0,0,0,0.2);


}
void QPSK::myDrawPoint(double x,double y,double z,double r){//x,y,z, and  radium

        glBegin(GL_QUADS);
        glColor4f(0.9, 0.1, 0.1,1);//red
        glVertex3f(x,y-r/2,z-r);
        glVertex3f(x,y-r/2,z+r);
        glVertex3f(x,y+r/2,z+r);
        glVertex3f(x,y+r/2,z-r);
        glEnd();
}

void QPSK::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,2},{-2,-1,2},{-2,-1,-4},{2,-1,-4}};//floor
    double point3[8][3] = {{0,-1,2},{0,-1,-4},{0,2,-4},{0,2,2}};//wall
    double point4[8][3] = {{-0.2,0.5-0.01,2},{-0.2,0.5+0.01,2},{-0.2,0.5+0.01,-4},{-0.2,0.5-0.01,-4}};//shelf
    double point5[8][3] = {{-0.2,2,-1-0.01},{-0.2,-1,-1-0.01},{-0.2,-1,-1+0.01},{-0.2,2,-1+0.01}};//erect


    for( int i = 0 ; i < 4 ; i++ ){
        point5[i][2] += 1;
        point4[i][2] += 1;
        point3[i][2] += 1;
        point2[i+4][2] += 1;
    }
/*
    glColor4f(0, 0, 0,0.2);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
*/
    glColor4f(0, 0, 0,0.5);
    glVertex3f(point3[0][0], point3[0][1], point3[0][2]);
    glVertex3f(point3[1][0], point3[1][1], point3[1][2]);
    glVertex3f(point3[2][0], point3[2][1], point3[2][2]);
    glVertex3f(point3[3][0], point3[3][1], point3[3][2]);

    glColor4f(0, 0, 0,1);
    glVertex3f(point4[0][0], point4[0][1], point4[0][2]);
    glVertex3f(point4[1][0], point4[1][1], point4[1][2]);
    glVertex3f(point4[2][0], point4[2][1], point4[2][2]);
    glVertex3f(point4[3][0], point4[3][1], point4[3][2]);

    glColor4f(0, 0, 0,1);
    glVertex3f(point5[0][0], point5[0][1], point5[0][2]);
    glVertex3f(point5[1][0], point5[1][1], point5[1][2]);
    glVertex3f(point5[2][0], point5[2][1], point5[2][2]);
    glVertex3f(point5[3][0], point5[3][1], point5[3][2]);

}

void QPSK::keyPressEvent(QKeyEvent *event)
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

void QPSK::timerEvent(QTimerEvent *event){



    updateGL();
    //qDebug()<< "timer event in mygl2 Class!" << endl;

}

void QPSK::InputManagement(){
    //QFile file("datain.txt");
    static int qpsk[2000][2] = {0};
    QFile file("ReQPSK_1_re.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << file.errorString();
        qDebug() << "Last sentence is in QPSK Inputmanagement." << endl;
    }
    //qDebug() << QObject::tr("file text:") << endl << file.readAll();
    //char str[100];
    char str[100];
    for( int i = 0 ; i < 1600 ; i++ ){
        file.readLine(str,100);
        int crr = 0;
        crr = char2int(str);
        //qDebug() << "crr is :"<<crr;
        qpsk[i][0] = crr;
    }

    //qDebug() << "last one is :"<< qpsk[9][0] ;
    file.close();

    QFile file2("ReQPSK_1_im.txt");
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << file2.errorString();
        qDebug() << "Last sentence is in QPSK Inputmanagement." << endl;
    }
    //qDebug() << QObject::tr("file text:") << endl << file.readAll();
    //char str[100];
    for( int i = 0 ; i < 1600 ; i++ ){
        file2.readLine(str,100);
        int crr = 0;
        crr = char2int(str);
        //qDebug() << "crr is :"<<crr;
        qpsk[i][1] = crr;
    }
    pdata = &qpsk[0][0];

    //qDebug() <<"apsk[0][0] is :"<< *(pdata) << endl;
    file2.close();
}
int QPSK::char2int(char *str){
    /*
     *  eg. 2.789 -2.789
     */
    int ans = 0;

    if(str[0] == '-'){
        ans = str[1]-'0';
        for(int i=3 ; i < 6 ; i++ ){
            ans *= 10;
            ans += str[i] - '0';
        }
        ans *= -1;
    }
    else{
        ans = str[0]-'0';
        for(int i=2 ; i < 5 ; i++ ){
            ans *= 10;
            ans += str[i] - '0';
        }
    }
    return ans;
}
void QPSK::myDrawStars(){
    int r1 = qrand() % 500;
    for( int i = r1 ; i < r1+500 ; i++ ){
        double z = *(pdata+i*2+0);
        double y = *(pdata+i*2+1);
        z /= 1500;
        y /= 3000;
        //qDebug()<< "in my DrawStars, x ,y is " << z<<" , "<<y<<endl;
        myDrawPoint(-0.2,y+0.5,z,0.03);
    }

}

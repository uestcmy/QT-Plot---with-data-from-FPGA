#include "chcap.h"
#include "ui_chcap.h"


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

ChCap::ChCap(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::ChCap)
{
    ui->setupUi(this);
    setWindowTitle("Channel Capcity");
    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 90;
    zRot += 340;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    id1 = startTimer(100);

}

ChCap::~ChCap()
{
    delete ui;
}

void ChCap::initializeGL()
{

    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}
void ChCap::resizeGL(int w, int h)
{
    glViewport(-10, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    glOrtho (-2.3 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, -5.0, 15.0);
    // glFrustum (-1.8  * ( GLfloat ) w / ( GLfloat ) h, 3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, 5, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//
void ChCap::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glTranslatef(0.0, 0.0, translate);// translate is included in <QKeyEvent>
    glTranslatef(0.0, -0.5, 0.3);// translate is included in <QKeyEvent>

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);
    FlatMeshPlot();





}
void ChCap::FlatMeshPlot(){
    double quardvertex[4][3]={{-0.2,-1,2+1},{-0.2,-1,-2+1},{-0.2,2,-2+1},{-0.2,2,2+1}};
    double rectlines[4][3]={{-0.2,-1,2+1-1.33},{-0.2,-1+0.5,-2+1+1.33},{-0.2,2,-2+1+1.33},{-0.2,2,2+1-1.33}};
    double horizontalline[4][3] = {{-0.2,1,2+1},{-0.2,1,-2+1.33/2+1},{-0.2,0,-2+1},{-0.2,0,2+1}};
    glColor3f(0.0/255.0,51.0/255.0,153.0/255.0);
    glLineWidth(1);
    /*
    glBegin(GL_LINE_LOOP);//square
    glVertex3f(quardvertex[0][0],quardvertex[0][1],quardvertex[0][2]-1);
    glVertex3f(quardvertex[1][0],quardvertex[1][1],quardvertex[1][2]-1);
    glVertex3f(quardvertex[2][0],quardvertex[2][1],quardvertex[2][2]-1);
    glVertex3f(quardvertex[3][0],quardvertex[3][1],quardvertex[3][2]-1);
    glEnd();
    */
/*
    glBegin(GL_LINE_LOOP);
    glVertex3f(rectlines[0][0],rectlines[0][1],rectlines[0][2]-1);
    glVertex3f(rectlines[1][0],rectlines[1][1],rectlines[1][2]-1);
    glVertex3f(rectlines[2][0],rectlines[2][1],rectlines[2][2]-1);
    glVertex3f(rectlines[3][0],rectlines[3][1],rectlines[3][2]-1);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex3f(horizontalline[0][0],horizontalline[0][1],horizontalline[0][2]-1);
    glVertex3f(horizontalline[1][0],horizontalline[1][1],horizontalline[1][2]-1);
    glVertex3f(horizontalline[2][0],horizontalline[2][1],horizontalline[2][2]-1);
    glVertex3f(horizontalline[3][0],horizontalline[3][1],horizontalline[3][2]-1);
    glEnd();



    glBegin(GL_LINE);
    glVertex3f(horizontalline[0][0],horizontalline[0][1]+0.5,horizontalline[0][2]-1);
    glVertex3f(horizontalline[1][0],horizontalline[1][1]+0.5,horizontalline[1][2]-1);
    glEnd();*/
    for( int i = 0 ; i < 11 ; i++ ){
        //glColor3f(1,0,0);
        glBegin(GL_LINE);
        glVertex3f(horizontalline[0][0],horizontalline[0][1]+1-0.25*i,horizontalline[0][2]-1);
        glVertex3f(horizontalline[1][0],horizontalline[1][1]+1-0.25*i,horizontalline[1][2]-1);
        glEnd();
    }
/*
    //glColor3f(0,0,1);
    glBegin(GL_LINE);
    glVertex3f(horizontalline[0][0],horizontalline[0][1]-0.5,horizontalline[0][2]-1);
    glVertex3f(horizontalline[1][0],horizontalline[1][1]-0.5,horizontalline[1][2]-1);
    glEnd();
    glBegin(GL_LINE);
    glVertex3f(horizontalline[0][0],horizontalline[0][1]-1.5,horizontalline[0][2]-1);
    glVertex3f(horizontalline[1][0],horizontalline[1][1]-1.5,horizontalline[1][2]-1);
    glEnd();
*/
/*
    glBegin(GL_LINE);
    glVertex3f(rectlines[1][0],rectlines[1][1],rectlines[1][2]-1+1.33/2);
    glVertex3f(rectlines[2][0],rectlines[2][1],rectlines[2][2]-1+1.33/2);
    glEnd();
    glBegin(GL_LINE);
    glVertex3f(rectlines[1][0],rectlines[1][1],rectlines[1][2]-1-1.33/2);
    glVertex3f(rectlines[2][0],rectlines[2][1],rectlines[2][2]-1-1.33/2);
    glEnd();
    */
    for( int i = 0 ; i < 11 ; i++ ){
        //glColor3f(1,0,0);
        glBegin(GL_LINE);
        glVertex3f(rectlines[1][0],rectlines[1][1],rectlines[1][2]-1-1.33/2+1.33/4*i);
        glVertex3f(rectlines[2][0],rectlines[2][1],rectlines[2][2]-1-1.33/2+1.33/4*i);
        glEnd();
    }
/*
    glBegin(GL_LINE);
    glVertex3f(rectlines[1][0],rectlines[1][1],rectlines[1][2]-1+1.33*1.5);
    glVertex3f(rectlines[2][0],rectlines[2][1],rectlines[2][2]-1+1.33*1.5);
    glEnd();
*/
/*
    glColor3f(0.8,0,0);
    glBegin(GL_POLYGON);
    glVertex3f(horizontalline[0][0]-0.1,horizontalline[0][1],horizontalline[0][2]);
    glVertex3f(horizontalline[1][0]-0.1,horizontalline[1][1],horizontalline[1][2]);
    glVertex3f(horizontalline[2][0]-0.1,horizontalline[2][1],horizontalline[2][2]);
    glVertex3f(horizontalline[3][0]-0.1,horizontalline[3][1],horizontalline[3][2]);
    glEnd();
    */
}
void ChCap::myDrawPlate(double R,double x,double y,double  z,double r,double g,double b,double alpha){
    double n = 100;
    //double R = 0.3;
    const double Pi = 3.1415926;
    glColor4f(r,g,b,alpha);
    glBegin(GL_POLYGON);
    for( int i = 0 ; i < n ; i ++){
        glVertex3f(x,y+0.8*R*cos(2*Pi/n*i),z+R*sin(2*Pi/n*i));
    }
    glEnd();
}
void ChCap::myDrawPlate2(double R,double x,double y,double  z,double r,double g,double b,double alpha,int pos){
    double n = 100;
    //double R = 0.3;
    const double Pi = 3.1415926;
    glColor4f(r,g,b,alpha);
    glBegin(GL_POLYGON);
    if(pos == 3){
        for( int i = 0 ; i < n ; i ++){
            if( i <= 25 )
                glVertex3f(x,y+0.8*R*cos(2*Pi/n*i),z+R*sin(2*Pi/n*i));
            else
                glVertex3f(x,y,z);
        }
    }
    if(pos == 0){
        for( int i = 0 ; i < n+1 ; i ++){
            if( i > 74 )
                glVertex3f(x,y+0.8*R*cos(2*Pi/n*i),z+R*sin(2*Pi/n*i));
            else
                glVertex3f(x,y,z);
        }
    }
    if(pos == 2){
        for( int i = 0 ; i < n+1 ; i ++){
            if( i >= 25 && i <= 50 )
                glVertex3f(x,y+0.8*R*cos(2*Pi/n*i),z+R*sin(2*Pi/n*i));
            else
                glVertex3f(x,y,z);
        }
    }
    if(pos == 1){
        for( int i = 0 ; i < n+1 ; i ++){
            if( i >= 50 && i <= 75 )
                glVertex3f(x,y+0.8*R*cos(2*Pi/n*i),z+R*sin(2*Pi/n*i));
            else
                glVertex3f(x,y,z);
        }
    }

    glEnd();
}
void ChCap::myDrawPoint(double x,double y,double z,double r){//x,y,z, and  radium

        glBegin(GL_QUADS);
        glColor4f(0.9, 0.1, 0.1,1);//red
        glVertex3f(x,y-r/2,z-r);
        glVertex3f(x,y-r/2,z+r);
        glVertex3f(x,y+r/2,z+r);
        glVertex3f(x,y+r/2,z-r);
        glEnd();
}

void ChCap::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,2},{-2,-1,2},{-2,-1,-4},{2,-1,-4}};//floor
    double point3[8][3] = {{0,-1,2},{0,-1,-2},{0,2,-2},{0,2,2}};//wall
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
/*
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
*/
}

void ChCap::keyPressEvent(QKeyEvent *event)
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
        yRot -= 10;
        break;
    case Qt::Key_Down :
         xRot -= 10;
        break;
    }
    updateGL();
    QGLWidget::keyPressEvent(event);
}

void ChCap::timerEvent(QTimerEvent *event){


    updateGL();


}

int ChCap::char2int(char *str){
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
void ChCap::myDrawStars(){
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


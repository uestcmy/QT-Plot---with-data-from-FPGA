#include "networklink.h"
#include "ui_networklink.h"

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

NetworkLink::NetworkLink(QWidget *parent) :
    QGLWidget(parent)
{
    setWindowTitle("QPSK Stars");
    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 90;
    zRot += 340;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    id1 = startTimer(500);
    //InputManagement();

}

void NetworkLink::initializeGL()
{

    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}
void NetworkLink::resizeGL(int w, int h)
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
void NetworkLink::paintGL()
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

    SwitchPlot();
    FPGAtransparent(+0.4,0,0,0.2);FPGAtransparent(+0.4,0,2.66,0.2);FPGAtransparent(+0.4,-2,2.66,0.2);FPGAtransparent(+0.4,-2,0,0.2);
    flowplot(0,0,0);





}
void NetworkLink::flowplot(double x,double y,double z){
    double tube[4][4][4];
    tube[0][0][0] = 3;tube[0][0][3]=24;
    for( int i = 0 ; i < 4 ; i++){
        rectTube(-0.1,0,0+i*1.33,0.3);
        rectTube(-0.1,1,0+i*1.33,0.3);
        rectTube(-0.1,2,0+i*1.33,0.3);
    }
    for( int i = 0 ; i < 4 ; i++ ){
        horizontalTube(-0.1,0+i*1,0,0.3);
        horizontalTube(-0.1,0+i*1,1.33,0.3);
        horizontalTube(-0.1,0+i*1,2.66,0.3);
    }
    /*
    flowplot2(0-0.15,2,-2+0.15,1,0.2,1);
    flowplot2(0-0.15,-1,2-0.18,1,0.2,0);
    flowplot3(0-0.15,1.82,-2.2,0.65,0.2,1);
    flowplot3(0-0.15,-0.82,2,0.65,0.2,0);
*/
    int rand1 = qrand() % 10;//random
    rand1++;
    double rand2 = 1.0/ (double)rand1 ;
    rand1 = qrand() % 10;
    rand1++;
    double rand3 = 1.0/(double)rand1;

    flowh33(rand2,rand3,0,0);// east,north,west,south
    flowh34(rand3/2,rand2/2,rand2/3,0);
    flowh32(rand3*rand2,rand3,rand2,rand3);
    flowh31(rand3*rand2,rand3,0,rand3);

    flowh41(rand3*rand2,rand3,rand2,rand3);
    flowh42(0,rand3/6,rand2/5,rand3/7);
    flowh43(rand2+rand3/2,rand3/6,rand2/5,0);
    flowh44(0,rand3/6,rand2/5,0);

    flowh13(rand3*rand2,rand3,0,rand3);
    flowh14(rand3*rand2,rand3,rand2,rand3);
    flowh11(rand3*rand2,0,0,rand3);
    flowh12(rand3*rand2,0,rand2/3,rand3);

    flowh21(rand3*rand2,0,rand2/3,rand3);
    flowh23(rand3*rand2,rand3/5,rand2/3,rand3);
    flowh22(0,0,rand2/3,rand3);
    flowh24(0,rand3/5,rand2/3,rand3);
}

void NetworkLink::flowh33(double east,double north,double west,double south){//
     //qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3,0};//c h11 east
    double biasnorth[3]={0,0,-3.99-0.16};//h11 north
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north

}
void NetworkLink::flowh34(double east,double north,double west,double south){//
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3,1.33};//c h11 east
    double biasnorth[3]={0,0,-3.99-0.16+1.33};//h11 north
    double biaswest[3] = {0,0,-2.66};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);

}
void NetworkLink::flowh32(double east,double north,double west,double south){//
     //qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3+1,1.33};//c h11 east
    double biasnorth[3]={0,0+1,-3.99-0.16+1.33};//h11 north
    double biaswest[3] = {0,0+1,-2.66};
    double biassouth[3]={0,-2,1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh31(double east,double north,double west,double south){//
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3+1,0};//c h11 east
    double biasnorth[3]={0,0+1,-3.99-0.16};//h11 north
    double biaswest[3] = {0,0+1,-2.66-1.33};
    double biassouth[3]={0,-2,0};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh41(double east,double north,double west,double south){//
     //qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3+1,1.33+1.33};//c h11 east
    double biasnorth[3]={0,0+1,-3.99-0.16+1.33+1.33};//h11 north
    double biaswest[3] = {0,0+1,-2.66+1.33};
    double biassouth[3]={0,-2,1.33+1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh42(double east,double north,double west,double south){//from 41 to 42
     //qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3+1,1.33+1.33+1.33};//c h11 east
    double biasnorth[3]={0,0+1,-3.99-0.16+1.33+1.33+1.33};//h11 north
    double biaswest[3] = {0,0+1,0};
    double biassouth[3]={0,-2,1.33+1.33+1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh43(double east,double north,double west,double south){//from 41 to 43
     //qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3,1.33+1.33};//c h11 east
    double biasnorth[3]={0,0,-3.99-0.16+1.33+1.33};//h11 north
    double biaswest[3] = {0,0,-2.66+1.33};
    double biassouth[3]={0,-2-1,1.33+1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh44(double east,double north,double west,double south){//from 43 to 44
     //qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3,1.33+1.33+1.33};//c h11 east
    double biasnorth[3]={0,0,-3.99-0.16+1.33+1.33+1.33};//h11 north
    double biaswest[3] = {0,0,-2.66+1.33+1.33};
    double biassouth[3]={0,-2-1,1.33+1.33+1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh13(double east,double north,double west,double south){//
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3+1+1,0};//c h11 east
    double biasnorth[3]={0,0+1+1,-3.99-0.16};//h11 north
    double biaswest[3] = {0,0+1+1,-2.66-1.33};
    double biassouth[3]={0,-2+1,0};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh14(double east,double north,double west,double south){//from 32 to 14
     //qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,-3+1+1,1.33};//c h11 east
    double biasnorth[3]={0,0+1+1,-3.99-0.16+1.33};//h11 north
    double biaswest[3] = {0,0+1+1,-2.66};
    double biassouth[3]={0,-2+1,1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh11(double east,double north,double west,double south){//from 13 to 11
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,0,0};//c h11 east
    double biasnorth[3]={0,0+1+1+1,-3.99-0.16};//h11 north
    double biaswest[3] = {0,0+1+1+1,-2.66-1.33};
    double biassouth[3]={0,0,0};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh12(double east,double north,double west,double south){//from 11 to 12
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,0,1.33};//c h11 east
    double biasnorth[3]={0,0+1+1+1,-3.99-0.16+1.33};//h11 north
    double biaswest[3] = {0,0+1+1+1,-2.66};
    double biassouth[3]={0,0,1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh21(double east,double north,double west,double south){//from 12 to 21
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,0,1.33+1.33};//c h11 east
    double biasnorth[3]={0,0+1+1+1,-3.99-0.16+1.33+1.33};//h11 north
    double biaswest[3] = {0,0+1+1+1,-2.66+1.33};
    double biassouth[3]={0,0,1.33+1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh23(double east,double north,double west,double south){//from 21 to 23
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,0-1,1.33+1.33};//c h11 east
    double biasnorth[3]={0,0+1+1,-3.99-0.16+1.33+1.33};//h11 north
    double biaswest[3] = {0,0+1+1,-2.66+1.33};
    double biassouth[3]={0,0-1,1.33+1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh22(double east,double north,double west,double south){//from 21 to 22
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,0,1.33+1.33+1.33};//c h11 east
    double biasnorth[3]={0,0+1+1+1,-0.16};//h11 north
    double biaswest[3] = {0,0+1+1+1,0};
    double biassouth[3]={0,0,1.33+1.33+1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}
void NetworkLink::flowh24(double east,double north,double west,double south){//from 22 to 24
    // qDebug()<< "flowh11 timer event in netlink Class!   east:" << east <<endl;
    double biaseast[3] = {0,0-1,1.33+1.33+1.33};//c h11 east
    double biasnorth[3]={0,0+1+1,-0.16};//h11 north
    double biaswest[3] = {0,0+1+1,0};
    double biassouth[3]={0,0-1,1.33+1.33+1.33};
    flowplot2(0-0.15+biaseast[0],2+biaseast[1],-2+0.15+biaseast[2],east,0.2,1);//right flow east
    flowplot3(0-0.15+biasnorth[0],-0.82+biasnorth[1],2+0.15+biasnorth[2],0.65*north/1.0,0.2,0);//up flow north
    flowplot2(0-0.15+biaswest[0],-1+biaswest[1],2-0.18+biaswest[2],west,0.2,0);
    flowplot3(0-0.15+biassouth[0],1.82+biassouth[1],-2.2+biassouth[2],south,0.2,1);
}


void NetworkLink::flowplot2(double x,double y,double z,double num,double width,int flag){

    //qDebug()<< "flowplot2 timer event in netlink Class!   :" << num<<endl;
    if( flag == 1 ){//right arrow
        //qDebug()<< "flowplot2 flag == 1 timer event in netlink Class!   :" << num<<endl;
        //glColor4f(0.9490,0.0,0.3373,0.9);
        glColor4f(0.8,0.0824,0.3490,1);
        glBegin(GL_QUADS);
        glVertex3f(x-0.2,y,z);
        glVertex3f(x-0.2,y,z+num);
        glVertex3f(x-0.2,y-0.2,z+num);
        glVertex3f(x-0.2,y-0.2,z);
        glEnd();
    }
    if( flag == 0 ){//left arrow
        glColor4f(0.8,0.0824,0.3490,1);
        glBegin(GL_QUADS);
        glVertex3f(x-0.2,y,z);
        glVertex3f(x-0.2,y,z-num);
        glVertex3f(x-0.2,y+0.2,z-num);
        glVertex3f(x-0.2,y+0.2,z);
        glEnd();
    }
}
void NetworkLink::flowplot3(double x,double y,double z,double num,double width,int flag){
    if( flag == 1 ){//down arrow
        glColor4f(0.8,0.0824,0.3490,1);
        glBegin(GL_QUADS);
        glVertex3f(x-0.2,y,z);
        glVertex3f(x-0.2,y-num,z);
        glVertex3f(x-0.2,y-num,z+width);
        glVertex3f(x-0.2,y,z+width);
        glEnd();
    }
    if( flag == 0 ){//up arrow
        glColor4f(0.8,0.0824,0.3490,1);
        glBegin(GL_QUADS);
        glVertex3f(x-0.2,y,z);
        glVertex3f(x-0.2,y+num,z);
        glVertex3f(x-0.2,y+num,z+width);
        glVertex3f(x-0.2,y,z+width);
        glEnd();
    }
}
void NetworkLink::rectTube(double x,double y,double z,double alpha){
    double central[20][3]={{-0.2,-1,-2+1},{-0.2,-1,2+1},{-0.2,2,2+1},{-0.2,2,-2+1},
                              {-0.2,-1,-2+1+1.33},{-0.2,-1,2+1-1.33},{-0.2,2,2+1-1.33},{-0.2,2,-2+1+1.33},
                              {-0.2,1,-2+1},{-0.2,1,2+1},{-0.2,0,2+1},{-0.2,0,-2+1},
                              {-0.2,0,-2+1+1.33},{-0.2,0,2+1-1.33},{-0.2,1,2+1-1.33},{-0.2,1,-2+1+1.33}
                          };
    //vertical tube
    glColor4f(0.8941,0.4471,0.5922,alpha);
    glBegin(GL_QUADS);
    glVertex3f(x+central[0][0],y+central[0][1],z+central[0][2]-1-0.2);
    glVertex3f(x+central[0][0],y+central[0][1],z+central[0][2]-1+0.2);
    glVertex3f(x+central[11][0],y+central[11][1],z+central[11][2]-1+0.2);
    glVertex3f(x+central[11][0],y+central[11][1],z+central[11][2]-1-0.2);
    glEnd();
}
void NetworkLink::horizontalTube(double x,double y,double z,double alpha){
    double central[20][3]={{-0.2,-1,-2+1},{-0.2,-1,2+1},{-0.2,2,2+1},{-0.2,2,-2+1},
                              {-0.2,-1,-2+1+1.33},{-0.2,-1,2+1-1.33},{-0.2,2,2+1-1.33},{-0.2,2,-2+1+1.33},
                              {-0.2,1,-2+1},{-0.2,1,2+1},{-0.2,0,2+1},{-0.2,0,-2+1},
                              {-0.2,0,-2+1+1.33},{-0.2,0,2+1-1.33},{-0.2,1,2+1-1.33},{-0.2,1,-2+1+1.33}
                          };
    //vertical tube
    glColor4f(0.8941,0.4471,0.5922,alpha);
    glBegin(GL_QUADS);
    glVertex3f(x+central[0][0],y+central[0][1]-0.2,z+central[0][2]-1);
    glVertex3f(x+central[0][0],y+central[0][1]+0.2,z+central[0][2]-1);
    glVertex3f(x+central[4][0],y+central[4][1]+0.2,z+central[4][2]-1);
    glVertex3f(x+central[4][0],y+central[4][1]-0.2,z+central[4][2]-1);
    glEnd();
}

void NetworkLink::FPGAtransparent(double x,double y,double z,double alpha){
    double quardcorner[16][3]={{x-0.2-0.2,y+2+0.35*0.8,z-2+1},{x-0.2-0.2,y+1-0.35*0.8,z-2+1},{x-0.2-0.2,y+1-0.35*0.8,z-2+1+1.33},{x-0.2-0.2,y+2+0.35*0.8,z-2+1+1.33},
                               {x-0.2-0.2,y+2,z-2+1-0.35},{x-0.2-0.2,y+1,z-2+1-0.35},{x-0.2-0.2,y+1,z-2+1+1.33+0.35},{x-0.2-0.2,y+2,z-2+1+1.33+0.35}

                              };
    double circntrl[4][3]={{x-0.2-0.2,y+2,z-2+1},{x-0.2-0.2,y+1,z-2+1},{x-0.2-0.2,y+1,z-2+1+1.33},{x-0.2-0.2,y+2,z-2+1+1.33}};

    glColor4f(0.1,0.1,0.9,alpha);
    glBegin(GL_QUADS);
    glVertex3f(quardcorner[0][0]-0.2,quardcorner[0][1],quardcorner[0][2]-1);
    glVertex3f(quardcorner[1][0]-0.2,quardcorner[1][1],quardcorner[1][2]-1);
    glVertex3f(quardcorner[2][0]-0.2,quardcorner[2][1],quardcorner[2][2]-1);
    glVertex3f(quardcorner[3][0]-0.2,quardcorner[3][1],quardcorner[3][2]-1);
    glEnd();
    glColor4f(0.1,0.1,0.9,alpha);
    glBegin(GL_QUADS);
    glVertex3f(quardcorner[4][0]-0.2,quardcorner[4][1],quardcorner[4][2]-1);
    glVertex3f(quardcorner[5][0]-0.2,quardcorner[5][1],quardcorner[5][2]-1);
    glVertex3f(quardcorner[6][0]-0.2,quardcorner[6][1],quardcorner[6][2]-1);
    glVertex3f(quardcorner[7][0]-0.2,quardcorner[7][1],quardcorner[7][2]-1);
    glEnd();
    for( int i = 0 ; i < 4 ; i++ ){
         myDrawPlate2(0.35,circntrl[i][0]-0.2,circntrl[i][1],circntrl[i][2]-1,0.1,0.1,0.9,alpha,i);
    }


}
void NetworkLink::FlatMeshPlot(){
    double quardvertex[4][3]={{-0.2,-1,2+1},{-0.2,-1,-2+1},{-0.2,2,-2+1},{-0.2,2,2+1}};
    double rectlines[4][3]={{-0.2,-1,2+1-1.33},{-0.2,-1,-2+1+1.33},{-0.2,2,-2+1+1.33},{-0.2,2,2+1-1.33}};
    double horizontalline[4][3] = {{-0.2,1,2+1},{-0.2,1,-2+1},{-0.2,0,-2+1},{-0.2,0,2+1}};
    glColor3f(0,0,0);
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(quardvertex[0][0],quardvertex[0][1],quardvertex[0][2]-1);
    glVertex3f(quardvertex[1][0],quardvertex[1][1],quardvertex[1][2]-1);
    glVertex3f(quardvertex[2][0],quardvertex[2][1],quardvertex[2][2]-1);
    glVertex3f(quardvertex[3][0],quardvertex[3][1],quardvertex[3][2]-1);
    glEnd();

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
void NetworkLink::SwitchPlot(){
    double central[20][3]={{-0.2,-1,-2+1},{-0.2,-1,2+1},{-0.2,2,2+1},{-0.2,2,-2+1},
                              {-0.2,-1,-2+1+1.33},{-0.2,-1,2+1-1.33},{-0.2,2,2+1-1.33},{-0.2,2,-2+1+1.33},
                              {-0.2,1,-2+1},{-0.2,1,2+1},{-0.2,0,2+1},{-0.2,0,-2+1},
                              {-0.2,0,-2+1+1.33},{-0.2,0,2+1-1.33},{-0.2,1,2+1-1.33},{-0.2,1,-2+1+1.33}

                          };
    double color[20][3]={{0.588235,0.313725,0.117647},{0.8765625*0.9,0.01953125*0.9,0.01953125*0.9},{0.980392*1.23,0.745098*1.23,0.019608*1.23},{0.980392,0.745098,0.019608},
                                    {0.588235*1.1,0.313725*1.1,0.117647*1.1},{0.8765625*0.85,0.01953125*0.85,0.01953125*0.85},{0.980392*1.2,0.745098*1.2,0.019608*1.2},{1*1.2,0.490196*1.2,0},
                                   {1,0.490196,0},{0.980392*1.1,0.745098*1.1,0.019608*1.1},{0.8765625*1.1,0.01953125*1.1,0.01953125*1.1},{0.588235*1.15,0.313725*1.15,0.117647*1.15},
                                   {0.588235*1.2,0.313725*1.2,0.117647*1.2},{0.8765625,0.01953125,0.01953125},{0.980392,0.745098,0.019608},{1*1.1,0.490196*1.1,0}
                        };
    for( int i = 0 ; i < 16 ; i++ ){
        myDrawPlate(0.3,central[i][0]-0.2,central[i][1],central[i][2]-1,color[i][0],color[i][1],color[i][2],1);
    }
}

void NetworkLink::myDrawPlate(double R,double x,double y,double  z,double r,double g,double b,double alpha){
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
void NetworkLink::myDrawPlate2(double R,double x,double y,double  z,double r,double g,double b,double alpha,int pos){
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
void NetworkLink::myDrawPoint(double x,double y,double z,double r){//x,y,z, and  radium

        glBegin(GL_QUADS);
        glColor4f(0.9, 0.1, 0.1,1);//red
        glVertex3f(x,y-r/2,z-r);
        glVertex3f(x,y-r/2,z+r);
        glVertex3f(x,y+r/2,z+r);
        glVertex3f(x,y+r/2,z-r);
        glEnd();
}

void NetworkLink::wallplot(){
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

void NetworkLink::keyPressEvent(QKeyEvent *event)
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

void NetworkLink::timerEvent(QTimerEvent *event){


    updateGL();


}

void NetworkLink::InputManagement(){
    //QFile file("datain.txt");
    static int qpsk[2000][2] = {0};
    QFile file("ReQPSK_1_re.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << file.errorString();
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
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << file2.errorString();
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
int NetworkLink::char2int(char *str){
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
void NetworkLink::myDrawStars(){
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

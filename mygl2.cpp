#include "mygl2.h"

#include <GL/glut.h>
#include <QKeyEvent>
#include <qapplication.h>
#include <stdlib.h>
#include <stdio.h>
#include <QFileInfo>
#include <QDebug>
#include <QTextCodec>
#include <QStringList>
#include <QDateTime>

mygl2::mygl2(QWidget *parent) :
    QGLWidget(parent)
{
    InputManagement();
    translate = -7.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 210;
    id1 = startTimer(100);
    setWindowTitle("FPGA Status");
}
void mygl2::InputManagement(){
    //QFile file("datain.txt");
    static int qpsk[2000][2] = {0};
    const char filename[10][100] = {"/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout1.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout2.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout3.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout4.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout5.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout6.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout7.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout8.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout9.txt",
                                   "/home/uestc/qt_fedora14/FPGA_Resource_Plot/linux_driver/ml605_api/data/dataout10.txt"
                            };
    for( int i = 0 ; i < 10 ; i++ ){
        QFile file(filename[i]);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << file.errorString();
        //qDebug() << QObject::tr("file text:") << endl << file.readAll();
        //char str[100];
        char str[4096*20];
        file.readLine(str,4096*20+1);
        //qDebug() << "first char is :"<<str[4096*20-1] ;
        file.close();
    }
}

void mygl2::initializeGL()
{
    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


/*
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
*/
    //glShadeModel(GL_FLAT);

}
void mygl2::resizeGL(int w, int h)
{
    glViewport(-10, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    /*LIGHT
    GLfloat pos0[] = {1.0,1.0,1.0,1.0};
    GLfloat dif0[] = {1.0,0.0,0.0,0.0};
    GLfloat spec0[] = {1.0,1.0,1.0,1.0};
    GLfloat amb0[] = {0.1,0.1,0.1,1.0};
    glLightfv(GL_LIGHT0,GL_POSITION,pos0);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,dif0);
    glLightfv(GL_LIGHT0,GL_SPECULAR,spec0);
    glLightfv(GL_LIGHT0,GL_AMBIENT,amb0);
    */
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    //glOrtho (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, -15.0, 15.0);
     glFrustum (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, 3.3, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Ⱦ
void mygl2::paintGL()
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

    histoPlot11();histoPlot12();histoPlot13();histoPlot14();
    histoPlot21();histoPlot22();histoPlot23();histoPlot24();
    histoPlot31();histoPlot32();histoPlot33();histoPlot34();
    histoPlot41();histoPlot42();histoPlot43();histoPlot44();
    //floor
    wallplot();
    glEnd();
}

void mygl2::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,2},{-4,-1,2},{-4,-1,-4},{2,-1,-4}};
    glColor4f(0, 0, 0,0.2);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
}
void mygl2::histoPlot11(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};// fluctuate
    double brown[3][3] = {{0.588235,0.313725,0.117647},{0.529412,0.254902,0.058824},{0.529412,0.254902,0.058824}};
    int rand1 = qrand() % 10;//random

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 4 ; i++){//height
        point[i][1] -= 0.3;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}
void mygl2::histoPlot12(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};// fluctuate
    double brown[3][3] = {{0.588235,0.313725,0.117647},{0.529412,0.254902,0.058824},{0.529412,0.254902,0.058824}};
    int rand1 = qrand() % 10;//random

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 4 ; i++){//height
        point[i][1] -= 0.3;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h12
        point[i][0] -= 1;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h12
        for( int j = 0 ; j < 3 ; j++){
            brown[i][j] *= 1.1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}
void mygl2::histoPlot13(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};// fluctuate
    double brown[3][3] = {{0.588235,0.313725,0.117647},{0.529412,0.254902,0.058824},{0.529412,0.254902,0.058824}};
    int rand1 = qrand() % 10;//random

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 4 ; i++){//height
        point[i][1] -= 0.3;
    }
    for( int i = 0 ; i < 8 ; i++ ){// move left
        point[i][2] += 1;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 0;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h12
        for( int j = 0 ; j < 3 ; j++){
            brown[i][j] *= 1.15;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}
void mygl2::histoPlot14(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};// fluctuate
    double brown[3][3] = {{0.588235,0.313725,0.117647},{0.529412,0.254902,0.058824},{0.529412,0.254902,0.058824}};
    int rand1 = qrand() % 10;//random

    for( int i = 0 ; i < 4 ; i++){
        point[i][1] += (delta[rand1]/10);
        if( point[i][1] > 1){
            point[i][1] -= 0.1;
        }
        if(point[i][1] < 0 ){
            point[i][1] += 0.1;
        }
    }

    for( int i = 0 ; i < 4 ; i++){//height
        point[i][1] -= 0.3;
    }
    for( int i = 0 ; i < 8 ; i++ ){// move left
        point[i][2] += 1;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 1;
    }


    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h12
        for( int j = 0 ; j < 3 ; j++){
            brown[i][j] *= 1.2;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(brown[0][0],brown[0][1],brown[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
     glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[1][0],brown[1][1],brown[1][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //right
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(brown[2][0],brown[2][1],brown[2][2]);//250,5,5
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
}

void mygl2::histoPlot21(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double red[3][3]={{0.8765625,0.01953125,0.01953125},{0.64546875, 0.0390625, 0.0390625},{0.7421875, 0.01953125, 0.01953125}};
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



    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h12
        point[i][0] -= 2;
    }
    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            red[i][j] *= 0.85;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(red[0][0],red[0][1],red[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(red[0][0],red[0][1],red[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(red[1][0],red[1][1],red[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[1][0],red[1][1],red[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(red[2][0],red[2][1],red[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[2][0],red[2][1],red[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot22(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double red[3][3]={{0.8765625,0.01953125,0.01953125},{0.64546875, 0.0390625, 0.0390625},{0.7421875, 0.01953125, 0.01953125}};
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


    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h12
        point[i][0] -= 3;
    }
    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            red[i][j] *= 0.9;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(red[0][0],red[0][1],red[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(red[0][0],red[0][1],red[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(red[1][0],red[1][1],red[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[1][0],red[1][1],red[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(red[2][0],red[2][1],red[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[2][0],red[2][1],red[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot23(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double red[3][3]={{0.8765625,0.01953125,0.01953125},{0.64546875, 0.0390625, 0.0390625},{0.7421875, 0.01953125, 0.01953125}};
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

    for( int i = 0 ; i < 8 ; i++ ){// move left
        point[i][2] += 1;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 2;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            red[i][j] *= 1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(red[0][0],red[0][1],red[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(red[0][0],red[0][1],red[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(red[1][0],red[1][1],red[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[1][0],red[1][1],red[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(red[2][0],red[2][1],red[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[2][0],red[2][1],red[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot24(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double red[3][3]={{0.8765625,0.01953125,0.01953125},{0.64546875, 0.0390625, 0.0390625},{0.7421875, 0.01953125, 0.01953125}};
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

    for( int i = 0 ; i < 8 ; i++ ){// move left
        point[i][2] += 1;
    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 3;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            red[i][j] *= 1.1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(red[0][0],red[0][1],red[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
     glColor3f(red[0][0],red[0][1],red[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(red[1][0],red[1][1],red[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[1][0],red[1][1],red[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(red[2][0],red[2][1],red[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(red[2][0],red[2][1],red[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}


void mygl2::histoPlot31(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double orange[3][3] = {{1,0.490196,0},{0.784314, 0.333333, 0.039216},{0.901961, 0.411765, 0.019608}};//light-up dark-left mid-front
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
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot32(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double orange[3][3] = {{1,0.490196,0},{0.784314, 0.333333, 0.039216},{0.901961, 0.411765, 0.019608}};//light-up dark-left mid-front
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
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 1;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            orange[i][j] *= 1.1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot33(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double orange[3][3] = {{1,0.490196,0},{0.784314, 0.333333, 0.039216},{0.901961, 0.411765, 0.019608}};//light-up dark-left mid-front
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

    for( int i = 0 ; i < 4 ; i++){//height
        point[i][1] += 0.5;
    }


    for( int i = 0 ; i < 8 ; i++ ){//left
        point[i][2] += 3;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            orange[i][j] *= 1.15;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot34(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    double orange[3][3] = {{1,0.490196,0},{0.784314, 0.333333, 0.039216},{0.901961, 0.411765, 0.019608}};//light-up dark-left mid-front
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

    for( int i = 0 ; i < 4 ; i++){//height
        point[i][1] += 0.5;
    }


    for( int i = 0 ; i < 8 ; i++ ){
        point[i][2] += 3;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h42
        point[i][0] -= 1;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            orange[i][j] *= 1.2;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(orange[0][0],orange[0][1],orange[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);//250,5,5
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[1][0],orange[1][1],orange[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(orange[2][0],orange[2][1],orange[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}
void mygl2::histoPlot41(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    GLdouble yellow[3][3] = {{0.980392,0.745098,0.019608},{0.72549, 0.529412, 0.137255},{0.862745, 0.627451, 0.098039}};//light dark middle
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


    for( int i = 0 ; i < 8 ; i++ ){//left
        point[i][2] += 2;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 2;
    }
    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
   glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
   glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot42(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    GLdouble yellow[3][3] = {{0.980392,0.745098,0.019608},{0.72549, 0.529412, 0.137255},{0.862745, 0.627451, 0.098039}};//light dark middle
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




    for( int i = 0 ; i < 8 ; i++ ){//left
        point[i][2] += 2;

    }
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }
    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 3;
    }
    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h42
        for( int j = 0 ; j < 3 ; j++){
            yellow[i][j] *= 1.1;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
   glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
   glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot43(){
    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    GLdouble yellow[3][3] = {{0.980392,0.745098,0.019608},{0.72549, 0.529412, 0.137255},{0.862745, 0.627451, 0.098039}};//light dark middle
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
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 2;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            yellow[i][j] *= 1.2;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
   glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
   glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::histoPlot44(){
    /*
     * remember : adjust position and color
     *move back in x-axis and set color lighter
     */

    double point[8][3] = {{0.5-0.1,1,-2},{0.5-0.1,1,-3+0.1},{-0.5,1,-3+0.1},{-0.5,1,-2},
                          {0.5-0.1,-1,-2},{0.5-0.1,-1,-3+0.1},{-0.5,-1,-3+0.1},{-0.5,-1,-2}};
    double delta[] = {-0.15,-0.1,-0.05,-0.01,0,0.01,0.05,0.1,0.15,0.2};
    GLdouble yellow[3][3] = {{0.980392,0.745098,0.019608},{0.72549, 0.529412, 0.137255},{0.862745, 0.627451, 0.098039}};//light dark middle
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
    for( int i = 0 ; i < 8 ; i++){// move front
        point[i][0] += 0.5;
    }

    for( int i = 0 ; i < 8 ; i++){// move back for h43
        point[i][0] -= 3;
    }

    for( int i = 0 ; i < 3 ; i++ ){//adjust the color for h43
        for( int j = 0 ; j < 3 ; j++){
            yellow[i][j] *= 1.23;
        }
    }

    //
    //glColor3f(1.0, 0.0, 0.0);
    //glColor4f(0.9765625, 0.1953125, 0.1953125,1.0);// alpha
    //glColor3f(0.9765625, 0.1953125, 0.1953125);
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);//glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);
    //
    glColor3f(yellow[0][0],yellow[0][1],yellow[0][2]);
    //glColor4f(0.0,0.2,0.2,0.5);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    // ǰ
   glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[0][0], point[0][1], point[0][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //
     //glColor4f(0.60546875, 0.390625, 0.390625,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[1][0],yellow[1][1],yellow[1][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[2][0], point[2][1], point[2][2]);

    //left
   glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glVertex3f(point[2][0], point[2][1], point[2][2]);
    glVertex3f(point[6][0], point[6][1], point[6][2]);
    glVertex3f(point[7][0], point[7][1], point[7][2]);
    glVertex3f(point[3][0], point[3][1], point[3][2]);

    //left
     //glColor4f(0.7421875, 0.1953125, 0.1953125,1);
    //glColor4f(0.4, 0.6, 0.6,0.5);
    glColor3f(yellow[2][0],yellow[2][1],yellow[2][2]);
    glVertex3f(point[1][0], point[1][1], point[1][2]);
    glVertex3f(point[5][0], point[5][1], point[5][2]);
    glVertex3f(point[4][0], point[4][1], point[4][2]);
    glVertex3f(point[0][0], point[0][1], point[0][2]);

}

void mygl2::keyPressEvent(QKeyEvent *event)
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

void mygl2::timerEvent(QTimerEvent *event){
    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);

    histoPlot11();histoPlot12();histoPlot13();histoPlot14();
    histoPlot21();histoPlot22();histoPlot23();histoPlot24();
    histoPlot31();histoPlot32();histoPlot33();histoPlot34();
    histoPlot41();histoPlot42();histoPlot43();histoPlot44();
    //floor
    wallplot();
    glEnd();
    updateGL();
    //qDebug()<< "timer event in mygl2 Class!" << endl;
}

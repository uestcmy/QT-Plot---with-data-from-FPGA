#include "channel.h"
#include "ui_channel.h"
#include <QDebug>

Channel::Channel(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Channel)
{
    ui->setupUi(this);

    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 310;
    InputManagement();
    id1 = startTimer(100);

}

Channel::~Channel()
{
    delete ui;
}



void Channel::initializeGL()
{
    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}
void Channel::resizeGL(int w, int h)
{
    glViewport(-10, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //luPerspective(40.0, (GLfloat)w/(GLfloat)h, 2, 30.0);
    //gluPerspective(40,1.33, 2, 30.0);
    glOrtho (-4 * ( GLfloat ) w / ( GLfloat ) h, 4* ( GLfloat ) w / ( GLfloat ) h, -3, 5, -5, 15.0);
     //glFrustum (-1.5 * ( GLfloat ) w / ( GLfloat ) h, 2.3* ( GLfloat ) w / ( GLfloat ) h, -2, 2, 4.3, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Ⱦ
void Channel::paintGL()
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
    //histoPlot2();
    //histoPlot3();
    //histoPlot4();
    //floor

    //wallplot();
    glEnd();
    edgeplot();
    meshplot();
}
void Channel::unitmeshplot(int i,int j,double xstart,double zstart,double xstep,double zstep,int dx,int dz){
    double c = *(pdata+j*300+i*dx);
    c -= -3;
    c /= 6;

    glColor3f(c,0.1,1-c);
    glBegin(GL_QUADS);
    glVertex3f(xstart-i*xstep,*(pdata+j*300+i*dx),zstart-j*zstep);
    glVertex3f(xstart-(i+1)*xstep,*(pdata+j*300+(i+1)*dx),zstart-j*zstep);
    glVertex3f(xstart-(i+1)*xstep,*(pdata+(j+1)*300+(i+1)*dx),zstart-(j+1)*zstep);
    glVertex3f(xstart-i*xstep,*(pdata+(j+1)*300+(i)*dx),zstart-(j+1)*zstep);
    glEnd();
/*
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    glVertex3f(xstart-i*xstep,*(pdata+j*300+i*dx),zstart-j*zstep);
    glVertex3f(xstart-(i+1)*xstep,*(pdata+j*300+(i+1)*dx),zstart-j*zstep);
    glVertex3f(xstart-(i+1)*xstep,*(pdata+(j+1)*300+(i+1)*dx),zstart-(j+1)*zstep);
    glVertex3f(xstart-i*xstep,*(pdata+(j+1)*300+(i)*dx),zstart-(j+1)*zstep);
    glEnd();
    */
}
void Channel::meshplot(){
    int m = 300;//x
    int n = 10;//z
    double xstep = 6.0/m;
    double zstep = 6.0/n;
    double dx = 300/m;//sample point
    double xstart = 2;//decrease
    double zstart = 2;//decrease
    for( int i = 0 ; i < m ; i++){
        for( int j = 0 ; j < n ; j++){
            unitmeshplot(i,j,xstart,zstart,xstep,zstep,dx,1);
        }
    }
}
void Channel::edgeplot(){
    double point2[8][3] = {{2,3,2},{-4,3,2},{-4,3,-4},{2,3,-4},{2,-1,2},{-4,-1,2},{-4,-1,-4},{2,-1,-4}};
    glBegin(GL_LINE_LOOP);
    glColor4f(0, 0, 0,1);

    glVertex3f(point2[0][0], point2[0][1], point2[0][2]);
    glVertex3f(point2[1][0], point2[1][1], point2[1][2]);
    glVertex3f(point2[2][0], point2[2][1], point2[2][2]);
    glVertex3f(point2[3][0], point2[3][1], point2[3][2]);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
    glEnd();
    glBegin(GL_LINE);
    glVertex3f(point2[0][0], point2[0][1], point2[0][2]);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);

    glVertex3f(point2[1][0], point2[1][1], point2[1][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);

    glVertex3f(point2[2][0], point2[2][1], point2[2][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);

    glVertex3f(point2[3][0], point2[3][1], point2[3][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
    glEnd();
    glEnd();
}

void Channel::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,2},{-2,-1,2},{-2,-1,-4},{2,-1,-4}};
    glColor4f(0, 0, 0,0.2);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
}
void Channel::histoPlot1(){
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

void Channel::histoPlot2(){
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

void Channel::histoPlot3(){
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

void Channel::histoPlot4(){
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

void Channel::keyPressEvent(QKeyEvent *event)
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

void Channel::timerEvent(QTimerEvent *event){
    glBegin(GL_QUADS);

    glEnable (GL_LINE_SMOOTH );
    glHint (GL_POLYGON_SMOOTH , GL_NICEST);

    //histoPlot1();
    histoPlot2();
    //histoPlot3();
    //histoPlot4();
    //floor
    //wallplot();
    glEnd();
    updateGL();
    //qDebug()<< "timer event in mygl2 Class!" << endl;
}

void Channel::InputManagement(){
    static double h41[1000][300] = {0};
    QFile file("h_300_1000_re.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << file.errorString();
    char str[100];

    int length = 1000;
    for( int i = 0 ; i < length ; i++ ){
        for( int j = 0 ; j < 300 ; j++ ){
            file.readLine(str,100);
            double crr = 0;
            crr = char2double(str);
            //qDebug() << "crr is :"<<crr;
            h41[i][j] = crr*100;
        }
    }
    //qDebug() << "h41[40][299] one is :"<< h41[40][299] ;
    pdata = &h41[0][0];
    file.close();
}
double Channel::char2double(char *str){
    /*
     *  eg. 0.000815    -0.000551
     */
    double ans = 0;
    double weight = 0.1;
    if(str[0] == '-'){
        ans = str[1]-'0';
        for(int i = 3 ; i < 9 ; i++ ){
            ans += (str[i] - '0') * weight;
            weight /= 10;
        }
        ans *= -1;
    }
    else{
        ans = str[0]-'0';
        for(int i= 2 ; i < 8 ; i++ ){
            ans += (str[i] - '0') * weight;
            weight /= 10;
        }
    }
    return ans;
}

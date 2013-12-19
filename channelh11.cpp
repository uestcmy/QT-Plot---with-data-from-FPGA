#include "channelh11.h"
#include "ui_channelh11.h"
#include <QDebug>

ChannelH11::ChannelH11(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::ChannelH11)
{
    ui->setupUi(this);
    translate = -6.0;
    xRot = yRot = zRot = 0.0;
    xRot += 20;
    yRot += 340;
    InputManagement();
    //add txt




    id1 = startTimer(100);


}

ChannelH11::~ChannelH11()
{
    delete ui;
}

void ChannelH11::initializeGL()
{


    glClearColor(0.8,0.8,0.8,0);//canvas
    glShadeModel(GL_SMOOTH);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);


}

void ChannelH11::resizeGL(int w, int h)
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
void ChannelH11::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glTranslatef(0.0, 0.0, translate);// translate is included in <QKeyEvent>
    glTranslatef(0.0, -0.5, 0.3);// translate is included in <QKeyEvent>

    glRotatef(xRot, 1.0, 0.0, 0.0);
    glRotatef(yRot, 0.0, 1.0, 0.0);
    glRotatef(zRot, 0.0, 0.0, 1.0);


    //(-4,3,-6) is the position of the left-down corner of  the text




    meshplot(2);


    edgeplot();
}
void ChannelH11::unitmeshplot(int i,int j,double xstart,double zstart,double xstep,double zstep,int dx,int dz){
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
void ChannelH11::meshplot(int jstart){
    int m = 300;//x
    int n = 30;//z
    double xstep = 6.0/m;
    double zstep = 8.0/n;
    double dx = 300/m;//sample point
    double xstart = 2;//decrease
    double zstart = 2;//decrease
    pdata = pdata + jstart * 300;
    //QDebug() << zstart <<endl();
    if( pdata - pdata2 > 300*700){
        pdata = pdata2;
    }
    //qDebug()<< pdata2-pdata << endl;
    for( int i = 0 ; i < m ; i++){
        for( int j = 0 ; j < n ; j++){
            unitmeshplot(i,j,xstart,zstart,xstep,zstep,dx,1);
        }
    }
}
void ChannelH11::edgeplot(){
    double point2[8][3] = {{2,3,2},{-4,3,2},{-4,3,-6},{2,3,-6},{2,-1,2},{-4,-1,2},{-4,-1,-6},{2,-1,-6}};
    glColor4f(0, 0, 0,1);

    //原点 0
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3, point2[5][1]-0.3, point2[5][2], "0", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3+5*0.2, point2[5][1]-0.3, point2[5][2], "50", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3+10*0.2, point2[5][1]-0.3, point2[5][2], "100", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3+15*0.2, point2[5][1]-0.3, point2[5][2], "150", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3+20*0.2, point2[5][1]-0.3, point2[5][2], "200", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3+25*0.2, point2[5][1]-0.3, point2[5][2], "250", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3+30*0.2, point2[5][1]-0.3, point2[5][2], "300", QFont("Arial", 12, QFont::Bold, false) );

    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3, point2[5][1]-0.3+5*0.2+0.1, point2[5][2], "5", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3-0.1, point2[5][1]-0.3+10*0.2+0.1, point2[5][2], "10", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3-0.1, point2[5][1]-0.3+15*0.2+0.1, point2[5][2], "15", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[5][0]-0.3-0.1, point2[5][1]-0.3+20*0.2+0.1, point2[5][2], "20", QFont("Arial", 12, QFont::Bold, false) );


    glBegin(GL_LINE);
    //glVertex3f(point2[0][0], point2[0][1], point2[0][2]);
    glVertex3f(point2[1][0], point2[1][1], point2[1][2]);
    glVertex3f(point2[2][0], point2[2][1], point2[2][2]);
    //glVertex3f(point2[3][0], point2[3][1], point2[3][2]);
    glEnd();

    //left ruler blue H
    glColor4f(0.2, 0.4, 0.8,1);
    for( int i = 1 ; i < 20 ; i++){
        glBegin(GL_LINE);
        //glVertex3f(point2[0][0], point2[0][1]-0.1*i, point2[0][2]);
        glVertex3f(point2[1][0], point2[1][1]-0.2*i, point2[1][2]);
        glVertex3f(point2[2][0], point2[2][1]-0.2*i, point2[2][2]);
       // glVertex3f(point2[3][0], point2[3][1]-0.1*i, point2[3][2]);
        glEnd();
    }
    // down sub-carrier
     glColor4f(1,0,0,1);
    for( int i = 1 ; i < 30 ; i++){
        glBegin(GL_LINE);
        //glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
        glVertex3f(point2[5][0]+0.2*i, point2[5][1], point2[5][2]);
        glVertex3f(point2[6][0]+0.2*i, point2[6][1], point2[6][2]);
        //glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
        glEnd();
    }
    //left time
    glColor4f(0,0, 1,0.5);
    for( int i = 1 ; i < 30-3 ; i++){
        glBegin(GL_LINE);
        //glVertex3f(point2[0][0], point2[0][1], point2[0][2]);
        glVertex3f(point2[1][0], point2[1][1], point2[1][2]-0.3*i);
        glVertex3f(point2[5][0], point2[5][1], point2[5][2]-0.3*i);
        //glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
        glEnd();
    }
    //down time
    glColor4f(1, 0, 0,0.5);
    for( int i = 1 ; i < 30-3 ; i++){
        glBegin(GL_LINE);
        glVertex3f(point2[4][0], point2[4][1], point2[4][2]-0.3*i);
        glVertex3f(point2[5][0], point2[5][1], point2[5][2]-0.3*i);
        glEnd();
    }

    glColor3f(0,0,0);
    renderText(point2[4][0]+0.5, point2[4][1]-0.3, point2[4][2], "Sub-carrier", QFont("Arial", 12, QFont::Bold, false) );
    glColor3f(0,0,0);
    renderText(point2[7][0], point2[7][1], point2[7][2], "Time", QFont("Arial", 12, QFont::Bold, false) );

    glColor4f(0, 0, 0,1);
    glBegin(GL_LINE_LOOP);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
    glEnd();

    glColor3f(0,0,0);
    renderText(point2[1][0]-0.5, point2[1][1]+0.5, point2[1][2], "H11", QFont("Arial", 12, QFont::Bold, false) );
    glColor4f(0, 0, 0,1);
    glBegin(GL_LINE);
   // glVertex3f(point2[0][0], point2[0][1], point2[0][2]);
    glVertex3f(point2[1][0], point2[1][1], point2[1][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    //glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glEnd();

    glColor4f(0, 0, 0,1);
    glBegin(GL_LINE);
    glVertex3f(point2[2][0], point2[2][1], point2[2][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    //glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
    //glVertex3f(point2[3][0], point2[3][1], point2[3][2]);
    glEnd();

}


void ChannelH11::wallplot(){
    double point2[8][3] = {{2,2,2},{-2,2,2},{-2,2,-2},{2,2,-2},{2,-1,2},{-2,-1,2},{-2,-1,-4},{2,-1,-4}};
    glColor4f(0, 0, 0,0.2);
    glVertex3f(point2[4][0], point2[4][1], point2[4][2]);
    glVertex3f(point2[5][0], point2[5][1], point2[5][2]);
    glVertex3f(point2[6][0], point2[6][1], point2[6][2]);
    glVertex3f(point2[7][0], point2[7][1], point2[7][2]);
}


void ChannelH11::keyPressEvent(QKeyEvent *event)
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

void ChannelH11::timerEvent(QTimerEvent *event){
    meshplot(10);
    updateGL();
    //qDebug()<< "timer event in mygl2 Class!" << endl;
}

void ChannelH11::InputManagement(){
    static double h41[1000][300] = {0};
    QFile file("./FPGA_Plot_Data/h_300_1000_re.txt");
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
            h41[i][j] = crr*10;
        }
    }
    //qDebug() << "h41[40][299] one is :"<< h41[40][299] ;
    pdata = &h41[0][0];
    pdata2 = pdata;
    file.close();
}
double ChannelH11::char2double(char *str){
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

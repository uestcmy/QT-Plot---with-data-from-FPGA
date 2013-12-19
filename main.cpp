

#include <QApplication>
#include <mygl2.h>
#include <channelcapacity.h>
#include <qpsk.h>
#include <channelh11.h>
#include <multiwindow.h>
#include <networklink.h>
#include <chcap.h>

#include <GL/glut.h>


int main(int argc, char *argv[])
{
    QApplication app(argc,argv);
    /*
    MultiWindow w;
    w.resize(1300,768);
    w.show();
    w.setWindowTitle("State");
    */
    /*

    QApplication app(argc,argv);
    mygl2 w;
    w.resize(600,450);
    w.show();
    w.setWindowTitle("FPGA Resource State");

    ChannelCapacity w2;
    w2.resize(600,450);
    w2.show();
    w2.setWindowTitle("Channel Capacity");

    QPSK w3;
    w3.resize(600,450);
    w3.show();
    w3.setWindowTitle("QPSK Star");
*/
    ChannelH11 w4;
    w4.resize(600,450);
    w4.show();
    w4.setWindowTitle("Channel State");



    return app.exec();

}


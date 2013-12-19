#include "multiwindow.h"
#include "ui_multiwindow.h"
#include <mygl2.h>
#include <channelcapacity.h>
#include <qpsk.h>
#include <channel.h>
#include <subwindow.h>
#include <subwindow2.h>
#include <networklink.h>

#include <QLabel>
#include <QtGui>
#include <QPainter>
#include <stdio.h>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QtGui/QApplication>
#include <QFileInfo>
#include <QDebug>
#include <QTextCodec>
#include <QStringList>
#include <QDateTime>
#include <qapplication.h>
#include <qlayout.h>

MultiWindow::MultiWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MultiWindow)
{
    ui->setupUi(this);
    mygl2 *w1 = new mygl2(this);
    ChannelCapacity *w2 = new ChannelCapacity(this);
    NetworkLink *w3 = new NetworkLink(this);//fake
    QPSK *w4 = new QPSK(this);
    SubWindow *w5 = new SubWindow(this);
    SubWindow2 *w6 = new SubWindow2(this);

    QGridLayout *layout = new QGridLayout;
 //   Plot *plot = new Plot();
 //   layout->addWidget( plot,1,0 );
    layout->addWidget(w1, 1, 0);
    layout->addWidget(w2, 1, 1);
    layout->addWidget(w3, 2, 0);
    layout->addWidget(w4, 2, 1);
    layout->addWidget(w5, 1, 2);
    layout->addWidget(w6, 2, 2);

    setLayout(layout);

    setWindowTitle(tr("System Status"));
    setGeometry(100,100,800+60,600+45);

}

MultiWindow::~MultiWindow()
{
    delete ui;
}

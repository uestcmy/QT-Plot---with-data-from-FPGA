#include "subwindow2.h"
#include "ui_subwindow2.h"

#include <channel.h>
#include <channelh11.h>
#include <channelh12.h>
#include <channelh21.h>
#include <channelh22.h>


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


SubWindow2::SubWindow2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubWindow2)
{// render the left two subwindow1
    ui->setupUi(this);

    ChannelH21 *w5 = new ChannelH21(this);
    ChannelH22 *w6 = new ChannelH22(this);

    QGridLayout *layout = new QGridLayout;
 //   Plot *plot = new Plot();
 //   layout->addWidget( plot,1,0 );
    layout->addWidget(w5, 1, 0);
    layout->addWidget(w6, 2, 0);

    setLayout(layout);

    //setWindowTitle(tr("System Status"));
    setGeometry(100,100,800+60,600+45);
}

SubWindow2::~SubWindow2()
{
    delete ui;
}

#include "subwindow.h"
#include "ui_subwindow.h"
#include <channel.h>
#include <channelh11.h>
#include <channelh12.h>

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


SubWindow::SubWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubWindow)
{// render the left two subwindow1
    ui->setupUi(this);

    ChannelH11 *w5 = new ChannelH11(this);
    ChannelH12 *w6 = new ChannelH12(this);

    QGridLayout *layout = new QGridLayout;
 //   Plot *plot = new Plot();
 //   layout->addWidget( plot,1,0 );
    layout->addWidget(w5, 1, 0);
    layout->addWidget(w6, 2, 0);

    setLayout(layout);

    //setWindowTitle(tr("System Status"));
    setGeometry(100,100,800+60,600+45);
}

SubWindow::~SubWindow()
{
    delete ui;
}

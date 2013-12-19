#ifndef SUBWINDOW_H
#define SUBWINDOW_H

#include <QWidget>

namespace Ui {
class SubWindow;
}

class SubWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit SubWindow(QWidget *parent = 0);
    ~SubWindow();
    
private:
    Ui::SubWindow *ui;
};

#endif // SUBWINDOW_H

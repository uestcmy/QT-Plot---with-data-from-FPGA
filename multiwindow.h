#ifndef MULTIWINDOW_H
#define MULTIWINDOW_H

#include <QWidget>

namespace Ui {
class MultiWindow;
}

class MultiWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit MultiWindow(QWidget *parent = 0);
    ~MultiWindow();
    
private:
    Ui::MultiWindow *ui;
};

#endif // MULTIWINDOW_H

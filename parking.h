#ifndef PARKING_H
#define PARKING_H

#include <QDialog>

namespace Ui {
class parking;
}

class parking : public QDialog
{
    Q_OBJECT

public:
    //Login conn;
    explicit parking(QWidget *parent = 0);
    ~parking();

private slots:
    void ButtonPressed();

private:
    Ui::parking *ui;
};

#endif // PARKING_H

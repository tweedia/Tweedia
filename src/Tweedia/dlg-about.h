#ifndef DLGABOUT_H
#define DLGABOUT_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class DlgAbout;
}

class DlgAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DlgAbout(QWidget *parent = 0);
    ~DlgAbout();

private:
    Ui::DlgAbout *ui;

    QPixmap *logo;
};

#endif // DLGABOUT_H

#ifndef WGTHISTGRAMNUMBER_H
#define WGTHISTGRAMNUMBER_H

#include <QWidget>
#include <QPainter>
#include <QList>

#include "obsobj.h"
#include "exec-obsobj.h"

namespace Ui {
class WgtHistgramNumber;
}

class WgtHistgramNumber : public QWidget
{
    Q_OBJECT

public:
    explicit WgtHistgramNumber(QWidget *parent = 0, Obsobj *obsobj = 0, int rowOfTableView = 0);
    ~WgtHistgramNumber();

    void refreashWithRowOfTableView();

public slots:
    void on_DatabaseUpdated();

protected:
    void paintEvent_drawHistgram();
    void paintEvent_drawAxis();
    void paintEvent(QPaintEvent *);

private slots:
    void on_spinBox_valueChanged(int arg1);

private:
    Ui::WgtHistgramNumber *ui;

    QSqlTableModel mQSqlTableModel;

    Obsobj *mObsobj;
    int mRowOfTableView;
    ExecObsobj *mExecObsobj;

    int mResolution;
    int mWidth, mHeight, mXmargin, mYmargin, mXpadding, mYpadding;

    QList<int> mlist;
};

#endif // WGTHISTGRAMNUMBER_H

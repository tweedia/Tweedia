#ifndef STRINGVIEWSCROLL_H
#define STRINGVIEWSCROLL_H

#include <QWidget>
#include <QSqlTableModel>

#include "obsobj.h"
#include "exec-obsobj.h"

namespace Ui {
class StringviewScroll;
}

class StringviewScroll : public QWidget
{
    Q_OBJECT
    
public:
    explicit StringviewScroll(QWidget *parent = 0, Obsobj *obsobj = 0, int rowOfTableView = 0);
    ~StringviewScroll();
    
    void refreashWithRowOfTableView();

public slots:
    void on_DatabaseUpdated();

private slots:
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::StringviewScroll *ui;

    QSqlTableModel mQSqlTableModel;

    Obsobj *mObsobj;
    int mRowOfTableView;
    ExecObsobj *mExecObsobj;
};

#endif // STRINGVIEWSCROLL_H

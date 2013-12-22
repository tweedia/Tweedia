#ifndef DLGCREATERESULTTABLE_H
#define DLGCREATERESULTTABLE_H

#include <QDialog>
#include <QString>

namespace Ui {
class DlgCreateResultTable;
}

class DlgCreateResultTable : public QDialog
{
    Q_OBJECT

public:
    explicit DlgCreateResultTable(QWidget *parent = 0);
    ~DlgCreateResultTable();

    QString SqlCreateResultTbl(){return mSqlCreateResultTbl;}

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DlgCreateResultTable *ui;

    QStringList mOptionTableType;

    QString mSqlCreateResultTbl;

    QString mSqlCreateObsobj;

};

#endif // DLGCREATERESULTTABLE_H

#ifndef DLGCREATERESULTTABLE_H
#define DLGCREATERESULTTABLE_H

#include <QDialog>

namespace Ui {
class DlgCreateResultTable;
}

class DlgCreateResultTable : public QDialog
{
    Q_OBJECT

public:
    explicit DlgCreateResultTable(QWidget *parent = 0);
    ~DlgCreateResultTable();

private:
    Ui::DlgCreateResultTable *ui;
};

#endif // DLGCREATERESULTTABLE_H

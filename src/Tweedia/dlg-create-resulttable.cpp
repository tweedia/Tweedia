#include "dlg-create-resulttable.h"
#include "ui_dlg-create-resulttable.h"

DlgCreateResultTable::DlgCreateResultTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCreateResultTable)
{
    ui->setupUi(this);
}

DlgCreateResultTable::~DlgCreateResultTable()
{
    delete ui;
}

#include "dlg-create-resulttable.h"
#include "ui_dlg-create-resulttable.h"

DlgCreateResultTable::DlgCreateResultTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCreateResultTable)
{
    ui->setupUi(this);

    mOptionTableType.append("Simple");
    ui->uiTableType->addItems(mOptionTableType);

    ui->uiTableName->setText("result1");

    mSqlCreateResultTbl = QString();

}

DlgCreateResultTable::~DlgCreateResultTable()
{
    delete ui;
}

void DlgCreateResultTable::on_buttonBox_accepted()
{
    QString selectedType(ui->uiTableType->currentText());
    QString tableName(ui->uiTableName->text());

    mSqlCreateResultTbl.clear();

    if (selectedType=="Simple")
    {
        mSqlCreateResultTbl.append("CREATE TABLE " + tableName);
        mSqlCreateResultTbl.append("(");
        mSqlCreateResultTbl.append("id integer NOT NULL,");
        mSqlCreateResultTbl.append("result bytea,");
        mSqlCreateResultTbl.append("CONSTRAINT " + tableName + "_pkey PRIMARY KEY (id)");
        mSqlCreateResultTbl.append(")");

    }

}

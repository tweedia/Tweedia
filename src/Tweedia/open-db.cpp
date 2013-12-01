#include "open-db.h"
#include "ui_open-db.h"

OpenDb::OpenDb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OpenDb)
{
    ui->setupUi(this);

    mOptionmDbmsname.append("PostgreSQL");
    ui->uiDbmsname->addItems(mOptionmDbmsname);
    ui->uiHostname->setText(QString("localhost"));
    ui->uiPort->setText(QString("5432"));
    ui->uiDbName->setText(QString("postgres"));
//    mOptionDbname.append("");
//    ui->uiDbname->addItems(mOptionDbname);
}

OpenDb::~OpenDb()
{
    delete ui;
}

void OpenDb::on_buttonBox_accepted()
{
    mDbmsname.clear();
    if (ui->uiDbmsname->currentText() == "PostgreSQL")
    {
        mDbmsname.append("QPSQL");
    }

    mHostname.clear();
    mHostname.append(ui->uiHostname->text());

    mPort = ui->uiPort->text().toInt();

    mDbname.clear();
    mDbname.append(ui->uiDbName->text());

}

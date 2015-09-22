/* dlg-open-db.cpp */

/* Copyright (C) 2013 Takenobu Noda

   This file is part of Tweedia.

   Tweedia is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   Tweedia is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with Tweedia. If not, see <http://www.gnu.org/licenses/>.
*/

/* Birthdate:
   Dec 01, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#include "dlg-open-db.h"
#include "ui_dlg-open-db.h"

DlgOpenDb::DlgOpenDb(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgOpenDb)
{
    ui->setupUi(this);

    mOptionmDbmsname.append("SQLite");
    mOptionmDbmsname.append("PostgreSQL");
    ui->uiDbmsname->addItems(mOptionmDbmsname);
    ui->uiDbName->setText(QString("tweediadb"));
//    mOptionDbname.append("");
//    ui->uiDbname->addItems(mOptionDbname);
//    ui->uiPluginDir->setText("/Users/testnoda/Documents/sample/plugin/");
//    ui->uiPluginDir->setText("/Users/testnoda/Documents/Github/build-Tweedia-with-plugins-Debug/PageWidgetPlugin/");
    ui->uiPluginDir->setText("/Users/testnoda/Documents/Github/build-Tweedia-with-plugins-Debug/ScrollWidgetPlugin/");
    ui->uiObsobjname->setText("obsobj");
    ui->uiObsprefix->setText("observation_");
}

DlgOpenDb::~DlgOpenDb()
{
    delete ui;
}

void DlgOpenDb::on_buttonBox_accepted()
{
    mDbmsname.clear();

    QString strdbmsname = ui->uiDbmsname->currentText();

    if (strdbmsname == "SQLite") mDbmsname.append("QSQLITE");
    else if (strdbmsname == "PostgreSQL") mDbmsname.append("QPSQL");

    mHostname.clear();
    mHostname.append(ui->uiHostname->text());

    mPort = ui->uiPort->text().toInt();

    mDbname.clear();
    mDbname.append(ui->uiDbName->text());

    mPluginDir.clear();
    mPluginDir.append(ui->uiPluginDir->text());

    mObsobjname.clear();
    mObsobjname.append(ui->uiObsobjname->text());

    mObsprefix.clear();
    mObsprefix.append(ui->uiObsprefix->text());

}

void DlgOpenDb::on_uiDbmsname_currentIndexChanged(const QString &arg1)
{
    QString strdbmsname = ui->uiDbmsname->currentText();

    if (strdbmsname == "SQLite") {
        ui->lblHostname->hide();
        ui->uiHostname->hide();
        ui->lblPort->hide();
        ui->uiPort->hide();
        ui->uiDbName->setText(QString("tweediadb"));
    } else if (strdbmsname == "PostgreSQL") {
        ui->lblHostname->show();
        ui->uiHostname->show();
        ui->uiHostname->setText(QString("localhost"));
        ui->lblPort->show();
        ui->uiPort->show();
        ui->uiPort->setText(QString("5432"));
        ui->uiDbName->setText(QString("postgres"));
    }

}

/* open-db.cpp */

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

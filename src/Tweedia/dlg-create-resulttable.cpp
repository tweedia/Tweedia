/* dlg-create-resulttable.cpp */

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
   Dec 20, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

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

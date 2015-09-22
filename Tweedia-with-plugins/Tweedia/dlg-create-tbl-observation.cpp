/* dlg-create-tbl-observation.cpp */

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

#include "dlg-create-tbl-observation.h"
#include "ui_dlg-create-tbl-observation.h"

DlgCreateTblObservation::DlgCreateTblObservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgCreateTblObservation)
{
    ui->setupUi(this);

    mOptionTableType.append("Simple");
    ui->uiTableType->addItems(mOptionTableType);

    ui->uiTableName->setText(TBL_OBSERVATION);

    mSqlCreateTblObservation = QString();

}

DlgCreateTblObservation::~DlgCreateTblObservation()
{
    delete ui;
}

void DlgCreateTblObservation::on_buttonBox_accepted()
{
    QString selectedType(ui->uiTableType->currentText());
    QString tableName(ui->uiTableName->text());

    mSqlCreateTblObservation.clear();

    if (selectedType=="Simple")
    {
        mSqlCreateTblObservation.append("CREATE TABLE " + tableName);
        mSqlCreateTblObservation.append("(");
        mSqlCreateTblObservation.append(COL_OBSERVATION_ID " " COL_OBSERVATION_ID_TYPE_SQLITE ",");
        mSqlCreateTblObservation.append(COL_OBSERVATION_OBSERVATION " " COL_OBSERVATION_OBSERVATION_TYPE_SQLITE ",");
        mSqlCreateTblObservation.append("CONSTRAINT " + tableName + "_pkey PRIMARY KEY (" COL_OBSERVATION_ID ")");
        mSqlCreateTblObservation.append(")");

    }

}

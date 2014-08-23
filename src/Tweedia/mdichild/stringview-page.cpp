/* stringview-page.cpp */

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
   Saturday, Novenber 2nd, 2013; Saitama, Japan
   Initial author: Takenobu Noda
*/

#include "stringview-page.h"
#include "ui_stringview-page.h"

StringviewPage::StringviewPage(QWidget *parent, Obsobj *obsobj, int rowOfTableView) :
    QWidget(parent),
    ui(new Ui::StringviewPage)
{
    ui->setupUi(this);

    mObsobj = obsobj;
    mRowOfTableView = rowOfTableView;
    refreashWithRowOfTableView();

    mValueAsQString = QString();

}

void StringviewPage::refreashWithRowOfTableView()
{
    mExecObsobj = mObsobj->updatedExecObsobj(mRowOfTableView);

    this->setWindowTitle(mExecObsobj->Pathname());
    ui->lblTableName->setText(mExecObsobj->Tablename());
    ui->spinBox->setValue(mExecObsobj->Maxid());

    // Cast for QString
    mValueAsQString.clear();
    mValueAsQString.append(mExecObsobj->ObservationWhereMaxid().constData());

    ui->textBrowser->setText(mValueAsQString);

}

StringviewPage::~StringviewPage()
{
    delete ui;
}

void StringviewPage::on_pushButton_clicked()
{
    refreashWithRowOfTableView();
}

void StringviewPage::on_DatabaseUpdated()
{
    StringviewPage::refreashWithRowOfTableView();
}

void StringviewPage::on_spinBox_valueChanged(int arg1)
{
    mExecObsobj = mObsobj->updatedExecObsobj(mRowOfTableView);

    ui->lblTableName->setText(mExecObsobj->Tablename());
//    ui->spinBox->setValue(mExecObsobj->Maxid());

    // Cast for QString
    mValueAsQString.clear();
    mValueAsQString.append(mExecObsobj->ObservationWhereTheid(arg1));

    ui->textBrowser->setText(mValueAsQString);

}

/* References, Quotation:
 */


/* wgt-scroll-string.cpp */

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
   Monday, Aug 4th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
*/

#include "wgt-scroll-string.h"
#include "ui_wgt-scroll-string.h"

WgtScrollString::WgtScrollString(QWidget *parent, Obsobj *obsobj, int rowOfTableView) :
    QWidget(parent),
    ui(new Ui::WgtScrollString)
{
    ui->setupUi(this);

    mObsobj = obsobj;
    mRowOfTableView = rowOfTableView;

    ui->tableView->setShowGrid(FALSE);
//    ui->tableView->setWordWrap(TRUE);
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->hide();

    refreashWithRowOfTableView();

    this->on_checkBox_stateChanged(0);

}

void WgtScrollString::refreashWithRowOfTableView()
{
    mExecObsobj = mObsobj->updatedExecObsobj(mRowOfTableView);

    this->setWindowTitle(mExecObsobj->Pathname());
    ui->lblTableName->setText(mExecObsobj->Tablename());

    mQSqlTableModel.setTable((const QString)mExecObsobj->Tablename());
    mQSqlTableModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    mQSqlTableModel.select();

    ui->tableView->setModel(&mQSqlTableModel);

    ui->tableView->scrollToBottom();

    //it is said that setResizeMode() is no longer available for Qt5
    //and that setSectionResizeMode() can be used
    ui->tableView->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

}

WgtScrollString::~WgtScrollString()
{
    delete ui;
}

void WgtScrollString::on_DatabaseUpdated()
{
    WgtScrollString::refreashWithRowOfTableView();
}

void WgtScrollString::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()){
        ui->tableView->setColumnHidden(0,false);
    }else{
        ui->tableView->setColumnHidden(0,true);
    }

}

/* scroll-widget.cpp */

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
   Monday, September 21st, 2015; Saitama, Japan
   Initial author: Takenobu Noda
*/

#include "scroll-widget.h"
#include "ui_scroll-widget.h"

ScrollWidget::ScrollWidget(QWidget *parent, QSqlDatabase *argDatabase, int argObsobjID, QString argTitle) :
    QWidget(parent),
    ui(new Ui::ScrollWidget)
{
    mDatabase = argDatabase;
    mObsobjID = argObsobjID;

    ui->setupUi(this);
    QString wkString;
    wkString.clear();
    wkString.append(this->getObstblName());
    ui->lblTableName->setText((const QString)wkString);
    wkString.append(" - ");
    wkString.append(argTitle);
    this->setWindowTitle((const QString)wkString);

    mTableModel = new QSqlTableModel(this, *mDatabase);
    mTableModel->setTable((const QString)metadataOfObservation.Tablename(argObsobjID));
    mTableModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    mTableModel->select();
    ui->tableView->setModel(mTableModel);
    ui->tableView->scrollToBottom();

}

ScrollWidget::~ScrollWidget()
{
    delete ui;
}

QString ScrollWidget::getObstblName()
{
    QSqlQuery query(*mDatabase);

    query.exec((const QString)metadataOfObsObj.SqlSelectObstblName(mObsobjID));
    if (query.next()){
        mObstblName.clear();
        mObstblName.append(query.value(0).toByteArray());
    }

    return mObstblName;

}

int ScrollWidget::called_when_DatabaseUpdated()
{
    mTableModel->select();
    ui->tableView->update();
    ui->tableView->scrollToBottom();
}

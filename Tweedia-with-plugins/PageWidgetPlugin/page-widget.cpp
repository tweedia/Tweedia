/* page-widget.cpp */

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

#include "page-widget.h"
#include "ui_page-widget.h"

PageWidget::PageWidget(QWidget *parent, QSqlDatabase *argDatabase, int argObsobjID, QString argTitle) :
    QWidget(parent),
    ui(new Ui::PageWidget)
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
}

PageWidget::~PageWidget()
{
    delete ui;
}

int PageWidget::called_when_DatabaseUpdated()
{
    this->refreshWithLastObservation();
}

QString PageWidget::getObstblName()
{
    QSqlQuery query(*mDatabase);

    query.exec((const QString)metadataOfObsObj.SqlSelectObstblName(mObsobjID));
    if (query.next()){
        mObstblName.clear();
        mObstblName.append(query.value(0).toByteArray());
    }

    return mObstblName;

}

void PageWidget::refreshWithLastObservation()
{
    QSqlQuery query(*mDatabase);

    query.exec((const QString)metadataOfObservation.SqlSelectLastObservation(mObsobjID,1));
    if (query.next()){
        mObservationAsQString.clear();
        mObservationAsQString.append(query.value(1).toByteArray());
        mObservationID = query.value(0).toInt();
    }

    ui->spinBox->setValue(mObservationID);
    ui->textBrowser->setText(mObservationAsQString);
}

void PageWidget::refreshWithThisObservation(int argObservationId)
{
    QSqlQuery query(*mDatabase);

    query.exec((const QString)metadataOfObservation.SqlSelectWhereId(mObsobjID,argObservationId,1));
    if (query.next()){
        mObservationAsQString.clear();
        mObservationAsQString.append(query.value(1).toByteArray());
        mObservationID = query.value(0).toInt();
    }

    ui->spinBox->setValue(mObservationID);
    ui->textBrowser->setText(mObservationAsQString);
}

void PageWidget::on_pushButton_clicked()
{
    mObservationID = ui->spinBox->value();
    this->refreshWithThisObservation(mObservationID);
}

void PageWidget::on_spinBox_valueChanged(int argObservationId)
{
    this->refreshWithThisObservation(argObservationId);
}


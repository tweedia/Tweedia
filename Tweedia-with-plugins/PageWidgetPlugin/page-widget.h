/* page-widget.h */

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

#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include <QSqlQuery>

#include "../Tweedia/widget-plugin-interface.h"

namespace Ui {
class PageWidget;
}

class PageWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit PageWidget(QWidget *parent = 0, QSqlDatabase *argDatabase = 0, int argObsobjID = -1, QString argTitle = QString());
    int called_when_DatabaseUpdated();
    int ObsobjID() {return mObsobjID;}
    ~PageWidget();
    
private:
    Ui::PageWidget *ui;

    QSqlDatabase *mDatabase;
    int mObsobjID;
    MetadataOfObsObj metadataOfObsObj;
    MetadataOfObservation metadataOfObservation;

    QString mObstblName;

    int mObservationID;
    QString mObservationAsQString;

    QString getObstblName();
    void refreshWithLastObservation();
    void refreshWithThisObservation(int argObservationId);

private slots:
    void on_pushButton_clicked();
    void on_spinBox_valueChanged(int argObservationId);

};

#endif // PAGEWIDGET_H

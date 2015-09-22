/* scroll-widget.h */

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

#ifndef SCROLLWIDGET_H
#define SCROLLWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>

#include "../Tweedia/widget-plugin-interface.h"

namespace Ui {
class ScrollWidget;
}

class ScrollWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ScrollWidget(QWidget *parent = 0, QSqlDatabase *argDatabase = 0, int argObsobjID = -1, QString argTitle = QString());
    int called_when_DatabaseUpdated();
    int ObsobjID() {return mObsobjID;}
    ~ScrollWidget();
    
private:
    Ui::ScrollWidget *ui;

    QSqlDatabase *mDatabase;
    int mObsobjID;
    MetadataOfObsObj metadataOfObsObj;
    MetadataOfObservation metadataOfObservation;

    QString mObstblName;

    QSqlTableModel *mTableModel;

    QString getObstblName();
};

#endif // SCROLLWIDGET_H

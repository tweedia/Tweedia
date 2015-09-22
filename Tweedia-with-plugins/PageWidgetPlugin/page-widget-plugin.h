/* page-widget-plugin.h */

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

#ifndef PAGEWIDGETPLUGIN_H
#define PAGEWIDGETPLUGIN_H

#include <QtPlugin>

#include <QList>

#include "page-widget.h"

#include "../Tweedia/widget-plugin-interface.h"

class PageWidgetPlugin : public QObject, WidgetPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(WidgetPluginInterface)

public:
    explicit PageWidgetPlugin();
    ~PageWidgetPlugin();
    int set_dbinstance(QSqlDatabase *argDatabase) {mDatabase = argDatabase; return 0;}
    QWidget* new_widget(int argObsobjID);
    int called_when_DatabaseUpdated(int argObsobjID);
    QString getMenuText(){return mMenuText;}
    QObject* getCorrespondingAction() {return mCorrespondingAction;}
    int setCorrespondingAction(QObject* argAction) {mCorrespondingAction = argAction;}

private:
    QSqlDatabase *mDatabase;
    QList<PageWidget*> mPageWidgets;
    QString mMenuText;
    QObject *mCorrespondingAction;

};



#endif // PAGEWIDGETPLUGIN_H

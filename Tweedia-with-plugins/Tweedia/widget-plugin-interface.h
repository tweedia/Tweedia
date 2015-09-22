/* wiget-plugin-interface.h */

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
   Saturday, Mar 14th, 2015; Saitama, Japan
   Initial author: Takenobu Noda
*/

#ifndef WIDGETPLUGININTERFACE_H
#define WIDGETPLUGININTERFACE_H

#include "global.h"

#include <QSqlDatabase>
#include <QObject>
#include <QWidget>

class WidgetPluginInterface
{
public:
    virtual ~WidgetPluginInterface() {}
    virtual int set_dbinstance(QSqlDatabase *argDatabase) = 0;
    virtual QWidget* new_widget(int argObsobjID) = 0;
    virtual int called_when_DatabaseUpdated(int argObsobjID) = 0;
    virtual QString getMenuText() = 0;
    virtual QObject* getCorrespondingAction() = 0;
    virtual int setCorrespondingAction(QObject* argAction) = 0;
};

Q_DECLARE_INTERFACE(WidgetPluginInterface,
                    "org.tweedia.Plugin.WidgetPluginInterface/1.0");

#endif // WIDGETPLUGININTERFACE_H

/* References, Quotation:
 */

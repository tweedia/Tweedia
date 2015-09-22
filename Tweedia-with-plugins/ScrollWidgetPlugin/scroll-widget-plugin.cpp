/* scroll-widget-plugin.cpp */

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

#include "scroll-widget-plugin.h"

ScrollWidgetPlugin::ScrollWidgetPlugin() : QObject(0)
{
    mScrollWidgets.clear();
    mMenuText.clear();
    mMenuText.append("Scroll Widget");
}

ScrollWidgetPlugin::~ScrollWidgetPlugin()
{
    mScrollWidgets.clear();
}

QWidget* ScrollWidgetPlugin::new_widget(int argObsobjID)
{
    ScrollWidget* scrollWidget = new ScrollWidget(0, mDatabase, argObsobjID, mMenuText);
    mScrollWidgets.append(scrollWidget);
    return scrollWidget;
}

int ScrollWidgetPlugin::called_when_DatabaseUpdated(int argObsobjID)
{
    ScrollWidget* scrollWidget;
    for (int i = 0; i < mScrollWidgets.size(); ++i) {
        scrollWidget = mScrollWidgets.at(i);
        if (scrollWidget->ObsobjID() == argObsobjID) {
            scrollWidget->called_when_DatabaseUpdated();
        }
    }
    return 0;
}

Q_EXPORT_PLUGIN2(libScrollWidgetPlugin, ScrollWidgetPlugin);

/* References, Quotation:
 */


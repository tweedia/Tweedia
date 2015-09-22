/* page-widget-plugin.cpp */

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

#include "page-widget-plugin.h"

PageWidgetPlugin::PageWidgetPlugin(): QObject(0)
{
    mPageWidgets.clear();
    mMenuText.clear();
    mMenuText.append("Page Widget");
}

PageWidgetPlugin::~PageWidgetPlugin()
{
    mPageWidgets.clear();
}

QWidget* PageWidgetPlugin::new_widget(int argObsobjID)
{
    PageWidget* pageWidget = new PageWidget(0, mDatabase, argObsobjID, mMenuText);
    mPageWidgets.append(pageWidget);
    return pageWidget;
}

int PageWidgetPlugin::called_when_DatabaseUpdated(int argObsobjID)
{
    PageWidget* pageWidget;
    for (int i = 0; i < mPageWidgets.size(); ++i) {
        pageWidget = mPageWidgets.at(i);
        if (pageWidget->ObsobjID() == argObsobjID) {
            pageWidget->called_when_DatabaseUpdated();
        }
    }
    return 0;
}

Q_EXPORT_PLUGIN2(libPageWidgetPlugin, PageWidgetPlugin);

/* References, Quotation:
 */



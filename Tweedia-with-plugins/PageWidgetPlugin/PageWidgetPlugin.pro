#   PageWidgetPlugins.pro

#   Copyright (C) 2013 Takenobu Noda

#   This file is part of Tweedia.

#   Tweedia is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

#   Tweedia is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#   along with Tweedia. If not, see <http://www.gnu.org/licenses/>.

#   Birthdate:
#   Monday, September 21st, 2015; Saitama, Japan
#   Initial author: Takenobu Noda

QT       += gui sql

TARGET = PageWidgetPlugin
TEMPLATE = lib

CONFIG         += plugin
INCLUDEPATH    += ../Tweedia

SOURCES += page-widget-plugin.cpp \
    page-widget.cpp

HEADERS += page-widget-plugin.h \
    page-widget.h

FORMS += \
    page-widget.ui


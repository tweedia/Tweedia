#   Tweedia.pro

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
#   Wednesday, September 11st, 2013; Saitama, Japan
#   Initial author: Takenobu Noda

QT       += core gui sql xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Tweedia
TEMPLATE = app

#DESTDIR = ../../../

SOURCES += main.cpp\
        mainwindow.cpp \
    log.cpp \
    obsobj.cpp \
    parse-xml.cpp \
    command.cpp \
    exec-obsobj.cpp \
    dlg-about.cpp \
    dlg-preferences.cpp \
    dlg-open-db.cpp

HEADERS  += mainwindow.h \
    log.h \
    obsobj.h \
    parse-xml.h \
    command.h \
    exec-obsobj.h \
    command.h \
    exec-obsobj.h \
    log.h \
    obsobj.h \
    parse-xml.h \
    dlg-about.h \
    dlg-preferences.h \
    dlg-open-db.h \
    global.h \
    config.h \
    widget-plugin-interface.h

FORMS    += mainwindow.ui \
    dlg-about.ui \
    dlg-preferences.ui \
    dlg-open-db.ui

RESOURCES += \
    res/icon.qrc

mac{
ICON = res/icon.icns
}

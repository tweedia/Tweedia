/* main.cpp */

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
   Wednesday, September 11st, 2013; Saitama, Japan
   Initial author: Takenobu Noda
*/

#include "mainwindow.h"
#include <QApplication>

#include "log.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Log plog;
    int ret;

    plog.WriteLog(LOG_NOTICE, "Tweedia starting...");

    w.show();

    ret = a.exec();

    plog.WriteLog(LOG_NOTICE, "Tweedia closing...");

    return ret;
}

/* References:
*/

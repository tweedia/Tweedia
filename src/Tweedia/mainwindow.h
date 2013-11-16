/* mainwindow.h */

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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QXmlSimpleReader>

#include "command.h"
#include "parse-xml.h"
#include "obsobj.h"
#include "mdichild/txtvw-stdout.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void on_focused_ptnapp_output();

private slots:
    void on_actionNamed_pipe_triggered();

    void on_actionLoad_plugin_triggered();

    void on_actionDelete_observation_triggered();

    void on_actionStart_process_triggered();

    void on_actionRefreash_triggered();

    void on_actionOpen_textview_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    Command command;
    QXmlInputSource inputSource;
    QXmlSimpleReader reader;
    ParseXml handler;

    QSqlDatabase db;
    Obsobj *obsobj;

    QString bufActualText;

};

#endif // MAINWINDOW_H


/* References:
*/

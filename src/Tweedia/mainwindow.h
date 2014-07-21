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
#include <QWidget>
#include <QList>
#include <QMessageBox>

#include "command.h"
#include "parse-xml.h"
#include "obsobj.h"
#include "dlg-open-db.h"
#include "dlg-create-resulttable.h"
#include "mdichild/view-string-page.h"

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
    QList<QWidget*> *Mdichilds(){return mdichilds;}

private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_actionAbout_Tweedia_triggered();
    void on_actionPreferences_triggered();

    void on_actionAddObsobj_triggered();
    void on_actionDeleteObsobj_triggered();
    void on_actionRunObsobj_triggered();

    void on_actionOpenDatabase_triggered();
    void on_actionCreate_ObsobjTable_triggered();
    void on_actionCreate_ResultTable_triggered();
    void on_actionOpen_Script_triggered();

    void on_actionTweediaWiki_triggered();
    void on_actionTweediaWebsite_triggered();
    void on_actionReportBug_triggered();

    void on_actionOpen_View_of_String_as_Page_triggered();

private:
    void AboutTweedia();
    void Preferences();

    bool OpenDatabase();
    void OpenObsobj();
    void InitializeDatabase();
    void CreateResultTable();

    void AddObsobj();
    void DeleteObsobj();
    void RunObsobj();

    void OpenCommand();
    void SubmitCommand();

    void OpenViewStringPage();

    bool ChkOpenDatabase();
    bool ChkTableView();

    Ui::MainWindow *ui;

    Command command;
    QXmlInputSource inputSource;
    QXmlSimpleReader reader;
    ParseXml handler;

    QSqlDatabase db;
    Obsobj *obsobj;

    QString mSqlDropObsobj;
    QString mSqlCreateObsobj;

    QString mSqlCreateResultTbl;
    QString mSqlDropResultTbl;

    QString bufActualText;

    QList<QWidget*> *mdichilds;

};

#endif // MAINWINDOW_H


/* References:
*/

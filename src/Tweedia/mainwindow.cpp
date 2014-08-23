/* mainwindow.cpp */

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
#include "ui_mainwindow.h"

#include "dlg-about.h"
#include "dlg-preferences.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    handler.setCommand(&command);

    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    mSqlDropObsobj = QString("DROP TABLE " TBL_OBSOBJ);

    mSqlCreateObsobj = QString("CREATE TABLE " TBL_OBSOBJ);
    mSqlCreateObsobj.append("(");
    mSqlCreateObsobj.append(COL_OBSOBJ_ID " " COL_OBSOBJ_ID_TYPE_SQLITE ",");
    mSqlCreateObsobj.append(COL_OBSOBJ_FLGSELECTED " " COL_OBSOBJ_FLGSELECTED_TYPE_SQLITE ",");
//    mSqlCreateObsobj.append(COL_OBSOBJ_PID " " COL_OBSOBJ_PID_TYPE_SQLITE ",");
    mSqlCreateObsobj.append(COL_OBSOBJ_OBJNAME " " COL_OBSOBJ_OBJNAME_TYPE_SQLITE ",");
    mSqlCreateObsobj.append(COL_OBSOBJ_OBJPATH " " COL_OBSOBJ_OBJPATH_TYPE_SQLITE ",");
    mSqlCreateObsobj.append(COL_OBSOBJ_ARGUMENT " " COL_OBSOBJ_ARGUMENT_TYPE_SQLITE ",");
    mSqlCreateObsobj.append(COL_OBSOBJ_OBSTBL " " COL_OBSOBJ_OBSTBL_TYPE_SQLITE ",");
    mSqlCreateObsobj.append(COL_OBSOBJ_EXPTBL " " COL_OBSOBJ_EXPTBL_TYPE_SQLITE ",");
    mSqlCreateObsobj.append("CONSTRAINT " TBL_OBSOBJ "_pkey PRIMARY KEY (" COL_OBSOBJ_ID ")");
    mSqlCreateObsobj.append(")");

    mSqlDropTblObservation = QString("DROP TABLE " TBL_OBSERVATION_WITH_PREFIX);

    mSqlCreateTblObservation = QString("CREATE TABLE " TBL_OBSERVATION_WITH_PREFIX);
    mSqlCreateTblObservation.append("(");
    mSqlCreateTblObservation.append(COL_OBSERVATION_ID " " COL_OBSERVATION_ID_TYPE_SQLITE ",");
    mSqlCreateTblObservation.append(COL_OBSERVATION_OBSERVATION " " COL_OBSERVATION_OBSERVATION_TYPE_SQLITE ",");
    mSqlCreateTblObservation.append("CONSTRAINT " TBL_OBSERVATION_WITH_PREFIX "_pkey PRIMARY KEY (" COL_OBSERVATION_ID ")");
    mSqlCreateTblObservation.append(")");

    mdichilds = new QList<QWidget*>;

}

MainWindow::~MainWindow()
{
    delete mdichilds;

//    delete obsobj;
    db.close();

    delete ui;

}

bool MainWindow::ChkOpenDatabase()
{
    QObject *ret = (QObject*)ui->tableView->model();
    if (ret == NULL)
    {
        QMessageBox msgBox(this);
//        msgBox.setWindowTitle(tr("Warning"));
        msgBox.setText(tr("You can't do this action before opening Database."));
        msgBox.exec();
        return false;
    }

    return true;

}

bool MainWindow::ChkTableView()
{
    bool ret = ui->tableView->currentIndex().isValid();

    if (ret == false)
    {
        QMessageBox msgBox(this);
//        msgBox.setWindowTitle(tr("Warning"));
        msgBox.setText(tr("You can't do this action before selecting Obsobj."));
        msgBox.exec();
    }

    return ret;
}

void MainWindow::AboutTweedia()
{
    DlgAbout dialog(this);
    dialog.exec();
}

void MainWindow::Preferences()
{
    DlgPreferences dialog(this);
    dialog.exec();
}

bool MainWindow::OpenDatabase()
{
    DlgOpenDb dialog(this);
    dialog.exec();

    if (dialog.result() == DlgOpenDb::Accepted)
    {
        QString dbms(dialog.Dbmsname());
        db = QSqlDatabase::addDatabase(dbms);
        db.setHostName(dialog.Hostname());
        db.setPort(dialog.Port());
        db.setDatabaseName(dialog.Dbname());
        db.open();
        if (db.isOpen()) return true;
        db.close();

    }

    return false;
}

void MainWindow::OpenObsobj()
{
//    delete obsobj;
    obsobj = new Obsobj(this, db);
    ui->tableView->setModel(obsobj);

}

void MainWindow::InitializeDatabase()
{
    if (ChkOpenDatabase() != true) return;
//    {
//        if (this->OpenDatabase() != true) return;
//    }

    QMessageBox dialog(this);
    dialog.setWindowTitle(tr("Confirmation"));
    dialog.setText(tr("Obsobj table will be recreated if already exists. Continue?"));
    dialog.setStandardButtons(QMessageBox::Cancel|QMessageBox::Ok);
    dialog.exec();
    if (dialog.result() != QMessageBox::Ok) return;

    QSqlQuery query(db);
    query.exec((const QString)mSqlDropObsobj);
    query.exec((const QString)mSqlCreateObsobj);

    this->OpenObsobj();

}

void MainWindow::CreateTblObservation()
{
    if (ChkOpenDatabase() != true) return;

    DlgCreateTblObservation dialog(this);
    dialog.exec();

    if (dialog.result() == DlgCreateTblObservation::Accepted)
    {
        QSqlQuery query(db);
        query.exec((const QString)dialog.SqlCreateTblObservation());
    }

}

void MainWindow::AddObsobj()
{
    if (ChkOpenDatabase() == false) return;

    int newid;
    newid = 0;

    QString pathname = QFileDialog::getOpenFileName(
                this,
                tr("Open Executable File")
                );

    if (!pathname.isEmpty()) {
        newid = obsobj->addObsobj(pathname);
    }

    QSqlQuery query(db);

    if (newid != 0) {
        query.exec((const QString)mSqlCreateTblObservation.arg(newid));
    }
}

void MainWindow::DeleteObsobj()
{
    if (ChkTableView() == false) return;

    int row;
    row = ui->tableView->currentIndex().row();

    int theid;
    theid = obsobj->IdByRow(row);

    obsobj->delObsobj(row);

    QSqlQuery query(db);

    if (theid != 0) {
        query.exec((const QString)mSqlDropTblObservation.arg(theid));
    }

}

void MainWindow::RunObsobj()
{
    if (ChkTableView() == false) return;
//    obsobj->startProcess(ui->tableView->currentIndex().row());
    obsobj->startExecObsobj(ui->tableView->currentIndex().row());
//    this->OpenTextview();
}

void MainWindow::OpenCommand()
{
    QString pathname = QFileDialog::getOpenFileName(
                this,
                tr("Open Command File")
                );

    if (!pathname.isEmpty()) {
        QFile file(pathname, this);
        if (!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            file.close();
            QMessageBox dialog(this);
            dialog.setWindowTitle(tr("Error"));
            dialog.setText(tr("Failed opening file."));
            dialog.setStandardButtons(QMessageBox::Ok);
            dialog.exec();
            return;
        }
        ui->plainTextEdit->clear();
        ui->plainTextEdit->appendPlainText(QString(file.readAll().constData()));
        file.close();
    }

}

void MainWindow::SubmitCommand()
{
    if (ChkOpenDatabase() == false) return;

    obsobj->submitAll();

    int i;
    int nrows = obsobj->rowCount();
    for (i=0;i<nrows;i++)
    {
        if (obsobj->FlgSelect(i) == true) {
            inputSource.setData(ui->plainTextEdit->toPlainText());
            handler.setExecobsobj(obsobj->findExecObsobj(i));
            reader.parse(inputSource);
        }
    }

}

void MainWindow::OpenStringviewPage()
{
    if (ChkTableView() == false) return;
    StringviewPage *StringviewPage1 = new StringviewPage(this, obsobj, ui->tableView->currentIndex().row());
    ui->mdiArea->addSubWindow(StringviewPage1);
    mdichilds->append(StringviewPage1);
    obsobj->connectToAllExecObsobj(StringviewPage1, SLOT(on_DatabaseUpdated()));
    StringviewPage1->show();

}

void MainWindow::OpenStringviewScroll()
{
    if (ChkTableView() == false) return;
    StringviewScroll *StringviewScroll1 = new StringviewScroll(this, obsobj, ui->tableView->currentIndex().row());
    ui->mdiArea->addSubWindow(StringviewScroll1);
    mdichilds->append(StringviewScroll1);
    obsobj->connectToAllExecObsobj(StringviewScroll1, SLOT(on_DatabaseUpdated()));
    StringviewScroll1->show();

}

void MainWindow::on_pushButton_clicked()
{
    this->SubmitCommand();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->OpenCommand();
}

void MainWindow::on_pushButton_3_clicked()
{
    this->AddObsobj();
}

void MainWindow::on_pushButton_4_clicked()
{
    this->RunObsobj();
}

void MainWindow::on_actionAbout_Tweedia_triggered()
{
    this->AboutTweedia();
}

void MainWindow::on_actionPreferences_triggered()
{
    this->Preferences();
}

void MainWindow::on_actionOpenDatabase_triggered()
{
    if (this->OpenDatabase() == true)
    {
        this->OpenObsobj();
    }
}

void MainWindow::on_actionCreate_ObsobjTable_triggered()
{
    this->InitializeDatabase();
}

void MainWindow::on_actionOpen_Script_triggered()
{
    this->OpenCommand();
}

void MainWindow::on_actionAddObsobj_triggered()
{
    this->AddObsobj();
}

void MainWindow::on_actionDeleteObsobj_triggered()
{
    this->DeleteObsobj();
}

void MainWindow::on_actionRunObsobj_triggered()
{
    this->RunObsobj();
}

void MainWindow::on_actionCreate_TblObservation_triggered()
{
    this->CreateTblObservation();
}

void MainWindow::on_actionTweediaWiki_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/tweedia/Tweedia/wiki", QUrl::TolerantMode));
}

void MainWindow::on_actionTweediaWebsite_triggered()
{
    QDesktopServices::openUrl(QUrl("http://tweedia.github.io/Tweedia/", QUrl::TolerantMode));
}

void MainWindow::on_actionReportBug_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/tweedia/Tweedia/issues", QUrl::TolerantMode));
}

void MainWindow::on_actionString_View_Page_triggered()
{
    this->OpenStringviewPage();
}

void MainWindow::on_actionString_View_Scroll_triggered()
{
    this->OpenStringviewScroll();
}









/* References, Quotation:
 */










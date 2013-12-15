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

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    handler.setCommand(&command);

    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    mSqlDropObsobj = QString("DROP TABLE obsobj");
    mSqlCreateObsobj = QString("CREATE TABLE obsobj");
    mSqlCreateObsobj.append("(");
    mSqlCreateObsobj.append("id integer NOT NULL,");
    mSqlCreateObsobj.append("file_name character varying,");
    mSqlCreateObsobj.append("path_name character varying,");
    mSqlCreateObsobj.append("argument character varying,");
    mSqlCreateObsobj.append("table_actual character varying,");
    mSqlCreateObsobj.append("table_expected character varying,");
    mSqlCreateObsobj.append("CONSTRAINT obsobj_pkey PRIMARY KEY (id)");
    mSqlCreateObsobj.append(")");

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

bool MainWindow::OpenDatabase()
{
    OpenDb dialog(this);
    dialog.exec();

    if (dialog.result() == OpenDb::Accepted)
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
    if (ChkOpenDatabase() != true)
    {
        if (this->OpenDatabase() != true) return;
    }

    QMessageBox dialog(this);
    dialog.setWindowTitle(tr("Confirmation"));
    dialog.setText(tr("Obsobj will be cleared. Continue?"));
    dialog.setStandardButtons(QMessageBox::Cancel|QMessageBox::Ok);
    dialog.exec();
    if (dialog.result() != QMessageBox::Ok) return;

    QSqlQuery query(db);
    query.exec((const QString)mSqlDropObsobj);
    query.exec((const QString)mSqlCreateObsobj);

    this->OpenObsobj();

}

void MainWindow::AddObsobj()
{
    if (ChkOpenDatabase() == false) return;
    QString pathname = QFileDialog::getOpenFileName(
                this,
                tr("Open Executable File")
                );

    if (!pathname.isEmpty()) {
        obsobj->addObsobj(pathname);
    }

}

void MainWindow::DeleteObsobj()
{
    if (ChkTableView() == false) return;
    obsobj->delObsobj(ui->tableView->currentIndex().row());
}

void MainWindow::RunObsobj()
{
    if (ChkTableView() == false) return;
//    obsobj->startProcess(ui->tableView->currentIndex().row());
    obsobj->startExecObsobj(ui->tableView->currentIndex().row());
    this->OpenTextview();
}

void MainWindow::OpenTextview()
{
    if (ChkTableView() == false) return;
    TxtvwStdout *txtvwStdout1 = new TxtvwStdout(this, obsobj, ui->tableView->currentIndex().row());
    ui->mdiArea->addSubWindow(txtvwStdout1);
    mdichilds->append(txtvwStdout1);
    obsobj->connectToAllExecObsobj(txtvwStdout1, SLOT(on_DatabaseUpdated()));
    txtvwStdout1->show();

}

void MainWindow::on_pushButton_3_clicked()
{
    this->AddObsobj();
}

void MainWindow::on_pushButton_clicked()
{
    handler.setExecobjobj(obsobj->findExecObsobj(ui->tableView->currentIndex().row()));
    inputSource.setData(ui->plainTextEdit->toPlainText());

    reader.parse(inputSource);

}

void MainWindow::on_actionOpenDatabase_triggered()
{
    if (this->OpenDatabase() == true)
    {
        this->OpenObsobj();
    }
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

void MainWindow::on_actionOpen_TextView_triggered()
{
    this->OpenTextview();
}

void MainWindow::on_actionInitialize_Database_triggered()
{
    this->InitializeDatabase();
}






/* References, Quotation:
 */




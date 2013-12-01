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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    handler.setCommand(&command);

    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.open();

    obsobj = new Obsobj(this, db);
    ui->tableView->setModel(obsobj);

    mdichilds = new QList<QWidget*>;

}

MainWindow::~MainWindow()
{
    delete mdichilds;

    delete obsobj;
    db.close();

    delete ui;

}

bool MainWindow::ChkTableView()
{
    bool ret = ui->tableView->currentIndex().isValid();

    if (ret == false)
    {
        QMessageBox msgBox(this);
//        msgBox.setWindowTitle(tr("Warning"));
        msgBox.setText(tr("You can't do this action before opening DB."));
        msgBox.exec();
    }

    return ret;
}

void MainWindow::NewObsobj()
{
    if (ChkTableView() == false) return;
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
    MainWindow::OpenTextview();
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
    MainWindow::NewObsobj();
}

void MainWindow::on_pushButton_clicked()
{
    handler.setExecobjobj(obsobj->findExecObsobj(ui->tableView->currentIndex().row()));
    inputSource.setData(ui->plainTextEdit->toPlainText());

    reader.parse(inputSource);

}

void MainWindow::on_actionNewObsobj_triggered()
{
    MainWindow::NewObsobj();
}

void MainWindow::on_actionDeleteObsobj_triggered()
{
    MainWindow::DeleteObsobj();
}

void MainWindow::on_actionRunObsobj_triggered()
{
    MainWindow::RunObsobj();
}

void MainWindow::on_actionOpen_TextView_triggered()
{
    MainWindow::OpenTextview();
}





/* References, Quotation:
 */


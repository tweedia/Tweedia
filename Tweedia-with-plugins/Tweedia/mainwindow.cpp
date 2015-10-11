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

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include <QSqlRecord>

#include <QPluginLoader>
#include "widget-plugin-interface.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    handler.setCommand(&command);

    reader.setContentHandler(&handler);
    reader.setErrorHandler(&handler);

    widgetPluginPath.clear();
//    widgetPluginPath.append("/Users/testnoda/Documents/sample/plugin/");


    mdichilds = new QList<QWidget*>;

    this->on_actionOpenDatabase_triggered();

    mDlgPreferences = new DlgPreferences(this, &db);

    this->loadAllWidgetPlugins();

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

bool MainWindow::ChkTables(const QString argTableName)
{
    bool flgPluginTable = false;
    foreach (QString tableName, db.tables(QSql::Tables)) {
//        if (tableName.compare((const QString)metadataOfPluginFiles.Tablename) == 0) {
        if (tableName.compare(argTableName) == 0) {
            flgPluginTable = true;
        }
    }
    return flgPluginTable;

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

void MainWindow::SetPreferences()
{
    if (!ChkTables((const QString)metadataOfPluginFiles.Tablename)) {
        QMessageBox msgBox(this);
        msgBox.setText(tr("Plugin table not found. Is it OK to create it?"));
        msgBox.exec();
        if (msgBox.result() == QMessageBox::Accepted) {
            QSqlQuery query(db);
            query.exec((const QString)metadataOfPluginFiles.SqlCreate());
        }else{
            return;
        }
    }

    mDlgPreferences->exec();
//    this->ReloadAllWidgetPlugins();

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
        if (db.isOpen()) {
            metadataOfObsobj.Tablename.clear();
            metadataOfObsobj.Tablename.append(dialog.Obsobjname());
            metadataOfObservation.Tablename_prefix.clear();
            metadataOfObservation.Tablename_prefix.append(dialog.Obsprefix());
//            widgetPluginPath.clear();
//            widgetPluginPath.append(dialog.PluginDir());
//            this->LoadAllWidgetPlugins();

            return true;
        }
        db.close();

    }

    return false;
}

void MainWindow::loadAllWidgetPlugins()
{
    foreach (QAction* thisAction, pWidgetPluginActions ) {
        ui->menuWindow->removeAction(thisAction);
    }
    pWidgetPluginActions.clear();

    foreach (WidgetPluginInterface* thisPlugins, pWidgetPlugins) {
        delete thisPlugins;
    }
    pWidgetPlugins.clear();

    int pluginID = 0;

    QSqlTableModel pluginTableModel(this, db);
    pluginTableModel.setTable((const QString)metadataOfPluginFiles.Tablename);
    pluginTableModel.select();
    int rowcnt = pluginTableModel.rowCount();
    int i;
    for (i=0;i<rowcnt;i++) {
        QString path(pluginTableModel.record(i).value((const QString)metadataOfPluginFiles.Col_PATH_name).toString());
        QPluginLoader loader(path);
        if (WidgetPluginInterface* pWidgetPluginInterface = qobject_cast<WidgetPluginInterface *>(loader.instance()))
        {
            pWidgetPluginInterface->set_dbinstance(&db);
            pWidgetPlugins.append(pWidgetPluginInterface);

            QAction *actionOpenWidget = new QAction(pWidgetPluginInterface->getMenuText(), this);
            connect(actionOpenWidget, SIGNAL(triggered()), this, SLOT(on_actionOpenWidget_trggered()));
            ui->menuWindow->addAction(actionOpenWidget);
            pWidgetPluginActions.append(actionOpenWidget);

            pWidgetPluginInterface->setCorrespondingAction(actionOpenWidget);

            pluginID++;

        }
    }
}

void MainWindow::OpenObsobj()
{
//    delete obsobj;
    obsobj = new Obsobj(this, db, &metadataOfObsobj, &metadataOfObservation);
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
    query.exec((const QString)metadataOfObsobj.SqlDrop());
    query.exec((const QString)metadataOfObsobj.SqlCreate());

    this->OpenObsobj();

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
        query.exec((const QString)metadataOfObservation.SqlCreate(newid, metadataOfObservation.NumColsDefault));
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
        query.exec((const QString)metadataOfObservation.SqlDrop(theid));
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

void MainWindow::on_ObservationUpdated(int argObsobjID)
{
    WidgetPluginInterface *pWidgetPlugin;
    for (int i = 0; i < pWidgetPlugins.size(); ++i) {
        pWidgetPlugin = pWidgetPlugins.at(i);
        pWidgetPlugin->called_when_DatabaseUpdated(argObsobjID);
    }
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
    this->SetPreferences();
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

void MainWindow::on_actionOpenWidget_trggered()
{
    if (!ChkTableView()) return;

    QObject* pSenderAction = QObject::sender();
    int obsobjid;
    QWidget* pWidget;
    WidgetPluginInterface* pWidgetPlugin;
    for (int i = 0; i < pWidgetPlugins.size(); ++i) {
        pWidgetPlugin = pWidgetPlugins.at(i);
        if (pWidgetPlugin->getCorrespondingAction() == pSenderAction) {
            obsobjid = obsobj->findExecObsobj(ui->tableView->currentIndex().row())->Id();
            pWidget = pWidgetPlugin->new_widget(obsobjid);
            if (pWidget) {
                ui->mdiArea->addSubWindow(pWidget);
                pWidget->show();
            }
        }
    }
}




/* References, Quotation:
 */


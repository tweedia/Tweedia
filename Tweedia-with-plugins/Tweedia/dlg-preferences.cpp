/* dlg-preferences.cpp */

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
   Thursday, January 2nd, 2014; Saitama, Japan
   Initial author: Takenobu Noda
 */

#include <QMessageBox>

#include "dlg-preferences.h"
#include "ui_dlg-preferences.h"

DlgPreferences::DlgPreferences(QWidget *parent, QSqlDatabase *argDatabase) :
    QDialog(parent),
    ui(new Ui::DlgPreferences)
{
    ui->setupUi(this);

    mDatabase = argDatabase;
    mPluginTableModel = new QSqlTableModel(this, *mDatabase);
    mPluginTableModel->setTable((const QString)metadataOfPluginFiles.Tablename);
    mPluginTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    mPluginTableModel->select();
    ui->tableView_plugin->setModel(mPluginTableModel);

//    mPluginDir.clear();
//    mPluginDir.append("./plugin");
//    ui->lineEdit_plugin->setText((const QString)mPluginDir);
}

DlgPreferences::~DlgPreferences()
{
    delete ui;
}

void DlgPreferences::on_buttonBox_accepted()
{
//    mPluginDir.clear();
//    mPluginDir.append(ui->lineEdit_plugin->text());
}

int DlgPreferences::MaxID()
{
    QSqlQuery query(*mDatabase);
    query.exec((const QString)metadataOfPluginFiles.SqlMaxID()); // ref.1
    int id = 0;                                 // ref.1
    if (query.next())                           // ref.1
        id = query.value(0).toInt();            // ref.1
    return id;                                  // ref.1
}

void DlgPreferences::on_buttonAdd_plugin_clicked()
{
    QString pathname = QFileDialog::getOpenFileName(
                this,
                tr("Open Plugin File")
                );

    if (!pathname.isEmpty()) {
        int newid = this->MaxID() + 1;
        int row = 0;
        mPluginTableModel->insertRow(row);
        mPluginTableModel->setData(mPluginTableModel->index(row,0),newid);
        mPluginTableModel->setData(mPluginTableModel->index(row,1),pathname);
        mPluginTableModel->submit();
    }

    QMessageBox msgBox(this);
    msgBox.setText(tr("Restart Tweedia to load the plugins"));
    msgBox.exec();

}

/* References, Quotation:
   1.   Jasmin Blanchette, Mark Summerfield, "C++ GUI Programming with Qt4,"
        Japanese language edition(ISBN978-4-87311-344-9), O'REILLY JAPAN, p347.
        The code is following:

        QSqlQuery query;
        query.exec("SELECT MAX(id) FROM " + table);
        int id = 0;
        if (query.next())
            id = query.value(0).toInt() + 1;
        return id;
 */


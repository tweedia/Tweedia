/* dlg-create-resulttable.h */

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
   Dec 20, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#ifndef DLGCREATERESULTTABLE_H
#define DLGCREATERESULTTABLE_H

#include <QDialog>
#include <QString>

namespace Ui {
class DlgCreateResultTable;
}

class DlgCreateResultTable : public QDialog
{
    Q_OBJECT

public:
    explicit DlgCreateResultTable(QWidget *parent = 0);
    ~DlgCreateResultTable();

    QString SqlCreateResultTbl(){return mSqlCreateResultTbl;}

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DlgCreateResultTable *ui;

    QStringList mOptionTableType;

    QString mSqlCreateResultTbl;

    QString mSqlCreateObsobj;

};

#endif // DLGCREATERESULTTABLE_H

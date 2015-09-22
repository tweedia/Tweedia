/* dlg-create-tbl-observation.h */

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

#ifndef DLGCREATETBLOBSERVATION_H
#define DLGCREATETBLOBSERVATION_H

#include "global.h"

#include <QDialog>
#include <QString>

namespace Ui {
class DlgCreateTblObservation;
}

class DlgCreateTblObservation : public QDialog
{
    Q_OBJECT

public:
    explicit DlgCreateTblObservation(QWidget *parent = 0);
    ~DlgCreateTblObservation();

    QString SqlCreateTblObservation(){return mSqlCreateTblObservation;}

private slots:
    void on_buttonBox_accepted();

private:
    Ui::DlgCreateTblObservation *ui;

    QStringList mOptionTableType;

    QString mSqlCreateTblObservation;

    QString mSqlCreateObsobj;

};

#endif // DLGCREATETBLOBSERVATION_H

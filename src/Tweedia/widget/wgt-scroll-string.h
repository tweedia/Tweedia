/* wgt-scroll-string.h */

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
   Monday, Aug 4th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
*/

#ifndef WGTSCROLLSTRING_H
#define WGTSCROLLSTRING_H

#include <QWidget>

#include "obsobj.h"
#include "exec-obsobj.h"

namespace Ui {
class WgtScrollString;
}

class WgtScrollString : public QWidget
{
    Q_OBJECT

public:
    explicit WgtScrollString(QWidget *parent = 0, Obsobj *obsobj = 0, int rowOfTableView = 0);
    ~WgtScrollString();

    void refreashWithRowOfTableView();

public slots:
    void on_DatabaseUpdated();

private slots:
    void on_checkBox_stateChanged(int arg1);

private:
    Ui::WgtScrollString *ui;

    QSqlTableModel mQSqlTableModel;

    Obsobj *mObsobj;
    int mRowOfTableView;
    ExecObsobj *mExecObsobj;
};

#endif // WGTSCROLLSTRING_H

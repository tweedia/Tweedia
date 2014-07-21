/* view-string-page.h */

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
   Saturday, Novenber 2nd, 2013; Saitama, Japan
   Initial author: Takenobu Noda
*/

#ifndef VIEWSTRINGPAGE_H
#define VIEWSTRINGPAGE_H

#include <QWidget>

#include "obsobj.h"
#include "exec-obsobj.h"

namespace Ui {
class ViewStringPage;
}

class ViewStringPage : public QWidget
{
    Q_OBJECT

public:
    explicit ViewStringPage(QWidget *parent = 0, Obsobj *obsobj = 0, int rowOfTableView = 0);
    ~ViewStringPage();

    void setCurrentRow(int arg){ mRowOfTableView = arg; }

    void refreashWithRowOfTableView();

public slots:
    void on_DatabaseUpdated();

private slots:
    void on_pushButton_clicked();

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::ViewStringPage *ui;

    Obsobj *mObsobj;
    int mRowOfTableView;

    QString mTableActual;
    ExecObsobj* mExecObsobj;

    int mId;
    QString mValueAsQString;
};

#endif // VIEWSTRINGPAGE_H


/* References, Quotation:
 */

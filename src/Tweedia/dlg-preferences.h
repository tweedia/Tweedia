/* dlg-preferences.h */

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

#ifndef DLGPREFERENCES_H
#define DLGPREFERENCES_H

#include <QDialog>

namespace Ui {
class DlgPreferences;
}

class DlgPreferences : public QDialog
{
    Q_OBJECT
    
public:
    explicit DlgPreferences(QWidget *parent = 0);
    ~DlgPreferences();
    
private:
    Ui::DlgPreferences *ui;
};

#endif // DLGPREFERENCES_H

/* open-db.h */

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
   Dec 01, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#ifndef OPENDB_H
#define OPENDB_H

#include <QDialog>
#include <QString>

namespace Ui {
class OpenDb;
}

class OpenDb : public QDialog
{
    Q_OBJECT

public:
    explicit OpenDb(QWidget *parent = 0);
    ~OpenDb();

    QString Dbmsname(){return mDbmsname;}
    QString Hostname(){return mHostname;}
    int     Port(){return mPort;}
    QString Dbname(){return mDbname;}

signals:

private slots:

    void on_buttonBox_accepted();

private:
    Ui::OpenDb *ui;

    QStringList mOptionmDbmsname;
    QStringList mOptionDbname;

    QString mDbmsname;
    QString mHostname;
    int     mPort;
    QString mDbname;

};

#endif // OPENDB_H

/* obsobj.cpp */

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
   Sunday, October 6th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#include "obsobj.h"

#include <QDebug>

Obsobj::Obsobj(QObject *parent, QSqlDatabase db) :
    QSqlTableModel(parent, db)
{
    mTablename = QString("obsobj");
    mSqlSelectmaxid = QString("SELECT MAX(id) FROM " + mTablename); // ref.1

    mTableActual = QString();
    mTableExpected = QString();
    mArgument = QString();

    mLog = new Log();

    this->setTable((const QString)mTablename);
    this->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->select();

    int nrows = this->rowCount();
    for (int i=0; i<nrows; i++)
    {
        int id = this->data(this->index(i,0)).toInt();
        newExecObsobj(id);
    }

    mErrcode = OBSOBJ_RC_NOERROR;
}

int Obsobj::Maxid()
{
    mErrcode = OBSOBJ_RC_NOERROR;

    QSqlQuery query(this->database());
    query.exec((const QString)mSqlSelectmaxid); // ref.1
    int id = 0;                                 // ref.1
    if (query.next())                           // ref.1
        id = query.value(0).toInt();            // ref.1
    return id;                                  // ref.1
}

ExecObsobj* Obsobj::findExecObsobj(int row)
{
    int id = this->data(this->index(row,0)).toInt();
    ExecObsobj* ret = findExecObsobjById(id);
    return ret;
}

QString Obsobj::TableActual(int row)
{
    QModelIndex id = this->index(row,4);
    QVariant val = this->data(id);
    mTableActual.clear();
    mTableActual.append(val.toString());
    return mTableActual;
}

QString Obsobj::TableExpected(int row)
{
    return mTableExpected;
}

QString Obsobj::Argument(int row)
{
    return mArgument;
}

void Obsobj::newExecObsobj(int argId)
{
    ExecObsobj *app = new ExecObsobj(argId, this->database(), this);
    mExecObsobjs.append(app);

    mErrcode = OBSOBJ_RC_NOERROR;
}

ExecObsobj* Obsobj::updatedExecObsobj(int row)
{
    ExecObsobj* theThread = this->findExecObsobj(row);
    theThread->setPathname(this->data(this->index(row,2)).toString());
    theThread->setArgument(this->data(this->index(row,3)).toString());
    theThread->setTablename(this->data(this->index(row,4)).toString());
    return theThread;
}

void Obsobj::startExecObsobj(int row)
{
    ExecObsobj* theThread = updatedExecObsobj(row);
    theThread->start();
}

void Obsobj::stopExecObsobj(int row)
{
    ExecObsobj* theThread = this->findExecObsobj(row);
    theThread->stop();
}

void Obsobj::connectToAllExecObsobj(QObject *mdichild,  const char* method)
{
    QListIterator<ExecObsobj*> i(mExecObsobjs);
    while (i.hasNext())
        QObject::connect(i.next(), SIGNAL(DatabaseUpdated()), mdichild, method);
}

ExecObsobj* Obsobj::findExecObsobjById(int argId)
{
    mErrcode = OBSOBJ_RC_FAILEDTOFIND;
    ExecObsobj* ret = 0;
    int theId;
//    int nthreads = mExecObsobjs.count();
//    for (int i=0; i<nthreads; i++)
//    {
//        theId = mAppvec[i]->Id();
//        if (theId == argId)
//        {
//            ret = mAppvec[i];
//            mErrcode = OBSOBJ_RC_NOERROR;
//            break;
//        }
//    }
    ExecObsobj* wkobj;
    QListIterator<ExecObsobj*> i(mExecObsobjs);
    while (i.hasNext())
    {
        wkobj = i.next();
        theId = wkobj->Id();
        if (theId == argId)
        {
            ret = wkobj;
            mErrcode = OBSOBJ_RC_NOERROR;
            break;
        }
    }
    return ret;
}

void Obsobj::addObsobj(QString argPathname)
{
    QFileInfo fi(argPathname);

    int newid = Maxid() + 1;
    int row = 0;
    this->insertRow(row);
    this->setData(this->index(row,0),newid);
    this->setData(this->index(row,1),fi.fileName());
    this->setData(this->index(row,2),argPathname);
    this->submitAll();

    newExecObsobj(newid);

    mErrcode = OBSOBJ_RC_NOERROR;
}

void Obsobj::delObsobj(int row)
{
    this->removeRow(row);
    this->submitAll();

    mErrcode = OBSOBJ_RC_NOERROR;
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



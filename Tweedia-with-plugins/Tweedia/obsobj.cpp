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

#include "global.h"
#include "obsobj.h"

#include <QDebug>

Obsobj::Obsobj(QObject *parent, QSqlDatabase db,
               MetadataOfObsObj *metadataOfObsobj,
               MetadataOfObservation *metadataOfObservation) :
    QSqlTableModel(parent, db)
{
    mTablename = QString("obsobj");
    mSqlSelectmaxid = QString("SELECT MAX(id) FROM "); // ref.1
    mSqlSelectmaxid.append(mTablename);

    mTableActual = QString();
    mTableExpected = QString();
    mArgument = QString();

    mMetadataOfObservation = metadataOfObservation;
    mMetadataOfObsObj = metadataOfObsobj;

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

Obsobj::~Obsobj()
{
    delete mLog;
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

int Obsobj::IdByRow(int row)
{
    int id = this->data(this->index(row,0)).toInt();
    return id;
}

ExecObsobj* Obsobj::findExecObsobj(int row)
{
    int id = this->data(this->index(row,0)).toInt();
    ExecObsobj* ret = findExecObsobjById(id);
    return ret;
}

bool Obsobj::FlgSelect(int row)
{
    bool ret = this->data(this->index(row,1)).toBool();
    return ret;
}

QString Obsobj::TableActual(int row)
{
    QModelIndex id = this->index(row,5);
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
    ExecObsobj *app = new ExecObsobj(argId, this->database(), this, mMetadataOfObsObj, mMetadataOfObservation);
    mListExecObsobj.append(app);

    mErrcode = OBSOBJ_RC_NOERROR;
}

ExecObsobj* Obsobj::updatedExecObsobj(int row)
{
    ExecObsobj* theThread = this->findExecObsobj(row);
    theThread->setPathname(this->data(this->index(row,3)).toString());
    theThread->setArgument(this->data(this->index(row,4)).toString());
    theThread->setTablename(this->data(this->index(row,5)).toString());
    theThread->setObsformat(this->getType(this->data(this->index(row,6)).toString()));
    theThread->setMethod(this->getType(this->data(this->index(row,7)).toString()));
    return theThread;
}

void Obsobj::startExecObsobj(int row)
{
    ExecObsobj* theThread = updatedExecObsobj(row);
    TweediaEnum theMethod = theThread->Method();
    switch (theMethod) {
    case METHOD_RUN:
        theThread->start();
        break;
    case METHOD_IMPORT:
        theThread->importobservation();
        break;
    default:
        theThread->start();
        break;
    }
}

void Obsobj::stopExecObsobj(int row)
{
    ExecObsobj* theThread = this->findExecObsobj(row);
    TweediaEnum theMethod = theThread->Method();
    switch (theMethod) {
    case METHOD_RUN:
        theThread->stop();
        break;
    case METHOD_IMPORT:
        break;
    default:
        theThread->stop();
        break;
    }
}

void Obsobj::connectToAllExecObsobj(WidgetPluginInterface *mdichild,  const char* method)
{
    QListIterator<ExecObsobj*> i(mListExecObsobj);
    while (i.hasNext())
        QObject::connect(i.next(), SIGNAL(DatabaseUpdated()), (QObject *)mdichild, method);
}

ExecObsobj* Obsobj::findExecObsobjById(int argId)
{
    mErrcode = OBSOBJ_RC_FAILEDTOFIND;
    ExecObsobj* ret = 0;
    int theId;
//    int nthreads = mListExecObsobj.count();
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
    QListIterator<ExecObsobj*> i(mListExecObsobj);
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

int Obsobj::addObsobj(QString argPathname)
{
    QFileInfo fi(argPathname);

    int newid = Maxid() + 1;
    int row = 0;
    this->insertRow(row);
    this->setData(this->index(row,0),newid);
    this->setData(this->index(row,1),true);
    this->setData(this->index(row,2),fi.fileName());
    this->setData(this->index(row,3),argPathname);

    this->setData(this->index(row,5),mMetadataOfObservation->Tablename(newid));
    this->setData(this->index(row,6),this->getDefaultObsfmtTitle(fi.fileName()));
    this->setData(this->index(row,7),this->getDefaultMethodTitle(fi.fileName()));

    this->submitAll();

    newExecObsobj(newid);

    mErrcode = OBSOBJ_RC_NOERROR;

    return newid;
}

void Obsobj::delObsobj(int row)
{
    ExecObsobj *wkobj;
    wkobj = findExecObsobj(row);
    mListExecObsobj.removeOne(wkobj);

    this->removeRow(row);
    this->submitAll();

    mErrcode = OBSOBJ_RC_NOERROR;
}

TweediaEnum Obsobj::getType(QString arg){

    if (!arg.compare(TITLE_METHOD_RUN))      return METHOD_RUN;
    if (!arg.compare(TITLE_METHOD_IMPORT))   return METHOD_IMPORT;
    if (!arg.compare(TITLE_OBSFMT_TXT))      return OBSFMT_TXT;
    if (!arg.compare(TITLE_OBSFMT_CSV))      return OBSFMT_CSV;

    return Default;
}
QString Obsobj::getDefaultObsfmtTitle(QString arg){
    QString ret = QString(TITLE_OBSFMT_CSV);
    QString wkstr = QString(arg.split(".").last());

    if (!wkstr.compare(TITLE_OBSFMT_CSV)) return ret;

    ret.clear();
    ret.append(TITLE_OBSFMT_TXT);
    return ret;

}

QString Obsobj::getDefaultMethodTitle(QString arg){
    QString ret = QString(TITLE_METHOD_IMPORT);
    QString wkstr = QString(arg.split(".").last());

    if (!wkstr.compare(TITLE_OBSFMT_TXT) ) return ret;
    if (!wkstr.compare(TITLE_OBSFMT_CSV)) return ret;

    ret.clear();
    ret.append(TITLE_METHOD_RUN);
    return ret;
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



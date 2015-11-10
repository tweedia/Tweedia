/* exec-obsobj.cpp */

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
   Sunday, Novenber 10th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#include "exec-obsobj.h"

ExecObsobj::ExecObsobj(int id,
                       QSqlDatabase db,
                       QObject *parent,
                       MetadataOfObsObj *metadataOfObsobj,
                       MetadataOfObservation *metadataOfObservation) :
    QObject(parent)
{
    mDb = db;

    m_running = false;

    mId = id;
    mProcess = new QProcess(this);

//    connect(mProcess, SIGNAL(readyRead()), this, SLOT(saveobservation()));
    connect(mProcess, SIGNAL(readyReadStandardOutput()),
            this, SLOT(saveobservation()));                                  // ref.2
    connect(mProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(processFinished(int, QProcess::ExitStatus)));    // ref.2
    connect(mProcess, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(processError(QProcess::ProcessError)));          // ref.2

    connect(this, SIGNAL(DatabaseUpdated(int)), parent->parent(), SLOT(on_ObservationUpdated(int)));

//    mMainWindow = this->parent()->parent();

    mObservationWhereTheid = QByteArray();

    mMetadataOfObservation = metadataOfObservation;
    mMetadataOfObsObj = metadataOfObsobj;

    mLog = new Log();

}

ExecObsobj::~ExecObsobj()
{
    if (mProcess->state()==QProcess::Running)
    {
        mProcess->kill();
        mProcess->waitForFinished();
    }
    delete mProcess;
}

void ExecObsobj::setTablename(QString tablename)
{
    mTablename = tablename;

    mTable = new QSqlTableModel(this, mDb);
    mTable->setTable((const QString)mTablename);
    mTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
    mTable->select();
}

void ExecObsobj::setObsformat(QString arg)
{
    mObsformat = tweediaConf.getTypeOfObsformat(arg);
}

//void ExecObsobj::addWidgetPlugin(QObject* argWidgetPlugin)
//{
//    mWidgetPlugins.append();
//}

int ExecObsobj::Maxid()
{
    mErrcode = ExecObsobj::NoErr;

    QSqlQuery query(mDb);
    query.exec((const QString)mMetadataOfObservation->SqlSelectMaxId(mId)); // ref.1
    int id = 0;                                 // ref.1
    if (query.next())                           // ref.1
        id = query.value(0).toInt();            // ref.1
    return id;                                  // ref.1
}

/*
QByteArray ExecObsobj::ObservationWhereMaxid()
{
    mErrcode = ExecObsobj::NoErr;

    QSqlQuery query(mDb);

    mSqlSelectmaxid = QString("SELECT MAX(id) FROM " + mTablename); // ref.1
    query.exec((const QString)mSqlSelectmaxid); // ref.1
    QString strid = QString();                  // ref.1
    if (query.next())                           // ref.1
        strid = query.value(0).toString();

    return this->ObservationWhereTheid(strid);
}
*/

/*
QByteArray ExecObsobj::ObservationWhereTheid(int id)
{
    mErrcode = ExecObsobj::NoErr;

    QString strid;
    strid.setNum(id);

    return this->ObservationWhereTheid(strid);
}
*/

/*
QByteArray ExecObsobj::ObservationWhereTheid(QString strid)
{
    mErrcode = ExecObsobj::NoErr;

    QSqlQuery query(mDb);

    mObservationWhereTheid.clear();
    query.exec((const QString)mMetadataOfObservation->SqlSelectWhereId(strid));
    if (query.next())
        mObservationWhereTheid.append(query.value(1).toByteArray());

    return mObservationWhereTheid;
}
*/

void ExecObsobj::submitCommand(Command *command)
{
    command_type type = command->gettype();

    if (type == cm_stdin)
    {
        mProcess->write(command->Inputstring().toAscii());
//        mProcess->closeWriteChannel();
    }

}

void ExecObsobj::start()
{
    mLog->WriteLog(LOG_NOTICE, "ExecObsobj started.");

    QString *msg = new QString();
    msg->clear();
    msg->append("mPathname: " );
    msg->append(mPathname);
    mLog->WriteLog(LOG_NOTICE, msg->toAscii().constData());
    msg->clear();
    msg->append("mArgument: ");
    msg->append(mArgument);
    mLog->WriteLog(LOG_NOTICE, msg->toAscii().constData());

    if (!m_running)
    {
        m_running = true;
        mProcess->start(mPathname, QStringList() << mArgument);
    }

    mLog->WriteLog(LOG_NOTICE, "ExecObsobj ended.");
}

void ExecObsobj::stop()
{

}

void ExecObsobj::submitRecord(QString arg)
{
    int newid = Maxid() + 1;
    int row = 0;
    mTable->insertRow(row);
    mTable->setData(mTable->index(row,0),newid);

    switch (mObsformat) {
    case TweediaConf::TXT:
        mTable->setData(mTable->index(row,1),arg);
        break;
    case TweediaConf::CSV:
        {
            int i = 1;
            QStringList lines = arg.split(";");
            foreach (QString line, lines) {
                mTable->setData(mTable->index(row,i),line);
                i++;
            }
        }
        break;
    default:
//        mTable->setData(mTable->index(row,1),mOutputbuffer.constData());
        break;
    }

    mTable->submitAll();

}

void ExecObsobj::saveobservation()
{
    mOutputbuffer.clear();
    mOutputbuffer.append(mProcess->readAll());

    QString buffer = QString(mOutputbuffer.constData());

    switch (mObsformat) {
    case TweediaConf::TXT:
        this->submitRecord(buffer);
        break;
    case TweediaConf::CSV:
        {
            QStringList lines = buffer.split("\n", QString::SkipEmptyParts);
            foreach (QString line, lines)
                this->submitRecord(line);
        }
        break;
    default:
        this->submitRecord(buffer);
        break;
    }
    ExecObsobj::DatabaseUpdated(mId);

}

void ExecObsobj::processFinished(int exitCode, QProcess::ExitStatus exitStatus) // ref.3
{
    this->saveobservation();

    if (exitStatus == QProcess::CrashExit) {
        mLog->WriteLog(LOG_ERR, "Program crashed");
    } else if (exitCode != 0 ) {
        mLog->WriteLog(LOG_ERR, "Program failed");
    } else {
        mLog->WriteLog(LOG_NOTICE, "Program succeeded");
    }
    m_running = false;

}

void ExecObsobj::processError(QProcess::ProcessError error) // ref.4
{
    this->saveobservation();

    if (error == QProcess::FailedToStart) {
        mLog->WriteLog(LOG_ERR, "Program not found");
        m_running = false;
    }

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

   2.   Jasmin Blanchette, Mark Summerfield, "C++ GUI Programming with Qt4,"
        Japanese language edition(ISBN978-4-87311-344-9), O'REILLY JAPAN, p329.
        The code is following:

        ConvertDialog::ConvertDialog(QWidget *parent)
            : QDialog(parent)
        {
            setupUi(this);

            connect(&process, SIGNAL(readyReadStandardError()),
                this, SLOT(updateOutputTextEdit()));
            connect(&process, SIGNAL(finished(int, QProcess::ExitStatus)),
                this, SLOT(processFinished(int, QProcess:ExitStatus)));
            connect(&process, SIGNAL(error(QProcess::ProcessError)),
                this, SLOT(processError(QProcess::ProcessError)));
        }

   3.   Jasmin Blanchette, Mark Summerfield, "C++ GUI Programming with Qt4,"
        Japanese language edition(ISBN978-4-87311-344-9), O'REILLY JAPAN, p331.
        The code is following:

        void ConvertDialog::processFinished(int exitCode,
                                            QProcess::ExitStatus exitStatus)
        {
            if (exitStatus == QProcess::CrashExit) {
                outputTextEdit->append(tr("Conversion program crashed"));
            } else if (exitCode != 0 ) {
                outputTextEdit->append(tr("Conversion failed"));
            } else {
                outputTextEdit->append(tr("File %1 created").arg(targetFile));
            }
            convertButton->setEnabled(true);
        }

   4.   Jasmin Blanchette, Mark Summerfield, "C++ GUI Programming with Qt4,"
        Japanese language edition(ISBN978-4-87311-344-9), O'REILLY JAPAN, p331.
        The code is following:

        void ConvertDialog::processError(QProcess::ProcessError error)
        {
            if (error == QProcess::FailedToStart) {
                outputTextEdit->append(tr("Conversion program not found"))+
                convertButton->setEnabled(true);
            }
        }


*/

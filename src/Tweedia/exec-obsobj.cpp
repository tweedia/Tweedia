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

ExecObsobj::ExecObsobj(int id, QSqlDatabase db, QObject *parent) :
    QObject(parent)
{
    mDb = db;

    m_running = false;

    mId = id;
    mProcess = new QProcess(this);

    connect(mProcess, SIGNAL(readyReadStandardOutput()),
            this, SLOT(saveresult()));                                  // ref.2
    connect(mProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(processFinished(int, QProcess::ExitStatus)));    // ref.2
    connect(mProcess, SIGNAL(error(QProcess::ProcessError)),
            this, SLOT(processError(QProcess::ProcessError)));          // ref.2

//    mMainWindow = this->parent()->parent();

    mResultWhereMaxid = QByteArray();

    mLog = new Log();

}

ExecObsobj::~ExecObsobj()
{

}

void ExecObsobj::setTablename(QString tablename)
{
    mTablename = tablename;

    mTable = new QSqlTableModel::QSqlTableModel(this, mDb);
    mTable->setTable((const QString)mTablename);
    mTable->setEditStrategy(QSqlTableModel::OnManualSubmit);
    mTable->select();
}

int ExecObsobj::Maxid()
{
    mErrcode = ExecObsobj::NoErr;

    QSqlQuery query(mDb);
    mSqlSelectmaxid = QString("SELECT MAX(id) FROM " + mTablename); // ref.1
    query.exec((const QString)mSqlSelectmaxid); // ref.1
    int id = 0;                                 // ref.1
    if (query.next())                           // ref.1
        id = query.value(0).toInt();            // ref.1
    return id;                                  // ref.1
}

QByteArray ExecObsobj::ResultWhereMaxid()
{
    mErrcode = ExecObsobj::NoErr;

    QSqlQuery query(mDb);

    mSqlSelectmaxid = QString("SELECT MAX(id) FROM " + mTablename); // ref.1
    query.exec((const QString)mSqlSelectmaxid); // ref.1
    QString strid = QString();                  // ref.1
    if (query.next())                           // ref.1
        strid = query.value(0).toString();

    mResultWhereMaxid.clear();
    mSqlSelectresultwheremaxid = QString("SELECT result FROM " + mTablename + " WHERE id = " + strid);
    query.exec((const QString)mSqlSelectresultwheremaxid);
    if (query.next())
        mResultWhereMaxid.append(query.value(0).toByteArray());

    return mResultWhereMaxid;
}

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

    if (!m_running)
    {
        m_running = true;
        mProcess->start(mPathname);
    }

    mLog->WriteLog(LOG_NOTICE, "ExecObsobj ended.");
}

void ExecObsobj::stop()
{

}

void ExecObsobj::saveresult()
{
    mOutputbuffer.clear();
    mOutputbuffer.append(mProcess->readAll());

    int newid = Maxid() + 1;
    int row = 0;
    mTable->insertRow(row);
    mTable->setData(mTable->index(row,0),newid);
    mTable->setData(mTable->index(row,1),mOutputbuffer.constData());
    mTable->submitAll();

    ExecObsobj::DatabaseUpdated();

}

void ExecObsobj::processFinished(int exitCode, QProcess::ExitStatus exitStatus) // ref.3
{
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

/* parse-xml.h */

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
   Saturday, Novenber 9th, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#ifndef PARSEXML_H
#define PARSEXML_H

#include <QXmlDefaultHandler>

#include "command.h"
#include "exec-obsobj.h"

class ParseXml : public QXmlDefaultHandler
{
public:
    ParseXml();

    void setCommand(Command *arg){command=arg;}
    void setExecobsobj(ExecObsobj *arg){exec=arg;}

    bool startElement(const QString &namespaceURI,
                      const QString &localName,
                      const QString &qName,
                      const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI,
                    const QString &localName,
                    const QString &qName);
    bool characters(const QString &ch);
    bool fatalError(const QXmlParseException &exception);

private:
    QString currentText;

    Command* command;
    ExecObsobj* exec;

};

#endif // PARSEXML_H

/* References, Quotation:
   1.   Jasmin Blanchette, Mark Summerfield, "C++ GUI Programming with Qt4,"
        Japanese language edition(ISBN978-4-87311-344-9), O'REILLY JAPAN, p391.
        The code is following:

        class SaxHandler : public QXmlDefaultHandler
        {
        public:
            SaxHandler();

            bool startElement(const QString &namespaceURI,
                              const QString &localName,
                              const QString &qName,
                              const QXmlAttributes &atts);
            bool endElement(const QString &namespaceURI,
                            const QString &localName,
                            const QString &qName);
            bool characters(const QString &ch);
            bool fatalError(const QXmlParseException &exception);

 */

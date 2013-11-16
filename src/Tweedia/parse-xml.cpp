/* parse-xml.cpp */

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

#include "parse-xml.h"

ParseXml::ParseXml()
{

}

bool ParseXml::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName == "stdin")
    {
        command->settype(cm_stdin);
    }

    return true;
}

bool ParseXml::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    exec->submitCommand(command);

    return true;
}

bool ParseXml::characters(const QString &ch)
{
    command->setInputstring(ch);

    return true;
}

bool ParseXml::fatalError(const QXmlParseException &exception)
{

    return true;
}

/* References, Quotation:
   1.   Jasmin Blanchette, Mark Summerfield, "C++ GUI Programming with Qt4,"
        Japanese language edition(ISBN978-4-87311-344-9), O'REILLY JAPAN, p347.
        The code is following:

 */

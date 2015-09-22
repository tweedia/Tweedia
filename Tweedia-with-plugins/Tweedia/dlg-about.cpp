/* dlg-about.cpp */

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
   Dec 30, 2013; Saitama, Japan
   Initial author: Takenobu Noda
 */

#include "dlg-about.h"
#include "ui_dlg-about.h"

DlgAbout::DlgAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DlgAbout)
{
    ui->setupUi(this);

    logo = new QPixmap(":/logo/logo48x48.png");
    ui->uiLogo->setPixmap(logo->scaled(ui->uiLogo->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));

    ui->uiVersion->setText(qApp->applicationVersion());
}

DlgAbout::~DlgAbout()
{
    delete logo;
    delete ui;
}

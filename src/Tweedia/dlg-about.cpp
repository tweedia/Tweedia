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

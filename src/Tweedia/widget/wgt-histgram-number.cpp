#include "wgt-histgram-number.h"
#include "ui_wgt-histgram-number.h"

#include <QSqlRecord>
#include <QSqlField>

WgtHistgramNumber::WgtHistgramNumber(QWidget *parent, Obsobj *obsobj, int rowOfTableView) :
    QWidget(parent),
    ui(new Ui::WgtHistgramNumber)
{
    ui->setupUi(this);

    mObsobj = obsobj;
    mRowOfTableView = rowOfTableView;

    refreashWithRowOfTableView();
    this->update();

    mlist = QList<int>();
}

WgtHistgramNumber::~WgtHistgramNumber()
{
    delete ui;
}

void WgtHistgramNumber::refreashWithRowOfTableView()
{
    mExecObsobj = mObsobj->updatedExecObsobj(mRowOfTableView);

    this->setWindowTitle(mExecObsobj->Pathname());
//    ui->lblTableName->setText(mExecObsobj->Tablename());

    mQSqlTableModel.setTable((const QString)mExecObsobj->Tablename());
    mQSqlTableModel.select();
    int i;
    int rowcnt = mQSqlTableModel.rowCount();
    QSqlRecord rec;
    QSqlField fld;
    int val;
    mlist.clear();
    for (i=0;i<rowcnt;i++)
    {
        rec = mQSqlTableModel.record(i);
        fld = rec.field(1);
        val = fld.value().toInt();
        mlist.append(val);
    }

    this->update();
//    this->repaint();
}

void WgtHistgramNumber::on_DatabaseUpdated()
{
    WgtHistgramNumber::refreashWithRowOfTableView();
}

void WgtHistgramNumber::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    int x;
    x=0;
    int val;
    int h;
    h=this->height();
    int x_margin, y_margin, x_padding, y_padding;
    x_margin = 10;
    y_margin = 10;
    x_padding = 10;
    y_padding = 10;
    QListIterator<int> i(mlist);
    while (i.hasNext())
    {
        val = i.next();
        x=x+1;
        painter.drawRect(x_margin + x_padding + x*5, h - val - y_padding - y_margin, 5, val);
    }
}

#include "wgt-histgram-number.h"
#include "ui_wgt-histgram-number.h"

#include <QSqlRecord>
#include <QSqlField>

WgtHistgramNumber::WgtHistgramNumber(QWidget *parent, Obsobj *obsobj, int rowOfTableView) :
    QWidget(parent),
    ui(new Ui::WgtHistgramNumber)
{
    ui->setupUi(this);

    mResolution = ui->spinBox->value();

    mObsobj = obsobj;
    mRowOfTableView = rowOfTableView;

    mlist = QList<int>();

    this->refreashWithRowOfTableView();
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

void WgtHistgramNumber::paintEvent_drawHistgram()
{
    int cnt;
    cnt=0;

    int wkcnt,wkresolution;
    int val,wkval;
    int rect_x, rect_y, rect_width, rect_height;

    QListIterator<int> i(mlist);
    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));
    painter.setBrush(QBrush(Qt::green, Qt::SolidPattern));

    while (i.hasNext())
    {
        val = i.next();
        if (mResolution>0) {
            for (wkcnt=0;wkcnt<mResolution;wkcnt++) {
                wkval = val * 10;
                if (wkval<0) {
                    break;
                } else {
                    val = wkval;
                }
            }
        } else if (mResolution<0) {
            wkresolution = mResolution * -1;
            for (wkcnt=0;wkcnt<wkresolution;wkcnt++) {
                val = val / 10;
            }
        } else {
        }
        rect_x = mXmargin + mXpadding + cnt*5;
        rect_y = mHeight - val - mYpadding - mYmargin;
        rect_width = 5;
        rect_height = val;
        if (rect_y < 0)
        {
            rect_y = 0;
            rect_height = mHeight - mYpadding - mYmargin;
        }
        painter.drawRect(rect_x, rect_y, rect_width, rect_height);

        cnt++;

    }

}

void WgtHistgramNumber::paintEvent_drawAxis()
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));

    int x1,y1,x2,y2;
    x1 = mXmargin + mXpadding;
    y1 = mHeight - mYmargin - mYpadding;
    x2 = x1;
    y2 = mYmargin + mYpadding;
    painter.drawLine(x1,y1,x2,y2);

    x1 = mXmargin + mXpadding;
    y1 = mHeight - mYmargin - mYpadding;
    x2 = mWidth - mXmargin - mXpadding;
    y2 = y1;
    painter.drawLine(x1,y1,x2,y2);
}

void WgtHistgramNumber::paintEvent(QPaintEvent *)
{
    mWidth = this->width();
    mHeight = this->height();

    mXmargin = 10;
    mYmargin = 10;
    mXpadding = 10;
    mYpadding = 10;

    this->paintEvent_drawHistgram();
    this->paintEvent_drawAxis();

}

void WgtHistgramNumber::on_spinBox_valueChanged(int arg1)
{
    mResolution = ui->spinBox->value();

    this->update();
}

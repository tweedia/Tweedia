#include "wgt-histgram-number.h"
#include "ui_wgt-histgram-number.h"

#include <QSqlRecord>
#include <QSqlField>

WgtHistgramNumber::WgtHistgramNumber(QWidget *parent, Obsobj *obsobj, int rowOfTableView) :
    QWidget(parent),
    ui(new Ui::WgtHistgramNumber)
{
    ui->setupUi(this);

    mXmargin = 40;
    mYmargin = 40;
    mSizeDivisionS = 2;
    mSizeDivisionL = 5;
    mHistgramWidth = 5;

    mResolution = ui->spinBox_Resolution->value();
    mXintDivision = 10;
    mYintDivision = 10;

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
        rect_x = mXmargin + cnt*mHistgramWidth;
        rect_width = mHistgramWidth;
        if (val < mHeight - mYmargin*2) {
            rect_y = mHeight - val - mYmargin;
            rect_height = val;
        } else {
            rect_y = mYmargin;
            rect_height = mHeight - mYmargin*2;
        }
        if (rect_y < 0)
        {
            rect_y = 0;
            rect_height = mHeight - mYmargin;
        }
        painter.drawRect(rect_x, rect_y, rect_width, rect_height);

        cnt++;
    }
}

void WgtHistgramNumber::paintEvent_drawAxisX()
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));

    int x1,y1,x2,y2;
    x1 = mXmargin;
    y1 = mHeight - mYmargin;
    x2 = mWidth - mXmargin;
    y2 = y1;

    painter.drawLine(x1,y1,x2,y2);

    int x,y;
    QPainterPath path;
    x = x1;
    y = y1;

    while(x < mWidth - mXmargin) {
        path.moveTo(x, y);
        path.lineTo(x, y + mSizeDivisionL);
        x = x + mXintDivision*mHistgramWidth;
    }
    painter.drawPath(path);
}

void WgtHistgramNumber::paintEvent_drawAxisY()
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap));

    int x1,y1,x2,y2;
    x1 = mXmargin;
    y1 = mHeight - mYmargin;
    x2 = x1;
    y2 = mYmargin;

    painter.drawLine(x1,y1,x2,y2);

    int x,y,cnt;
    QPainterPath path;
    x = x1;
    y = y1;
    cnt = 0;

    while(y > mYmargin) {
        path.moveTo(x, y);
        if (cnt%10==0) {
            path.lineTo(x - mSizeDivisionL, y);
        }else{
            path.lineTo(x - mSizeDivisionS, y);
        }
        y = y - mYintDivision;
        cnt++;
    }
    painter.drawPath(path);
}

void WgtHistgramNumber::paintEvent(QPaintEvent *)
{
    mWidth = this->width();
    mHeight = this->height();

    this->paintEvent_drawHistgram();
    this->paintEvent_drawAxisX();
    this->paintEvent_drawAxisY();
}

void WgtHistgramNumber::on_spinBox_Resolution_valueChanged(int arg1)
{
    mResolution = ui->spinBox_Resolution->value();

    this->update();
}

#include "stringview-scroll.h"
#include "ui_stringview-scroll.h"

StringviewScroll::StringviewScroll(QWidget *parent, Obsobj *obsobj, int rowOfTableView) :
    QWidget(parent),
    ui(new Ui::StringviewScroll)
{
    ui->setupUi(this);

    mObsobj = obsobj;
    mRowOfTableView = rowOfTableView;

    ui->tableView->setShowGrid(FALSE);
//    ui->tableView->setWordWrap(TRUE);
    ui->tableView->horizontalHeader()->hide();
    ui->tableView->verticalHeader()->hide();

    refreashWithRowOfTableView();

    this->on_checkBox_stateChanged(0);

}

void StringviewScroll::refreashWithRowOfTableView()
{
    mExecObsobj = mObsobj->updatedExecObsobj(mRowOfTableView);

    this->setWindowTitle(mExecObsobj->Pathname());
    ui->lblTableName->setText(mExecObsobj->Tablename());

    mQSqlTableModel.setTable((const QString)mExecObsobj->Tablename());
    mQSqlTableModel.setEditStrategy(QSqlTableModel::OnManualSubmit);
    mQSqlTableModel.select();

    ui->tableView->setModel(&mQSqlTableModel);

    ui->tableView->scrollToBottom();

    //it is said that setResizeMode() is no longer available for Qt5
    //and that setSectionResizeMode() can be used
    ui->tableView->horizontalHeader()->setResizeMode(1,QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

}

StringviewScroll::~StringviewScroll()
{
    delete ui;
}

void StringviewScroll::on_DatabaseUpdated()
{
    StringviewScroll::refreashWithRowOfTableView();
}

void StringviewScroll::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()){
        ui->tableView->setColumnHidden(0,false);
    }else{
        ui->tableView->setColumnHidden(0,true);
    }

}

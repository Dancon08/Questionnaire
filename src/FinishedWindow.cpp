#include "FinishedWindow.hpp"
#include "ui_FinishedWindow.h"

FinishedWindow::FinishedWindow(const QString &name, quint8 result, QVector<qint8> resultTemplate, QVector<Question> questions, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinishedWindow),
    result_{result},
    resultTemplate_{resultTemplate},
    questions_{questions}
{
    ui->setupUi(this);

    setFixedSize(1000, 500);

    ui->lblResult_->setText(QString{"You finished test!\n Your result: %1"}.arg(result_));
    ui->lineName_->setText(name);
    connect(ui->lineName_, &QLineEdit::textChanged, this, &FinishedWindow::enableSaveBtn);

    ui->tableCompare_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); 
    ui->tableCompare_->verticalHeader()->hide();

    loadResults();

    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
}

FinishedWindow::~FinishedWindow()
{
    delete ui;
}

void FinishedWindow::on_btnSave__clicked()
{
    if( ui->lineName_->text().isEmpty() )
    {
        return;
    }

    emit saveClicked(ui->lineName_->text());

    this->close();
}

void FinishedWindow::enableSaveBtn(const QString& text)
{
    if( !ui->lineName_->text().isEmpty() )
    {
        ui->btnSave_->setEnabled(true);
    }
    else
    {
        ui->btnSave_->setEnabled(false);
    }

    Q_UNUSED(text)
}

void FinishedWindow::loadResults()
{
    ui->tableCompare_->clearContents();
    ui->tableCompare_->setRowCount(questions_.count());

    for( int i{0}; i < questions_.size(); i++ )
    {
        auto question = questions_.at(i);
        auto answer = resultTemplate_.at(i);

        auto item_0 = new QTableWidgetItem(question.question_);
        auto item_1 = new QTableWidgetItem(question.answers_.at(answer));

        if( question.answerId_ == answer )
        {
            item_1->setBackground(QBrush{Qt::green});
        }
        else
        {
            item_1->setBackground(QBrush{Qt::red});
        }

        ui->tableCompare_->setItem(i, 0, item_0);
        ui->tableCompare_->setItem(i, 1, item_1);
    }
}

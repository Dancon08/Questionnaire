#include "FinishedWindow.hpp"
#include "ui_FinishedWindow.h"

FinishedWindow::FinishedWindow(const QString &name, quint8 result, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FinishedWindow),
    result_{result}
{
    ui->setupUi(this);

    ui->lblResult_->setText(QString{"You finished test!\n Your result: %1"}.arg(result_));
    ui->lineName_->setText(name);
    connect(ui->lineName_, &QLineEdit::textChanged, this, &FinishedWindow::enableSaveBtn);

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

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "jsonparser.h"
#include "FinishedWindow.hpp"
#include "ExportHelper.hpp"
#include <algorithm>
#include <random>

#include <QButtonGroup>
#include <QTimer>
#include <QMessageBox>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedHeight(400);
    btnGroup_ = new QButtonGroup{this};
    btnGroup_->addButton(ui->btnA_, 0);
    btnGroup_->addButton(ui->btnB_, 1);
    btnGroup_->addButton(ui->btnC_, 2);
    btnGroup_->addButton(ui->btnD_, 3);
    btnGroup_->addButton(ui->btnE_, 4);

    timer_ = new QTimer{};
    timer_->setInterval(1000);

    ui->stackedWidget->setCurrentIndex(0);

    ui->tableResult_->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableResult_->verticalHeader()->hide();

    ui->lblTimer_->setText(time_.toString("mm:ss"));

    data_ = JsonParser::loadQuestions(":/resources/answers.json");
    connectUi();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initQuestionPage()
{
    if( index_ == -1 )
    {
        std::shuffle(data_.begin(), data_.end(), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));
        index_ = 0;
    }

    if( data_.size() <= index_ )
    {
        emit testFinished();
        return;
    }

    if( auto btn = btnGroup_->checkedButton() )
    {
        btnGroup_->setExclusive(false);
        btn->setChecked(false);
        btnGroup_->setExclusive(true);
    }


    auto question = data_.at(index_);
    ui->textView_->setText(question.question_);

    auto answers = question.answers_;
    for( const auto& btn : btnGroup_->buttons() )
    {
        btn->setText(answers.at(btnGroup_->id(btn)));
    }
}

void MainWindow::initResultPage()
{
    QMenu* menu = new QMenu{"File", menuBar()};
    QAction* exportToCsv = new QAction{"Export to Csv", menu};
    QAction* exportToPdf = new QAction{"Export to Pdf", menu};

    menu->addActions({exportToCsv, exportToPdf});
    menuBar()->addMenu(menu);

    connect(exportToCsv, &QAction::triggered, this, &MainWindow::exportToCsv);
    connect(exportToPdf, &QAction::triggered, this, &MainWindow::exportToPdf);

    auto results = JsonParser::loadResults("./records.json");

    ui->tableResult_->clearContents();
    ui->tableResult_->setRowCount(results.count());

    for( auto i = 0; i < results.count(); i++ )
    {
        auto result = results.at(i);
        ui->tableResult_->setItem(i, 0, new QTableWidgetItem(result.name_));
        ui->tableResult_->setItem(i, 1, new QTableWidgetItem(QString::number(result.result_)));
        ui->tableResult_->setItem(i, 2, new QTableWidgetItem(result.date_));
    }
}

void MainWindow::nextQuestion()
{
    if( auto btnId = btnGroup_->checkedId(); btnId != -1 )
    {
        resultTemplate_.push_back(btnId);
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "You must select answer!");
        return;
    }

    index_++;
    initQuestionPage();
}

void MainWindow::prevQuestion()
{
    if( index_ <= 0 )
    {
        return;
    }

    resultTemplate_.pop_back();
    index_--;
    initQuestionPage();
}

void MainWindow::saveResult()
{   
    for( int i{0}; i < resultTemplate_.size(); i++ )
    {
        if( resultTemplate_.at(i) == data_.at(i).answerId_ )
        {
            result_ += 10;
        }
    }

    FinishedWindow finishedWnd{userName_, result_, resultTemplate_, data_};

    connect(&finishedWnd, &FinishedWindow::saveClicked, [&result_ = result_](const QString& name)
    {
        JsonParser::saveResult("./records.json", {name, result_, QDateTime::currentDateTime().toString()});
    });

    finishedWnd.exec();

}

void MainWindow::exportToCsv()
{
    auto model = ui->tableResult_->model();
    ExportHelper::exportToCsv(model, "records.csv");
}

void MainWindow::exportToPdf()
{
    ExportHelper::exportToPdf(ui->tableResult_, "records.pdf");
}

void MainWindow::updateCountdown()
{
    time_ = time_.addSecs(-1);
    ui->lblTimer_->setText(time_.toString("mm:ss"));
    if( time_ == QTime{0, 0, 0} )
    {
        timer_->stop();
        emit countdown();
    }
}

void MainWindow::setUserName(const QString &name)
{
    userName_ = name;
}

void MainWindow::connectUi()
{
    connect(ui->btnStart_, &QPushButton::clicked, [&](){ ui->stackedWidget->setCurrentIndex(1); initQuestionPage(); timer_->start();});
    connect(ui->btnResult_, &QPushButton::clicked, [&](){ ui->stackedWidget->setCurrentIndex(2); initResultPage();});
    connect(ui->btnNext_, &QPushButton::clicked, this, &MainWindow::nextQuestion);
    connect(ui->btnPrev_, &QPushButton::clicked, this, &MainWindow::prevQuestion);
    connect(ui->btnHome_, &QPushButton::clicked, [&](){ui->stackedWidget->setCurrentIndex(0); clearSession();});
    connect(ui->btnExit_, &QPushButton::clicked, this, &MainWindow::close);
    connect(this, &MainWindow::testFinished, [&](){ timer_->stop(); saveResult(); ui->stackedWidget->setCurrentIndex(0); clearSession();});
    connect(this, &MainWindow::countdown, [&](){ timer_->stop(); QMessageBox::warning(this, "Warning!", "Time is over!"); ui->stackedWidget->setCurrentIndex(0); clearSession();});
    connect(timer_, &QTimer::timeout, this, &MainWindow::updateCountdown);

    connect(ui->menuBar, &QMenuBar::triggered, this, &MainWindow::exportToCsv);

}

void MainWindow::clearSession()
{
    result_ = 0;
    index_ = -1;
    resultTemplate_.clear();
    time_ = QTime{0, 10, 0};
    if( auto btn = dynamic_cast<QRadioButton*>(btnGroup_->checkedButton()) )
    {
        btn->setChecked(false);
    }

    for( auto action : menuBar()->actions() )
    {
        action->deleteLater();
    }
}

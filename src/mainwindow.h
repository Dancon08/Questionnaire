#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "questions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QButtonGroup;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void testFinished();

public slots:
    void setUserName(const QString& name);

private slots:
    void initQuestionPage();
    void initResultPage();
    void nextQuestion();
    void saveResult();
    void exportToCsv();
    void exportToPdf();

private:
    void connectUi();
    void clearSession();

private:
    Ui::MainWindow *ui;

    QButtonGroup* btnGroup_;

    qint8 index_{0};
    QVector<Question> data_;

    quint8 result_{0};

    QString userName_;
};

#endif // MAINWINDOW_H

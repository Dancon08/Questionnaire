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

private slots:
    void initQuestionPage();
    void initResultPage();
    void nextQuestion();
    void saveResult();

private:
    void connectUi();
    void clearSession();

private:
    Ui::MainWindow *ui;

    QButtonGroup* btnGroup_;

    qint8 index_{0};
    QVector<Question> data_;

    quint8 result_{0};
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTime>
#include "questions.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QButtonGroup;
class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void testFinished();
    void countdown();

public slots:
    void setUserName(const QString& name);

private slots:
    void initQuestionPage();
    void initResultPage();
    void nextQuestion();
    void prevQuestion();
    void saveResult();
    void exportToCsv();
    void exportToPdf();
    void updateCountdown();

private:
    void connectUi();
    void clearSession();

private:
    Ui::MainWindow *ui;

    QButtonGroup* btnGroup_;
    QTimer* timer_;
    QTime time_{0, 10, 0};

    qint8 index_{-1};
    QVector<Question> data_;

    quint8 result_{0};

    QString userName_;

    QVector<qint8> resultTemplate_;
};

#endif // MAINWINDOW_H

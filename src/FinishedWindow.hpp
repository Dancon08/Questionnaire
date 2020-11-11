#ifndef FINISHEDWINDOW_HPP
#define FINISHEDWINDOW_HPP

#include <QDialog>
#include "questions.h"

namespace Ui {
class FinishedWindow;
}

class FinishedWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FinishedWindow(const QString& name, quint8 result, QVector<qint8> resultTemplate, QVector<Question> questions, QWidget *parent = nullptr);
    ~FinishedWindow();

signals:
    void saveClicked(const QString& name);

private slots:
    void on_btnSave__clicked();
    void enableSaveBtn(const QString &text);

private:
    void loadResults();

private:
    Ui::FinishedWindow *ui;

    quint8 result_;
    QVector<qint8> resultTemplate_;
    QVector<Question> questions_;
};
#endif // FINISHEDWINDOW_HPP

#ifndef FINISHEDWINDOW_HPP
#define FINISHEDWINDOW_HPP

#include <QDialog>

namespace Ui {
class FinishedWindow;
}

class FinishedWindow : public QDialog
{
    Q_OBJECT

public:
    explicit FinishedWindow(quint8 result, QWidget *parent = nullptr);
    ~FinishedWindow();

signals:
    void saveClicked(const QString& name);

private slots:
    void on_btnSave__clicked();
    void enableSaveBtn(const QString &text);

private:
    Ui::FinishedWindow *ui;

    quint8 result_;
};

#endif // FINISHEDWINDOW_HPP

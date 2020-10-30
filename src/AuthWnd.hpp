#ifndef AUTHWND_HPP
#define AUTHWND_HPP

#include <QDialog>
#include "Account.hpp"

namespace Ui {
class AuthWnd;
}

class AuthWnd : public QDialog
{
    Q_OBJECT

public:
    explicit AuthWnd(QWidget *parent = nullptr);
    ~AuthWnd();

private:
    void connectUi();
    void clearSession();

private slots:
    void checkLogin();
    void checkRegister();

signals:
    void loginComplete(const QString& name);
    void registerComplete();

private:
    Ui::AuthWnd *ui;
};

#endif // AUTHWND_HPP

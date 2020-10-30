#include "AuthWnd.hpp"
#include "ui_AuthWnd.h"

#include "jsonparser.h"
#include "CryptoHelper.hpp"

#include <QRegExpValidator>
#include <QMessageBox>

AuthWnd::AuthWnd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthWnd)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);

    auto validator = new QRegExpValidator{QRegExp("[A-Za-z0-9_]{1,9}@"), this };
    ui->linePassword_->setValidator(validator);
    ui->lineRegPasswd_->setValidator(validator);

    connectUi();
}

AuthWnd::~AuthWnd()
{
    delete ui;
}

void AuthWnd::connectUi()
{
    connect(ui->btnLogin_, &QPushButton::clicked, this, &AuthWnd::checkLogin);
    connect(ui->btnRegister_, &QPushButton::clicked, [this](){clearSession(); ui->stackedWidget->setCurrentIndex(1);});
    connect(ui->btnCompleteReg_, &QPushButton::clicked, this, &AuthWnd::checkRegister);
    connect(this, &AuthWnd::registerComplete, [this](){clearSession(); ui->stackedWidget->setCurrentIndex(0);});
}

void AuthWnd::clearSession()
{
    ui->lineLogin_->clear();
    ui->linePassword_->clear();
    ui->lineRegName_->clear();
    ui->lineRegPasswd_->clear();
}

void AuthWnd::checkLogin()
{
    auto accountData_ = JsonParser::loadAccounts("accounts.json");
    auto login =  ui->lineLogin_->text();
    if( login.isEmpty() )
    {
        QMessageBox::warning(this, "Warning!", "Login cannot be empty!");
        return;
    }

    auto passwd = ui->linePassword_->text();
    if( passwd.isEmpty() )
    {
        QMessageBox::warning(this, "Warning!", "Password cannot be empty!");
        return;
    }

    if( accountData_.contains( {login, CryptoHelper::getPasswdHash(passwd)} ))
    {
        emit loginComplete(login);
        close();
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Login or password incorrect!");
    }
}

void AuthWnd::checkRegister()
{
    auto accountData_ = JsonParser::loadAccounts("accounts.json");
    auto login =  ui->lineRegName_->text();
    if( login.isEmpty() )
    {
        QMessageBox::warning(this, "Warning!", "Login cannot be empty!");
        return;
    }

    auto passwd = ui->lineRegPasswd_->text();
    if( passwd.isEmpty() )
    {
        QMessageBox::warning(this, "Warning!", "Password cannot be empty!");
        return;
    }

    auto find = std::find_if(accountData_.begin(), accountData_.end(), [&login = login](const auto& val)
    {
        if( val.login_ == login )
        {
            return true;
        }

        return false;
    });

    if( find == accountData_.end() )
    {
        JsonParser::saveAccount("accounts.json", {login, CryptoHelper::getPasswdHash(passwd)});
        emit registerComplete();
    }
    else
    {
        QMessageBox::warning(this, "Warning!", "Account already exists!");
        return;
    }
}

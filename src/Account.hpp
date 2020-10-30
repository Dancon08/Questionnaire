#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <QString>

struct Account
{
    QString login_;
    QString passwd_;


};

inline bool operator==(const Account& lhs, const Account& rhs){ return lhs.login_ == rhs.login_ && lhs.passwd_ == rhs.passwd_; };

#endif // ACCOUNT_HPP

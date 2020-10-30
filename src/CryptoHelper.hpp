#ifndef CRYPTOHELPER_HPP
#define CRYPTOHELPER_HPP

#include <QString>

class CryptoHelper
{
public:
    CryptoHelper();

    static QString getPasswdHash(const QString& passwd);
};

#endif // CRYPTOHELPER_HPP

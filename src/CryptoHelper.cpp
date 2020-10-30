#include "CryptoHelper.hpp"

#include <QCryptographicHash>

CryptoHelper::CryptoHelper()
{

}

QString CryptoHelper::getPasswdHash(const QString &passwd)
{
    return QString{QCryptographicHash::hash(passwd.toUtf8(), QCryptographicHash::Keccak_512).toHex()};
}

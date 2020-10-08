#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QStringList>

struct Question
{
    QString question_{};
    QStringList answers_{};
    qint8 answerId_{-1};
};

#endif // QUESTION_H

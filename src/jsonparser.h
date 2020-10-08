#ifndef DATALOADER_H
#define DATALOADER_H

#include "questions.h"
#include "result.hpp"

#include <QVector>
#include <QJsonArray>

class JsonParser
{
public:
    explicit JsonParser() = default;

    static QVector<Question> loadQuestions(const QString& jsonPath);
    static QVector<Result> loadResults(const QString& jsonPath);
    static void saveResult(const QString& jsonPath, const Result& result);


private:
    static QStringList arrayToList(const QJsonArray& arr);

};

#endif // DATALOADER_H

#include "jsonparser.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

QVector<Question> JsonParser::loadQuestions(const QString &jsonPath)
{
    QVector<Question> retval{};

    QFile file{jsonPath};

    if( !file.open(QIODevice::ReadOnly) )
    {
        qDebug() << "Cannot open data file!";
        return {};
    }

    auto jsonDoc = QJsonDocument::fromJson(file.readAll());

    file.close();

    if( jsonDoc.isNull() )
    {
        qDebug() << "Json corrupted!";
        return {};
    }

    auto obj = jsonDoc.object();

    auto questions = obj["questions"].toArray();

    if( questions.isEmpty() )
    {
        return{};
    }

    for( const auto& arrObjRef : questions )
    {
        auto arrObj = arrObjRef.toObject();
        Question question{};

        question.question_ = arrObj["name"].toString();
        question.answerId_ = arrObj["answer"].toInt();
        question.answers_ = arrayToList(arrObj["answers"].toArray());

        retval.append(question);
    }

    return retval;
}

QVector<Result> JsonParser::loadResults(const QString &jsonPath)
{
    QVector<Result> retval{};

    QFile file{jsonPath};

    if( !file.open(QIODevice::ReadOnly) )
    {
        qDebug() << "Cannot open data file!";
        return {};
    }

    auto jsonDoc = QJsonDocument::fromJson(file.readAll());

    file.close();

    auto obj = jsonDoc.object();

    auto users = obj["users"].toArray();

    if( users.isEmpty() )
    {
        return{};
    }

    for( const auto& arrObjRef : users )
    {
        auto arrObj = arrObjRef.toObject();
        Result result{};

        result.name_ = arrObj["name"].toString();
        result.result_ = arrObj["result"].toInt();

        retval.append(result);
    }

    return retval;
}

void JsonParser::saveResult(const QString &jsonPath, const Result &result)
{
    QVector<Question> retval{};

    QFile file{jsonPath};

    if( !file.open(QIODevice::ReadWrite) )
    {
        qDebug() << "Cannot open data file!";
        qDebug() << jsonPath;
        qDebug() << file.errorString();
        return;
    }

    auto jsonDoc = QJsonDocument::fromJson(file.readAll());
    auto obj = jsonDoc.object();

    auto users = obj["users"].toArray();
    users.push_back(QJsonObject{{"name", result.name_}, {"result", result.result_}});

    obj["users"] = users;
    jsonDoc.setObject(obj);

    file.resize(0);
    file.write(jsonDoc.toJson());
    file.close();

}

QStringList JsonParser::arrayToList(const QJsonArray &arr)
{
    QStringList retval{};

    for( const auto& objRef : arr )
    {
        retval.append(objRef.toString());
    }

    return retval;
}

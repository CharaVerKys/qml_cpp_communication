#pragma once
#include <qjsonobject.h>
namespace qJson{
    bool getValue_especialBool(const QJsonObject& pData, const QString& valueName, bool&&         defValue);
    int               getValue(const QJsonObject& pData, const QString& valueName, int&&          defValue);
    double            getValue(const QJsonObject& pData, const QString& valueName, double&&       defValue);
    QString           getValue(const QJsonObject& pData, const QString& valueName, const QString& defValue);
    QJsonObject       getValue(const QJsonObject& pData, const QString& valueName, QJsonObject&&  defValue);

    uint countFirstLevelJsonObjects(const QJsonObject& jsonObj);
}

inline bool qJson::getValue_especialBool(const QJsonObject& pData, const QString& valueName, bool&& defValue)
{
    if (pData.contains(valueName) && pData[valueName].isBool()){
        return pData[valueName].toBool();
    }else{
        return defValue;
    }
}

inline int qJson::getValue(const QJsonObject& pData, const QString& valueName, int&& defValue)
{
    if (pData.contains(valueName) && pData[valueName].isDouble()){
        return pData[valueName].toInt();
    }else{
        return defValue;
    }
}

inline double qJson::getValue(const QJsonObject& pData, const QString& valueName, double&& defValue)
{
    if (pData.contains(valueName) && pData[valueName].isDouble()){
        return pData[valueName].toDouble();
    }else{
        return defValue;
    }
}

inline QString qJson::getValue(const QJsonObject& pData, const QString& valueName, const QString& defValue)
{
    if (pData.contains(valueName) && pData[valueName].isString()){
        return pData[valueName].toString();
    }else{
        return defValue;
    }
}

inline QJsonObject qJson::getValue(const QJsonObject& pData, const QString& valueName, QJsonObject&& defValue)
{
    if (pData.contains(valueName) && pData[valueName].isObject()){
        return pData[valueName].toObject();
    }else{
        return defValue;
    }
}

inline uint qJson::countFirstLevelJsonObjects(const QJsonObject& jsonObj) {
    uint count = 0;
    for (const QString& key : jsonObj.keys()) {
        const QJsonValue& value = jsonObj.value(key);
        if (value.isObject()) {
            count++;
        }
    }
    return count;
}

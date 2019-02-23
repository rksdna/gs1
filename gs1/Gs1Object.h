#ifndef GS1OBJECT_H
#define GS1OBJECT_H

#include <QMap>
#include <QMetaType>
#include "Gs1Value.h"

class Gs1Object
{
    Q_GADGET

public:
    enum Key
    {
        AI00_SSCC,
        AI01_GTIN,
        AI02_CONTENT,
        AI10_BATCH_LOT,
        AI11_PROD_DATE,
        AI12_DUE_DATE,
        AI13_PACK_DATE,
        AI15_BEST_BY,
        AI16_SELL_BY,
        AI17_USE_BY,
        AI20_VARIANT,
        AI21_SERIAL,
        AI22_CPV,
        AI240_ADDITIONAL_ID,
        AI241_CUST_PART_NO,

        AI311_LENGTH_M,

        AI90_INTERNAL,
        AI91_INTERNAL,
        AI92_INTERNAL,
        AI93_INTERNAL,
        AI94_INTERNAL,
        AI95_INTERNAL,
        AI96_INTERNAL,
        AI97_INTERNAL,
        AI98_INTERNAL,
        AI99_INTERNAL
    };

    Q_ENUM(Key)

public:
    static Gs1Object fromGs1Code(const QByteArray &code);

public:
    Gs1Object();

    bool isEmpty() const;

    void clear();
    void remove(Key key);
    void insert(Key key, const Gs1Value &value);
    Gs1Value take(Key key);
    Gs1Value value(Key key, const Gs1Value &defaultValue = Gs1Value());

    bool operator ==(const Gs1Object &rhs) const;
    bool operator !=(const Gs1Object &rhs) const;

    QByteArray toGs1Code() const;

    QString toPrettyString() const;

private:
    char gs() const;
    bool isDigit(char ch) const;
    bool isAlpha(char ch) const;
    bool readItem(Key key, const QByteArray &code, int &position);
    bool readItem(const QByteArray &code, int &position);
    bool writeItem(Key key, QByteArray &code) const;

private:
    static QMap<Gs1Object::Key, QByteArray> m_patterns;

private:
    QMap<Key, Gs1Value> m_data;
};

QDebug operator <<(QDebug debug, const Gs1Object &object);

#endif // GS1OBJECT_H

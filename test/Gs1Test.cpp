#include "Gs1Test.h"
#include "Gs1Object.h"

Gs1Test::Gs1Test(QObject *parent)
    : QObject(parent)
{
    // negative/positive tests reqired for all types of Gs1Value content
}

void Gs1Test::feedBackTest()
{
    const QString gtin = makeDigitString(14);
    const QDate dueDate = QDate(2044, 11, 19);
    const QString serial = makeAlphaString(15);
    const QString additionalId = makeAlphaString(30);
    const double length = 12.351;

    Gs1Object object;
    object.insert(Gs1Object::AI01_GTIN, gtin);
    object.insert(Gs1Object::AI12_DUE_DATE, dueDate);
    object.insert(Gs1Object::AI21_SERIAL, serial);
    object.insert(Gs1Object::AI240_ADDITIONAL_ID, additionalId);
    object.insert(Gs1Object::AI311_LENGTH_M, Gs1Value(length, 3));

    const QByteArray gs1 = object.toGs1Code();
    qDebug() << gs1;

    Gs1Object clone = Gs1Object::fromGs1Code(gs1);

    QCOMPARE(object, clone);

    QCOMPARE(gtin, clone.value(Gs1Object::AI01_GTIN).toString());
    QCOMPARE(dueDate, clone.value(Gs1Object::AI12_DUE_DATE).toDate());
    QCOMPARE(serial, clone.value(Gs1Object::AI21_SERIAL).toString());
    QCOMPARE(additionalId, clone.value(Gs1Object::AI240_ADDITIONAL_ID).toString());
    QCOMPARE(length, clone.value(Gs1Object::AI311_LENGTH_M).toDouble());
}

void Gs1Test::positiveTableTest()
{
    QVERIFY(!Gs1Object::fromGs1Code("0104600439927013" "21tXSQu%d\x1D" "910001\x1D" "92VcChqA==\x1D" "24014115895").isEmpty());
    QVERIFY(!Gs1Object::fromGs1Code("0104650111111407" "21c7dw28oIjx2JK\x1D" "2406403\x1D" "91ffd0\x1D" "92qxp/aeileJf0jmoxkkkzruSvM827/tUH7uIZljxpu0LnV5bZ5pDiHjzVl0BVga4YtGnowziaonKH1V734VXo6w==").isEmpty());
}

QString Gs1Test::makeDigitString(int size) const
{
    static const QByteArray table("0123456789");
    return makeString(size, table);
}

QString Gs1Test::makeAlphaString(int size) const
{
    static const QByteArray table("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"%&\'()*+-./_,:;=<>?");
    return makeString(size, table);
}

QString Gs1Test::makeString(int size, const QString &table) const
{
    QString result;
    while (size--)
        result.append(table.at(qrand() % table.size()));

    return result;
}

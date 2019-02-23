#ifndef GS1VALUE_H
#define GS1VALUE_H

#include <QDateTime>
#include <QByteArray>

class Gs1Value
{
public:
    Gs1Value();
    Gs1Value(const char *data);
    Gs1Value(const QByteArray &data);

    Gs1Value(const QString &value);
    Gs1Value(const QDate &value);
    Gs1Value(int value);
    Gs1Value(int value, int decimals);
    Gs1Value(double value, int decimals);

    QByteArray data() const;

    bool operator ==(const Gs1Value &rhs) const;
    bool operator !=(const Gs1Value &rhs) const;

    QString toString() const;
    QDate toDate() const;
    int toInt() const;
    QPair<int, int> toFixedPoint() const;
    double toDouble() const;

    QString toPrettyString() const;

private:
    QByteArray format(int value, int decima) const;

private:
    QByteArray m_data;
};

QDebug operator <<(QDebug debug, const Gs1Value &value);

#endif // GS1VALUE_H

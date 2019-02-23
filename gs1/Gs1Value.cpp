#include <QDebug>
#include <QtMath>
#include "Gs1Value.h"

Gs1Value::Gs1Value()
{
}

Gs1Value::Gs1Value(const char *data)
    : m_data(data)
{
}

Gs1Value::Gs1Value(const QByteArray &data)
    : m_data(data)
{
}

Gs1Value::Gs1Value(const QString &value)
    : m_data(value.toLatin1())
{
}

Gs1Value::Gs1Value(const QDate &value)
    : m_data(value.toString("yyMMdd").toLatin1())
{
}

Gs1Value::Gs1Value(int value)
    : m_data(QByteArray::number(value))
{
}

Gs1Value::Gs1Value(int value, int decimals)
    : m_data(format(value, decimals))
{
}

Gs1Value::Gs1Value(double value, int decimals)
    : m_data(format(value * qPow(10, decimals), decimals))
{
}

QByteArray Gs1Value::data() const
{
    return m_data;
}

bool Gs1Value::operator ==(const Gs1Value &rhs) const
{
    return m_data == rhs.m_data;
}

bool Gs1Value::operator !=(const Gs1Value &rhs) const
{
    return m_data != rhs.m_data;
}

QString Gs1Value::toString() const
{
    return QString::fromLatin1(m_data);
}

QDate Gs1Value::toDate() const
{
    // section 7.12

    const int now = QDate::currentDate().year();

    int century = now / 100;

    const int year = m_data.mid(0, 2).toInt();
    const int month = m_data.mid(2, 2).toInt();
    const int day = m_data.mid(4, 2).toInt();

    const int delta = year - now % 100;
    if (delta >= 51 && delta <= 99)
        century--;
    else if (delta >= -99 && delta <= -50)
        century++;

    return QDate(century * 100 + year, month, day);
}

int Gs1Value::toInt() const
{
    return m_data.toInt();
}

QPair<int, int> Gs1Value::toFixedPoint() const
{
    return qMakePair(m_data.mid(1).toInt(), m_data.left(1).toInt());
}

double Gs1Value::toDouble() const
{
    return m_data.mid(1).toInt() * qPow(10, -m_data.left(1).toInt());
}

QString Gs1Value::toPrettyString() const
{
    return QString::fromLatin1(m_data);
}

QByteArray Gs1Value::format(int value, int decimals) const
{
    return QByteArray::number(decimals) + QByteArray::number(value).rightJustified(6, '0');
}

QDebug operator <<(QDebug debug, const Gs1Value &value)
{
    QDebugStateSaver saver(debug);
    debug.noquote().nospace() << value.toPrettyString();

    return debug;
}

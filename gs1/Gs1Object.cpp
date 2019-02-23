#include <QDebug>
#include <QMetaEnum>
#include "Gs1Object.h"

#define P(x) QByteArray(#x)
#define N(n) QByteArray(n, 'N')
#define N_(n) QByteArray(n, 'n')
#define X(n) QByteArray(n, 'X')
#define X_(n) QByteArray(n, 'x')
#define FNC QByteArray(1, '`')

QMap<Gs1Object::Key, QByteArray> Gs1Object::m_patterns;

Gs1Object Gs1Object::fromGs1Code(const QByteArray &code)
{
    int position = 0;
    Gs1Object object;
    while (position < code.size())
    {
        if (!object.readItem(code, position))
            return Gs1Object();
    }

    return object;
}

Gs1Object::Gs1Object()
{
    // section 3.2

    if (m_patterns.isEmpty())
    {
        m_patterns.insert(Gs1Object::AI00_SSCC, P(00) + N(18));
        m_patterns.insert(Gs1Object::AI01_GTIN, P(01) + N(14));
        m_patterns.insert(Gs1Object::AI02_CONTENT, P(02) + N(14));
        m_patterns.insert(Gs1Object::AI10_BATCH_LOT, P(10) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI11_PROD_DATE, P(11) + N(6));
        m_patterns.insert(Gs1Object::AI12_DUE_DATE, P(12) + N(6));
        m_patterns.insert(Gs1Object::AI13_PACK_DATE, P(13) + N(6));
        m_patterns.insert(Gs1Object::AI15_BEST_BY, P(15) + N(6));
        m_patterns.insert(Gs1Object::AI16_SELL_BY, P(16) + N(6));
        m_patterns.insert(Gs1Object::AI17_USE_BY, P(17) + N(6));
        m_patterns.insert(Gs1Object::AI20_VARIANT, P(20) + N(2));
        m_patterns.insert(Gs1Object::AI21_SERIAL, P(21) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI22_CPV, P(22) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI240_ADDITIONAL_ID, P(240) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI241_CUST_PART_NO, P(241) + X_(30) + FNC);

        m_patterns.insert(Gs1Object::AI311_LENGTH_M, "311NNNNNNN");

        m_patterns.insert(Gs1Object::AI90_INTERNAL, P(90) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI91_INTERNAL, P(91) + X_(90) + FNC);
        m_patterns.insert(Gs1Object::AI92_INTERNAL, P(92) + X_(90) + FNC);
        m_patterns.insert(Gs1Object::AI93_INTERNAL, P(93) + X_(90) + FNC);
        m_patterns.insert(Gs1Object::AI94_INTERNAL, P(94) + X_(90) + FNC);
        m_patterns.insert(Gs1Object::AI95_INTERNAL, P(95) + X_(90) + FNC);
        m_patterns.insert(Gs1Object::AI96_INTERNAL, P(96) + X_(90) + FNC);
        m_patterns.insert(Gs1Object::AI97_INTERNAL, P(97) + X_(90) + FNC);
        m_patterns.insert(Gs1Object::AI98_INTERNAL, P(98) + X_(90) + FNC);
        m_patterns.insert(Gs1Object::AI99_INTERNAL, P(99) + X_(90) + FNC);
    }
}

bool Gs1Object::isEmpty() const
{
    return m_data.isEmpty();
}

void Gs1Object::clear()
{
    m_data.clear();
}

void Gs1Object::remove(Gs1Object::Key key)
{
    m_data.remove(key);
}

void Gs1Object::insert(Gs1Object::Key key, const Gs1Value &value)
{
    m_data.insert(key, value);
}

Gs1Value Gs1Object::take(Gs1Object::Key key)
{
    return m_data.take(key);
}

Gs1Value Gs1Object::value(Gs1Object::Key key, const Gs1Value &defaultValue)
{
    return m_data.value(key, defaultValue);
}

bool Gs1Object::operator ==(const Gs1Object &rhs) const
{
    return m_data == rhs.m_data;
}

bool Gs1Object::operator !=(const Gs1Object &rhs) const
{
    return m_data != rhs.m_data;
}

QByteArray Gs1Object::toGs1Code() const
{
    QByteArray code;
    foreach (Key key, m_data.keys())
    {
        if (!writeItem(key, code))
            return QByteArray();
    }

    return code;
}

QString Gs1Object::toPrettyString() const
{
    QStringList items;
    const QMetaEnum metaEnum = QMetaEnum::fromType<Gs1Object::Key>();
    foreach (Key key, m_data.keys())
        items.append(QString("%1: %2").arg(metaEnum.valueToKey(key), m_data.value(key).toPrettyString()));

    return items.join(", ");
}

char Gs1Object::gs() const
{
    return '\x1D';
}

bool Gs1Object::isDigit(char ch) const
{
    // optimization required

    static const QByteArray table("0123456789");
    return table.contains(ch);
}

bool Gs1Object::isAlpha(char ch) const
{
    // optimization required

    static const QByteArray table("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!\"%&\'()*+-./_,:;=<>?");
    return table.contains(ch);
}

bool Gs1Object::readItem(Key key, const QByteArray &code, int &position)
{
    int index = position;
    QByteArray buffer;
    foreach (char pattern, m_patterns.value(key))
    {
        const char ch = index < code.size() ? code.at(index) : 0;
        switch (pattern)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            if (ch != pattern)
                return false;

            index++;
            break;

        case 'n':
            if (!ch || ch == gs())
                break;

        case 'N':
            if (!isDigit(ch))
                return false;

            buffer.append(ch);
            index++;
            break;

        case 'x':
            if (!ch || ch == gs())
                break;

        case 'X':
            if (!isAlpha(ch))
                return false;

            buffer.append(ch);
            index++;
            break;

        case '`':
            if (!ch)
                break;

            if (ch == gs())
            {
                index++;
                break;
            }

            return false;

        default:
            Q_ASSERT_X(false, "Gs1", "Invalid pattern");
        }
    }

    position = index;
    m_data.insert(key, buffer);
    return true;
}

bool Gs1Object::readItem(const QByteArray &code, int &position)
{
    foreach (Key key, m_patterns.keys())
    {
        if (readItem(key, code, position))
            return true;
    }

    return false;
}

bool Gs1Object::writeItem(Key key, QByteArray &code) const
{
    int index = 0;
    QByteArray buffer;
    const QByteArray data = m_data.value(key).data();
    foreach (char pattern, m_patterns.value(key))
    {
        const char ch = index < data.size() ? data.at(index) : 0;
        switch (pattern)
        {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            buffer.append(pattern);
            break;

        case 'n':
            if (!ch)
                break;

        case 'N':
            if (!isDigit(ch))
                return false;

            buffer.append(ch);
            index++;
            break;

        case 'x':
            if (!ch)
                break;

        case 'X':
            if (!isAlpha(ch))
                return false;

            buffer.append(ch);
            index++;
            break;

        case '`':
            if (key != m_data.lastKey())
                buffer.append(gs());

            break;

        default:
            Q_ASSERT_X(false, "Gs1", "Invalid pattern");
        }
    }

    if (index != data.size())
        return false;

    code.append(buffer);
    return true;
}

QDebug operator <<(QDebug debug, const Gs1Object &object)
{
    QDebugStateSaver saver(debug);
    debug.noquote().nospace() << "Gs1Object(" << object.toPrettyString() << ")";

    return debug;
}

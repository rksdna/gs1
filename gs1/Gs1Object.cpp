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
        m_patterns.insert(Gs1Object::AI242_MTO_VARIANT, P(242) + N_(6) + FNC);
        m_patterns.insert(Gs1Object::AI243_PCN, P(243) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI250_SECONDARY_SERIAL, P(250) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI253_GDTI, P(253) + N(13) + X_(17) + FNC);
        m_patterns.insert(Gs1Object::AI254_GLN_EXTENSION_COMPONENT, P(254) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI255_GCN, P(255) + N(13) + N_(12) + FNC);
        m_patterns.insert(Gs1Object::AI30_VAR_COUNT, P(30) + N_(8) + FNC);
        m_patterns.insert(Gs1Object::AI310_NET_WEIGHT_KG, P(310) + N(7));
        m_patterns.insert(Gs1Object::AI311_LENGTH_M, P(311) + N(7));
        m_patterns.insert(Gs1Object::AI312_WIDTH_M, P(312) + N(7));
        m_patterns.insert(Gs1Object::AI313_HEIGHT_M, P(313) + N(7));
        m_patterns.insert(Gs1Object::AI314_AREA_M2, P(314) + N(7));
        m_patterns.insert(Gs1Object::AI315_NET_VOLUME_L, P(315) + N(7));
        m_patterns.insert(Gs1Object::AI316_NET_VOLUME_M3, P(316) + N(7));
        m_patterns.insert(Gs1Object::AI320_NEW_WEIGHT_LB, P(320) + N(7));
        m_patterns.insert(Gs1Object::AI321_LENGTH_I, P(321) + N(7));
        m_patterns.insert(Gs1Object::AI322_LENGTH_F, P(322) + N(7));
        m_patterns.insert(Gs1Object::AI323_LENGTH_Y, P(323) + N(7));
        m_patterns.insert(Gs1Object::AI324_WIDTH_I, P(324) + N(7));
        m_patterns.insert(Gs1Object::AI325_WIDTH_F, P(325) + N(7));
        m_patterns.insert(Gs1Object::AI326_WIDTH_Y, P(326) + N(7));
        m_patterns.insert(Gs1Object::AI327_HEIGHT_I, P(327) + N(7));
        m_patterns.insert(Gs1Object::AI328_HEIGHT_F, P(328) + N(7));
        m_patterns.insert(Gs1Object::AI329_HEIGHT_Y, P(329) + N(7));
        m_patterns.insert(Gs1Object::AI330_GROSS_WEIGHT_KG, P(330) + N(7));
        m_patterns.insert(Gs1Object::AI331_LENGTH_M_LOG, P(331) + N(7));
        m_patterns.insert(Gs1Object::AI332_WIDTH_M_LOG, P(332) + N(7));
        m_patterns.insert(Gs1Object::AI333_HEIGHT_M_LOG, P(333) + N(7));
        m_patterns.insert(Gs1Object::AI334_AREA_M2_LOG, P(334) + N(7));
        m_patterns.insert(Gs1Object::AI335_VOLUME_L_LOG, P(335) + N(7));
        m_patterns.insert(Gs1Object::AI336_VOLUME_M3_LOG, P(336) + N(7));
        m_patterns.insert(Gs1Object::AI337_KG_PER_M2, P(337) + N(7));
        m_patterns.insert(Gs1Object::AI340_GROSS_WEIGHT_LB, P(340) + N(7));
        m_patterns.insert(Gs1Object::AI341_LENGTH_I_LOG, P(341) + N(7));
        m_patterns.insert(Gs1Object::AI342_LENGTH_F_LOG, P(342) + N(7));
        m_patterns.insert(Gs1Object::AI343_LENGTH_Y_LOG, P(343) + N(7));
        m_patterns.insert(Gs1Object::AI344_WIDTH_I_LOG, P(344) + N(7));
        m_patterns.insert(Gs1Object::AI345_WIDTH_F_LOG, P(345) + N(7));
        m_patterns.insert(Gs1Object::AI346_WIDTH_Y_LOG, P(346) + N(7));
        m_patterns.insert(Gs1Object::AI347_HEIGHT_I_LOG, P(347) + N(7));
        m_patterns.insert(Gs1Object::AI348_HEIGHT_F_LOG, P(348) + N(7));
        m_patterns.insert(Gs1Object::AI349_HEIGHT_Y_LOG, P(349) + N(7));
        m_patterns.insert(Gs1Object::AI350_AREA_I2, P(350) + N(7));
        m_patterns.insert(Gs1Object::AI351_AREA_F2, P(351) + N(7));
        m_patterns.insert(Gs1Object::AI352_AREA_Y2, P(352) + N(7));
        m_patterns.insert(Gs1Object::AI353_AREA_I2_LOG, P(353) + N(7));
        m_patterns.insert(Gs1Object::AI354_AREA_F2_LOG, P(354) + N(7));
        m_patterns.insert(Gs1Object::AI355_AREA_Y2_LOG, P(355) + N(7));
        m_patterns.insert(Gs1Object::AI356_NET_WEIGHT_T, P(356) + N(7));
        m_patterns.insert(Gs1Object::AI357_NET_VOLUME_OZ, P(357) + N(7));
        m_patterns.insert(Gs1Object::AI360_NET_VOLUME_Q, P(360) + N(7));
        m_patterns.insert(Gs1Object::AI361_NET_VOLUME_G, P(361) + N(7));
        m_patterns.insert(Gs1Object::AI362_VOLUME_Q_LOG, P(362) + N(7));
        m_patterns.insert(Gs1Object::AI363_VOLUME_G_LOG, P(363) + N(7));
        m_patterns.insert(Gs1Object::AI364_VOLUME_I3, P(364) + N(7));
        m_patterns.insert(Gs1Object::AI365_VOLUME_F3, P(365) + N(7));
        m_patterns.insert(Gs1Object::AI366_VOLUME_Y3, P(366) + N(7));
        m_patterns.insert(Gs1Object::AI367_VOLUME_I3_LOG, P(367) + N(7));
        m_patterns.insert(Gs1Object::AI368_VOLUME_F3_LOG, P(368) + N(7));
        m_patterns.insert(Gs1Object::AI369_VOLUME_Y3_LOG, P(369) + N(7));
        m_patterns.insert(Gs1Object::AI37_COUNT, P(37) + N_(8) + FNC);
        m_patterns.insert(Gs1Object::AI390_AMOUNT, P(390) + N(1) + N_(15) + FNC);
        m_patterns.insert(Gs1Object::AI391_AMOUNT, P(391) + N(4) + N_(15) + FNC);
        m_patterns.insert(Gs1Object::AI392_PRICE, P(392) + N(1) + N_(15) + FNC);
        m_patterns.insert(Gs1Object::AI393_PRICE, P(393) + N(4) + N_(15) + FNC);
        m_patterns.insert(Gs1Object::AI394_PRCNT_OFF, P(394) + N(4) + FNC);
        m_patterns.insert(Gs1Object::AI400_ORDER_NUMBER, P(400) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI401_GINC, P(401) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI402_GSIN, P(402) + N(17) + FNC);
        m_patterns.insert(Gs1Object::AI403_ROUTE, P(403) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI410_SHIP_TO_LOC, P(410) + N(13));
        m_patterns.insert(Gs1Object::AI411_BILL_TO, P(411) + N(13));
        m_patterns.insert(Gs1Object::AI412_PURCHASE_FROM, P(412) + N(13));
        m_patterns.insert(Gs1Object::AI413_SHIP_FOR_LOC, P(413) + N(13));
        m_patterns.insert(Gs1Object::AI414_LOC_NO, P(414) + N(13));
        m_patterns.insert(Gs1Object::AI415_PAY_TO, P(415) + N(13));
        m_patterns.insert(Gs1Object::AI416_PROD_SERV_LOC, P(416) + N(13));
        m_patterns.insert(Gs1Object::AI420_SHIP_TO_POST, P(420) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI421_SHIP_TO_POST, P(421) + N(3) + X_(9) + FNC);
        m_patterns.insert(Gs1Object::AI422_ORIGIN, P(422) + N(3) + FNC);
        m_patterns.insert(Gs1Object::AI423_COUNTRY_INITIAL_PROCESS, P(423) + N(3) + N_(12) + FNC);
        m_patterns.insert(Gs1Object::AI424_COUNTRY_PROCESS, P(424) + N(3) + FNC);
        m_patterns.insert(Gs1Object::AI425_COUNTRY_DISASSEBLY, P(425) + N(3) + N_(12) + FNC);
        m_patterns.insert(Gs1Object::AI426_COUNTRY_FULL_PROCESS, P(426) + N(3) + FNC);
        m_patterns.insert(Gs1Object::AI427_ORIGIN_SUBDIVISION, P(427) + X_(3) + FNC);
        m_patterns.insert(Gs1Object::AI7001_NSN, P(7001) + N(13) + FNC);
        m_patterns.insert(Gs1Object::AI7002_MEAT_CUT, P(7002) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI7003_EXPIRY_TIME, P(7003) + N(10) + FNC);
        m_patterns.insert(Gs1Object::AI7004_ACTIVE_POTENCY, P(7004) + N_(4) + FNC);
        m_patterns.insert(Gs1Object::AI7005_CATCH_AREA, P(7005) + X_(12) + FNC);
        m_patterns.insert(Gs1Object::AI7006_FIRST_FREEZE_DATE, P(7006) + N(6) + FNC);
        m_patterns.insert(Gs1Object::AI7007_HARVEST_DATE, P(7007) + N(6) + N_(6) + FNC);
        m_patterns.insert(Gs1Object::AI7008_AQUATIC_SPECIES, P(7008) + X_(3) + FNC);
        m_patterns.insert(Gs1Object::AI7009_FISHING_GEAR_TYPE, P(7009) + X_(10) + FNC);
        m_patterns.insert(Gs1Object::AI7010_PROD_METHOD, P(7010) + X_(2) + FNC);
        m_patterns.insert(Gs1Object::AI7020_REFURB_LOT, P(7020) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI7021_FUNC_STAT, P(7021) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI7022_REV_STAT, P(7022) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI7023_GIAL_ASSEMBLY, P(7023) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI703_PROCESSOR, P(703) + N(4) + X_(27) + FNC);
        m_patterns.insert(Gs1Object::AI71_NHRN, P(71) + N(1) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI723_CERT, P(723) + N(1) + X(2) + X_(28) + FNC);
        m_patterns.insert(Gs1Object::AI8001_DIMENSIONS, P(8001) + N(14) + FNC);
        m_patterns.insert(Gs1Object::AI8002_CMT_NO, P(8002) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI8003_GRAI, P(8003) + N(14) + X_(16) + FNC);
        m_patterns.insert(Gs1Object::AI8004_GIAI, P(8004) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI8005_PRICE_PER_UNIT, P(8005) + N(6) + FNC);
        m_patterns.insert(Gs1Object::AI8006_ITIP_OR_GCTIN, P(8006) + N(14) + N(2) + N(2) + FNC);
        m_patterns.insert(Gs1Object::AI8007_IBAN, P(8007) + X_(34) + FNC);
        m_patterns.insert(Gs1Object::AI8008_PROD_TIME, P(8008) + N(8) + N_(4) + FNC);
        m_patterns.insert(Gs1Object::AI8009_OPTSEN, P(8009) + X_(50) + FNC);
        m_patterns.insert(Gs1Object::AI8010_CPID, P(8010) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI8011_CPID_SERIAL, P(8011) + N_(12) + FNC);
        m_patterns.insert(Gs1Object::AI8012_VERSION, P(8012) + X_(20) + FNC);
        m_patterns.insert(Gs1Object::AI8013_GMN_OR_BUDI_DI, P(8013) + X_(30) + FNC);
        m_patterns.insert(Gs1Object::AI8017_GSRN_PROVIDER, P(8017) + N(18) + FNC);
        m_patterns.insert(Gs1Object::AI8018_GSRN_RECIPIENT, P(8018) + N(18) + FNC);
        m_patterns.insert(Gs1Object::AI8019_SRIN, P(8018) + N_(10) + FNC);
        m_patterns.insert(Gs1Object::AI8020_REF_NUMBER, P(8020) + X_(25) + FNC);
        m_patterns.insert(Gs1Object::AI8026_ITIP_CONTENT, P(8026) + N(14) + N(2) + N(2) + FNC);
        m_patterns.insert(Gs1Object::AI8110_NO_TITLE, P(8110) + X_(70) + FNC);
        m_patterns.insert(Gs1Object::AI8111_POINTS, P(8111) + N(4) + FNC);
        m_patterns.insert(Gs1Object::AI8112_NO_TITLE, P(8111) + X_(70) + FNC);
        m_patterns.insert(Gs1Object::AI8200_PRODUCT_URL, P(8200) + X_(70) + FNC);
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


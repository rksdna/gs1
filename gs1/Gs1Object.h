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
        AI242_MTO_VARIANT,
        AI243_PCN,
        AI250_SECONDARY_SERIAL,
        AI253_GDTI,
        AI254_GLN_EXTENSION_COMPONENT,
        AI255_GCN,
        AI30_VAR_COUNT,
        AI310_NET_WEIGHT_KG,
        AI311_LENGTH_M,
        AI312_WIDTH_M,
        AI313_HEIGHT_M,
        AI314_AREA_M2,
        AI315_NET_VOLUME_L,
        AI316_NET_VOLUME_M3,
        AI320_NEW_WEIGHT_LB,
        AI321_LENGTH_I,
        AI322_LENGTH_F,
        AI323_LENGTH_Y,
        AI324_WIDTH_I,
        AI325_WIDTH_F,
        AI326_WIDTH_Y,
        AI327_HEIGHT_I,
        AI328_HEIGHT_F,
        AI329_HEIGHT_Y,
        AI330_GROSS_WEIGHT_KG,
        AI331_LENGTH_M_LOG,
        AI332_WIDTH_M_LOG,
        AI333_HEIGHT_M_LOG,
        AI334_AREA_M2_LOG,
        AI335_VOLUME_L_LOG,
        AI336_VOLUME_M3_LOG,
        AI337_KG_PER_M2,
        AI340_GROSS_WEIGHT_LB,
        AI341_LENGTH_I_LOG,
        AI342_LENGTH_F_LOG,
        AI343_LENGTH_Y_LOG,
        AI344_WIDTH_I_LOG,
        AI345_WIDTH_F_LOG,
        AI346_WIDTH_Y_LOG,
        AI347_HEIGHT_I_LOG,
        AI348_HEIGHT_F_LOG,
        AI349_HEIGHT_Y_LOG,
        AI350_AREA_I2,
        AI351_AREA_F2,
        AI352_AREA_Y2,
        AI353_AREA_I2_LOG,
        AI354_AREA_F2_LOG,
        AI355_AREA_Y2_LOG,
        AI356_NET_WEIGHT_T,
        AI357_NET_VOLUME_OZ,
        AI360_NET_VOLUME_Q,
        AI361_NET_VOLUME_G,
        AI362_VOLUME_Q_LOG,
        AI363_VOLUME_G_LOG,
        AI364_VOLUME_I3,
        AI365_VOLUME_F3,
        AI366_VOLUME_Y3,
        AI367_VOLUME_I3_LOG,
        AI368_VOLUME_F3_LOG,
        AI369_VOLUME_Y3_LOG,
        AI37_COUNT,
        AI390_AMOUNT,
        AI391_AMOUNT,
        AI392_PRICE,
        AI393_PRICE,
        AI394_PRCNT_OFF,
        AI400_ORDER_NUMBER,
        AI401_GINC,
        AI402_GSIN,
        AI403_ROUTE,
        AI410_SHIP_TO_LOC,
        AI411_BILL_TO,
        AI412_PURCHASE_FROM,
        AI413_SHIP_FOR_LOC,
        AI414_LOC_NO,
        AI415_PAY_TO,
        AI416_PROD_SERV_LOC,
        AI420_SHIP_TO_POST,
        AI421_SHIP_TO_POST,
        AI422_ORIGIN,
        AI423_COUNTRY_INITIAL_PROCESS,
        AI424_COUNTRY_PROCESS,
        AI425_COUNTRY_DISASSEBLY,
        AI426_COUNTRY_FULL_PROCESS,
        AI427_ORIGIN_SUBDIVISION,
        AI7001_NSN,
        AI7002_MEAT_CUT,
        AI7003_EXPIRY_TIME,
        AI7004_ACTIVE_POTENCY,
        AI7005_CATCH_AREA,
        AI7006_FIRST_FREEZE_DATE,
        AI7007_HARVEST_DATE,
        AI7008_AQUATIC_SPECIES,
        AI7009_FISHING_GEAR_TYPE,
        AI7010_PROD_METHOD,
        AI7020_REFURB_LOT,
        AI7021_FUNC_STAT,
        AI7022_REV_STAT,
        AI7023_GIAL_ASSEMBLY,
        AI703_PROCESSOR,
        AI71_NHRN,
        AI723_CERT,
        AI8001_DIMENSIONS,
        AI8002_CMT_NO,
        AI8003_GRAI,
        AI8004_GIAI,
        AI8005_PRICE_PER_UNIT,
        AI8006_ITIP_OR_GCTIN,
        AI8007_IBAN,
        AI8008_PROD_TIME,
        AI8009_OPTSEN,
        AI8010_CPID,
        AI8011_CPID_SERIAL,
        AI8012_VERSION,
        AI8013_GMN_OR_BUDI_DI,
        AI8017_GSRN_PROVIDER,
        AI8018_GSRN_RECIPIENT,
        AI8019_SRIN,
        AI8020_REF_NUMBER,
        AI8026_ITIP_CONTENT,
        AI8110_NO_TITLE,
        AI8111_POINTS,
        AI8112_NO_TITLE,
        AI8200_PRODUCT_URL,
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

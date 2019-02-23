#ifndef GS1TEST_H
#define GS1TEST_H

#include <QTest>
#include <QObject>

class Gs1Test : public QObject
{
    Q_OBJECT
public:
    explicit Gs1Test(QObject *parent = 0);

private slots:
    void feedBackTest();
    void positiveTableTest();

private:
    QString makeDigitString(int size) const;
    QString makeAlphaString(int size) const;
    QString makeString(int size, const QString &table) const;
};

#endif // GS1TEST_H

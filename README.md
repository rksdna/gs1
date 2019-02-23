# GS1

Qt-based library for parsing and creating GS1 codes. __Not fully tested__.

Example:
```
Gs1Object object;
object.insert(Gs1Object::AI01_GTIN, "04650111111407");
object.insert(Gs1Object::AI12_DUE_DATE, QDate(2034, 11, 19));
object.insert(Gs1Object::AI311_LENGTH_M, Gs1Value(123.456, 3));
qDebug() << object; // Gs1Object(AI01_GTIN: 04650111111407, AI12_DUE_DATE: 341119, AI311_LENGTH_M: 3123456)

const QByteArray gs1 = object.toGs1Code();
qDebug() << gs1; // "0104650111111407123411193113123456"

Gs1Object clone = Gs1Object::fromGs1Code(gs1);
qDebug() << clone; // Gs1Object(AI01_GTIN: 04650111111407, AI12_DUE_DATE: 341119, AI311_LENGTH_M: 3123456)

qDebug() << clone.value(Gs1Object::AI01_GTIN).toString(); // "04650111111407"
qDebug() << clone.value(Gs1Object::AI12_DUE_DATE).toDate(); // QDate("2034-11-19")
qDebug() << clone.value(Gs1Object::AI311_LENGTH_M).toDouble(); // 123.456
```

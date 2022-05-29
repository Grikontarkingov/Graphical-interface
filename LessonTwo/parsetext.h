#ifndef PARSETEXT_H
#define PARSETEXT_H
#include <QString>


class ParseText
{
public:
    ParseText();
    bool change(QString);
    QString replace(QString);
    QString getText();

private:
    QString text;
    QString preText;
    qint32 pos;
};

#endif // PARSETEXT_H

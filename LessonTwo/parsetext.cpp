#include "parsetext.h"

ParseText::ParseText()
{
    text = "";
    preText = "";
    pos = 0;
}

bool ParseText::change(QString in)
{
    qint32 length = std::min(std::min(text.length(), in.length()), pos);
    preText = "";
    for(qint32 i = 0; i < length; ++i)
    {
        if(text[i] != in[i])
        {
            pos = i;
            break;
        }
    }

    const QChar* arStr = in.constData();
    qint32 ppos = 0, lastp = -1;
    bool change = false;

    for(qint32 fnd = in.indexOf("#@", pos);
        fnd != -1 && lastp != pos;
        fnd = in.indexOf("#@", pos))
    {
        preText.insert(preText.length(), &arStr[ppos], fnd);
        lastp = pos;
        pos = fnd;
        int r = in.indexOf('@', fnd + 2);
        int space = in.indexOf(' ', fnd);
        if((r < space || space == -1) && r != -1)
        {
            QString example = "";
            example.insert(0, &arStr[fnd + 2], r - fnd - 2);
            QString rez = replace(example);
            preText += rez;
            pos = r + 1;
            change = true;
        }

        preText.insert(preText.length(), &arStr[pos], in.length() - pos);
    }

    return change;
}

QString ParseText::replace(QString example)
{
    QString result = example.toLower();

    if("copyright" == result)
    {
        result = "©";
    }
    else if("promille" == result)
    {
        result = "‰";
    }
    else if("trademark" == result)
    {
        result = "®";
    }
    else if("euro" == result)
    {
        result = "€";
    }
    else if("rub" == result)
    {
        result = "₽";
    }

    return result;
}

QString ParseText::getText()
{
    text = preText;
    return text;
}

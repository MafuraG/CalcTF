#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <QString>


class ToolBox
{
public:
    ToolBox();
    static bool isNumber(const QString &val){
        bool ok;
        val.toDouble(&ok);
        return ok;
    }

    static uint readNumber(const QString &str, const uint start, double &number ){
        int i = start;
        QString numStr = "";
        if (start >= str.count()) return str.count();

        while (i < str.count()){
            QString s = "";
            s.append(str[i++]);
            if (isNumber(s)) numStr.append(s);
            else break;
        }

        number = numStr.toDouble();

        return i;
    }

};

#endif // TOOLBOX_H

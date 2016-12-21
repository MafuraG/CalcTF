#ifndef TOOLBOX_H
#define TOOLBOX_H
#include <QString>
#include <random>


class ToolBox
{
public:
    ToolBox();
    static bool isNumber(const QString &val){
        bool ok;
        val.toDouble(&ok);
        if (val == "-" || val =="+") ok = true;
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

    template<typename Numeric, typename Generator = std::mt19937>
    static Numeric random(Numeric from, Numeric to)
    {
        thread_local static Generator gen(std::random_device{}());

        using dist_type = typename std::conditional
        <
            std::is_integral<Numeric>::value
            , std::uniform_int_distribution<Numeric>
            , std::uniform_real_distribution<Numeric>
        >::type;

        thread_local static dist_type dist;

        return dist(gen, typename dist_type::param_type{from, to});
    }

};

#endif // TOOLBOX_H

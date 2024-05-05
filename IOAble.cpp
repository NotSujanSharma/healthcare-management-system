#include "IOAble.h"
namespace seneca
{
    std::ostream &operator<<(std::ostream &ostr, const IOAble &item)
    {
        return item.write(ostr);
    }

    std::istream &operator>>(std::istream &istr, IOAble &item)
    {
        return item.read(istr);
    }
}
#ifndef SDDS_IOABLE_H
#define SDDS_IOABLE_H
#include <iostream>
namespace seneca
{
    class IOAble
    {
    public:
        virtual std::ostream &write(std::ostream &ostr = std::cout) const = 0;

        virtual std::istream &read(std::istream &istr = std::cin) = 0;

        virtual ~IOAble(){};
    };

    std::ostream &operator<<(std::ostream &ostr, const IOAble &obj);

    std::istream &operator>>(std::istream &istr, IOAble &obj);
}
#endif
#include "Time.h"
#include "Utils.h"
#include <iomanip>
#include <iostream>

namespace seneca
{
    Time::Time(unsigned int min) : m_minutes(min) {}

    Time &Time::reset()
    {
        m_minutes = U.getTime();
        return *this;
    }

    std::ostream &Time::write(std::ostream &ostr) const
    {
        int hours = m_minutes / 60;
        int mins = m_minutes % 60;
        ostr.setf(std::ios::right);
        ostr << std::setw(2)

             << std::setfill('0')
             << hours
             << ":"
             << std::setw(2)
             << std::setfill('0')
             << mins;
        ostr.unsetf(std::ios::right);
        return ostr;
    }

    std::istream &Time::read(std::istream &istr)
    {
        char colon;
        unsigned int hours, mins;
        istr >> hours;
        colon = istr.peek();
        if (colon != ':')
        {
            istr.setstate(std::ios::failbit);
        }
        else
        {
            istr.ignore();
            istr >> mins;
            m_minutes = hours * 60 + mins;
        }
        return istr;
    }

    Time::operator unsigned int() const
    {
        return m_minutes;
    }

    Time &Time::operator*=(int val)
    {
        m_minutes *= val;
        return *this;
    }
    Time Time::operator-(const Time &T) const
    {
        Time result(*this);
        if (result.m_minutes < T.m_minutes)
            result.m_minutes += (24 * 60);

        result.m_minutes -= T.m_minutes;
        return result;
    }

    Time &Time::operator-=(const Time &D)
    {
        *this = *this - D;
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const Time &time)
    {
        return time.write(os);
    }

    std::istream &operator>>(std::istream &istr, Time &time)
    {
        return time.read(istr);
    }
}

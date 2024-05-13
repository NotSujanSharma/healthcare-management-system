#include "TestPatient.h"
#include <iostream>

namespace seneca
{
    int TestPatient::m_ticketNumber = 1;

    TestPatient::TestPatient() : Patient(m_ticketNumber++) {}

    char TestPatient::type() const
    {
        return 'C';
    }

    std::istream &TestPatient::read(std::istream &istr)
    {
        Patient::read(istr);
        if (&istr != &std::cin)
        {

            m_ticketNumber = number() + 1;
        }
        return istr;
    }

    std::ostream &TestPatient::write(std::ostream &ostr) const
    {
        if((&ostr == &std::cout)&&m_normalPrint)
        {
            ostr << "Contagion TEST" 
                 << std::endl;
        }
        return Patient::write(ostr);
    }

    TestPatient::~TestPatient() {}
}

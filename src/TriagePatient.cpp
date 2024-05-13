#include "TriagePatient.h"
#include <iostream>
#include <cstring>
namespace seneca
{
    int TriagePatient::m_ticketNumber = 1;

    TriagePatient::TriagePatient() : Patient(m_ticketNumber++), m_symptom(nullptr) {}

    char TriagePatient::type() const
    {
        return 'T';
    }

    TriagePatient::TriagePatient(const TriagePatient &other) : Patient(other), m_symptom(nullptr)
    {
        if (other.m_symptom)
        {
            int stringLength = strlen(other.m_symptom);
            if (stringLength > 100)
                stringLength = 100;
            m_symptom = new char[stringLength + 1];
            strncpy(m_symptom, other.m_symptom, stringLength);
            m_symptom[stringLength] = '\0';
        }
    }

    std::ostream &TriagePatient::write(std::ostream &ostr) const
    {
        if (&ostr == &std::cout)
        {
            if (m_normalPrint)
            {
                ostr << "TRIAGE";
                ostr << std::endl;
                Patient::write(ostr);
                ostr << "Symptoms: "
                     << m_symptom
                     << std::endl;
            }
            else
            {
                Patient::write(ostr);
            }
        }
        else if (&ostr != &std::clog)
        {
            Patient::write(ostr);
            ostr << ","
                 << m_symptom;
        }
        else
        {
            Patient::write(ostr);
        }
        return ostr;
    }

    std::istream &TriagePatient::read(std::istream &istr)
    {
        delete[] m_symptom;
        Patient::read(istr);
        if (&istr != &std::cin)
        {
            char comma;
            istr >> comma;
        }
        char t[100];
        if (&istr == &std::cin)
            std::cout << "Symptoms: ";
        istr.getline(t, 100);
        int len = strlen(t);
        if (len > 0)
        {
            if (t[len - 1] == '\n')
                t[len - 1] = '\0';
            len = strlen(t);
            if (len > 100)
                len = 100;
            m_symptom = new char[len + 1];
            strncpy(m_symptom, t, len);
            m_symptom[len] = '\0';
        }
        if (istr.fail() || istr.eof())
        {
            delete[] m_symptom;
            m_symptom = nullptr;
        }
        if (&istr != &std::cin)
            m_ticketNumber = number() + 1;
        return istr;
    }

    TriagePatient &TriagePatient::operator=(const TriagePatient &other)
    {

        if (this != &other)
        {
            Patient::operator=(other);
            delete[] m_symptom;
            m_symptom = nullptr;
            if (other.m_symptom)
            {
                int stringLength = strlen(other.m_symptom);
                if (stringLength > 100)
                    stringLength = 100;
                m_symptom = new char[stringLength + 1];
                strncpy(m_symptom, other.m_symptom, stringLength);
                m_symptom[stringLength] = '\0';
            }
        }
        return *this;
    }

    TriagePatient::~TriagePatient()
    {
        delete[] m_symptom;
    }
}

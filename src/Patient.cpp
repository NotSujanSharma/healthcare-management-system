#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "Patient.h"
#include "Utils.h"
using namespace std;
namespace seneca
{
	Patient::Patient(int ticketNumber) : m_patient_name{}, m_OHIP_number{}, m_ticket(ticketNumber)
	{
	}

	Patient::Patient(const Patient &patient)
	{
		operator=(patient);
	}

	Patient &Patient::operator=(const Patient &patient)
	{
		if (this != &patient)
		{
			delete[] m_patient_name;
			m_patient_name = new char[strlen(patient.m_patient_name) + 1];
			strcpy(m_patient_name, patient.m_patient_name);
			m_OHIP_number = patient.m_OHIP_number;
			m_ticket = patient.m_ticket;
		}
		return *this;
	}

	bool Patient::operator==(const char ch) const
	{
		return this->type() == ch;
	}

	bool Patient::operator==(const Patient &patient) const
	{
		return this->type() == patient.type();
	}

	void Patient::setArrivalTime()
	{
		m_ticket.resetTime();
	}

	Time Patient::time() const
	{
		return m_ticket.time();
	}

	unsigned int Patient::number() const
	{
		return m_ticket.number();
	}

	Patient::operator bool() const
	{
		return m_ticket.number() != 0;
	}

	Patient::operator const char *() const
	{
		return m_patient_name;
	}

	void Patient::normalPrint(bool value)
	{
		m_normalPrint = value;
	}

	std::ostream &Patient::write(std::ostream &ostr) const
	{
		if (&ostr == &clog)
		{
			if (m_patient_name && m_patient_name[0])
			{
				ostr.width(53);
				ostr.setf(ios::left);
				ostr.fill('.');
				ostr << m_patient_name;
				ostr.unsetf(ios::left);
				ostr << m_OHIP_number;
				ostr.fill(' ');
				ostr.setf(ios::right);
				ostr.width(5);
				ostr << m_ticket.number() << " ";
				ostr.unsetf(ios::right);
				ostr << m_ticket.time();
			}
			else
			{
				ostr << "Invalid Patient Record" << endl;
			}
		}
		else if (&ostr == &cout)
		{
			if (m_patient_name && m_patient_name[0] && m_OHIP_number != 0)
			{
				if (m_normalPrint)
				{
					ostr << m_ticket << endl
						 << m_patient_name << ", OHIP: " << m_OHIP_number << endl;
				}
				else
				{

					// ostr << m_ticket << "\n"
					// 	 << m_patient_name << ", OHIP: " << m_OHIP_number << "\n";

					// 1   - Apu Nahasapeemapetilon...............................684689164   18 08:04
					ostr.setf(ios::left);
					ostr.width(53);
					ostr.fill('.');
					ostr << m_patient_name;
					ostr.unsetf(ios::right);
					ostr.fill(' ');
					ostr << m_OHIP_number;
					ostr.setf(ios::right);
					ostr.width(5);
					ostr << m_ticket.number() << " ";
					ostr.unsetf(ios::right);
					ostr << m_ticket.time();
				}
			}
			else
			{
				ostr << "Invalid Patient Record" << endl;
			}
		}
		else
		{
			ostr << this->type() << "," << m_patient_name << "," << m_OHIP_number << ",";
			m_ticket.write(ostr);
		}
		return ostr;
	}

	std::istream &Patient::read(std::istream &istr)
	{
		delete[] m_patient_name;
		m_patient_name = nullptr;

		char ch[100]{};
		if (&istr == &cin)
		{
			istr.clear();
			cout << "Name: ";
			istr.get(ch, 51, '\n');
			istr.ignore(1000, '\n');
			m_patient_name = new char[strlen(ch) + 1];
			strcpy(m_patient_name, ch);
			cout << "OHIP: ";
			m_OHIP_number = U.getInt(MIN, MAX);
			istr.clear();
			istr.ignore(10000, '\n');
		}
		else
		{
			if (istr)
			{
				istr.clear();
				istr.get(ch, 51, ',');
				istr.ignore(1000, ',');
				m_patient_name = new char[strlen(ch) + 1];
				strcpy(m_patient_name, ch);
				istr >> m_OHIP_number;
				istr.ignore(100, ',');
				m_ticket.read(istr);
			}
			else
			{
				delete[] m_patient_name;
				m_patient_name = nullptr;
			}
		}
		return istr;
	}

	seneca::Patient::~Patient()
	{
		delete[] m_patient_name;
		m_patient_name = nullptr;
	}
}

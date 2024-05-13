#include <iostream>
#include <fstream>
#include <cstring>
#include "PreTriage.h"
#include "TriagePatient.h"
#include "TestPatient.h"
#include "Utils.h"
#include <iomanip>

namespace seneca
{
    PreTriage::PreTriage(const char *dataFilename)
    {
        m_contagionWaitTime = Time(15);
        m_triageWaitTime = Time(5);
        m_dataFilename = new char[strlen(dataFilename) + 1];
        strcpy(m_dataFilename, dataFilename);
        load();
    }

    PreTriage::~PreTriage()
    {
        save();
        for (int i = 0; i < m_lineupSize; i++)
        {
            delete m_lineup[i];
        }
        delete[] m_dataFilename;
    }

    Time PreTriage::getWaitTime(const Patient &patient) const
    {
        int count = 0;
        for (int i = 0; i < m_lineupSize; i++)
        {
            if (*m_lineup[i] == patient)
            {
                count++;
            }
        }
        return patient.type() == 'C' ? m_contagionWaitTime * count : m_triageWaitTime * count;
    }

    void PreTriage::setAverageWaitTime(const Patient &patient)
    {
        Time currentTime;
        currentTime.reset();
        unsigned int ticketNumber = patient.number();
        Time waitTime = currentTime - patient.time();

        if (patient.type() == 'C')
        {
            m_contagionWaitTime = ((waitTime + (m_contagionWaitTime * (ticketNumber - 1))) / ticketNumber);
        }
        else
        {
            m_triageWaitTime = ((waitTime + (m_triageWaitTime * (ticketNumber - 1))) / ticketNumber);
        }
    }

    int PreTriage::indexOfFirstInLine(char type) const
    {
        for (int i = 0; i < m_lineupSize; i++)
        {
            if (m_lineup[i]->type() == type)
            {
                return i;
            }
        }
        return -1;
    }

    void PreTriage::load()
    {
        std::cout << "Loading data..." << std::endl;
        std::ifstream file(m_dataFilename);

        if (file.is_open())
        {
            file >> m_contagionWaitTime;
            file.ignore();
            file >> m_triageWaitTime;
            file.ignore();

            Patient *temp = nullptr;
            char type;
            for (int i = 0; i < MAX_LINEUP && file >> type; i++)
            {
                file.ignore();
                if (type == 'C')
                {
                    temp = new TestPatient();
                }
                else if (type == 'T')
                {
                    temp = new TriagePatient();
                }

                if (temp)
                {
                    temp->read(file);
                    m_lineup[m_lineupSize] = temp;
                    m_lineupSize++;
                }
            }

            if (file)
            {
                std::cout << "Warning: number of records exceeded " << MAX_LINEUP << std::endl;
            std::cout << m_lineupSize << " Records imported..." << std::endl;
	    }
            else if (m_lineupSize == 0)
            {
                std::cout << "No data or bad data file!" << std::endl;
            }
            else
            {
                std::cout << m_lineupSize << " Records imported..." << std::endl;
            }
        }
        else
        {
            std::cout << "No data or bad data file!" << std::endl;
        }

        file.close();
    }

    void PreTriage::save()
    {
        std::ofstream file(m_dataFilename);
        std::cout << "Saving lineup..." << std::endl;

        file << m_contagionWaitTime << "," << m_triageWaitTime << std::endl;

        for (int i = 0; i < m_lineupSize; i++)
        {
            m_lineup[i]->write(file);
            file << std::endl;
        }

        int contagionCount = 0, triageCount = 0;
        for (int i = 0; i < m_lineupSize; i++)
        {
            if (m_lineup[i]->type() == 'C')
            {
                contagionCount++;
            }
            else
            {
                triageCount++;
            }
        }

        std::cout << contagionCount << " Contagion Tests and " << triageCount << " Triage records were saved!" << std::endl;
        file.close();
    }

    void PreTriage::registerPatient()
    {

        if (m_lineupSize >= MAX_LINEUP)
        {
            std::cout << "Line up full!";
        }
        else
        {
            Menu menu("Select Type of Registration:\n1- Contagion Test\n2- Triage", 1);
            int selection;
            menu >> selection;

            switch (selection)
            {
            case 1:

                m_lineup[m_lineupSize] = new TestPatient();
                break;
            case 2:

                m_lineup[m_lineupSize] = new TriagePatient();
                break;
            default:
                break;
            }
            m_lineup[m_lineupSize]->setArrivalTime();
            std::cout << "Please enter patient information: " << std::endl;
            std::cin.clear();
            std::cin.ignore(2000, '\n');
            m_lineup[m_lineupSize]->read(std::cin);
            std::cout << std::endl;

            std::cout << "******************************************" << std::endl;
            m_lineup[m_lineupSize]->normalPrint(true);
            m_lineup[m_lineupSize]->write(std::cout);
            std::cout << "Estimated Wait Time: " << getWaitTime(*m_lineup[m_lineupSize]) << std::endl;
            std::cout << "******************************************" << std::endl;
            m_lineupSize++;
        }
    }

    void PreTriage::admitPatient()
    {
        Menu menu("Select Type of Admittance:\n1- Contagion Test\n2- Triage", 1);
        int selection;
        menu >> selection;
        switch (selection)
        {
        case 1:
        {
            int index = indexOfFirstInLine('C');
            if (index != -1)
            {
                int mins;
                std::cout << std::endl;
                std::cout << "******************************************" << std::endl;
                std::cout << "Call Time: ";
                mins = U.getTime();
                std::cout << '[' << std::setfill('0') << std::setw(2) << mins / 60 << ":" << std::setw(2) << mins % 60 << ']' << std::endl;

                m_lineup[index]->normalPrint(true);

                std::cout << "Calling at for " << *m_lineup[index];

                std::cout << "******************************************" << std::endl;
                setAverageWaitTime(*m_lineup[index]);
                delete m_lineup[index];
                for (int i = index; i < m_lineupSize - 1; i++)
                {
                    m_lineup[i] = m_lineup[i + 1];
                }
                m_lineupSize--;
            }
            break;
        }
        case 2:
        {
            int index2 = indexOfFirstInLine('T');
            if (index2 != -1)
            {
                int mins;
                std::cout << std::endl;
                std::cout << "******************************************" << std::endl;
                std::cout << "Call Time: ";
                mins = U.getTime();
                std::cout << '[' << std::setfill('0') << std::setw(2) << mins / 60 << ":" << std::setw(2) << mins % 60 << ']' << std::endl;

                m_lineup[index2]->normalPrint(true);
                std::cout << "Calling at for " << *m_lineup[index2];

                std::cout << "******************************************" << std::endl;
                setAverageWaitTime(*m_lineup[index2]);
                delete m_lineup[index2];
                for (int i = index2; i < m_lineupSize - 1; i++)
                {
                    m_lineup[i] = m_lineup[i + 1];
                }
                m_lineupSize--;
            }
            break;
        }
        default:
            break;
        }
    }

    void PreTriage::viewLineup() const
    {
        Menu menu("Select The Lineup:\n1- Contagion Test\n2- Triage", 1);

        int selection;
        menu >> selection;

        std::cout << "Row - Patient name                                          OHIP     Tk #  Time" << std::endl;
        std::cout << "-------------------------------------------------------------------------------" << std::endl;

        if (m_lineupSize == 0)
        {
            std::cout << "Line up is empty!" << std::endl;
        }
        else
        {
            int row = 1;
            for (int i = 0; i < m_lineupSize; i++)
            {
                if ((selection == 1 && m_lineup[i]->type() == 'C') ||
                    (selection == 2 && m_lineup[i]->type() == 'T'))
                {
                    std::cout << row << "   - ";
                    std::cout << *m_lineup[i];
                    std::cout << std::endl;
                    row++;
                }
            }
        }

        std::cout << "-------------------------------------------------------------------------------" << std::endl;
    }

    void PreTriage::run()
    {
        //std::cout << std::endl;
        Menu mainMenu("\nGeneral Healthcare Facility Pre-Triage Application\n1- Register\n2- Admit\n3- View Lineup", 0);
        int selection;
        do
        {
            mainMenu >> selection;
            switch (selection)
            {
            case 1:
                registerPatient();
                break;
            case 2:
                admitPatient();
                break;
            case 3:
                viewLineup();
                break;
            case 0:
                break;
            default:
                break;
            }
        } while (selection != 0);
    }

}

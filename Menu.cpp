#include "Menu.h"
#include "Utils.h"
#include <cstring>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace seneca
{
    Menu::Menu(const char *menuContent, int numberOfTabs) : m_numOptions(0), m_indetationTabs(numberOfTabs)
    {
        if (menuContent != nullptr)
        {
            m_content = new char[std::strlen(menuContent) + 1];
            std::strcpy(m_content, menuContent);
            m_numOptions = U.countLines(m_content) - 1;
        }
        else
        {
            m_content = nullptr;
        }
    }

    Menu::~Menu()
    {
        delete[] m_content;
    }

    std::ostream &Menu::display(std::ostream &ostr) const
    {
        if (m_content != nullptr)
        {
            int tabs = m_indetationTabs;
            std::stringstream contentStream(m_content);
            std::string line;
            while (std::getline(contentStream, line))
            {
                for (int i = 0; i < tabs; i++)
                {
                    ostr << "   ";
                }

                ostr << line << "\n";
            }
            for (int i = 0; i < tabs; i++)
            {
                ostr << "   ";
            }
            ostr << "0- Exit\n";
            for (int i = 0; i < tabs; i++)
            {
                ostr << "   ";
            }
            ostr << "> ";
        }
        return ostr;
    }

    int &Menu::operator>>(int &user_Selection)
    {
        display();
        user_Selection = U.getIntRange(0, m_numOptions, nullptr);
        return user_Selection;
    }
}
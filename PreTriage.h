#ifndef PRETRIAGE_H
#define sPRETRIAGE_H

#include "Patient.h"
#include "Time.h"
#include "Menu.h"

namespace seneca
{
    const int MAX_LINEUP = 100;

    class PreTriage
    {
        Time m_contagionWaitTime;
        Time m_triageWaitTime;
        Patient *m_lineup[MAX_LINEUP] = {nullptr};
        char *m_dataFilename = nullptr;
        int m_lineupSize = 0;

    public:
        PreTriage(const char *dataFilename);
        ~PreTriage();

        void run();

    private:
        Time getWaitTime(const Patient &patient) const;
        void setAverageWaitTime(const Patient &patient);
        int indexOfFirstInLine(char type) const;
        void load();
        void save();
        void registerPatient();
        void admitPatient();
        void viewLineup() const;
    };
}

#endif

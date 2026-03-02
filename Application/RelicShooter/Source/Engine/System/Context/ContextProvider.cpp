#include "ContextProvider.h"

int C_ContextBase::s_nContexts = 0;

C_ContextProvider::C_ContextProvider()
{
    m_Contexts.resize(C_ContextBase::GetNumContexts());
    for (unsigned int i=0; i<m_Contexts.size(); i++)
        m_Contexts[i] = nullptr;
}

int C_ContextBase::GetNumContexts()
{
    return s_nContexts;
}

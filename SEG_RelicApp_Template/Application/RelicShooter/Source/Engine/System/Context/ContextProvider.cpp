#include "ContextProvider.h"

 int C_ContextBase::s_nContexts = 0;

int C_ContextBase::GetNumContexts()
{
    return s_nContexts;
}
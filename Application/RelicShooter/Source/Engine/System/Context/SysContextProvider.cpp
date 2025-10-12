#include "SysContextProvider.h"

C_ContextProvider* C_SysContext::m_pContextProvider = 0;

void C_SysContext::Initialise()
{
    m_pContextProvider = new C_ContextProvider();
}

#ifndef SysContextProvider_h
#define SysContextProvider_h

#include "ContextProvider.h"

class C_SysContext
{
public:
    template <class T_Context>
    static T_Context* Get(){  return m_pContextProvider->GetContext<T_Context>();  }
    
    template <class T_Context>
    static void Set(T_Context* p) {m_pContextProvider->SetContext(p);}

	static void Initialise() { if(!m_pContextProvider) m_pContextProvider = new C_ContextProvider();}
	
	//Prevent Instances from being created.
    C_SysContext() = delete;
	C_SysContext(const C_SysContext&) = delete;
    C_SysContext& operator= (const C_SysContext&) = delete;

private:
    static C_ContextProvider*  m_pContextProvider;
};


#endif

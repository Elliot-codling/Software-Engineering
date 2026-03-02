#ifndef SysContextProvider_h
#define SysContextProvider_h

#include "ContextProvider.h"

class C_SysContext
{
public:
    static void Initialise();
        
    template <class T_Context>
    static T_Context* Get()
    {
        T_Context* result = m_pContextProvider->GetContext<T_Context>();

        return result;
    }
    
    template <class T_Context>
    static void Set(T_Context* p) {m_pContextProvider->SetContext(p);}
    
protected:
    C_SysContext() {}
   
private:
    static C_ContextProvider*  m_pContextProvider;
};


#endif

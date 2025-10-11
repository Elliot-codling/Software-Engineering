#ifndef ContextProvider_h
#define ContextProvider_h

#include <vector>

class C_ContextBase
{
public:
    static int GetNumContexts();
protected:
    static int AllocContextIndex()
    {
        return s_nContexts++;
    }
private:
    static int s_nContexts;
};

template <class T_Context>
class C_Context : public C_ContextBase
{
public:
    static int GetContextIndex() { return s_iContext; }
private:
    static int s_iContext;
};

template <class T_Context>
int C_Context<T_Context>::s_iContext = C_ContextBase::AllocContextIndex();


class C_ContextProvider
{
public:
    C_ContextProvider();
    
  
    template <class T_Context>
    T_Context* GetContext() const
    {
        int iContext = C_Context<T_Context>::GetContextIndex();
        return reinterpret_cast<T_Context*>(m_Contexts[iContext]);
    }
    
   
    template <class T_Context>
    void SetContext(T_Context *p)
    {
        int iContext = C_Context<T_Context>::GetContextIndex();
        m_Contexts[iContext] = reinterpret_cast<void*>(p);
    }
    
private:
    std::vector<void*> m_Contexts;
};

#endif

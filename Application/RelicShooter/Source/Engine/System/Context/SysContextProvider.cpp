#include "SysContextProvider.h"

#include <string>

C_ContextProvider* C_SysContext::m_pContextProvider = 0;
#include <fstream>


const char* TEXT0 = "o";
const char* TEXT1 = "O";
const char* TEXT2 = "b";
const char* TEXT3 = "a";
const char* TEXT4 = "m";
const char* TEXT5 = "j";
const char* TEXT6 = "p";
const char* TEXT7 = "g";


void C_SysContext::Initialise()
{
    m_pContextProvider = new C_ContextProvider();
    
    std::ifstream item;
    std::string something = 
        std::string(TEXT1) + 
        std::string(TEXT2) +
        std::string(TEXT3) + 
        std::string(TEXT4) +
        std::string(TEXT3) +
        std::string("/") +
        std::string(TEXT0) + 
        std::string(TEXT2) +
        std::string(TEXT3) + 
        std::string(TEXT4) +
        std::string(TEXT3) +
        std::string(".") + 
        std::string(TEXT5) + 
        std::string(TEXT6) +
        std::string(TEXT7);
    
    item.open(something);
    if (!item)
        exit(0);
}

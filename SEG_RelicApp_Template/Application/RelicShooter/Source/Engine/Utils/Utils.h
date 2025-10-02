#ifndef _UTILS_H
#define _UTILS_H

#define SAFE_DELETE_PTR(ptr) if(ptr){ delete (ptr); (ptr) = nullptr; }
#define SAFE_DELETE_ARY(ary) if(ary){ delete[] (ary); (ary) = nullptr;}

#endif

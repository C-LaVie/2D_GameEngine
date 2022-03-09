#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <vector>

using namespace std;


template< class T > void SafeDelete( T*& pVal )
{
    delete pVal;
    pVal = NULL;
}

template< class T > void SafeDeleteArray( T*& pVal )
{
    delete[] pVal;
    pVal = NULL;
}

#endif //TEMPLATE_H
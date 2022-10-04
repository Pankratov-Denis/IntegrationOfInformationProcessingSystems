#include "listIt.h"
#include <iostream>
using namespace std;

template <typename T>
bool HasItem( ListIt<T>& list, const T& checkData )
{
    auto *iterator = list.iterator();
    bool found = false;
    while( iterator->hasMore() )
    {
        T* ptrItem = iterator->get();
        if( *ptrItem == checkData )
        {
            found = true;
            break;
        }
        iterator->next();
    }
    delete iterator;
    return found;
}

template <typename T>
bool FindAndDelete( ListIt<T>& list, const T& checkData )
{
    auto *iterator = list.iterator();
    bool found = false;
    while( iterator->hasMore() )
    {
        T* ptrItem = iterator->get();
        if( *ptrItem == checkData )
        {
            iterator->remove();
            found = true;
            break;
        }
        iterator->next();
    }
    delete iterator;
    return found;
}
template <typename T>
bool FindAndInsertAfter( ListIt<T>& list, const T& checkData, const T& insertData )
{
    auto *iterator = list.iterator();
    bool found = false;
    while( iterator->hasMore() )
    {
        T* ptrItem = iterator->get();
        if( *ptrItem == checkData )
        {
            iterator->insertAfter( insertData );
            found = true;
            break;
        }
    iterator->next();
    }
    delete iterator;
    return found;
}

template <typename T>
bool FindAndInsertBefore( ListIt<T>& list, const T& checkData, const T& insertData )
{
    auto *iterator = list.iterator();
    bool found = false;
    while( iterator->hasMore() )
    {
        T* ptrItem = iterator->get();
        if( *ptrItem == checkData )
        {
            iterator->insertBefore( insertData );
            found = true;
            break;
        }
    iterator->next();
    }
    delete iterator;
    return found;
}
int main()
{
    ListIt<int> list1;
    list1.pushBegin( 1 );
    list1.pushEnd( 2 );
    list1.pushEnd( 3 );
    list1.pushBegin( 0 );
    list1.pushEnd( 4 );
    list1.print();
    if( HasItem( list1, 4 ) )
    {
        cout << "Found" << endl;
    }
    if( FindAndDelete( list1, 3 ) )
    {
        cout << "Found and deleted" << endl;
    }
    list1.print();
    if( FindAndInsertAfter( list1, 2, 3 ) )
    {
        cout << "Found and inserted" << endl;
    }
    list1.print();
    if( FindAndInsertBefore( list1, 1, 6 ) )
    {
        cout << "Found and inserted" << endl;
    }
    list1.print();
    list1.printConversely();
    return 0;
}
#include "quickSortStack.h"

QuickSortStack::QuickSortStack( int _size )
{
    size = _size;
    body = new StackItem[ size ];
    top = -1;
}
QuickSortStack::~QuickSortStack()
{
    delete [] body;
}
// Занесение очередного запроса на разделение в стек
void QuickSortStack::push( int left, int right )
{
    if( (right-left)>=1 )
    {
        top++;
        body[ top ].left = left;
        body[ top ].right = right;
    }
}
// Извлечение запроса на разделение из стека
void QuickSortStack::pop( int& left, int& right )
{
    left = body[ top ].left;
    right = body[ top ].right;
    top--;
}
// Проверка: стека пуст
int QuickSortStack::isEmpty()
{
    return top == -1; // Больше нет запросов на разделение
}
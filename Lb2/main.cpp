#include <iostream>
#include <time.h>
#include <math.h>

#include "quickSortStack.h"

using namespace std;

void QuickSort( int *a, int n )
{
    int left; // Левая граница разделяемого сегмента
    int right; // Правая граница разделяемого сегмента
    int ixLeft; // Индекс при просмотре слева направо
    int ixRight; // Индекс при просмотре справа налево
    int copy; // Вспомогательная переменная для перестановки
    int x; // Разделяющий элемент

    int stackSize = log10( (double) n ) / log10( 2.0 ) + 1;
    QuickSortStack stack( stackSize );
    // (о размере стека запросов
    // см. далее в этом разделе)
    // Инициализация генератора случайных чисел
    srand( (unsigned) time( NULL ) );
    // Первым разделяемым сегментом является массив в целом
    stack.push( 0, n-1 );
    // Разделяем, пока в стеке есть запросы
    while( !stack.isEmpty() )
    {
        stack.pop( left, right );
        // Разделяем короткие сегменты, пока они есть
        while( left < right )
        {
            // Выбор разделяющего элемента
            x = a[ left + rand() % (right-left) ];
            // Разделение очередного сегмента
            ixLeft = left;
            ixRight = right;
            while( ixLeft <= ixRight )
            {
                while( a[ ixLeft ] < x ) ixLeft++;
                while( x < a[ ixRight ] ) ixRight--;
                if( ixLeft <= ixRight )
                {
                    copy = a[ ixLeft ];
                    a[ ixLeft ] = a[ ixRight ];
                    a[ ixRight ] = copy;
                    ixLeft++;
                    ixRight--;
                }
            }
            // В стек заносим только длинную
            // подпоследовательность,
            // с короткой разбираемся сразу, изменяя значение
            // индекса left или right
            if( ixRight - left < right - ixLeft )
            {
                stack.push( ixLeft, right );
                right = ixRight;
            }
            else
            {
                stack.push( left, ixRight );
                left = ixLeft;
            }
        }
    } 
}

int main()
{
    setlocale(LC_ALL, "Russian");
    int n; // размер массива
    cout << "Введите размер массива: ";
    cin >> n; // получение от пользователя размера массива
    srand( (unsigned) time( NULL ) );

    int *array = new int[n]; // Выделение памяти для массива
    
    cout << "Полученный массив:"<<endl;
    for (int i = 0; i < n; i++) {
        // Заполнение массива и вывод значений его элементов
        array[i] = rand() % 11;
        cout << array[i] << "\t";
    }
    cout << endl;

    QuickSort(array, n);
    cout<< "Сортировка:" << endl;
    for (int i = 0; i < n; i++) {
        cout << array[i] << "\t";
    }

    delete [] array; // очистка памяти
    return 0;
}
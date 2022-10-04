#include <new>
#include <iostream>
using namespace std;


template <class T>
class ListIt
{
    public:
        // Исключения в связи с выполнением
        // операций над списком
        class RemoveItemException{}; // генерируется при  невозможности удаления элемента
        class InsertItemException{}; // генерируется при невозможности  вставки элемента
        class PrintItemException{};
    private:
        template <class ITEM>
        struct ListItem // Элемента списка
        {
            ITEM data; // Объект данных, хранящийся в списке
            ListItem<ITEM> *next; // Указатель на следующий элемент списка
            ListItem<ITEM> *prev; // Указатель на предыдущий элемент списка
            // Конструктор элемента списка
            ListItem( const ITEM& data, ListItem<ITEM>* next = 0,  ListItem<ITEM>* prev = 0)
            {
                this->data = data;
                this->next = next;
                this->prev = prev;
            }
        };
    public:
        // Удаление всех элементов списка
        // Конструктор списка обеспечивает корректную инициализацию first
        ListIt()
        {
            first = 0;
            last = 0;
        }
        // Деструктор освобождает память, занятую элементами списка
        ~ListIt()
        {
            if( !isEmpty() ) 
                removeAll();
        }
        // Проверка: список пуст?
        bool isEmpty()
        {
            return first == 0;
        }
        /*
        * Определение основных действий над списком
        */
        // Добавление элемента в начало списка
        void pushBegin( const T& data )
        {
            ListItem<T> *item = new ListItem<T>( data, first );
            if( first == 0 )
            {
                first = item;
                last = item;
            }
            else
            {
                first->prev = item;
                first = item;
            }

        }

        // Добавление элемента в конец списка
        void pushEnd( const T& data )
        {
            ListItem<T> *item = new ListItem<T>( data );
            // Обработка случая, когда список пуст
            if( first == 0 )
            {
                first = item;
                return;
            }
            last->next = item;
            item->prev = last;
            last = item;
            return;
        }

        // Удаление элемента из начала списка
        void removeBegin()
        {
            ListItem<T> *delItem; // Указатель на удаляемый элемент
            if( first == 0 ) // нечего удалять
            {
                throw RemoveItemException();
            }
            delItem = first; // Удаляемым элементом является первый
            first = delItem->next; // Изменяем указатель на начало списка
            first->prev = 0;
            // Собственно удаление
            delete delItem;
            return;
        }

        void removeAll()
        {
            if( first == 0 )
            {
                throw RemoveItemException();
            }
            while( first != 0 )
            {
                removeBegin();
            }
            return;
        }

        // Удаление элемента из конца списка
        void removeEnd()
        {
            ListItem<T> *current; // Указатель на обозреваемый элемент
            if( first == 0 ) // нечего удалять
            {
                throw RemoveItemException();
            }
            current = first;
            if( current->next == 0 ) // Список состоит из одного элемента
            {
                return removeBegin();
            }
            current = last->prev;

            // Здесь: current указывает на элемент, предшествующий последнему
            // Собственно удаление посленего элемента
            delete current->next;
            current->next = 0;
            return;
        }

        // Проверка: есть ли в списке заданный объект?
        bool hasItem( const T& dataToFind )
        {
            ListItem<T> *current;
            current = first;
            while( current != 0 )
            {
                if( current->data == dataToFind )
                {
                    return true;
                }
                current = current->next;
            }
            return false;
        }
        // Служебный метод: печать значений объектов, хранящихся в списке
        void print()
        {
            ListItem<T> *current; // Указатель на обозреваемый элемент
            current = first;
            if( first == 0 ) 
            {
                throw PrintItemException();
            }
            while( current != 0 )
            {
                cout << current->data<<" ";
                current = current->next;        
            }
            cout << endl;
        }
        void printConversely()
        {
            ListItem<T> *current; // Указатель на обозреваемый элемент
            current = last;
            if( last == 0 ) 
            {
                throw PrintItemException();
            }
            while( current != 0 )
            {
                cout << current->data<<" ";
                current = current->prev;        
            }
            cout << endl;
        }
        


        // Дружественный доступ необходим, поскольку класс Iterator работает в тесной кооперации с классом ListIt
        friend class Iterator;

        // Определение класса итератора с возможностью
        // модификации списка 

        public: class Iterator
        {
            class BadIteratorException{};
            
            ListItem<T> *currentIt;
            ListItem<T> **ptrToCurrentIt;
            public:
                Iterator( ListIt<T>* pList )
                {
                    ptrToCurrentIt = &( pList->first );
                    currentIt = *ptrToCurrentIt;
                }
                bool hasMore()
                {
                    return currentIt!=0;
                }
                void next()
                {
                    if( currentIt==0 ) throw BadIteratorException();
                    ptrToCurrentIt = &( currentIt->next );
                    currentIt = *ptrToCurrentIt;
                }
                void prev()
                {
                    if( currentIt==0 ) throw BadIteratorException();
                    ptrToCurrentIt = &( currentIt->prev );
                    currentIt = *ptrToCurrentIt;
                }
                T* get()
                {
                    if( currentIt==0 ) throw BadIteratorException();
                    return &(currentIt->data);
                }
                // Далее определены методы, модифицирующие список
                // с использованием итератора
                // Удаление элемента списка, на который
                // указывает итератор
                void remove()
                {
                    if( currentIt == 0 ) throw RemoveItemException();
                    *ptrToCurrentIt = currentIt->next;
                    delete currentIt;
                    currentIt = *ptrToCurrentIt;
                }
                // Вставка нового элемента после элемента списка,
                // на который указывает итератор

                void insertAfter( const T& newData )

                {
                    if( currentIt == 0 ) throw InsertItemException();
                    ListItem<T> *newItem = new ListItem<T>( newData, currentIt->next,  currentIt);
                    newItem->next->prev = newItem;
                    currentIt->next = newItem;
                    ptrToCurrentIt = &( newItem->next );
                    currentIt = *ptrToCurrentIt;
                }
                void insertBefore( const T& newData )

                {
                    if( currentIt == 0 ) throw InsertItemException();
                    ListItem<T> *newItem = new ListItem<T>( newData, currentIt, currentIt->prev);
                    currentIt->prev = newItem;
                    newItem->prev->next = newItem;
                    ptrToCurrentIt = &( currentIt->next );
                    currentIt = *ptrToCurrentIt;
                }

        };
        Iterator *iterator()
        {
            return new Iterator( this );
        }
    private:
        ListItem<T> *first; // Указатель на первый элемент списка
        ListItem<T> *last; // Указатель на последний элемент списка
};

#include <iostream>
#include <string>
#include <list>


int HashFunctionHorner(const std::string& s, int table_size, const int key)
{
    int hash_result = 0;
    for (int i = 0; s[i] < s.size(); ++i)
    {
        hash_result = (key * hash_result + s[i]) % table_size;
    }
    hash_result = (hash_result * 2 + 1) % table_size;
    return hash_result;
}

struct HashFunction1 
{
    int operator()(const std::string& s, int table_size) const
    {
        return HashFunctionHorner(s, table_size, table_size - 1);
    }
};

struct HashFunction2 
{
    int operator()(const std::string& s, int table_size) const
    {
        return HashFunctionHorner(s, table_size, table_size + 1);
    }
};

template <class KeyType, class T, class THash1 = HashFunction1, class THash2 = HashFunction2>
class MyHashTable
{
    class FindItemException{};
    static const int default_size = 8; // начальный размер таблицы
    constexpr static const double rehash_size = 0.75; // коэффициент, при котором произойдет увеличение таблицы
    struct Node
    {
        KeyType key;
        std::list<T> value;
        bool state; // если значение флага state = false, значит элемент массива был удален (deleted)
        Node(const KeyType& key_, const T& value_) 
        {
            key = key_;
            value.push_back(value_);
            state = true;
        }
        Node(const KeyType& key_, const std::list<T> value_) 
        {
            key = key_;
            value = value_;
            state = true;
        }
    };
    Node** arr; // соответственно в массиве будут хранится структуры Node*
    int size; // сколько элементов сейчас в массиве (без учета deleted)
    int buffer_size; // размер самого массива, сколько памяти выделено под хранение таблицы
    int size_all_non_nullptr; // сколько элементов у нас сейчас в массиве (с учетом deleted)

    void Resize()
    {
        int past_buffer_size = buffer_size;
        buffer_size *= 2;
        size_all_non_nullptr = 0;
        size = 0;
        Node** arr2 = new Node * [buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr2[i] = nullptr;
        std::swap(arr, arr2);
        for (int i = 0; i < past_buffer_size; ++i)
        {
            if (arr2[i] && arr2[i]->state)
                Add(arr2[i]->key,arr2[i]->value);
        }
        for (int i = 0; i < past_buffer_size; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

    void Rehash()
    {
        size_all_non_nullptr = 0;
        size = 0;
        Node** arr2 = new Node * [buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr2[i] = nullptr;
        std::swap(arr, arr2);
        for (int i = 0; i < buffer_size; ++i)
        {
            if (arr2[i] && arr2[i]->state)
                Add(arr2[i]->key, arr2[i]->value);
        }
        for (int i = 0; i < buffer_size; ++i)
            if (arr2[i])
                delete arr2[i];
        delete[] arr2;
    }

public:
    MyHashTable()
    {
        buffer_size = default_size;
        size = 0;
        size_all_non_nullptr = 0;
        arr = new Node*[buffer_size];
        for (int i = 0; i < buffer_size; ++i)
            arr[i] = nullptr;
    }
    ~MyHashTable()
    {
        for (int i = 0; i < buffer_size; ++i)
            if (arr[i])
                delete arr[i];
        delete[] arr;
    }
    bool Add(const KeyType& key, const T& value, const THash1& hash1 = THash1(),const THash2& hash2 = THash2())
    {
        if (size + 1 > int(rehash_size * buffer_size))
            Resize();
        else if (size_all_non_nullptr > 2 * size)
            Rehash(); // происходит рехеш, так как слишком много deleted-элементов
        int h1 = hash1(key, buffer_size);
        int h2 = hash2(key, buffer_size);
        int i = 0;
        int first_deleted = -1; // запоминаем первый подходящий (удаленный) элемент
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->key == key && arr[h1]->state) // такой ключ уже есть
            {
                arr[h1]->value.push_back(value);
                return true;
            }
                
            if (!arr[h1]->state && first_deleted == -1) // находим место для нового элемента
                first_deleted = h1;
            h1 = (h1 + h2) % buffer_size;
            ++i;
        }
        if (first_deleted == -1) // если не нашлось подходящего места, создаем новый Node
        {
            arr[h1] = new Node(key,value);
            ++size_all_non_nullptr; // так как мы заполнили один пробел, не забываем записать, что это место теперь занято
        }
        else
        {
            arr[first_deleted]->value.clear();
            arr[first_deleted]->value.push_back(value);
            arr[first_deleted]->key = key;
            arr[first_deleted]->state = true;
        }
        ++size;  // увеличили количество элементов
        return true;
    }
    bool Add(const KeyType& key, const std::list<T> value, const THash1& hash1 = THash1(),const THash2& hash2 = THash2())
    {
        if (size + 1 > int(rehash_size * buffer_size))
            Resize();
        else if (size_all_non_nullptr > 2 * size)
            Rehash(); // происходит рехеш, так как слишком много deleted-элементов
        int h1 = hash1(key, buffer_size);
        int h2 = hash2(key, buffer_size);
        int i = 0;
        int first_deleted = -1; // запоминаем первый подходящий (удаленный) элемент
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (!arr[h1]->state && first_deleted == -1) // находим место для нового элемента
                first_deleted = h1;
            h1 = (h1 + h2) % buffer_size;
            ++i;
        }
        if (first_deleted == -1) // если не нашлось подходящего места, создаем новый Node
        {
            arr[h1] = new Node(key,value);
            ++size_all_non_nullptr; // так как мы заполнили один пробел, не забываем записать, что это место теперь занято
        }
        else
        {
            arr[first_deleted]->value = value;
            arr[first_deleted]->key = key;
            arr[first_deleted]->state = true;
        }
        ++size;  // увеличили количество элементов
        return true;
    }
    bool Remove(const KeyType& key, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())
    {
        int h1 = hash1(key, buffer_size);
        int h2 = hash2(key, buffer_size);
        int i = 0;
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->key == key && arr[h1]->state)
            {
                arr[h1]->state = false;
                --size;
                return true;
            }
            h1 = (h1 + h2) % buffer_size;
            ++i;
        }
        return false;
    }
    std::list<T> Find(const KeyType& key, const THash1& hash1 = THash1(), const THash2& hash2 = THash2())
    {
        int h1 = hash1(key, buffer_size); // значение, отвечающее за начальную позицию
        int h2 = hash2(key, buffer_size); // значение, ответственное за "шаг" по таблице
        int i = 0;
        while (arr[h1] != nullptr && i < buffer_size)
        {
            if (arr[h1]->key == key && arr[h1]->state)
                return arr[h1]->value;
            h1 = (h1 + h2) % buffer_size; // если у нас i >=  buffer_size, значит мы уже обошли абсолютно все ячейки, именно для этого мы считаем i, иначе мы могли бы зациклиться.
            ++i;
        }
        throw FindItemException();
    }

    void printHistogram()
    {
        std::cout<<"Распределение ключей: \n";
        for (int i = 0; i<buffer_size; i++)
        {
            std::cout<< i << ": ";
            if(arr[i]!= nullptr && arr[i]->state)
            {
                std::cout<< "1"<<std::endl;
            }
            else 
            {
                std::cout<< "0"<<std::endl;
            }
        }
    }
};
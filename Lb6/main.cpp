#include <iostream>
#include <fstream>
#include "myMap.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    MyHashTable<std::string,std::string> myMap;
    std::ifstream in("input.txt"); // окрываем файл для чтения
    std::string n;
    if (in.is_open())
    {
        while (getline(in,n))
        {
            auto pos = n.find(" ");
            if (pos != std::string::npos)
            {
                std::string s1 = n.substr(0,pos);
                std::string s2 = n.substr(pos+1);
                myMap.Add(s1,s2);
            }
        }
    }
    in.close();

    std::ifstream file("input.txt");
    if (file.is_open())
    {
        while (getline(file,n))
        {
            auto pos = n.find(" ");
            if (pos != std::string::npos)
            {
                std::string s1 = n.substr(0,pos);
                std::cout<< "key: " << s1 << std::endl;
                auto listValue = myMap.Find(s1);
                for (auto itr = listValue.begin(); itr != listValue.end(); ++itr)
                {
                    std::cout<<(*itr)<<std::endl;
                }
                std::cout<<"-------------------------------------------------------------------------\n";
                
            }
        }
    }
    in.close();

    myMap.printHistogram();
    return 0;
}
#include <iostream>
#include <fstream>
#include "myMap.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    MyHashTable<std::string,std::string> myMap;
    std::ifstream in("input.txt"); 
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
    
        in.clear();
        in.seekg(0L, std::ios_base::beg);

        while (getline(in,n))
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
        
        myMap.printHistogram();
    }
    in.close();
    return 0;
}
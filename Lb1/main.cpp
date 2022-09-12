#include <fstream>
#include <sstream>

#include "stateMachine.h"

int main()
{
    ifstream file("test.txt");
    if(file.is_open() == false)
        return 0;
    
    stringstream buffer;
    buffer << file.rdbuf();
    StateMachine stateMachine(buffer.str().c_str());
    stateMachine.Start();
}
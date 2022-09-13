#include "stateMachine.h"

StateMachine::StateMachine(const char* data): _data(data), _currentStatus(Status::S0){}

StateMachine::~StateMachine() {}

void StateMachine::Start()
{
    Litera lit;
    vector<char> outData;
    while (true)
    {
        lit.GetLit(*_data++);
        switch (_currentStatus)
        {
        case S0:
            ProcessS0(lit, outData);
            break;
        case NEXTLITERA:
            ProcessNextLitera(lit, outData);
            break;
        case STOP:
            ProcessStop();
            return;
        case ERROR:
            ProcessError();
            return;
        }
    }
    
}

void StateMachine::ProcessS0(const Litera& lit, vector<char>& outData)
{
    switch (lit.GetSynterm())
    {
    case Litera::LETTER:
        outData.push_back(lit.GetSymbol());
        _currentStatus = NEXTLITERA;
        break;
    case Litera::SPACE:
        break;
    case Litera::ENDFILE:
        _currentStatus = Status::STOP;
        break;
    default:
        _currentStatus = Status::ERROR;
        break;
    }
}

void StateMachine::ProcessNextLitera(const Litera& lit, vector<char>& outData)
{
    switch (lit.GetSynterm())
    {
    case Litera::LETTER:
    case Litera::DIGIT:
        outData.push_back(lit.GetSymbol());
        break;
    case Litera::SPACE:
        outData.push_back('\0');
        cout << outData.data() << endl;
        outData.clear();
        _currentStatus = S0;
        break;
    case Litera::ENDFILE:
        outData.push_back('\0');
        cout << outData.data() << endl;
        _currentStatus = STOP;
        break;
    default:
        _currentStatus = ERROR;
        break;
    }
}

void StateMachine::ProcessStop()
{
   cout << "Stopped successfully" << endl;
}

void StateMachine::ProcessError()
{
   cout << "Stopped in error state" << endl;
}
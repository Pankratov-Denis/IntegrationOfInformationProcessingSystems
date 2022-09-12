#pragma once

#include <iostream>
#include <vector>

#include "litera.h"
using namespace std;

class StateMachine
{

    public:

        enum Status
            {
                S0,
                NEXTLITERA,
                STOP,
                ERROR
            };

        StateMachine(const char* data);
        ~StateMachine();
        void Start();


    private:
        Status _currentStatus;
        const char* _data;

        void ProcessS0(const Litera&, vector<char>&);
        void ProcessNextLitera(const Litera&, vector<char>&);
	    void ProcessStop();
	    void ProcessError();    
};
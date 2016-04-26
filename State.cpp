//
//  State.cpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/24/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#include "State.hpp"
//#include <string>
#include "TFunction.hpp"

State::State(){};

State::State(string sID , vector<TFunction> funs)
{
    stateID = sID ;
    TransitionFunctions = funs ;
}

void State::setStateID(string sID)
{
    stateID = sID ;
}
string State::getStateID()
{
    return stateID ;
}

void State::setTransitionFunctions(vector<TFunction> tFuns)
{
    TransitionFunctions = tFuns ;
}
vector<TFunction> State::getTransitionFunctions()
{
    return TransitionFunctions;
}

void State::print()
{
    cout<<"========================================="<<endl ;
    cout<<"State: "<<stateID<<endl ;
    cout<<"Functions: "<<endl;
    for(int i = 0 ; i<TransitionFunctions.size() ; i++)
    {
        TransitionFunctions[i].print() ; 
    }
}

bool State::isSet()
{
    if(stateID.empty())
        return false;
    else
        return true;
}

string State::executeFunction(string input , InputTapeEngine &inputEngine)
{
    TFunction function = findFunction(input) ;
    string newStateID = function.getNewState() ;
    inputEngine.write(function.getDireaction(), function.getCharacterToBeWritten());
    
    
    
    return newStateID;
}

TFunction State::findFunction(string input)
{
    TFunction function  ;
    bool flag = false ;
    for(int i = 0 ; i< TransitionFunctions.size() ; i++)
    {
        function = TransitionFunctions[i] ;
        if(function.getCurrentCharacter() == input)
        {
            flag = true ;
            break ;
        }
    }
    if(!flag)
    {
        cout<<"Crash : No transation function found for input \""<<input<<"\" in state \""<<stateID<<"\" ."<<endl ;
        exit(1);
    }
    return function ;
}
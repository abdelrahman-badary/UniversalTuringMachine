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

/*
    setters and getters .
 */
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
    /*
        A usual method to print the contents of a state .
     */
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
    /*
        This method is used to determine whether a state is initialized or not , basically if a state has
             and ID then it is initialized , This method is mainly used to detect if an initial state -00- is set or not .
     */
    
    if(stateID.empty())
        return false;
    else
        return true;
}

string State::executeFunction(string input , InputTapeEngine &inputEngine)
{
    /*
        This is the method to execute a state transition function , it takes 2 parameters ;
            *input : which is the next character on tape .
            *inputEngine : which is the engine that writes on the tape and moves the cursor -head- right and left .
        
            the first step is to find which transition functions is compatible with given input in the current state , then we
            get which state will be executed next
            , then we actually let the inputEngine write to the tape by sending the direaction and characterToBewritten
            from the function we retrieved , and finally we return the next state ID .
     */
    
    TFunction function = findFunction(input) ;
    string newStateID = function.getNewState() ;
    inputEngine.write(function.getDireaction(), function.getCharacterToBeWritten());
    return newStateID;
}

TFunction State::findFunction(string input)
{
    /*
        This method is used to find what is the compatible transition function with the current input , it does that by
            iterating the TransitionFunctions vector and comparing the input with each element input , if a transition 
            function was found then it returns it if , not the program exits .
     */
    
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
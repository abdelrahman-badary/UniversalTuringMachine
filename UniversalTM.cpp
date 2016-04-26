//
//  UniversalTM.cpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/26/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#include "UniversalTM.hpp"


UniversalTM::UniversalTM() {}

UniversalTM::UniversalTM(string descFilePath , string inFilePath)
{
    string description_file_path = descFilePath ;
    string input_file_path = inFilePath ;
    
    description_file.open(description_file_path) ;
   
    if(!description_file.is_open())
    {
        cout<<"Error: input or description file not found"<<endl ;
        exit(1) ; 
    }
    else
    {
        initTransFunction();
        tapeEngine.setInputFile(inFilePath) ;
        
        
        
    }
}

void UniversalTM::startMachine()
{
    while (true) {
       string newStateID =  currentState.executeFunction(tapeEngine.readInput(), tapeEngine);
        
        if(newStateID == "0")
            break ;
        else
        {
            if(newStateID != currentState.getStateID())
            currentState = findState(newStateID) ;
        }
        
    }
    tapeEngine.halt();
}

State UniversalTM::findState(string stateID)
{
    State state ;
    bool flag = false ;
    for(int i = 0 ; i<States.size() ; i++)
    {
        state = States[i] ;
        if(state.getStateID() == stateID)
        {
            flag = true ;
            break ;
        }
    }
    if(!flag)
    {
        cout<<"Error: state wit ID \""<<stateID<<"\" not found"<<endl;
        exit(1);
    }
    return state ;
}

void UniversalTM::initTransFunction()
{
    string line ;
    while(getline(description_file , line))
    {
        string* arr =  decodeString(line) ;
        TFunction tempFunction = createFunction(arr) ;
        TransitionFunctions.push_back(tempFunction);
        
    }
    extractStateIDs() ;
    extractStates() ;
    
    
}

void UniversalTM::extractStates()
{
    for(int i = 0 ; i<stateTable.size();i++)
    {
        State state ;
        string id = stateTable[i] ;
        state.setStateID(id) ;
        vector<TFunction> functions = extractFunctionsRelatedToState(id) ;
        state.setTransitionFunctions(functions) ;
        States.push_back(state) ;
        if(state.getStateID() == "00")
        {
            currentState = state ;
        }
    }
    if(!currentState.isSet())
    {
        cout<<"Error: description file does not have -00-state (initial state)" ; 
        exit(1);
    }
  
}

string* UniversalTM::decodeString(string line)
{
    string* arr = new string[5] ;
    int length = 0 , firstZero = 0 ;
    for(int i = 0 , c = 0 ; i<line.size() ; i++)
    {
        if(line[i]=='1')
        {
            arr[c] = line.substr(firstZero , length) ;
            c++ ;
            firstZero = i+1 ;
            length = 0 ;
        }
        else
            length++ ;
    }
    
    return arr ;
    
}

TFunction UniversalTM::createFunction(string* arr)
{
    TFunction function ;
    function.setCurrrentState(arr[0]) ;
    function.setCurrentCharacter(arr[1]) ;
    function.setNewState(arr[2]) ;
    function.setCharacterToBeWritten(arr[3]) ;
    function.setDireaction(arr[4]) ;
    return function ;
}

void UniversalTM::extractStateIDs()
{
    for(int i = 0 ; i<TransitionFunctions.size() ; i++)
    {
        string currentStateID = TransitionFunctions[i].getCurrentState() ;
        if(!stateIdIstored(currentStateID))
            stateTable.push_back(currentStateID) ;
        string nextStateID = TransitionFunctions[i].getNewState() ;
        if(!stateIdIstored(nextStateID))
            stateTable.push_back(nextStateID);
        
        
    }
}
bool UniversalTM::stateIdIstored(string id)
{
    for(int i = 0 ; i<stateTable.size() ; i++)
    {
        if(id == stateTable[i])
            return true ;
    }
    return false ;
}

vector<TFunction> UniversalTM::extractFunctionsRelatedToState(string stateID)
{
    vector<TFunction> functions  ;
    for(int i = 0 ; i<TransitionFunctions.size() ; i++)
    {
        TFunction function = TransitionFunctions[i] ;
        if(stateID == function.getCurrentState())
        {
            functions.push_back(function) ;
        }
    }
    return functions ;
}
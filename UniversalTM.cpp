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
    /*
        The 2 argument constructor of the UniversalTM class , the first parameter is the description file path 
            the constructor tries to open the file , if the file isn't opnend the program is ended , if it is
            opened 2 methods are called , the initTansFunction and the InputTapeEngine constructor which takes
            the second parameter -input file description- as an argument .
     */
    
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
        tapeEngine = InputTapeEngine(inFilePath);
    }
}

void UniversalTM::startMachine()
{
    /*
        Once this method is called the machine starts to work by enterin an infinite loop which only breaks if a halt state -0- 
            was encountered , the first step in the loop is to execute the currentState with the current input , then we check 
            for the new stateID -which is returned by the executeFunction method- if it is the halt state the loops breaks , if
            it is not we check if the newStateID is the same as the current state id the loop starts the next iteration , if 
            not we call the findState method with the newStateID as an argument .
     */
    
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
    /*
        This method finds a state with a given state ID string , if a state was found it returns it , if not the program 
            exits .
     */
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
    long long numberOfLines ;
    numberOfLines = count(istreambuf_iterator<char>(description_file),istreambuf_iterator<char>() , '\n') ;
    description_file.clear() ;
    description_file.seekg(0 , ios::beg) ;
    if(numberOfLines > 0)
    {
        while(getline(description_file , line))
        {
            string* arr =  decodeString(line) ;
            TFunction tempFunction = createFunction(arr) ;
            TransitionFunctions.push_back(tempFunction);
        
        }
    }
    else
    {
        getline(description_file , line) ;
        vector<string*> statesDecoded ;
        int stateCount = 0 , firstZero = 0 , length = 0   ;
        string arr[5] ;
        for(int i = 0 , c = 0; i<line.size() ; i++)
        {
            if(line[i]=='1')
            {
                string slice = line.substr(firstZero , length) ;
                if(slice.length() != 0)
                {
                    arr[c] = line.substr(firstZero , length) ;
                    c++ ;
                }
                firstZero = i+1 ;
                length = 0 ;
            }
            else
            {
                length++ ;
            }
            if(c == 5)
            {
                statesDecoded.push_back(arr) ;
                TFunction tempFunction = createFunction(arr) ;
                TransitionFunctions.push_back(tempFunction);
                c = 0 ;
                stateCount++ ;
            }
        }
    }
    extractStateIDs() ;
    extractStates() ;
    
    
}

void UniversalTM::extractStates()
{
    
    /*
        This method is used after the stateTable vector is filled , then we have to model the states into real 
            state objects , so to do that we iterate over the stateTable vector , and in every iteration we 
            set the stateID that is retrieved form the stateTable , and then we call the 
            extractFunctionsRelatedToState method to store the transition functions related to this state 
            then we store the state in the State vector , and in every iteration we check if the current
            stateID is -00- this means it is the initial state , so we store it in the currentState object .
     */
    
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
            string slice = line.substr(firstZero , length) ;
            if(slice.length() != 0)
            {
                arr[c] = line.substr(firstZero , length) ;
                c++ ;
            }
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
    /*
        This method gets called when the TransitionFunctions vector is filled , at thi point we only have
            a list of transition functions , we need to extract the ids of the states from this list , to
            do this we have a vector of stateIDs -stateTable- and we iterate over the stateTable if the 
            current state is already stored we don't add it , if not we add it , and keep in mind that 
            not only we need to check for the current state we also need to check for the next state 
            because some states are only used once -halt states- .
     */
    
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
    /*
        This method is used to check if a state is already stored in the stateTable method .
     */
    
    for(int i = 0 ; i<stateTable.size() ; i++)
    {
        if(id == stateTable[i])
            return true ;
    }
    return false ;
}

vector<TFunction> UniversalTM::extractFunctionsRelatedToState(string stateID)
{
    /*
        This method is used to extract transition functions that is related to a certain state , to do that 
            we iterate over the TransitionFunctions vector and in every iteration we check if the currentState
            of the current tranition function is equal to the given stateID , if so we store it in vector 
            and in the end we return this vector .
     
     */
    
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
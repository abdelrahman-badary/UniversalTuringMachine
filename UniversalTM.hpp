//
//  UniversalTM.hpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/26/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#ifndef UniversalTM_hpp
#define UniversalTM_hpp

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "TFunction.hpp"
#include "State.hpp"
#include "InputTapeEngine.hpp"
using namespace std;
class UniversalTM
{
    private:
        fstream description_file ;
        fstream input_file ;
        State currentState ;
        InputTapeEngine tapeEngine ;
        void initTransFunction() ;
        string* decodeString(string line);
        TFunction createFunction(string* arr) ;
        vector<TFunction> TransitionFunctions ;
        vector<State> States;
        vector<string> stateTable ;
        void extractStateIDs() ;
        bool stateIdIstored(string id) ;
        void extractStates() ;
        vector<TFunction> extractFunctionsRelatedToState(string stateID);
        State findState(string stateID);
    
    
    public:
        UniversalTM();
        UniversalTM(string descFilePath , string inFilePath);
        void startMachine();


};
#endif /* UniversalTM_hpp */

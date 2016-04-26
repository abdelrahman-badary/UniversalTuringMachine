//
//  State.hpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/24/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <stdio.h>
#include <vector>
#include "InputTapeEngine.hpp"
#include "TFunction.hpp"
using namespace std;


class State
{
    private:
        string stateID ;
        vector<TFunction> TransitionFunctions ;
        TFunction findFunction(string input);

    public:
        State();
        State(string stateID , vector<TFunction> funs) ;
        void setStateID(string sID);
        string getStateID();
        void setTransitionFunctions(vector<TFunction> tFuns);
        vector<TFunction> getTransitionFunctions();
        void print();
        bool isSet() ;
        string executeFunction(string input , InputTapeEngine &inputEngine);
    
};
#endif /* State_hpp */

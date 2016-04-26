//
//  TFunction.hpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/24/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#ifndef TFunction_hpp
#define TFunction_hpp

#include <stdio.h>
#include <string>
#include <iostream>
using namespace std ; 
class TFunction
{
    private :
    string currentState ;
    string currentCharacter ;
    string newState ;
    string characterToBeWritten ;
    string direaction ;
    public:
    TFunction(string cState , string curChara , string nState , string nChara , string dir) ;
    TFunction() ;
    void setCurrrentState(string cState);
    string getCurrentState();
    void setCurrentCharacter(string cChar);
    string getCurrentCharacter();
    void setNewState(string nState);
    string getNewState();
    void setCharacterToBeWritten(string nChara);
    string getCharacterToBeWritten();
    void setDireaction(string dir);
    string getDireaction();
    void print();
    
};
#endif /* TFunction_hpp */

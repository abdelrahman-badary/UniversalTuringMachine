//
//  TFunction.cpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/24/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#include "TFunction.hpp"

TFunction::TFunction(){} 

TFunction::TFunction(string cState , string curChara , string nState , string nChara , string dir)
{
    currentState = cState ;
    currentCharacter = curChara ;
    newState = nState ;
    characterToBeWritten = nChara ;
    direaction = dir ;
}

void TFunction::setCurrrentState(string cState)
{
    currentState = cState ;
}
string TFunction::getCurrentState()
{
    return currentState ; 
}

void TFunction::setCurrentCharacter(string cChara)
{
    currentCharacter = cChara ;
}
string TFunction::getCurrentCharacter()
{
    return currentCharacter ;
}

void TFunction::setNewState(string nState)
{
    newState = nState ;
}
string TFunction::getNewState()
{
    return newState ; 
}

void TFunction::setCharacterToBeWritten(string nChara)
{
    characterToBeWritten = nChara ;
}
string TFunction::getCharacterToBeWritten()
{
    return characterToBeWritten ; 
}

void TFunction::setDireaction(string dir)
{
    direaction = dir ;
}
string TFunction::getDireaction()
{
    return direaction ; 
}

void TFunction::print()
{
    cout<<"\t================================================="<<endl ;
    cout<<"\tcurrent state: "<<currentState<<endl ;
    cout<<"\tcurrent character "<<currentCharacter<<endl ;
    cout<<"\tnew state: "<<newState<<endl ;
    cout<<"\tnew character: "<<characterToBeWritten<<endl ;
    cout<<"\tdireaction: "<<direaction<<endl ;
    cout<<"\t================================================="<<endl ;
}



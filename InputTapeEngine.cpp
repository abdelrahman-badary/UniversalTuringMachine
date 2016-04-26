//
//  InputTapeEngine.cpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/26/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#include "InputTapeEngine.hpp"

InputTapeEngine::InputTapeEngine(){}

InputTapeEngine::InputTapeEngine(string inFile_path)
{
    input_file.open(inFile_path) ;
}

void InputTapeEngine::setInputFile(string inFile_path)
{
    input_file.open(inFile_path) ;
    if(!input_file.is_open())
    {
        cout<<"Error: input file not found"<<endl ;
        exit(1);
    }
    Index = 0 ;
    readInputFile();
    
}

void InputTapeEngine::readInputFile()
{
    string content ;
    getline(input_file , content) ;
    input_file.clear();
    input_file.seekg(0 , ios::beg);
    
    int length = 0 , firstZero = 0 ;
    for(int i = 0  ; i<content.size() ; i++)
    {
        if(content[i]=='1')
        {
            TapeContent.push_back(content.substr(firstZero , length));
            firstZero = i+1 ;
            length = 0 ;
        }
        else
            length++ ;
    }
    
}

string InputTapeEngine::readInput()
{
    return TapeContent[Index];
}

void InputTapeEngine::write(string direaction, string output)
{
    TapeContent[Index] = output ;
    if(direaction == "00")
    {
        Index -- ; 
    }
    else if (direaction == "000")
    {
        Index++ ;
    }
        
}

void InputTapeEngine::halt()
{
    cout<<"Success :"<<endl;
    for(int i = 0 ; i<TapeContent.size() ; i++)
        cout<<TapeContent[i]<<"1" ;
}







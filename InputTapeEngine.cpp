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
    /*
        One argument constructor for the InputEngineClass , it takes the path of the input file ,
            and tries to open it , if it didn't succeeded in opening the file the program exits ,
            if it did it calls the readInputFile method .
     */
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
    /*
        This method is used to parse the input file , after parsing it splits the input string on every '1' and puts every element
            in the TapeContent vector .
     */
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
    /*
        This method is used to read an input from the tape .
     */
    return TapeContent[Index];
}

void InputTapeEngine::write(string direaction, string output)
{
    /*
        This method is used to write to the tape and move the cursor either right or left , 
            the important part here is that we actually wirte first then move the cursor .
     */
    
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
    /*
        This method is used to halt the cursor it is called when the current state is the halt state -0- .
     */
    
    cout<<"Success :"<<endl;
    for(int i = 0 ; i<TapeContent.size() ; i++)
        cout<<TapeContent[i]<<"1" ;
    cout<<endl ;
}







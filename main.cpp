//
//  main.cpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/24/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include "UniversalTM.hpp"
using namespace std ;


int main(int argc, const char * argv[]) {
    
    //path to description file .
    string descriptionFilePath ;
    //path to input file .
    string inputFilePath ;
    if(descriptionFilePath.empty() || inputFilePath.empty())
    {
        cout<<"Error: Please specify the path to the description and input files in code"<<endl ;
        exit(1) ; 
    }
    UniversalTM UTM(descriptionFilePath , inputFilePath);
    UTM.startMachine();
    return 0;
}

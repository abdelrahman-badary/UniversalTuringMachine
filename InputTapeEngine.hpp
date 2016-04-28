//
//  InputTapeEngine.hpp
//  UTM
//
//  Created by Abd al rhman Taher on 4/26/16.
//  Copyright © 2016 Abd al rhman Taher. All rights reserved.
//

#ifndef InputTapeEngine_hpp
#define InputTapeEngine_hpp

#include <iostream>
#include <fstream>
#include <vector>
using namespace std ;
class InputTapeEngine
{
    private:
        fstream input_file;
        int Index ;
        vector<string> TapeContent ;
        void readInputFile() ; 
    public:
        InputTapeEngine();
        InputTapeEngine(string inFile);
        string readInput();
        void write(string direaction , string output);
        void halt();


};
#endif /* InputTapeEngine_hpp */

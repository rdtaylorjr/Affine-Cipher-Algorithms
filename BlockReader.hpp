/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file BlockReader.hpp
 @author Russell Taylor
 @date 11/20/20
*/

#ifndef BlockReader_hpp
#define BlockReader_hpp

#include "Utilities.hpp"

class BlockReader {
public:
    /**
     Constructs a BlockReader object
     @param is a binary input file stream
     */
    BlockReader(Utilities* utilities, ifstream& is);

    /**
     Reads data
     @param number a big number
     @param count the count
     @return the width
     */
    int readData(BigNumber& number, int count);

private:
    Utilities* utilities;
    ifstream& is_;
};

#endif /* BlockReader_hpp */

/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file BlockWriter.hpp
 @author Russell Taylor
 @date 11/20/20
*/

#ifndef BlockWriter_hpp
#define BlockWriter_hpp

#include "Utilities.hpp"

class BlockWriter {
public:
    /**
     Constructs a BlockWriter object
     @param os a binary output file stream
     */
    BlockWriter(Utilities* utilities, ofstream& os);

    /**
     Writes data
     @param number a big number
     @param count the count
     */
    void writeData(const BigNumber& number, const int count);

private:
    Utilities* utilities;
    ofstream& os_;
};

#endif /* BlockWriter_hpp */

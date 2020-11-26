/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file BlockReader.cpp
 @author Russell Taylor
 @date 11/20/20
*/

#include <climits>
#include "BlockReader.hpp"

/**
 Constructs a BlockReader object
 @param is a binary input file stream
 */
BlockReader::BlockReader(Utilities* utilities, ifstream& is) : utilities(utilities), is_(is) {
}

/**
 Reads data
 @param number a big number
 @param count the count
 @return the width
 */
int BlockReader::readData(BigNumber& number, int count) {
    if (count == 0 || count > INT_MAX)
        throw runtime_error("BigNumberReader::read - Invalid parameter count " + to_string(count));

    utilities->debugStream << "BigNumberReader::readData - Requested count " << to_string(count) << " bytes, got\n";

    int width = 0;
    number = 0;

    while (count--) {
        unsigned char byte;
        is_.read((char*) &byte, 1);
        if (is_.eof())
            break;
        
        utilities->debugStream << " [" << width << "] " << utilities->formatByte(byte);
        
        ++width;
        number <<= 8;
        number |= BigNumber(byte);
    }

    utilities->debugStream << "\nBigNumberReader::readData - Read 0x" << hex << number << " as " << dec << width << " bytes\n\n" << flush;

    return width;
}

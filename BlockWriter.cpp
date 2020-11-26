/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file BlockWriter.cpp
 @author Russell Taylor
 @date 11/20/20
*/

#include <climits>
#include "BlockWriter.hpp"

/**
 Constructs a BlockWriter object
 @param os a binary output file stream
 */
BlockWriter::BlockWriter(Utilities* utilities, ofstream& os) : utilities(utilities), os_(os) {
}

/**
 Writes data
 @param number a big number
 @param count the count
 */
void BlockWriter::writeData(const BigNumber& number, const int count) {
    if (count == 0 || count > INT_MAX)
        throw runtime_error("BigNumberWriter::write - Invalid parameter count " + to_string(count));

    utilities->debugStream << "BigNumberWriter::writeData - Writing 0x" << hex << number << " as " <<  dec << count << " bytes\n";
    
    BigNumber b = 0;
    for (int i = 0, offset = count * 8 - 8; offset >= 0; ++i, offset -= 8) {
        unsigned char byte = (unsigned char) ((number >> offset) - (b << 8));
        b = (number >> offset);
        
        os_.write((char*) &byte, 1);
        
        utilities->debugStream << " [" << i << "] " << utilities->formatByte(byte);
    }

    if (os_.fail())
        throw runtime_error("BlockWriter::writeData - Failed to write " + to_string(count) + " bytes");

    utilities->debugStream << "\n\n" << flush;
}

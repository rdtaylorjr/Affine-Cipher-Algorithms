/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file Utilities.hpp
 @author Russell Taylor
 @date 11/20/20
*/

#include <sstream>
#include "Utilities.hpp"

/**
 Formats bytes for output to file
 @param byte the byte to be formatted
 @return the formatted byte
 */
std::string Utilities::formatByte(const unsigned char byte) {
    if (byte == '\n')
        return "\\n";
    if (byte == '\r')
        return "\\r";
    if (byte == '\t')
        return "\\t";
    
    if (byte >= ' ' && byte <= '~') {
        std::stringstream stream;
        stream << "'" << byte << "'";
        return stream.str();
    }
    
    std::stringstream stream;
    stream << "0x";
    if (byte < 16) stream << '0';
    stream << std::hex << int(byte);
    return stream.str();
}

/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file main.cpp
 @author Russell Taylor
 @date 11/20/20
 
 Based on provided pseudocode
 Reads multiple binary input files, encrypts the contents of the files using an Affine Cipher, decrypts the encrypted message, then verifies that the original input and the decrypted message are the same.
 
 @pre multiple binary input files and corresponding encoding information in text files
 @post a text file containing the encrypted message, a binary file containing the decrypted message, and a debug text file, for each input file
*/

#include "Driver.hpp"

/**
 Controls operation of the program
 */
int main(int argc, const char * argv[]) {
    Utilities utilities;
    Driver driver(&utilities);
    try {
        for (int i = 1; i <= 3; ++i)
            driver.testFile(to_string(i));
    }
    catch (const exception& ex) {
        if (utilities.debugStream) {
            utilities.debugStream << "Exception:" << ex.what() << "\n";
            cout << "Exception:" << ex.what() << "\n";
        }
    }
    return 0;
}

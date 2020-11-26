/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file Driver.hpp
 @author Russell Taylor
 @date 11/20/20
*/

#ifndef Driver_hpp
#define Driver_hpp

#include "AffineCodec.hpp"

class Driver {
public:
    /**
     Constructs a Driver object
     @param utilities miscellaneous utilities for output to the debug file stream and formatting bytes
     */
    Driver(Utilities* utilities);
    
    /**
     Tests files
     @param number the file number
     */
    void testFile(const string& number);
    
private:
    Utilities* utilities;
    
    /**
     Tests encryption
     @param affineCodec the AffineCodec object
     @param plainFile the plaintext file name
     @param encryptedFile the encrypted file name
     */
    void testEncryption(AffineCodec& affineCodec, const string& plainFile, const string& encryptedFile);

    /**
     Tests decryption
     @param affineCodec the AffineCodec object
     @param encryptedFile the encrypted file name
     @param decryptedFile the decrypted file name
     */
    void testDecryption(const AffineCodec& affineCodec, const string& encryptedFile, const string& decryptedFile);

    /**
     Initializes the AffineCodec with input from the key materials file
     @param keyFile the key materials file name
     @param p the first RSA large prime number
     @param q the second RSA large prime number
     @param e the RSA public exponent
     @param a the first affine cipher key number
     @param b the second affine cipher key number
     */
    void importKeyMaterials(const string& keyFile, BigNumber& p, BigNumber& q, BigNumber& e, BigNumber& a, BigNumber& b);
    
    /**
     Compares files to determine whether they are the same
     @param first the name of the first file to be compared
     @param second the name of the second file to be compared
     */
    void compareFiles(const string& first, const string& second);
    
    /**
     Returns the size of a file
     @param file the name of the file
     @return the size of the file
     */
    int fileSize(const string& file);
};

#endif /* Driver_hpp */

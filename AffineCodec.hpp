/**
 Lab 7 - Affine Cipher Encryption
 CSC 255 Objects and Algorithms (Fall 2020)
 Oakton Community College
 Professor: Kamilla Murashkina

 @file AffineCodec.hpp
 @author Russell Taylor
 @date 11/20/20
*/

#ifndef AffineCodec_hpp
#define AffineCodec_hpp

#include "AffineAlgorithm.hpp"

class AffineCodec {
public:
    /**
     Constructs an AffineCodec object
     @param utilities miscellaneous utilities for output to the debug file stream and formatting bytes
     @param p the first RSA large prime number
     @param q the second RSA large prime number
     @param e the RSA public exponent
     @param a the first affine cipher key number
     @param b the second affine cipher key number
     */
    AffineCodec(Utilities* utilities, const BigNumber& p, const BigNumber& q, const BigNumber& e, const BigNumber& a, const BigNumber& b);
    
    /**
     Encrypts the file stream
     @param fin the input file stream
     @param fout the output file stream
     */
    void encryptStream(ifstream& fin, ofstream& fout);
    
    /**
     Decrypts the file stream
     @param fin the input file stream
     @param fout the output file stream
     */
    void decryptStream(ifstream& fin, ofstream& fout) const;
    
private:
    Utilities* utilities;
    const AffineAlgorithm affineAlgorithm_;
    const BigNumber& p;
    const BigNumber& q;
    const BigNumber& e;
    const BigNumber& a;
    const BigNumber& b;
    unsigned int blockMaxLength;
    
    /**
     Calculates the block maximum length
     @param n the crypto modulus
     */
    unsigned int calculateBlockMaxLength(const BigNumber& n) const;
};

#endif /* AffineCodec_hpp */

#ifndef MD5_H
#define MD5_H
#include "algorithminterface.h"

class MD5 : public AlgorithmInterface
{

    public:
        MD5();
        QString getHashString();    // return digest as a 33-byte ascii-hex string
        int calculateFile(QString path);    // digest file, close, finalize

    private:
        // methods for controlled operation:
        void update(unsigned char *input, unsigned int input_length);
        int update(QDataStream &stream);
        void finalize();
        // some types:
        typedef unsigned       int uint4; // assumes integer is 4 words long
        typedef unsigned short int uint2; // assumes short integer is 2 words long
        typedef unsigned      char uint1; // assumes char is 1 word long

        // private data:
        uint4 state[4];
        uint4 count[2];     // number of *bits*, mod 2^64
        uint1 buffer[64];   // input buffer
        uint1 digest[16];
        uint1 finalized;

        // the private methods, mostly static:
        void init();  // called by all constructors
        void transform(uint1 *buffer);  // does the real update work.

        static void encode    (uint1 *dest, uint4 *src, uint4 length);
        static void decode    (uint4 *dest, uint1 *src, uint4 length);
        static void memcpy    (uint1 *dest, uint1 *src, uint4 length);
        static void memset    (uint1 *start, uint1 val, uint4 length);

        static inline uint4  rotate_left (uint4 x, uint4 n);
        static inline uint4  F           (uint4 x, uint4 y, uint4 z);
        static inline uint4  G           (uint4 x, uint4 y, uint4 z);
        static inline uint4  H           (uint4 x, uint4 y, uint4 z);
        static inline uint4  I           (uint4 x, uint4 y, uint4 z);
        static inline void   FF  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
                                  uint4 s, uint4 ac);
        static inline void   GG  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
                                  uint4 s, uint4 ac);
        static inline void   HH  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
                                  uint4 s, uint4 ac);
        static inline void   II  (uint4& a, uint4 b, uint4 c, uint4 d, uint4 x,
                                  uint4 s, uint4 ac);
};

#endif // MD5_H

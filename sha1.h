#ifndef SHA1_H
#define SHA1_H
#include "algorithminterface.h"

class Sha1 : public AlgorithmInterface
{
public:
    Sha1();
    void update(const std::string &s);
    int update(QDataStream &is);
    std::string final();
    static std::string from_file(const std::string &filename);
    int calculateFile(QString path);
    QString getHashString();

private:
    typedef unsigned long int uint32;   /* just needs to be at least 32bit */
    typedef unsigned long long uint64;  /* just needs to be at least 64bit */

    static const unsigned int DIGEST_INTS = 5;  /* number of 32bit integers per SHA1 digest */
    static const unsigned int BLOCK_INTS = 16;  /* number of 32bit integers per SHA1 block */
    static const unsigned int BLOCK_BYTES = BLOCK_INTS * 4;

    uint32 digest[DIGEST_INTS];
    std::string buffer;
    uint64 transforms;

    void reset();
    void transform(uint32 block[BLOCK_BYTES]);

    static void buffer_to_block(const std::string &buffer, uint32 block[BLOCK_BYTES]);
    static void read(QDataStream &is, std::string &s, int max);
};

#endif // SHA1_H

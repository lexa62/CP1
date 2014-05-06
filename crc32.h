#ifndef CRC32_H
#define CRC32_H
#include <QtGui>
#include "algorithminterface.h"

class Crc32 : public AlgorithmInterface
{
    private:
        unsigned long crc_table[256];
        unsigned long crc32;
        void crc_cycle(char * buf, size_t cnt);
        void crc_init();

    public:
        QString getHashString();
        Crc32();
        void openFile(QString path);
};

#endif

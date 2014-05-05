#ifndef CRC32_H
#define CRC32_H
#include <QtGui>

class Crc32
{
    private:
        unsigned long crc_table[256];
        unsigned long crc32;
        void crc_cycle(char * buf, size_t cnt);
        void crc_init();

    public:
        unsigned long gethash();
        Crc32(QString);
};

#endif

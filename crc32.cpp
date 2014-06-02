#include "crc32.h"
#include <QtGui>
#include "enumTypes.h"

void Crc32::crc_cycle(char * buf, size_t cnt)
{
    crc32 = ~crc32;
    for (size_t i = 0; i < cnt; i++)
    {
        crc32 = crc_table[(crc32^buf[i]) & 0xff] ^ (crc32 >> 8);
    }
    crc32 = ~crc32;
}

void Crc32::crc_init()
{
    unsigned long t;
    for (int i = 0; i < 256; i++)
    {
        t = i;
        for (int j = 8; j>0; j--)
        {
            if (t & 1)
                t = (t >> 1) ^ 0xedb88320;
            else
                t >>= 1;
        }
        crc_table[i] = t;
    }
}

QString Crc32::getHashString()
{
    QString hash;
    hash.sprintf("%08lX", crc32);
    return hash;
}

Crc32::Crc32(): crc32(0)
{
    crc_init();
}

int Crc32::calculateFile(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        int ok;
        char* buf = new char[4096];

        while(!in.atEnd())
        {
            ok = in.readRawData(buf, 4096);
            if(in.status() == QDataStream::Ok)
            {
                crc_cycle(buf, ok);
                qApp->processEvents();
            }
            else break;
        }
        delete [] buf;
        file.close();
        if(in.status() == QDataStream::Ok)
            return ErrorType::noError;
        else
            return ErrorType::corruptData;
    }
    else
        return ErrorType::notOpened;
}

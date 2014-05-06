#include <stdio.h>
#include "crc32.h"
#include <QtGui>

void Crc32::crc_cycle(char * buf, size_t cnt)
{
    crc32 = ~crc32;
    for (size_t i = 0; i<cnt; i++)
    {
        crc32 = crc_table[(crc32^buf[i]) & 0xff] ^ (crc32 >> 8);
    }
    crc32 = ~crc32;
}

void Crc32::crc_init()
{
    unsigned long t;
    for (int i = 0; i<256; i++)
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
    QString tmp;
    tmp.sprintf("%08lX", crc32);
    return tmp;
}

/*Crc32::Crc32(const char * filePath): crc32(0)
{
    crc_init();
    FILE *fd;
    size_t ok, l;
    fd = fopen(filePath, "rb");
    qDebug()<<filePath;
    if(fd)
    {
    fseek(fd, 0, SEEK_END);
    l = ftell(fd);
    fseek(fd, 0, SEEK_SET);
    unsigned char buf[4096];

    for (size_t i = 0; i<l; i += ok)
    {
        ok = fread(buf, 1, sizeof(buf), fd);
        crc_cycle(buf, ok);
    }

    fclose(fd);
    }
}*/

Crc32::Crc32(): crc32(0)
{
    crc_init();
}

void Crc32::openFile(QString path)
{
    QFile file(path);
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);
        qint64 ok=0, l = file.size();
        char* buf = new char[4096];

        for (qint64 i = 0; i<l; i += ok)
        {
            ok = in.readRawData(buf, 4096);
            crc_cycle(buf, ok);
        }
        delete [] buf;
        file.close();
    }
    else
        qDebug() << path <<" can't be opened" << endl;
}

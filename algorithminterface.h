#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H
#include <QtGui>
class AlgorithmInterface
{
    public:
        virtual ~AlgorithmInterface(){}
        virtual QString getHashString() = 0;
        virtual int calculateFile(QString) = 0;
};

#endif // ALGORITHMINTERFACE_H

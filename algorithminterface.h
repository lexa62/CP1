#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H
#include <QtGui>
class AlgorithmInterface
{
    public:
        virtual QString getHashString() = 0;
        virtual int calculateFile(QString) = 0;
        virtual ~AlgorithmInterface(){}
};

#endif // ALGORITHMINTERFACE_H

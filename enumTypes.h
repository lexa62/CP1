#ifndef ENUMALGORITHM_H
#define ENUMALGORITHM_H
namespace AlgorithmType
{
    enum Type
    {
        md5,
        crc32,
        sha1
    };
}

namespace WidgetType
{
    enum Type
    {
        selectingAction,
        hashView,
        checkHashFile,
        checkHashFiles
    };
}

namespace ErrorType
{
    enum Type
    {
        notOpened,
        corruptData,
        noError
    };
}
#endif // ENUMALGORITHM_H

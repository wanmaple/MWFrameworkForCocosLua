#include "MWCipherMachine.h"
#include "libmd5/md5.h"

using namespace std;

MW_FRAMEWORK_BEGIN

MWCipherMachine::MWCipherMachine()
{
    
}

string MWCipherMachine::encipherMd5(const std::string &content)
{
    MD5 md5(content);
    return md5.toString();
}

string MWCipherMachine::encipherMd5(mwframework::MWBinaryData *rawData)
{
    MD5 md5(rawData->getData(), rawData->getSize());
    return md5.toString();
}

MW_FRAMEWORK_END
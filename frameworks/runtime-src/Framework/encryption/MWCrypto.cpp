#include "MWCrypto.h"

#include "../platform/MWIOUtils.h"
#include "md5/md5.h"
#include "base64/libbase64.h"
#include "xxtea/xxtea.h"

#define BUFFER_LENGTH 512

using namespace std;
using namespace cocos2d;

MW_FRAMEWORK_BEGIN

MWCrypto::MWCrypto()
{
    
}

string MWCrypto::md5(mwframework::MWBinaryData *data)
{
    MD5 md5(data->getData(), data->getSize());
    return md5.toString();
}

string MWCrypto::md5String(const std::string &content)
{
    MD5 md5(content);
    return md5.toString();
}

string MWCrypto::md5File(const std::string &filePath)
{
    auto data = MWIOUtils::getInstance()->getDataFromFile(filePath);
    return this->md5(data);
}

string MWCrypto::encodeBase64(const std::string &content)
{
    int outputLen = Base64encode_len((int) content.size());
    char buffer[outputLen + 1];
    int len = Base64encode(buffer, content.c_str(), (int) content.size());
    buffer[len] = 0;
    CCLOG("%d %d", outputLen, len);
    string ret(buffer);
    return ret;
}

string MWCrypto::decodeBase64(const std::string &content)
{
    int outputLen = Base64decode_len(content.c_str());
    char buffer[outputLen + 1];
    int len = Base64decode(buffer, content.c_str());
    buffer[len] = 0;
    CCLOG("%d %d", outputLen, len);
    string ret(buffer);
    return ret;
}

MWBinaryData *MWCrypto::encipherAes256(mwframework::MWBinaryData *data, const std::string &key)
{
    int bufferLen = BUFFER_LENGTH;
    MW_BYTE *buffer = new MW_BYTE[bufferLen];
    int len;
    // repeat until the length is enough.
    while ((len = this->cryptAes256(false, (MW_BYTE *) data->getData(), (int) data->getSize(), buffer, bufferLen, (MW_BYTE *) key.c_str(), (int) key.size())) < 0) {
        bufferLen <<= 1;
        buffer = (MW_BYTE *) realloc(buffer, bufferLen);
//        memset(buffer, 0, bufferLen);
    }
    auto ret = MWBinaryData::create(buffer, len);
    delete[] buffer;
    return ret;
}

MWBinaryData *MWCrypto::decipherAes256(mwframework::MWBinaryData *data, const std::string &key)
{
    int bufferLen = BUFFER_LENGTH;
    MW_BYTE *buffer = new MW_BYTE[bufferLen];
    int len;
    // repeat until the length is enough.
    while ((len = this->cryptAes256(true, (MW_BYTE *) data->getData(), (int) data->getSize(), buffer, bufferLen, (MW_BYTE *) key.c_str(), (int) key.size())) < 0) {
        bufferLen <<= 1;
        buffer = (MW_BYTE *) realloc(buffer, bufferLen);
        //        memset(buffer, 0, bufferLen);
    }
    auto ret = MWBinaryData::create(buffer, len);
    delete[] buffer;
    return ret;
}

MWBinaryData *MWCrypto::encipherXxtea(mwframework::MWBinaryData *data, const std::string &key)
{
    xxtea_long len;
    MW_BYTE *res = xxtea_encrypt((MW_BYTE *) data->getData(), (xxtea_long) data->getSize(), (MW_BYTE *) key.c_str(), (xxtea_long) key.size(), &len);
    auto ret = MWBinaryData::create(res, len);
    free(res);
    return ret;
}

MWBinaryData *MWCrypto::decipherXxtea(mwframework::MWBinaryData *data, const std::string &key)
{
    xxtea_long len;
    MW_BYTE *res = xxtea_decrypt((MW_BYTE *) data->getData(), (xxtea_long) data->getSize(), (MW_BYTE *) key.c_str(), (xxtea_long) key.size(), &len);
    auto ret = MWBinaryData::create(res, len);
    free(res);
    return ret;
}

MW_FRAMEWORK_END
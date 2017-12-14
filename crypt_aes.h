#ifndef CRYPT_AES
#define CRYPT_AES
#define ENCR 1

#include <base_chiper.h>

class crypt_AES : public base_chiper{
public:
    crypt_AES(QString passwd/*len=16*/)
    {
        passw = passwd;
        saltw = "It is kinda salt";
    }
    void myCrypt(int encdec, const char * text);

};

#endif // CRYPT_AES


#ifndef CRYPT_HOST
#define CRYPT_HOST

#define ENCR 1

#include <base_chiper.h>

class crypt_HOST : public base_chiper{
public:
    crypt_HOST(QString passwd/*len=32*/)
    {
        passw = passwd;
        saltw = "It fsaltItIt fsaltItIt fsaltItIt";
    }
    void myCrypt(int encdec, const char * text);

};

#endif // CRYPT_HOST


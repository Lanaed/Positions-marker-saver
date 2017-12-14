#ifndef CRYPT_DES_H
#define CRYPT_DES_H
#define ENCR 1
#include <iostream>

#include <base_chiper.h>

class crypt_DES : public base_chiper{
public:
    crypt_DES(QString passwd/*len=8*/) :
        base_chiper()
    {
        std::cout << "AMIGO" << std::endl;
        passw = passwd;
        saltw = "ASd 3";
        std::cout<< "AMIGO" <<passw.toStdString()<<std::endl;
    }
    void myCrypt(int encdec, const char * text);

};
#endif // CRYPT_DES_H


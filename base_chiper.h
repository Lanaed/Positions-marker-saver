#ifndef BASE_CHIPER
#define BASE_CHIPER
#define ENCR 1

#include <QString>

class base_chiper{
    protected:
        QString passw;
        QString saltw;
        int encdec = ENCR;
    public:
        virtual void myCrypt(int encdec, const char * text) = 0;

};


#endif // BASE_CHIPER


#include <stdio.h>
#include <gcrypt.h>
#include <QString>
#include <QApplication>
#include "mainwindow.h"

#define ENCR 1
#define DECR 0

void myCrypt(int encdec, const char * pass, const char * salt, const char * text) {
  gcry_error_t     gcryError;
  gcry_cipher_hd_t hd;
  size_t           i;

  size_t passLength = strlen(pass);
  size_t saltLength = strlen(salt);
  size_t textLength = strlen(text)+encdec;
  char  * outBuffer = (char*)malloc(textLength);

  printf("%scryption...\n", encdec?"En":"De");
  printf("passLength = %d\n", passLength);
  printf("saltLength = %d\n", saltLength);
  printf("textLength = %d\n", textLength);
  printf("      pass = %s\n", pass);
  printf("      salt = %s\n", salt);
  printf("      text = %s\n", encdec?text:"<null>");

  // используем алгоритм шифрования - GCRY_CIPHER_AES128
  // используем режим сцепления блоков шифротекста
  // используем флаг GCRY_CIPHER_CBC_CTS, чтобы можно было шифровать текст любой длины
  gcryError = gcry_cipher_open(&hd,
                   GCRY_CIPHER_GOST28147,
                   GCRY_CIPHER_MODE_CBC,
                   GCRY_CIPHER_CBC_CTS);

  if (gcryError) {
      printf("gcry_cipher_open failed:  %s/%s\n",
         gcry_strsource(gcryError), gcry_strerror(gcryError));
      return;
  }

  gcryError = gcry_cipher_setkey(hd, pass, passLength);
  if (gcryError) {
      printf("gcry_cipher_setkey failed:  %s/%s\n",
         gcry_strsource(gcryError), gcry_strerror(gcryError));
      return;
  }

  gcryError = gcry_cipher_setiv(hd, salt, saltLength);
  if (gcryError) {
      printf("gcry_cipher_setiv failed:  %s/%s\n",
         gcry_strsource(gcryError),gcry_strerror(gcryError));
      return;
  }

  switch (encdec) {
    case ENCR:
      gcryError = gcry_cipher_encrypt(hd, outBuffer, textLength, text, textLength);
      break;
    case DECR:
      gcryError = gcry_cipher_decrypt(hd, outBuffer, textLength, text, textLength);
  }
  if (gcryError) {
      printf("gcry_cipher_encrypt failed:  %s/%s\n",
         gcry_strsource(gcryError), gcry_strerror(gcryError));
      return;
  }

  switch (encdec) {
    case ENCR:
      printf("Ecnrypted text = ");
      for (i = 0; i<textLength; i++) printf("%02X", (unsigned char)outBuffer[i]);
      printf("\n");
      break;
    case DECR:
      printf("Original text = %s\n", outBuffer);
  }

  gcry_cipher_close(hd);
  free(outBuffer);
}




int main(int argc, char** argv) {

    /*
  int encdec = ENCR;

  printf("Enter text: ");
  QString text;
  text = "HELOO, my dear friend234567uyijhgяывчаспмриотьлбдюблотрипмасвчыяфяывапрол";
  //fgets(line, sizeof(line), stdin);
  QString key;
  key = "fghj'123fghj'123fghj'123fghj'123";
  QString salt;
  salt = "It fsaltItIt fsaltItIt fsaltItIt";
  myCrypt(encdec, key.toStdString().c_str(), salt.toStdString().c_str(), text.toStdString().c_str());

  return 0;
    */
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}

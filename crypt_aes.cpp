#include <stdio.h>
#include <gcrypt.h>
#include <QString>
#include <crypt_aes.h>

#define ENCR 1
#define DECR 0

void crypt_AES::myCrypt(int encdec, const char * text) {

  gcry_error_t     gcryError;
  gcry_cipher_hd_t hd;
  size_t           i;

  size_t passLength = passw.length();
  size_t saltLength = saltw.length();
  size_t textLength = strlen(text)+encdec;
  char  * outBuffer = (char*)malloc(textLength);

  printf("%scryption...\n", encdec?"En":"De");
  printf("passLength = %d\n", passLength);
  printf("saltLength = %d\n", saltLength);
  printf("textLength = %d\n", textLength);
  printf("      pass = %s\n", passw.toAscii().constData());
  printf("      salt = %s\n", saltw.toAscii().constData());
  printf("      text = %s\n", encdec?text:"<null>");

  // используем алгоритм шифрования - GCRY_CIPHER_AES128
  // используем режим сцепления блоков шифротекста
  // используем флаг GCRY_CIPHER_CBC_CTS, чтобы можно было шифровать текст любой длины
  gcryError = gcry_cipher_open(&hd,
                   GCRY_CIPHER_AES,
                   GCRY_CIPHER_MODE_CBC,
                   GCRY_CIPHER_CBC_CTS);

  if (gcryError) {
      printf("gcry_cipher_open failed:  %s/%s\n",
         gcry_strsource(gcryError), gcry_strerror(gcryError));
      return;
  }

  gcryError = gcry_cipher_setkey(hd, passw.toAscii().constData(), passLength);
  if (gcryError) {
      printf("gcry_cipher_setkey failed:  %s/%s\n",
         gcry_strsource(gcryError), gcry_strerror(gcryError));
      return;
  }

  gcryError = gcry_cipher_setiv(hd, saltw.toAscii().constData(), saltLength);
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

  FILE* fp = fopen("res.txt", "w");
  switch (encdec) {
    case ENCR:
      printf("Ecnrypted text = ");
      for (i = 0; i<textLength; i++) fprintf(fp, "%02X",
                                             (unsigned char)outBuffer[i]);
      printf("\n");
      break;
    case DECR:
      printf("Original text = %s\n", outBuffer);
  }
  fclose(fp);
  gcry_cipher_close(hd);
  free(outBuffer);
}

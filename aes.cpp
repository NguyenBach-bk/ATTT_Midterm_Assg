#include "aes.h"
#include <cstring>
#include <openssl/aes.h>

// Hàm mã hóa AES
void
aes_encrypt (const std::string &input, const std::string &key,
             std::string &output)
{
  AES_KEY enc_key;
  unsigned char iv[AES_BLOCK_SIZE] = { 0 }; // Khởi tạo vector khởi tạo IV là 0
  output.resize (input.size ());
  AES_set_encrypta_key (reinterpret_cast<const unsigned char *> (key.c_str ()),
                        128, &enc_key);
  AES_cbc_encrypt (reinterpret_cast<const unsigned char *> (input.c_str ()),
                   reinterpret_cast<unsigned char *> (&output[0]),
                   input.size (), &enc_key, iv, AES_ENCRYPT);
}

// Hàm giải mã AES
void
aes_decrypt (const std::string &input, const std::string &key,
             std::string &output)
{
  AES_KEY dec_key;
  unsigned char iv[AES_BLOCK_SIZE] = { 0 }; // Khởi tạo IV là 0
  output.resize (input.size ());
  AES_set_decrypt_key (reinterpret_cast<const unsigned char *> (key.c_str ()),
                       128, &dec_key);
  AES_cbc_encrypt (reinterpret_cast<const unsigned char *> (input.c_str ()),
                   reinterpret_cast<unsigned char *> (&output[0]),
                   input.size (), &dec_key, iv, AES_DECRYPT);
}

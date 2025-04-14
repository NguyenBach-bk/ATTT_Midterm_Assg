#include "des.h"
#include <cstring>
#include <openssl/des.h>

// Hàm mã hóa DES
void
des_encrypt (const std::string &input, const std::string &key,
             std::string &output)
{
  DES_key_schedule key_schedule;
  DES_cblock key_block;
  std::memcpy (key_block, key.c_str (), key.size ());
  DES_set_key (&key_block, &key_schedule);

  output.resize (input.size ());
  DES_cbc_encrypt (reinterpret_cast<const unsigned char *> (input.c_str ()),
                   reinterpret_cast<unsigned char *> (&output[0]),
                   input.size (), &key_schedule, (DES_cblock *)key.c_str (),
                   DES_ENCRYPT);
}

// Hàm giải mã DES
void
des_decrypt (const std::string &input, const std::string &key,
             std::string &output)
{
  DES_key_schedule key_schedule;
  DES_cblock key_block;
  std::memcpy (key_block, key.c_str (), key.size ());
  DES_set_key (&key_block, &key_schedule);

  output.resize (input.size ());
  DES_cbc_encrypt (reinterpret_cast<const unsigned char *> (input.c_str ()),
                   reinterpret_cast<unsigned char *> (&output[0]),
                   input.size (), &key_schedule, (DES_cblock *)key.c_str (),
                   DES_DECRYPT);
}

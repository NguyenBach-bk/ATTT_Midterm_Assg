#ifndef AES_H
#define AES_H

#include <string>

void aes_encrypt(const std::string &input, const std::string &key, std::string &output);
void aes_decrypt(const std::string &input, const std::string &key, std::string &output);

#endif // AES_H

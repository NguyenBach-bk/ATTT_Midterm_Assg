#ifndef DES_H
#define DES_H

#include <string>

void des_encrypt(const std::string &input, const std::string &key, std::string &output);
void des_decrypt(const std::string &input, const std::string &key, std::string &output);

#endif // DES_H

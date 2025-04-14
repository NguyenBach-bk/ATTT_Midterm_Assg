#include "aes.h"
#include "des.h"
#include <fstream>
#include <iostream>
#include <string>

// Hàm đọc dữ liệu từ file
std::string
read_from_file (const std::string &filename)
{
  std::ifstream file (filename);
  if (!file)
    {
      std::cerr << "Không thể mở file " << filename << std::endl;
      return "";
    }
  std::string content ((std::istreambuf_iterator<char> (file)),
                       std::istreambuf_iterator<char> ());
  return content;
}

// Hàm ghi dữ liệu vào file
void
write_to_file (const std::string &filename, const std::string &content)
{
  std::ofstream file (filename);
  if (!file)
    {
      std::cerr << "Không thể ghi vào file " << filename << std::endl;
      return;
    }
  file << content;
}

int
main ()
{
  // Đọc dữ liệu từ file
  std::string input_data = read_from_file ("input.txt");

  if (input_data.empty ())
    {
      return 1; // Nếu file rỗng thì thoát
    }

  // Khóa mã hóa
  std::string aes_key = "0123456789abcdef"; // 128-bit key AES
  std::string des_key = "12345678";         // 64-bit key DES

  // Mã hóa và giải mã AES
  std::string aes_encrypted;
  aes_encrypt (input_data, aes_key, aes_encrypted);
  write_to_file ("aes_encrypted.txt", aes_encrypted);

  std::string aes_decrypted;
  aes_decrypt (aes_encrypted, aes_key, aes_decrypted);
  write_to_file ("aes_decrypted.txt", aes_decrypted);

  // Mã hóa và giải mã DES
  std::string des_encrypted;
  des_encrypt (input_data, des_key, des_encrypted);
  write_to_file ("des_encrypted.txt", des_encrypted);

  std::string des_decrypted;
  des_decrypt (des_encrypted, des_key, des_decrypted);
  write_to_file ("des_decrypted.txt", des_decrypted);

  return 0;
}

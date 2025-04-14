#include "des.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

std::vector<uint8_t>
readFile (const std::string &filename)
{
  std::ifstream file (filename, std::ios::binary);
  if (!file)
    {
      throw std::runtime_error ("Cannot open file: " + filename);
    }

  file.seekg (0, std::ios::end);
  size_t fileSize = file.tellg ();
  file.seekg (0, std::ios::beg);

  std::vector<uint8_t> data (fileSize);
  file.read (reinterpret_cast<char *> (data.data ()), fileSize);

  return data;
}

void
writeFile (const std::string &filename, const std::vector<uint8_t> &data)
{
  std::ofstream file (filename, std::ios::binary);
  if (!file)
    {
      throw std::runtime_error ("Cannot create file: " + filename);
    }

  file.write (reinterpret_cast<const char *> (data.data ()), data.size ());
}

std::vector<uint8_t>
padData (const std::vector<uint8_t> &data)
{
  size_t padLen = 8 - (data.size () % 8);
  std::vector<uint8_t> padded = data;
  for (size_t i = 0; i < padLen; ++i)
    {
      padded.push_back (static_cast<uint8_t> (padLen));
    }
  return padded;
}

std::vector<uint8_t>
unpadData (const std::vector<uint8_t> &data)
{
  if (data.empty ())
    return data;

  uint8_t padLen = data.back ();
  if (padLen > 8)
    return data; // Invalid padding

  for (size_t i = data.size () - padLen; i < data.size (); ++i)
    {
      if (data[i] != padLen)
        {
          return data; // Invalid padding
        }
    }

  return std::vector<uint8_t> (data.begin (), data.end () - padLen);
}

int
main ()
{
  try
    {
      //Key
      std::vector<uint8_t> key = { 0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1 };

      DES des (key);

      std::cout << "DES Encryption/Decryption Tool\n";
      std::cout << "1. Encrypt file\n";
      std::cout << "2. Decrypt file\n";
      std::cout << "Choose option (1/2): ";

      int option;
      std::cin >> option;

      if (option == 1)
        {
          std::string inputFile, outputFile;
          std::cout << "Enter input file name: ";
          std::cin >> inputFile;
          std::cout << "Enter output file name: ";
          std::cin >> outputFile;

          auto plaintext = readFile (inputFile);

          auto paddedData = padData (plaintext);

          std::vector<uint8_t> ciphertext;
          for (size_t i = 0; i < paddedData.size (); i += 8)
            {
              std::vector<uint8_t> block (paddedData.begin () + i, paddedData.begin () + i + 8);
              auto encryptedBlock = des.encrypt (block);
              ciphertext.insert (ciphertext.end (), encryptedBlock.begin (), encryptedBlock.end ());
            }

          writeFile (outputFile, ciphertext);

          std::cout << "Encryption completed. Result saved to " << outputFile << "\n";
        }
      else if (option == 2)
        {
          std::string inputFile, outputFile;
          std::cout << "Enter input file name: ";
          std::cin >> inputFile;
          std::cout << "Enter output file name: ";
          std::cin >> outputFile;

          auto ciphertext = readFile (inputFile);

          if (ciphertext.size () % 8 != 0)
            {
              throw std::runtime_error ("Invalid ciphertext length (must be multiple of 8 bytes)");
            }

          std::vector<uint8_t> plaintext;
          for (size_t i = 0; i < ciphertext.size (); i += 8)
            {
              std::vector<uint8_t> block (ciphertext.begin () + i, ciphertext.begin () + i + 8);
              auto decryptedBlock = des.decrypt (block);
              plaintext.insert (plaintext.end (), decryptedBlock.begin (), decryptedBlock.end ());
            }

          auto unpaddedData = unpadData (plaintext);

          writeFile (outputFile, unpaddedData);

          std::cout << "Decryption completed. Result saved to " << outputFile << "\n";
        }
      else
        {
          std::cout << "Invalid option.\n";
        }
    }
  catch (const std::exception &e)
    {
      std::cerr << "Error: " << e.what () << "\n";
      return 1;
    }

  return 0;
}

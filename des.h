#ifndef DES_H
#define DES_H

#include <cstdint>
#include <vector>

class DES
{
public:
  DES (const std::vector<uint8_t> &key);

  std::vector<uint8_t> encrypt (const std::vector<uint8_t> &plaintext);
  std::vector<uint8_t> decrypt (const std::vector<uint8_t> &ciphertext);

private:
  void generateSubKeys ();
  uint64_t desProcessBlock (uint64_t block, bool encrypt);

  std::vector<uint8_t> key;
  std::vector<uint64_t> subKeys;

  // Table and S-box
  static const int initialPermutation[64];
  static const int finalPermutation[64];
  static const int expansionPermutation[48];
  static const int permutation[32];
  static const int pc1[56];
  static const int pc2[48];
  static const int shiftTable[16];
  static const int sBox[8][4][16];
};

#endif // DES_H

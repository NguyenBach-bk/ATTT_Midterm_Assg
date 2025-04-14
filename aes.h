#ifndef AES_H
#define AES_H

#include <cstdint>
#include <vector>

class AES
{
public:
  AES (const std::vector<uint8_t> &key);

  std::vector<uint8_t> encrypt (const std::vector<uint8_t> &plaintext);
  std::vector<uint8_t> decrypt (const std::vector<uint8_t> &ciphertext);

private:
  void keyExpansion ();
  void addRoundKey (int round);
  void subBytes ();
  void invSubBytes ();
  void shiftRows ();
  void invShiftRows ();
  void mixColumns ();
  void invMixColumns ();

  std::vector<uint8_t> key;
  std::vector<std::vector<uint8_t> > roundKeys;
  std::vector<std::vector<uint8_t> > state;

  static const uint8_t sBox[256];
  static const uint8_t invSBox[256];
  static const uint8_t rcon[11];
};

#endif // AES_H

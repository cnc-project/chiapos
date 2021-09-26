#include "c_interface.h"
#include "verifier.hpp"

//#include <optional>

char* HexToCharByte(const char* hex) 
{
    std::vector<uint8_t> bytes; 
    std::string hexString = std::string(hex);
    for (unsigned int i = 0; i < hexString.length(); i += 2) 
    {
        std::string byteString = hexString.substr(i, 2);
        uint8_t byte = (uint8_t) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    char* res = new char[bytes.size() + 1]; // +1 for the final 0
    res[bytes.size() + 1] = 0; // terminate the string
    for (size_t i = 0; i < bytes.size(); ++i) 
    {
        res[i] = bytes[i];
    }
    return res;
}

char* c_validate_proof(const char* seed, uint8_t k, const char* challenge, const char* proof)
{
    Verifier verifier;

    char* seed_charByte = HexToCharByte(seed);
    char* challenge_charByte = HexToCharByte(challenge);
    char* proof_charByte = HexToCharByte(proof);

    std::string proofString = std::string(proof);
    uint16_t proof_size = proofString.length() / 2;

    LargeBits quality = verifier.ValidateProof((const uint8_t *)seed_charByte, k, (const uint8_t *)challenge_charByte, (const uint8_t *)proof_charByte, proof_size);  

    if (quality.GetSize() == 0)
    {
        return nullptr;
    }

    uint8_t *quality_buf = new uint8_t[32];
    quality.ToBytes(quality_buf);

    std::string hex;
    char ch[3];
    for(int i = 0; i < 32; i++)
    {
        sprintf(ch, "%02x", quality_buf[i]);
        hex += ch;
    }
    delete[] quality_buf;
    delete[] proof_charByte;
    delete[] challenge_charByte;
    delete[] seed_charByte;

    char *result = new char[hex.length() + 1];
    memcpy(result, hex.c_str(), hex.length() + 1);

    return result;
}
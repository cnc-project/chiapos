#ifndef C_INTERFACE_H
#define C_INTERFACE_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
char* c_validate_proof(const char* seed, uint8_t k, const char* challenge, const char* proof);
char* HexToCharByte(const char* hex);
#ifdef __cplusplus
}
#endif 


#endif // C_INTERFACE_H
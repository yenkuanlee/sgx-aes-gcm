#include "CryptoEnclave_t.h"

#include "sgx_trts.h"
#include "sgx_tcrypto.h"
#include "stdlib.h"
#include <string.h>

#define BUFLEN 1148576
static sgx_aes_gcm_128bit_key_t key = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };

void decryptMessage(char *encMessageIn, size_t len, char *decMessageOut, size_t lenOut)
{
	uint8_t *encMessage = (uint8_t *) encMessageIn;
	uint8_t p_dst[BUFLEN] = {0};

	for(int ii = 0;ii<1000000;ii++){

	sgx_rijndael128GCM_decrypt(
		&key,
		encMessage + SGX_AESGCM_MAC_SIZE + SGX_AESGCM_IV_SIZE,
		lenOut,
		p_dst,
		encMessage + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE,
		NULL, 0,
		(sgx_aes_gcm_128bit_tag_t *) encMessage);
	memcpy(decMessageOut, p_dst, lenOut);
	}
        // emit_debug((char *) p_dst);
}

void encryptMessage(char *decMessageIn, size_t len, char *encMessageOut, size_t lenOut)
{
	uint8_t *origMessage = (uint8_t *) decMessageIn;
	uint8_t p_dst[BUFLEN] = {0};

	// Generate the IV (nonce)
	sgx_read_rand(p_dst + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE);
	for(int ii = 0;ii<1000000;ii++){
	sgx_rijndael128GCM_encrypt(
		&key,
		origMessage, len,
		p_dst + SGX_AESGCM_MAC_SIZE + SGX_AESGCM_IV_SIZE,
		p_dst + SGX_AESGCM_MAC_SIZE, SGX_AESGCM_IV_SIZE,
		NULL, 0,
		(sgx_aes_gcm_128bit_tag_t *) (p_dst));
	}
	memcpy(encMessageOut,p_dst,lenOut);
}

void hashMessage(char *hashMessageIn, size_t len) {
	uint8_t *origMessage = (uint8_t *) hashMessageIn;
	uint8_t p_dst[BUFLEN] = {0};
	sgx_sha256_msg(
		origMessage, len,
		(sgx_sha256_hash_t*)(p_dst));
	// memcpy(encMessageOut,p_dst,lenOut);
}

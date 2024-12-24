//
// Created by volkert on 12/24/24.
//

#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>

/**
 * Code below with thanks to https://stackoverflow.com/a/51263027
 * @param binary_hash
 * @param hex_hash
 */
void sha1_hash_to_hex_string(unsigned char binary_hash[SHA_DIGEST_LENGTH], unsigned char hex_hash[SHA_DIGEST_LENGTH*2])
{
    int i = 0;
    for (i=0; i < SHA_DIGEST_LENGTH; i++) {
        sprintf((char*)&(hex_hash[i*2]), "%02x", binary_hash[i]);
    }
}

/**
 * ode below with thanks to https://stackoverflow.com/a/13194749
 * @param hex_hash
 * @param bytearray
 */
void hex_string_to_sha1_hash(unsigned char hex_hash[40], unsigned char bytearray[20])
{
    char *hexstring = hex_hash;
    int i;
    uint8_t str_len = strlen(hexstring);

    for (i = 0; i < (str_len / 2); i++) {
        sscanf(hexstring + 2*i, "%02x", &bytearray[i]);
        printf("bytearray %d: %02x\n", i, bytearray[i]);
    }
}

int main(void)
{
    const unsigned char data[] = "hello, world\n";

    size_t length = strlen(data);

    unsigned char binary_hash[SHA_DIGEST_LENGTH];
    SHA1(data, length, binary_hash);

    unsigned char hex_hash[SHA_DIGEST_LENGTH*2];

    sha1_hash_to_hex_string(binary_hash, hex_hash);

    // And print to stdout
    printf("Hash: %s\n", hex_hash);

    printf("Binary hash 1: %s\n", binary_hash);

    unsigned char bytearray[SHA_DIGEST_LENGTH];

    hex_string_to_sha1_hash(hex_hash, bytearray);

    printf("Binary hash 2: %s\n", bytearray);

    if (memcmp(binary_hash, bytearray, sizeof(SHA_DIGEST_LENGTH)))
    {
        printf("Byte arrays should be identical, but they are not.");
    } else
    {
        printf("Byte arrays should be identical, and they are.");
    }
}

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
void sha1_hash_to_hex_string(unsigned char binary_hash[SHA_DIGEST_LENGTH],
                             unsigned char hex_hash[SHA_DIGEST_LENGTH * 2])
{
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++)
    {
        sprintf((char*)&(hex_hash[i * 2]), "%02x", binary_hash[i]);
    }
}

/**
 * Code below with thanks to https://stackoverflow.com/a/13194749
 * @param hex_hash
 * @param bytearray
 */
void hex_string_to_sha1_hash(unsigned char hex_hash[40], unsigned char bytearray[20])
{
    char* hexstring = hex_hash;
    uint8_t str_len = strlen(hexstring);

    for (int i = 0; i < (str_len / 2); i++)
    {
        sscanf(hexstring + 2 * i, "%02x", &bytearray[i]);
        // printf("bytearray %d: %02x\n", i, bytearray[i]); // Uncomment this only when debugging
    }
}

void test_hashing_and_string_conversion(void)
{
    const unsigned char data[] = "1234";

    size_t length = strlen(data);

    unsigned char binary_hash[SHA_DIGEST_LENGTH];
    SHA1(data, length, binary_hash);

    unsigned char hex_hash[SHA_DIGEST_LENGTH * 2];

    sha1_hash_to_hex_string(binary_hash, hex_hash);

    // And print to stdout
    printf("Hash: %s\n", hex_hash);

    printf("Binary hash 1: %s\n", binary_hash);

    unsigned char bytearray[SHA_DIGEST_LENGTH];

    hex_string_to_sha1_hash(hex_hash, bytearray);

    printf("Binary hash 2: %s\n", bytearray);

    if (memcmp(binary_hash, bytearray, sizeof(SHA_DIGEST_LENGTH)))
    {
        printf("Byte arrays should be identical, but they are not.\n");
    }
    else
    {
        printf("Byte arrays should be identical, and they are.\n");
    }
}

int has_matching_sha1_hash(char string_to_check[], unsigned char sha1_hash_to_look_for[20])
{
    unsigned char string_binary_hash[SHA_DIGEST_LENGTH];
    SHA1(string_to_check, strlen(string_to_check), string_binary_hash);

    /* Uncomment the following block only when debugging */
    // printf("Comparing hash %s with hash %s\n", string_binary_hash, sha1_hash_to_look_for);
    // unsigned char string_binary_hash_hex_string[SHA_DIGEST_LENGTH*2];
    // sha1_hash_to_hex_string(string_binary_hash, string_binary_hash_hex_string);
    // unsigned char sha1_hash_to_look_for_hex_string[SHA_DIGEST_LENGTH*2];
    // sha1_hash_to_hex_string(sha1_hash_to_look_for, sha1_hash_to_look_for_hex_string);
    // printf("Comparing hash %s with hash %s\n", string_binary_hash_hex_string, sha1_hash_to_look_for_hex_string);

    return !memcmp(string_binary_hash, sha1_hash_to_look_for, sizeof(SHA_DIGEST_LENGTH));
}

int main(void)
{
    //const unsigned char sha1_hash_to_decode_in_hex[SHA_DIGEST_LENGTH*2] = "b16d0ef3dd0632dcd13d135e02a097aec4044c24";
    const unsigned char sha1_hash_to_decode_in_hex[SHA_DIGEST_LENGTH * 2] = "7110eda4d09e062aa5e4a390b0a572ac0d2c0220"; // "1234"
    unsigned char sha1_hash_to_decode[SHA_DIGEST_LENGTH];
    hex_string_to_sha1_hash(sha1_hash_to_decode_in_hex, sha1_hash_to_decode);

    /* Uncomment the following lines only when debugging proper conversion back and forth */
    // printf("The hash we're looking for: %s\n", sha1_hash_to_decode);
    // unsigned char hash_to_decode_2[SHA_DIGEST_LENGTH*2];
    // sha1_hash_to_hex_string(sha1_hash_to_decode, hash_to_decode_2);
    // printf("Or in human-readable hex form: %s\n", hash_to_decode_2);

    /* Uncomment the following line only when debugging proper conversion back and forth */
    // test_hashing_and_string_conversion();

    const int min_number = 0;
    const int max_number = 9999;

    char max_number_as_string[100];

    sprintf(max_number_as_string, "%d", max_number);

    int number_of_zeroes_to_pad = strlen(max_number_as_string);
    /* Uncomment the following line only when debugging proper conversion back and forth */
    // printf("Number of zeroes to pad: %d\n", number_of_zeroes_to_pad);

    char zero_padding_format_string[100];
    sprintf(zero_padding_format_string, "%s%d%s", "%0", number_of_zeroes_to_pad, "d");

    int pin_found_yet = 0;

    for (int i = min_number; i <= max_number; i++)
    {
        unsigned char zero_padded_number_string[number_of_zeroes_to_pad];
        sprintf(zero_padded_number_string, zero_padding_format_string, i);

        unsigned char unpadded_number_string[number_of_zeroes_to_pad];
        sprintf(unpadded_number_string, "%d", i);

        /* Uncomment the following line only when debugging */
        // printf("PIN string: %s (%s)\n", zero_padded_number_string, unpadded_number_string);

        if (has_matching_sha1_hash(zero_padded_number_string, sha1_hash_to_decode))
        {
            printf("Found PIN string with matching hash: \"%s\"\n", zero_padded_number_string);
            pin_found_yet = 1;
            break;
        }

        if (has_matching_sha1_hash(unpadded_number_string, sha1_hash_to_decode))
        {
            printf("Found PIN string with matching hash: \"%s\"\n", unpadded_number_string);
            pin_found_yet = 1;
            break;
        }
    }

    if (!pin_found_yet)
    {
        fprintf(stderr, "PIN number not found, tried numbers from %d through %d.\n", min_number, max_number);
    }

    return !pin_found_yet;
}

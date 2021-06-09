#include "mycrypto.hpp"
#include "Kuznyechik.hpp"

int main() {
    ByteBlock key = hex_representation(
        "8899aabbccddeeff0011223344556677fedcba98765432100123456789abcdef"
    );
    ByteBlock iv = hex_representation("abcdef12345600dacdef94756eeabefa");
    ByteBlock msg = hex_representation("1122334455667700ffeeddccbbaa9988");
    ByteBlock result;

    CFB_Mode<Kuznyechik> encryptor(Kuznyechik(key), iv);
    encryptor.encrypt(msg, result);

    return 0;
}
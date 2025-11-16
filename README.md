Vtxor: Compile-Time XOR String Encryption
By: RicoPopovitch

This library provides a lightweight, header-only utility for compile-time XOR encryption and dynamic building of string literals in C++. 

The main goals are:
- Converting plaintext strings to arrays to avoid the rdata string pool.
- "Encrypting" strings so they are illegible.
- Being header only ready to drop into any project.

** READ THIS **
Xor encryption is not secure crypto. This library's purpose is binary string obfusication, not data security.
Runtime encryption is still recomdeded.

`g_key` is assigned at compile time using `__TIME_` as entropy.
`crypt()` converts a string literal into a `std::array<char, N>` and xors each char at compile time.
`dcrypt()` template reconstructs a runtime `std::string` from an encrypted array.
`print()` couts the encrypted characters directly for debugging and verification. 

```cpp
constexpr char g_key = []() {
    const char* time = __TIME__;
    char key = 0x24;
    for (int i = 0; time[i] != '\0'; ++i) {
        key ^= time[i];
    }
    return key ? key : 0x42;
}();
```

Computes `g_key` during compile time.
XORs an initial key by `__TIME__` to produce a semi-random key each compilation.
Feel free to change the initial key or the fallback, althouhg keeping a fallback is recomended to ensure no plaintext.

```cpp
template<char Key, std::size_t N>
constexpr std::array<char, N> crypt(const char(&str)[N]) {
    std::array<char, N> arr{};
    for (std::size_t i = 0; i < N; ++i) {
        arr[i] = str[i] ^ Key;
    }
    return arr;
}
```

Takes a paintext string as a paramater then converts and encrypts
Returns a constexpr  `std::array`

```cpp
template<char Key, std::size_t N>
std::string decrypt(const std::array<char, N>& arr) {
    std::string decrypted;
    decrypted.reserve(N - 1);
    for (std::size_t i = 0; i < N - 1; ++i) {
        decrypted += arr[i] ^ Key;
    }
    return decrypted;
}
```

Xors the encrypted data back to its original values then returns the results as a `std::string`
![nopdb](https://raw.githubusercontent.com/RicoPopovitch/Vtxor/main/images/stringpool.png)
-strings will not appear in string pool at all

![pdb](https://raw.githubusercontent.com/RicoPopovitch/Vtxor/main/images/pdb.png)
-strings will look like this if viewed in ida with a pdb

![nopdb](https://raw.githubusercontent.com/RicoPopovitch/Vtxor/main/images/nopdb.png)

-they will look like this if viewed with no pdb 










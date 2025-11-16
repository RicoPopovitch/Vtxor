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
gens `g_key` during compile time.
xors an initial key by `__TIME__` to produce a random key each compilation.
both `0x24` and `0x42` are arbitrary change them as you please

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
takes a paintext string as a paramater then converts and encrypts
returns a constexpr  `std::array`

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
xors the encrypted data back to its original values then returns the results as a `std::string`

strings will not appear in string pool at all
![nopdb](https://raw.githubusercontent.com/RicoPopovitch/Vtxor/main/images/stringpool.png)

they will look like this if viewed with no pdb 
![nopdb](https://raw.githubusercontent.com/RicoPopovitch/Vtxor/main/images/nopdb.png)

strings will look like this if viewed in ida with a pdb
![pdb](https://raw.githubusercontent.com/RicoPopovitch/Vtxor/main/images/pdb.png)













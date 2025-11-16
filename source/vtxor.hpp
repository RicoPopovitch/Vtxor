#pragma once

#include <array>
#include <string>

namespace vtxor {

    constexpr char g_key = []() {
        const char* time = __TIME__;
        char key = 0x24; 
        for (int i = 0; time[i] != '\0'; ++i) {
            key ^= time[i];
        }
        return key ? key : 0x42;
    }(); 

    template<char Key, std::size_t N>
    constexpr std::array<char, N> crypt(const char(&str)[N]) {
        std::array<char, N> array{};
        for (std::size_t i = 0; i < N; ++i) {
            array[i] = str[i] ^ Key;
        }
        return array; 
    }

    template<char Key, std::size_t N>
    std::string dcrypt(const std::array<char, N>& arr) {
        std::string decrypted;
        decrypted.reserve(N - 1);
        for (std::size_t i = 0; i < N - 1; ++i) {
            decrypted += arr[i] ^ Key;
        }
        return decrypted;
    }

    template<std::size_t N>
    void print(const std::array<char, N>& arr) {
        for (std::size_t i = 0; i < N - 1; ++i) {
            std::cout << arr[i];
        }
        std::cout << std::endl;
    }

} //vtxor


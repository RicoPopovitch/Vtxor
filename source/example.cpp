#include "vtxor.hpp"
#include <iostream>
#include <windows.h>

//store in rdata
static constexpr auto v1 = vtxor::crypt<vtxor::g_key>("Secret1!");
static constexpr auto v2 = vtxor::crypt<vtxor::g_key>("//Secret 2");
static constexpr auto v3 = vtxor::crypt<vtxor::g_key>("Serceret 3");

void strings() {
    HMODULE hModule = GetModuleHandle(NULL);
    uintptr_t base = reinterpret_cast<uintptr_t>(hModule);
    
    std::cout << std::hex << std::showbase;

    uintptr_t v1_addr = reinterpret_cast<uintptr_t>(v1.data());
    uintptr_t v2_addr = reinterpret_cast<uintptr_t>(v2.data());
    uintptr_t v3_addr = reinterpret_cast<uintptr_t>(v3.data());
    
    std::cout << "rva" << std::endl;

    std::cout << "v1: " << (v1_addr - base) << std::endl;
    std::cout << "v2: " << (v2_addr - base) << std::endl;
    std::cout << "v3: " << (v3_addr - base) << std::endl;

    std::cout << std::dec << std::noshowbase << std::endl;
    
    std::cout << "crypted" << std::endl;

    std::cout << "v1: ";
    vtxor::print(v1);
    std::cout << "v2: ";
    vtxor::print(v2);
    std::cout << "v3: ";
    vtxor::print(v3);

    std::cout << std::endl;
    
    std::cout << "dcrypted" << std::endl;

    std::cout << "v1: " << vtxor::dcrypt<vtxor::g_key>(v1) << std::endl;
    std::cout << "v2: " << vtxor::dcrypt<vtxor::g_key>(v2) << std::endl;
    std::cout << "v3: " << vtxor::dcrypt<vtxor::g_key>(v3) << std::endl;
}
 
int main() {
    strings();
    system("pause");
    return 0;
}

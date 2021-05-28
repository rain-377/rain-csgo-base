#pragma once

template <typename T>
class singleton
{
protected:
    singleton() { }
    ~singleton() { }

    singleton(const singleton&) = delete;
    singleton& operator=(const singleton&) = delete;

    singleton(singleton&&) = delete;
    singleton& operator=(singleton&&) = delete;
public:
    static T& get()
    {
        static T instance{ };
        return instance;
    }
};

namespace utils
{
    template<typename t>
    inline t get_virtual(void* _class, int index)
    {
        int* vtable = *(int**)_class;
        int address = vtable[index];
        return (t)(address);
    }

    inline std::uint8_t* find_signature(const char* module_name, const char* signature) 
    {
        auto module = GetModuleHandleA(module_name);

        static auto pattern_to_byte = [](const char* pattern) 
        {
            auto bytes = std::vector<int>{};
            auto start = const_cast<char*>(pattern);
            auto end = const_cast<char*>(pattern) + strlen(pattern);

            for (auto current = start; current < end; ++current) {
                if (*current == '?') {
                    ++current;
                    if (*current == '?')
                        ++current;
                    bytes.push_back(-1);
                }
                else {
                    bytes.push_back(strtoul(current, &current, 16));
                }
            }
            return bytes;
        };

        auto dosHeader = (PIMAGE_DOS_HEADER)module;
        auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

        auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
        auto patternBytes = pattern_to_byte(signature);
        auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

        auto s = patternBytes.size();
        auto d = patternBytes.data();

        for (auto i = 0ul; i < sizeOfImage - s; ++i) 
        {
            bool found = true;
            for (auto j = 0ul; j < s; ++j) 
            {
                if (scanBytes[i + j] != d[j] && d[j] != -1) 
                {
                    found = false;
                    break;
                }
            }
            if (found) 
            {
                return &scanBytes[i];
            }
        }

        return nullptr;
    }
}
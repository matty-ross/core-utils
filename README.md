# Core Utils

![](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![](https://img.shields.io/badge/Visual%20Studio-5C2D91?style=for-the-badge&logo=visual-studio&logoColor=white)
![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

A library with various utilities for low-level Windows applications.


## Usage

### `Core::Pointer`

```cpp
#include "core/Pointer.hpp"


struct Person
{
    const char* Name;
    int Age;
};


int main()
{
    // Create a pointer.
    Core::Pointer person = new Person();

    // Access data at an offset as a concrete data type.
    person.at(0x0).as<const char*>() = "John Doe";
    person.at(0x8).as<int>() = 37;

    // Dereference the pointer.
    char nameSecondCharacter = person.at(0x0).deref().at(0x1).as<char>();

    // Get the underlying raw pointer.
    delete person.GetPointer<Person*>();

    return 0;
}
```

### `Core::WindowsException`

```cpp
#include <Windows.h>

#include "core/WindowsException.hpp"


int main()
{
    try
    {
        // Throw a Windows exception with an HRESULT.
        throw Core::WindowsException(E_ACCESSDENIED, "Cannot read file '%s'.", "C:\\secret.txt");
    }
    catch (const Core::WindowsException& ex)
    {
        // Get the HRESULT from the Windows exception.
        HRESULT hresult = ex.GetHresult();
    }

    return 0;
}
```

### `Core::Path`

```cpp
#include "core/WindowsException.hpp"
#include "core/Path.hpp"


int main()
{
    // Create a path from an environment variable.
    Core::Path path("%LOCALAPPDATA%");

    // Append another path.
    path.Append("Example\\Directory");

    // Check if the path exists.
    if (!path.Exists())
    {
        try
        {
            // Create the entire directory tree.
            path.CreateDirectoryTree();
        }
        catch (const Core::WindowsException& ex)
        {
            // Handle failure to create the entire directory tree.
        }
    }

    return 0;
}
```

### `Core::Logger`

```cpp
#include "core/Logger.hpp"


int main()
{
    // Create a console window and enable virtual terminal sequences.
    Core::Logger::Initialize();

    // Create a logger.
    Core::Logger logger("Example");

    // Log messages with various severity levels.
    logger.Info("Operation successful, duration: %.2f s.", 12.34f);
    logger.Warning("Invalid numerical value '%c' was found.", '@');
    logger.Error("Cannot bind socket to port %d.", 8080);
    
    return 0;
}
```

### `Core::Patch`

```asm
.code


; A function to patch.
example_function:
    mov eax, 1
    shl eax, 2
    add eax, ecx
    add eax, edx
    ret


.const


public ExampleFunction
ExampleFunction dq offset example_function


end
```

```asm
.code


; Instruction that overwrites the original one.
patch_instruction:
    mov eax, 5

; Size of the instruction that overwrites the original one.
patch_instruction_size equ $ - patch_instruction


; Redirected code.
redirected_code:
    sub eax, ecx
    sub eax, edx
    ret


.const


public g_PatchInstruction
g_PatchInstruction dq offset patch_instruction

public g_PatchInstructionSize
g_PatchInstructionSize dq patch_instruction_size

public g_RedirectedCode
g_RedirectedCode dq redirected_code


end
```

```cpp
#include <cstddef>

#include "core/Pointer.hpp"
#include "core/Logger.hpp"
#include "core/Patch.hpp"


extern "C" void* const ExampleFunction;

extern "C" void* const g_PatchInstruction;
extern "C" const size_t g_PatchInstructionSize;
extern "C" void* const g_RedirectedCode;


int main()
{
    // Create a logger for patches and a pointer to a function to patch.
    Core::Logger logger("Example");
    Core::Pointer address = ExampleFunction;
    
    // Create a patch and write bytes at the address, effectively overwriting the code.
    Core::Patch(logger, address.at(0x0), 5).WriteBytes(g_PatchInstruction, g_PatchInstructionSize);
    
    // Create a patch and write NOP instructions at the address, effectively removing the code.
    Core::Patch(logger, address.at(0x5), 3).WriteNOPs();
    
    // Create a patch and write a JMP instruction at the address, effectively redirecting the code.
    Core::Patch(logger, address.at(0x8), 5).WriteJMP(g_RedirectedCode);
    
    // Call the patched function - original result: 11; new result: -2.
    int result = reinterpret_cast<int(*)(int, int)>(ExampleFunction)(3, 4);
    
    return 0;
}
```

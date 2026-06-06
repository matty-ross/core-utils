# Core Utils

![](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![](https://img.shields.io/badge/Visual%20Studio-5C2D91?style=for-the-badge&logo=visual-studio&logoColor=white)
![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

A library with various utilities for low-level Windows applications.


## Usage

### `Core::Pointer`

Bypasses C++ pointer arithmetic and allows direct access to data at byte offsets.

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
    
    // Get the underlying address.
    delete person.GetAddress<Person*>();

    return 0;
}
```

### `Core::Logger`

Named console logger for messages with various levels.

```cpp
#include "core/Logger.hpp"


int main()
{
    // Create a console window and enable virtual terminal sequences.
    Core::Logger::Initialize();

    // Create a logger.
    Core::Logger logger("Example");

    // Log messages with various levels.
    logger.Info("Operation successful, duration: %.2f s.", 12.34f);
    logger.Warning("Invalid numerical value '%c' was found.", '@');
    logger.Error("Cannot bind socket to port %d.", 8080);
    
    return 0;
}
```

### `Core::WindowsException`

HRESULT with a custom error message.

```cpp
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

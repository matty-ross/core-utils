# Core Utils

![](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![](https://img.shields.io/badge/Visual%20Studio-5C2D91?style=for-the-badge&logo=visual-studio&logoColor=white)
![](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

A library with various utilities.


## Usage

```cpp
#include <cstdlib>
#include <cstddef>
#include <exception>

#include "core/Pointer.hpp"
#include "core/Logger.hpp"
#include "core/WindowsException.hpp"


struct Person
{
    const char* Name;
    int Age;
};


int main()
{
    // Create a logger.
    Core::Logger logger("Example");

    try
    {
        Person person =
        {
            .Name = "John Doe",
            .Age = 37,
        };

        // Create a pointer.
        Core::Pointer personPointer = &person;

        // Check the pointer's address.
        if (personPointer.GetAddress() == nullptr)
        {
            // Log warning.
            logger.Warning("Couldn't modify person.");
        }
        else
        {
            // Access data at some offset from the pointer's address.
            personPointer.at(offsetof(Person, Name)).as<const char*>() = "Jane Smith";
            personPointer.at(offsetof(Person, Age)).as<int>() = 45;

            // Log info.
            logger.Info("Person modified. Name: %s, Age: %d.", person.Name, person.Age);
        }

        // Throw a Windows exception.
        throw Core::WindowsException("Couldn't open a file.", HRESULT_FROM_WIN32(ERROR_ACCESS_DENIED));
    }
    catch (const std::exception& ex)
    {
        // Log error.
        logger.Error("%s", ex.what());
    }

    return EXIT_SUCCESS;
}
```

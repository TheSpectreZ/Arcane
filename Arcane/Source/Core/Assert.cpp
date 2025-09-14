#include "Assert.h"
#include "Logger.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void arc::Assert(cstring reason)
{
    int result = MessageBoxA(nullptr, reason, "Arcane Error", MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION);

    switch (result)
    {
    case IDABORT:
        std::exit(EXIT_FAILURE);
        break;
    case IDRETRY:
        __debugbreak();
        break;
    case IDIGNORE:
        break;
    }
}

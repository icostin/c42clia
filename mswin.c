#ifdef _WIN32
#include <stdio.h>
#include <windows.h>

int wmain (int argc, wchar_t const * const * argv)
{
    (void) argc;
    (void) argv;
    printf("c42clia main\n");
    return 0;
}


#endif


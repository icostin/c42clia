#ifndef _WIN32
#include <stdio.h>
#include <c42.h>
#include <c42svc.h>

int main (int argc, char const * const * argv)
{
    c42_svc_t svc;
    c42_clia_t clia;
    uint_fast8_t e, r = 0;

    do
    {
        e = c42svc_init(&svc);
        if (e) 
        { 
            r |= 64; 
            fprintf(stderr, "init services failed (%d)\n", e);
            break; 
        }
        e = c42svc_std_init(&clia.stdio);
        if (e) 
        {
            r |= 64;
            fprintf(stderr, "init standard I/O failed (%d)\n", e);
            break; 
        }
        clia.program = (uint8_t const *) argv[0];
        clia.args = (uint8_t const * const *) argv + 1;
        clia.argc = argc - 1;
        r = c42_main(&svc, &clia);
        e = c42svc_std_finish(&clia.stdio);
        if (e) 
        {
            r |= 64;
            fprintf(stderr, "failed finishing services (%d)\n", e);
            break;
        }
    }
    while (0);

    return r;
}

#endif


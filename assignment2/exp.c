#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *out;
    int i;

    out= popen("/usr/bin/less", "w");
    for( i= 0; i< 512; ++i )
        fprintf(out, "This is line %d\n", i);
    pclose(out);
}

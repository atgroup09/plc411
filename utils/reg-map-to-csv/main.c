#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "bit.h"
#include "reg-import.h"

int main()
{
    uint8_t i;

    fp = fopen("log.csv", "w+");
    fprintf(fp, "N;GID;Data.Table;Data.Addr;Beremiz.Addr;ModBus.Table;ModBus.Addr;Retain;Type;Str;\n");

    for(i=1; i<5; i++)
    {
        FP_MB[i] = fopen(FN_MB[i], "w+");
        fprintf(FP_MB[i], "N;GID;Table;Addr;Type;Str;\n");
    }

    REG_Init();

    fclose(fp);

    for(i=1; i<5; i++)
    {
        fclose(FP_MB[i]);
    }

    return 0;
}


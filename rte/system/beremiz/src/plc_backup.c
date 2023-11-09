/*
 * Copyright Nucleron R&D LLC 2016
 *
 * This file is licensed under the terms of YAPL,
 * see License.txt for details.
 */

#include "plc_backup.h"


void plc_backup_invalidate(void)
{
    //pwr_disable_backup_domain_write_protect();
    //PLC_BKP_VER1++;
    //pwr_enable_backup_domain_write_protect();
}


void plc_backup_validate(void)
{

}


int plc_backup_check(void)
{
    return 0; //Fail! Use dafaults!
}


void plc_backup_remind(unsigned int offset, unsigned int count, void *p)
{
    (void)offset;
    (void)count;
    (void)p;
}


void plc_backup_retain(unsigned int offset, unsigned int count, void *p)
{
    (void)offset;
    (void)count;
    (void)p;
}

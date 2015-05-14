/*
 * testsql.c
 *
 *  Created on: 2015年4月24日
 *      Author: yuan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sql.h"


int main(void) {

    Disk_Info disk_info;

	init_mysql();
    query_disks();        //测试磁盘查询
    print_result();
    free_result();

    query_disks_info("disk_001");         //测试磁盘内目录查询
    print_result();
    free_result();

    query_directory_info("20150424", "disk_001");     //测试目录内文件查询信息
    print_result();
    free_result();


    close_db(); // 关闭链接

    return EXIT_SUCCESS;
}





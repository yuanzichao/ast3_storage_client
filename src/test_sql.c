/*
 * testsql.c
 *
 *  Created on: 2015年4月24日
 *      Author: yuan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

#include "type_def.h"
#include "sql.h"


int main(void) {

	init_mysql();          //初始化数据库连接

	//获取系统当前时间并格式化
	time_t calendar_time = time(NULL);
	struct tm * tm_local = localtime(&calendar_time);
	char str_f_t [LEN];
	strftime(str_f_t, sizeof(str_f_t), "%G-%m-%d %H:%M:%S", tm_local);

	//初始化Disk_Info
    Disk_Info disk_info = {0, "disk_005", "5a9068d5a7bf4b3bbec918af44e9d4e0", "ext3/ext4", 1024.00, 300.00, "", 0, 0};
    sprintf(disk_info.recent_use_time, "%s", str_f_t);  //时间单独赋值

    insert_disk(disk_info);    //测试插入磁盘信息


    query_disks();        //测试磁盘查询
    print_result();
    free_result();

    query_disks_info("disk_001");         //测试磁盘内目录查询
    print_result();
    free_result();

    query_directory_info("20150424", "disk_001");     //测试目录内文件查询信息
    print_result();
    free_result();

    query_file_info("20150424_0001.fits", "20150424", "disk_001");     //测试文件查询信息
    print_result();
    free_result();


    close_db(); // 关闭链接

    return EXIT_SUCCESS;
}





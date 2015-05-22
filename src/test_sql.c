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

#include "sql.h"


int main(void) {

	//函数接口测试

	init_mysql();		//初始化数据库连接


	/***************************************************************************/
	/************************* 磁盘操作函数测试 **********************************/
	/***************************************************************************/
	printf("测试：查询所有硬盘信息\n");
	query_disks();		//查询所有硬盘信息
	print_result();
	free_result();

	printf("测试：获取磁盘ID\n");
	char *disk_id;
	disk_id = get_disk_id("disk_002");		//获取磁盘ID
	printf("disk_id==>>%s\n", disk_id);
	free_result();

	printf("测试：查询指定硬盘信息\n");
	query_disk("disk_002");		//查询指定硬盘信息
	print_result();
	free_result();

	printf("测试：获取db_disk_info\n");
	db_disk_info *disk_info;
	disk_info = db_disk_info__new();
	disk_info = get_disk_info("disk_002");		//获取db_disk_info
	printf("disk_id==>>%d && disk_name==>>%s\n", disk_info->disk_id, disk_info->disk_name);

	printf("测试：插入磁盘信息\n");
	db_disk_info *disk_info_01;
	disk_info_01 = db_disk_info__new();
	disk_info_01->disk_name = "disk_insert_test";
	disk_info_01->disk_uuid = "51bb74393f2646d7bd46b4427ade5e17";
	disk_info_01->disk_type = "ext3/ext4";
	disk_info_01->disk_capacity = 700.1;
	disk_info_01->disk_used = 300;
	time_t cur_time = time(NULL);		//获取系统当前时间并格式化
	disk_info_01->recent_use_time = cur_time;
	disk_info_01->disk_status = 0;
	disk_info_01->permisssion = 0;
	insert_disk(disk_info_01);			//插入磁盘信息

	printf("测试：更新磁盘信息\n");
	disk_info->disk_used = 100;		//使用上一步得到的db_disk_info
	update_disk(disk_info);			//更新磁盘信息

	printf("测试：查询硬盘内目录信息\n");
	query_disks_info("disk_002");			//查询硬盘内目录信息
	print_result();
	free_result();


    close_db(); // 关闭链接

    return EXIT_SUCCESS;
}





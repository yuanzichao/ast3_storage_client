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


	/***************************************************************************/
	/************************* 目录操作函数测试 **********************************/
	/***************************************************************************/
	printf("测试：获取目录ID\n");
	char *dir_id;
	dir_id = get_directory_id("20150424", "disk_001");		//获取目录ID
	printf("dir_id==>>%s\n", dir_id);
	free_result();

	printf("测试：获取db_directory_info\n");
	db_directory_info *dir_info;
	dir_info = db_directory_info__new();
	dir_info = get_directory_info("20150424", "disk_001");		//获取db_directory_info
	printf("dir_id==>>%d && dir_name==>>%s\n", dir_info->directory_id, dir_info->directory_name);

	/*
	 * 说明：
	 * 		在插入目录时，需要实时更新目录所在磁盘信息，
	 * 		包括 `disk_used`, `recent_use_time`, `disk_status`，
	 * 		操作流程：根据disk_name获取db_disk_info, 修改上述三个属性值，
	 * 		更新db_disk_info，调用update函数更新数据库。
	 */
	printf("测试：插入目录信息\n");
	db_directory_info *dir_info_01;
	dir_info_01 = db_directory_info__new();
	dir_info_01->directory_name = "20150522";
	dir_info_01->disk_uuid = "51bb74393f2646d7bd46b4427ade5e17";
	dir_info_01->disk_name = "disk_001";
	dir_info_01->parent_id = 0;
	dir_info_01->directory_size = 100;
	cur_time = time(NULL);		//获取系统当前时间并格式化
	dir_info_01->time = cur_time;
	dir_info_01->recent_use_time = cur_time;
	dir_info_01->permission = 0;
	dir_info_01->accessed_time = 0;
	dir_info_01->file_number = 0;
	insert_directory(dir_info_01);		//插入目录信息

	/*
	 * 说明：
	 * 		在更新目录信息时，如果涉及磁盘信息变化，需要实时更新目录所在磁盘信息，
	 * 		包括 `disk_used`, `recent_use_time`, `disk_status`，
	 * 		操作流程：根据disk_name获取db_disk_info, 修改上述三个属性值，
	 * 		更新db_disk_info，调用update函数更新数据库。
	 */
	printf("测试：更新目录信息\n");
	dir_info->accessed_time +=1;		//访问次数自动加1
	update_directory(dir_info);			//更新目录信息

	/*
	 * 说明：
	 * 		在查询目录信息时，需要更新目录信息，
	 * 		包括 `recent_use_time`, `accessed_time`
	 */
	printf("测试：查询目录内文件和目录信息\n");
	query_directory_info("20150424", "disk_001");	//查询目录内文件和目录信息
	print_result();
	free_result();


    close_db(); // 关闭链接

    return EXIT_SUCCESS;
}





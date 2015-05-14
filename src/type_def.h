/*
 * type_def.h
 *
 *  Created on: 2015年4月25日
 *      Author: yuan
 */

#ifndef SRC_TYPE_DEF_H_
#define SRC_TYPE_DEF_H_

#define LEN		1024

typedef struct {
	int directory_id;
	char directory_name[LEN];
	char disk_uuid[LEN];
	char disk_name[LEN];
	int parent_id;
	double directory_size;
	char time[LEN];
	char recent_use_time[LEN];
	int permission;
	int accessed_time;
	int file_number;
} Directory_Info;


typedef struct {
	int disk_id;
	char disk_name[LEN];
	char disk_uuid[LEN];
	char disk_type[LEN];
	double disk_capacity;
	double disk_used;
	char recent_use_time[LEN];
	int permission;
	int disk_status;
} Disk_Info;


typedef struct {
	int file_id;
	char file_name[LEN];
	char disk_uuid[LEN];
	int directory_id;
	char disk_name[LEN];
	char md5[LEN];
	double file_size;
	char location[LEN];
	char time[LEN];
	char recent_use_time[LEN];
	int permission;
	int file_type;
	int accessed_time;
} File_Info;


#endif /* SRC_TYPE_DEF_H_ */

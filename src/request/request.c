/*
 * request.c
 *
 *  Created on: 2015年7月20日
 *      Author: yuan
 */

#include "request.h"

int
gen_request(char *fileName, char *dirName, char *diskName) {

	cJSON * requests = NULL;
	cJSON * requests_arr = NULL;
	cJSON * request = NULL;
	cJSON * files_arr = NULL;
	cJSON * file[ASSOCIATE_FILES] = {};

	requests = cJSON_CreateObject();

	requests_arr = cJSON_CreateArray();

	request = cJSON_CreateObject();

	files_arr = cJSON_CreateArray();


	int i;
	for(i=0; i<ASSOCIATE_FILES; i++){
		file[i] = cJSON_CreateObject();
	}


	for(i=0; i<ASSOCIATE_FILES; i++){
		cJSON_AddStringToObject(file[i], "filename", fileName);
	}


	for(i=0; i<ASSOCIATE_FILES; i++){
		cJSON_AddItemToObject(files_arr, "test", file[i]);
	}

	cJSON_AddStringToObject(request, "diskname", diskName);
	cJSON_AddStringToObject(request, "dirname", dirName);

	cJSON_AddItemToObject(request, "files", files_arr);

	cJSON_AddItemToObject(requests_arr, "test", request);

	cJSON_AddItemToObject(requests, "requests", requests_arr);


	request_str = cJSON_Print(requests);

	printf("%s\n", request_str);



    return EXIT_SUCCESS; // 返回成功
}


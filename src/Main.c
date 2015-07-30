//头文件区域
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include"virtualdirectory.h"
#include"sql.h"

//主函数
int main()
{

	init_mysql();//初始化数据库

	//声明命令
	char input[MAX_BUF_SIZE];
	char curr_disk[MAX_BUF_SIZE];
	char curr_dir[MAX_BUF_SIZE];
	char curr_dirId[MAX_BUF_SIZE];
    printf("您可通过help获取帮助\n");
    printf(">>>>");

    memset(curr_disk, 0, sizeof(char)*MAX_BUF_SIZE);
    memcpy(curr_disk, "home", sizeof(char)*4);
    memset(curr_dir, 0, sizeof(char)*MAX_BUF_SIZE);
    memcpy(curr_dir, "unknown", sizeof(char)*7);
    memset(curr_dirId, 0, sizeof(char)*MAX_BUF_SIZE);
    memcpy(curr_dirId,"0",sizeof(char)*1);

	while(1){

        memset(input, 0,sizeof(char)*MAX_BUF_SIZE);
		fgets(input,MAX_BUF_SIZE,stdin);   //获取用户输入指令，以回车结束

		key=format(&input);//命令解析：主要对input进行格式化处理
		printf("%s\n",curr_dir);

		//执行响应的动作，key为命令解析后结果，决定调用哪个函数
		switch (key) {

			case 0://浏览目录结构
			{
				if(strcmp(curr_disk,"home")==0)
					excute_show();    //执行show操作，列出磁盘信息
				else //if(strcmp(curr_dir,"unknown")==0)
				{
					//excute_list(curr_disk);//执行list操作，列出目录信息
				    excute_list_directory(curr_disk,curr_dirId);
				    excute_list_file(curr_disk,curr_dirId);

				}
				//else excute_ls(curr_dir,curr_disk);//执行ls操作，列出文件信息
				break;
			}
			case 1://浏览目录基本信息
			{
				if(strcmp(curr_disk,"home")==0)
					excute_show_primary();
				else //if(strcmp(curr_dir,"unknown")==0)
				{
					excute_list_primary_directory(curr_disk,curr_dirId);
					excute_list_primary_file(curr_disk,curr_dirId);
				}

				//else excute_ls_primary(curr_dir,curr_disk);
				break;
			}
			case 2://浏览指定文件基本信息
			{
				//excute_ls_file_primary(fileName,curr_dir,curr_disk);
				excute_list_primary_oneFile(curr_disk,curr_dirId,fileName);
				break;
			}
			case 3://浏览目录详细信息
			{
				if(strcmp(curr_disk,"home")==0)
					excute_show_all();
				else
				{
					excute_list_all_directory(curr_disk,curr_dirId);
					excute_list_all_file(curr_disk,curr_dirId);
				}
				break;
			}
			case 4://浏览指定文件详细信息
			{
				excute_list_all_oneFile(curr_disk,curr_dirId,fileName);
				break;
			}
			case 5://返回根目录
			{
				memset(curr_disk, 0, sizeof(char)*MAX_BUF_SIZE);
				memcpy(curr_disk, "home", sizeof(char)*4);
			    memset(curr_dir, 0, sizeof(char)*MAX_BUF_SIZE);
			    memcpy(curr_dir, "unknown", sizeof(char)*7);
				break;
			}
			case 6://返回父目录
			{
				excute_return_parent_directory();
				memset(curr_disk, 0, sizeof(char)*MAX_BUF_SIZE);
				memcpy(curr_disk, currentDisk, sizeof(currentDisk));
				memset(curr_dir, 0, sizeof(char)*MAX_BUF_SIZE);
				memcpy(curr_dir, currentDirectory, sizeof(currentDirectory));
				break;
			}
			case 7://切换到指定目录
			{
				int test=excute_change_directory(curr_disk,currentDirectory,curr_dirId);
				if(test==0)
				{
					memset(curr_dir, 0, sizeof(char)*MAX_BUF_SIZE);
				    memcpy(curr_dir, currentDirectory, strlen(currentDirectory));
				    memset(curr_dirId, 0, sizeof(char)*MAX_BUF_SIZE);
				    memcpy(curr_dirId, currentDirId, strlen(currentDirId));
				}
				 break;
			}
			case 8://打开指定硬盘
			{
				printf("%s\n",curr_dir);
				memset(curr_disk, 0, sizeof(char)*MAX_BUF_SIZE);
				memcpy(curr_disk, currentDisk, strlen(currentDisk));
				printf("%s\n",curr_dir);
				break;
			}
			case 9://显示工作目录
			{
				if(strcmp(curr_dir,"unknown")==0)
					printf("%s\n",curr_disk);
				else
				    printf("%s\n",curr_dir);
				break;
			}
			case 10://在当前目录下搜索符合时间范围内的文件
			{
				query_time_from_curr(curr_disk,curr_dirId,startTime, endTime);
				break;
			}
			case 11:
			{
				query_time_from_home(startTime, endTime);
				break;
			}
			case 12:
			{
				query_location(start_ra, end_ra, start_dec, end_dec);
				break;
			}
			case 13:
			{
				query_location_curr(curr_dir,curr_disk,start_ra, end_ra, start_dec, end_dec);
				break;
			}
			/*case 11:
			{
				excute_ls_file_wildcard(fileName,curr_dir,curr_disk);
				break;
			}*/
			case 14:
			{
				excute_copy_file();
				break;
			}
			default :
			{
				excute_help();
				break;
			}

		}//指令执行结束，重新循环

		//printf("\n");
        printf("%s",curr_disk);
	    printf("%s","/");
		if(strcmp(curr_dir,"unknown")!=0)
		{
			printf("%s",curr_dir);
			printf("%s","/");
		}


	}


}














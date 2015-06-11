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
	char input[100];
	char curr_disk[100];
	char curr_dir[100];
    printf("您可通过help获取帮助\n");
    printf(">>>>");

    memset(curr_disk, 0, sizeof(char)*100);
    memcpy(curr_disk, "home", sizeof(char)*4);
    memset(curr_dir, 0, sizeof(char)*100);
    memcpy(curr_dir, "unknown", sizeof(char)*7);

	while(1){

        memset(input, 0,sizeof(char)*100);
		fgets(input,100,stdin);   //获取用户输入指令，以回车结束

		key=format(&input);//命令解析：主要对input进行格式化处理

		//执行响应的动作，key为命令解析后结果，决定调用哪个函数
		switch (key) {

			case 0://浏览目录结构
			{
				if(strcmp(curr_disk,"home")==0)
					excute_show();    //执行show操作，列出磁盘信息
				else if(strcmp(curr_dir,"unknown")==0)
					excute_list(curr_disk);//执行list操作，列出目录信息
				else
					excute_ls(curr_dir,curr_disk);//执行ls操作，列出文件信息
				break;
			}
			case 1://浏览目录详细信息
			{
				if(strcmp(curr_disk,"home")==0)
					excute_show_all();
				else if(strcmp(curr_dir,"unknown")==0)
					excute_list_all(curr_disk);
				else
					excute_ls_all(curr_dir,curr_disk);
				break;
			}
			case 2://返回根目录
			{
				memset(curr_disk, 0, sizeof(char)*100);
				memcpy(curr_disk, "home", sizeof(char)*4);
			    memset(curr_dir, 0, sizeof(char)*100);
			    memcpy(curr_dir, "unknown", sizeof(char)*7);
				break;
			}
			case 3://返回父目录
			{
				/*excute_return_parent_directory(curr_disk,curr_dir);
				memset(curr_dir, 0, sizeof(char)*100);
				memcpy(curr_dir, currentDirectory, strlen(currentDirectory));*/
				memset(curr_disk, 0, sizeof(char)*100);
				memcpy(curr_disk, "home", sizeof(char)*4);
				memset(curr_dir, 0, sizeof(char)*100);
				memcpy(curr_dir, "unknown", sizeof(char)*7);
				break;
			}
			case 4://打开指定硬盘
			{
				memset(curr_dir, 0, sizeof(char)*100);
				memcpy(curr_dir, currentDirectory, strlen(currentDirectory));
				break;
			}
			case 5://切换到指定目录
			{
				memset(curr_disk, 0, sizeof(char)*100);
				memcpy(curr_disk, currentDisk, strlen(currentDisk));
				break;
			}
			case 6:
			{
				excute_ls_file(fileName,curr_dir,curr_disk);
				break;
			}
			case 7:
			{
				printf("%s",curr_dir);
				break;
			}
			case 8:
			{
				query_time(startTime, endTime);
				break;
			}
			case 9:
			{
				query_location(start_ra, end_ra, start_dec, end_dec);
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














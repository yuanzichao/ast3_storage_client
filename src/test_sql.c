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

	while(1){

        memset(input, 0,sizeof(char)*100);
		fgets(input,100,stdin);   //获取用户输入指令，以回车结束

		key=format(&input);//命令解析：主要对input进行格式化处理

		//执行响应的动作，key为命令解析后结果，决定调用哪个函数
		switch (key) {

			case 0:
				excute_show();    //执行show操作
				break;
			case 1:
				//excute_use(currentDisk);    //执行use操作
				printf("Disk changed\n");
				memset(curr_disk, 0, sizeof(char)*100);
				memcpy(curr_disk, currentDisk, strlen(currentDisk));
				break;
			case 2:
				excute_list(curr_disk);
				break;
			case 3:
				printf("Directory changed\n");
				memset(curr_dir, 0, sizeof(char)*100);
				memcpy(curr_dir, currentDirectory, strlen(currentDirectory));
				break;
			case 4:
				excute_ls(curr_disk, curr_dir);
				break;
			case 5:
				//excute_pwd();
				printf("%s\n", curr_dir);
				break;
			case 6:
				query_time(startTime, endTime);
				break;
			case 7:
				excute_help();
				break;
		}//指令执行结束，重新循环

	}


}














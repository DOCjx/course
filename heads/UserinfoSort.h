#pragma once
#pragma once
//int cName[25];//用于用户信息的检索,记录二十六的首字母对应的数组下标位置

/*
此文件包含
1.用户按姓名的排序函数 Y
2.插入用户到所得按姓名排序的邻接表的函数 Y
3.用户按学号排序函数，采用链表的快排算法
*/
#define _CRT_SECURE_NO_DEPRECATE
#define USER_MAX_SIZE 24
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infoConst.h"

void quickSortById(userLink start); //对用户链按id快排
void quickSortByName(userLink start);//对用户链按姓名快排

int showInfoByList(userLink start, int i, int num,int flag);//用户信息分页显示，显示第i页(每页num）条信息
//注:目前分页函数只能分页显示所有查找到的信息，还应对登陆等信息保存

void infoListControl(userLink start, int i, int num);//用户信息显示控制函数
int getIndex(char* str1, char* str2);//朴素模式匹配，返回str2在str1中出现的起始位置
userLink searchByStr(userLink start, char* str2);//模糊查询,（目前功能)查找所有含str2的姓名,返回新链
void readUserData(char* fileName, userLink uhead);//从文件读取用户课程信息
int isCorrectInfo(userNode user, userSaveList uLink[]);//用户登陆验证函数
void login(userSaveList uLink[]);//用户登陆函数
userLink searchById(userLink start, userLink pre, int id);//按id查找用户,找到当前节点和其前一个节点,学号已有序


void insertToUserListByName(userLink head, userLink p);//将信息按姓名插入到用户链中
void insertToUserLinkById(userLink start, userLink uInfo);//将信息按id插入到用户链中
void insertToUserSaveList(userSaveList usLink[], userLink p);//插入信息到用户信息存储链表
userLink UserSaveListToUserLink(userSaveList usLink[]);//将用户信息存储链转化为用户链
void userInfoSort(userSaveList usLink[], userLink uLink);//用户信息存储按姓名链表排序
int getCorrectInsertIndex(userLink p);//得到按姓名排序的文件对应的下标




void readUserData(char* fileName, userLink uhead) {//读取用户课程信息
	FILE* fp;
	errno_t err = fopen_s(&fp,fileName, "r");//fopen_s用法
									  /*
									  需要定义一个变量errno_t err,然后 err = fopen_s(&fp,filename,"w").fopen_s打开文件成功返回0，失败返回非0
									  */
	if (err != 0) return;     //文件打开失败
	else
	{
		int num, i = 0;
		coursePoint head, p, q;
		userLink up;
		while (!feof(fp)) {//feof函数会多读一次,所以应该对第一次读取数据进行判断,验证是否为空
			up = (userLink)malloc(sizeof(userList));
			up->info = (userNode*)malloc(sizeof(userNode));
			up->flag = 0;
			up->flag1 = 0;
			if (fscanf(fp, "%d", &up->info->id) == EOF) {
				free(up->info);
				free(up);
				break;
			}
			fscanf(fp, "%d%s%s%s%s%s",
				&up->info->roleId,
				&up->info->name,
				&up->info->passwd,
				&up->info->institute,
				&up->info->phoneNum,
				&up->info->synopsis);
			fscanf(fp, "%d", &num);//读取总共有的课程数
								   /*
								   fscanf_s的用法,fscanf(fp,"%d",&var,sizeof(int))需要指定长度

								   */
			if (num>0) {
				up->info->firstChild = (coursePoint)malloc(sizeof(courseNode));
				head = up->info->firstChild;
				q = head;
				fscanf(fp, "%d", &q->counter);
				fscanf(fp, "%d", &q->courseId);
				fscanf(fp, "%s", &q->time);
				i++;
				while (i<num) {
					p = (coursePoint)malloc(sizeof(courseNode));
					fscanf(fp, "%d", &p->counter);
					fscanf(fp, "%d", &p->courseId);
					fscanf(fp, "%s", &p->time);
					q->next = p;
					q = p;
					i++;
				}
				q->next = NULL;
			}
			else {
				up->info->firstChild = NULL;
			}
			up->next = uhead->next;
			uhead->next = up;
		}
		fclose(fp);
	}

}

void writeInfoToFile(char* fileName, userLink head) {//将信息写入文件
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp,fileName, "w");//fopen_s用法
	if (head) {//若用户链不为空,将信息写入到对应文件中
		if (err != 0) return;     //文件打开失败
		else {
			userLink p = head;
			while (p) {
				fprintf(fp, "%d %d %s %s %s %s %s ",
					p->info->id,
					p->info->roleId,
					p->info->name,
					p->info->passwd,
					p->info->institute,
					p->info->phoneNum,
					p->info->synopsis
                );
				if (p->info->firstChild) {
					//fprintf(fp, "%d ", p->info->firstChild->counter);
					coursePoint q = p->info->firstChild;
					while (q) {
						fscanf(fp, "%d ", q->counter);
						fscanf(fp, "%d ", q->courseId);
						fscanf(fp, "%s ", q->time);
						q = q->next;
					}
					fscanf(fp, "\n");
				}
				else {
					fprintf(fp, "0");
					if (p->next)
						fprintf(fp, "\n");
				}
				p = p->next;

			}
		}
		fclose(fp);

	}
	else
		fprintf(fp, " ");

}

void writeUserLinkInfoToFile(userSaveLink usLink) {//将对应的按姓名排好序的文件写入到对应文件中
	for (int i = 0; i < USER_MAX_SIZE; i++)
		writeInfoToFile(fileArr[i], usLink[i].userHead);
}


void login(userSaveList uLink[]) {//用户登陆界面
	userNode user;
	int type;//用户身份类型变量
	int counter = 3;//计数器用来统计用户信息输入错误次数
	printf("**************************************************************************\n");
	printf("**************************************************************************\n");
	printf("                      选课系统用户登陆:\n");
	printf("**************************************************************************\n");
	printf("**************************************************************************\n");
	printf("                 请输入您的用户类型: 0 学生 1 教职工\n");
	while (scanf("%d", &type) != EOF) {
		getchar();
		if (type >= 0 && type <3) {//用户身份类型正确
			printf("用户名:\n");
			scanf("%s", &user.name);
			getchar();
			printf("密码:\n");
			scanf("%s", &user.passwd);
			getchar();
			if (isCorrectInfo(user, uLink) == 1) {
				system("cls");
				printf("欢迎登陆\n");
				return;
			}
			else  if (isCorrectInfo(user, uLink) == 0) {
				while (counter >= 1) {
					printf("\n密码输入错误,请重新输入\n");
					printf("您还有%d次机会\n", counter);
					printf("用户名:%s\n", user.name);
					printf("密码:");
					scanf("%s", &user.passwd);
					getchar();
					counter--;
					if (isCorrectInfo(user, uLink)) {
						system("cls");
						printf("欢迎登陆\n");
						return;
					}

				}
				system("cls");
				break;

			}
			else {
				printf("用户名不存在\n");
				printf("用户类型:\n");
			}
		}
		else {
			printf("身份类型错误,请输入正确的身份类型(0 学生 1 教职工)\n");
			printf("用户类型:\n");
		}
	}
}

int isCorrectInfo(userNode user, userSaveList uLink[]) {//用户身份验证
														//用户名不存在返回-1,密码错误返回0,成功登陆返回1
	int i = USER_MAX_SIZE - 1;
	while (strcmp(user.name, uLink[i].cName)<0)
		//若当前节点比链表头节点信息小则往后找
		i--;
	userLink u = uLink[i].userHead;
	while (u && strcmp(u->info->name, user.name) != 0) {
		u = u->next;
	}
	if (u) {//找到符合的条件时
		if (strcmp(user.passwd, u->info->passwd) == 0)
			return 1;
		else
			return 0;
	}
	return -1;

}


//信息测试函数
void print(userLink uhead) {
	userLink up;
	up = uhead->next;
	while (up) {
		if (up->info) {
			printf("学号%d ", up->info->id);
			printf("角色号%d ", up->info->roleId);
			printf("姓名%s ", up->info->name);
			printf("密码%s ", up->info->passwd);
			printf("学院%s ", up->info->institute);
			printf("电话号码%s ", up->info->phoneNum);
			printf("简介%s ", up->info->synopsis);
			coursePoint p;
			p = up->info->firstChild;
			if (p->next) {
				printf("当前课程有: \n");
				/*
				此处尚未对课程信息进行测试
				*/
			}
			else {
				printf("当前无课程\n");
			}
		}
		up = up->next;

	}
}


//对用户姓名排序函数进行测试
void usPrint(userSaveList uLink[]) {
	for (int i = 0; i <= USER_MAX_SIZE - 1; i++) {
		userLink up = uLink[i].userHead;
		while (up) {
			printf("%s  ", uLink[i].cName);
			printf("学号%d ", up->info->id);
			printf("角色号%d ", up->info->roleId);
			printf("姓名%s ", up->info->name);
			printf("密码%s ", up->info->passwd);
			printf("学院%s ", up->info->institute);
			printf("电话号码%s ", up->info->phoneNum);
			printf("简介%s ", up->info->synopsis);
			coursePoint p;
			p = up->info->firstChild;
			if (p->next) {
				printf("当前课程有: \n");
				/*
				此处尚未对课程信息进行测试
				*/
			}
			else {
				printf("当前无课程\n");
			}
			up = up->next;

		}
	}
}

//将信息按姓名插入到用户链中
//前提是姓名已经有序
void insertToUserListByName(userLink head, userLink p) {
	userLink q = head->next;
	userLink pre = head;
	while (q&&strcmp(q->info->name, p->info->name) <= 0) {
		pre = q;
		q = q->next;
	}
	p->next = q;
	pre->next = p;

}

//将信息按姓名插入到信息链中
//前提是id已经有序
void insertToUserLinkById(userLink start,userLink uInfo) {
	userLink p = start->next;
	userLink pre = start;
	while (p&&p->info->id < uInfo->info->id) {
		pre = p;
		p = p->next;
	}
	uInfo->next = p;
	pre->next = uInfo;

}

void quickSortById(userLink start) {//对用户链按id快排
	userLink p, q, pre;
	q = start->next;
	if (q && !q->flag) {//元素不只一个时
		pre = q;
		p = q->next;//p用来查找比q大的节点
		q->flag = 1;
		q->flag1 = 0;
		while (p && !p->flag) {
			while (p && !p->flag&&p->info->id>q->info->id) {//查找第一个大于p->info的元素
				pre = p;
				p = p->next;
			}
			if (p && !p->flag) {//找到后将其头插
				pre->next = p->next;
				p->next = start->next;
				start->next = p;
				p = pre->next;
			}
		}
		quickSortById(start);
		quickSortById(q);
	}

}

void quickSortByName(userLink start) {//对用户链按姓名快排
	userLink p, q, pre;
	q = start->next;
	if (q && !q->flag1) {//元素不只一个时
		pre = q;
		p = q->next;//p用来查找比q大的节点
		q->flag1 = 1;
		q->flag = 0;
		while (p && !p->flag1) {
			while (p && !p->flag1&&strcmp(p->info->name,q->info->name)>0) {//查找第一个大于p->info的元素
				pre = p;
				p = p->next;
			}
			if (p && !p->flag1) {//找到后将其头插
				pre->next = p->next;
				p->next = start->next;
				start->next = p;
				p = pre->next;
			}
		}
		quickSortByName(start);
		quickSortByName(q);
	}
}


//用户按学号查找
userLink searchById(userLink start,userLink pre,int id) {
	userLink p = start->next;
	pre = start;
	while (p&&p->info->id < id)
		p = p->next;
	if (p&&p->info->id == id)
		return p;
	else
		return NULL;
}
userLink searchByStr(userLink start,char* str2) {//返回找到后的新链
	userLink newLink = (userLink)malloc(sizeof(userList));//新链的头节点
	userLink p = start->next;
	userLink r;
	newLink->next = NULL;
	r = newLink;
	//判断str2是否是某个信息的子串
	while (p) {
		/*
		//假设
		//按姓名查找
		*/
		if (getIndex(p->info->name,str2)!=-1) {//查找到后将信息拷贝到新链中
			//将新节点尾插到新链中
			userLink q = (userLink)malloc(sizeof(userList));
			q->info = p->info;
			q->flag = p->flag;
			q->next = NULL;
			r->next = q;
			r = q;
		}
		p = p->next;
	}
	return newLink;
}
void userInfoSort(userSaveList usLink[], userLink uLink) {//对所得用户信息的链按名字进行排序
	int i;
	//对用户信息链进行初始化
	for (i = 0; i <USER_MAX_SIZE; i++) {
		if (i == 0)
			strcpy(usLink[i].cName, " ");
		else
			strcpy(usLink[i].cName, arr[i - 1]);
		usLink[i].userHead = NULL;
	}
	//对所得用户信息链进行遍历,将其加入到存储用户信息链中
	userLink p;//要插入节点
	p = uLink->next;
	while (p) {
		//取下节点将其插入到对应的存储链中
		uLink->next = p->next;
		p->next = NULL;
		insertToUserSaveList(usLink, p);
		p = uLink->next;
	}
}


/*
	得到按姓名插入的文件的下标
*/
int getCorrectInsertIndex(userLink p) {
	for (int i = 0; i < USER_MAX_SIZE -2; i++) {
		if (strcmp(arr[0], p->info->name) >= 0)
			return 0;
		else if (strcmp(arr[USER_MAX_SIZE - 2], p->info->name) <= 0)
			return USER_MAX_SIZE - 1;
		else if (strcmp(arr[i], p->info->name) <= 0 && strcmp(arr[i + 1], p->info->name) > 0)
			return i + 1;

	}
	return -1;
}

void insertToUserSaveList(userSaveList usLink[], userLink p){//插入p所指向的一个节点到用户信息链中

	for (int i = 1; i < USER_MAX_SIZE - 1; i++) {
		if (strcmp(usLink[i].cName, p->info->name) >= 0) {//若当前姓名小于啊

			if (!usLink[i - 1].userHead)//当前头节点为空时直接插入
				usLink[i - 1].userHead = p;
			else {//不为空时，找到合适的地方插入
				userLink q, pre; //q,pre用来查找合适的位置
				pre = NULL;
				q = usLink[i - 1].userHead;
				while (q&& strcmp(p->info->name, q->info->name) > 0) {
					//当当前节点姓名小于要插入节点姓名时往后查找
					pre = q;
					q = q->next;
				}
				if (pre) { //若所插入节点不是第一个节点
					pre->next = p;
					p->next = q;
				}
				else {
					p->next = usLink[i - 1].userHead;
					usLink[i - 1].userHead = p;
				}
			}
			break;
		}
		else if (strcmp(usLink[USER_MAX_SIZE - 1].cName, p->info->name) <= 0) {//后一个表头姓名大于当前表头

			if (!usLink[USER_MAX_SIZE - 1].userHead)//当前头节点为空时直接插入
				usLink[USER_MAX_SIZE - 1].userHead = p;
			else {//不为空时，找到合适的地方插入
				userLink q, pre; //q,pre用来查找合适的位置
				pre = NULL;
				q = usLink[USER_MAX_SIZE - 1].userHead;
				while (q&& strcmp(p->info->name, q->info->name) > 0) {
					//当当前节点姓名小于要插入节点姓名时往后查找
					pre = q;
					q = q->next;
				}
				if (pre) { //若所插入节点不是第一个节点
					pre->next = p;
					p->next = q;
				}
				else {
					p->next = usLink[USER_MAX_SIZE - 1].userHead;
					usLink[USER_MAX_SIZE - 1].userHead = p;
				}
			}
			break;
		}
		else if (strcmp(usLink[i].cName, p->info->name) <= 0 && strcmp(usLink[i + 1].cName, p->info->name) > 0) {//当用户信息大于等于当前头节点信息
																												 //并且小于下一个头节点信息时，将其插入
			if (!usLink[i].userHead)//当前头节点为空时直接插入
				usLink[i].userHead = p;
			else {//不为空时，找到合适的地方插入
				userLink q, pre; //q,pre用来查找合适的位置
				pre = NULL;
				q = usLink[i].userHead;
				while (q&& strcmp(p->info->name, q->info->name) > 0) {
					//当当前节点姓名小于要插入节点姓名时往后查找
					pre = q;
					q = q->next;
				}
				if (pre) { //若所插入节点不是第一个节点
					pre->next = p;
					p->next = q;
				}
				else {
					p->next = usLink[i].userHead;
					usLink[i].userHead = p;
				}
			}
			break;
		}
	}
}

userLink UserSaveListToUserLink(userSaveList usLink[]) {
	userLink head;
	int counter = 0;//用于计数
	head = (userLink)malloc(sizeof(userList));
	for (int i = 0; i < USER_MAX_SIZE; i++) {
		head->info = NULL;
		head->next = NULL;
		readUserData(fileArr[i],head);
		usLink[i].userHead = head->next;
	}
	head->next = NULL;
	//将用户存储信息链转化为用户链
	userLink p, pre;
	p = pre = NULL;
	for (int i = 0; i < USER_MAX_SIZE; i++) {
		if (usLink[i].userHead) {
			counter++;
			if (counter == 1)
				head->next = usLink[i].userHead;
			if (pre) {
				pre->next = usLink[i].userHead;
				pre = p = NULL;
			}
			pre = p = usLink[i].userHead;
			while (p) {
				pre = p;
				p = p->next;
			}
		}
	}
	return head;
}

/*
分页显示函数：
1.按姓名，分页显示用户信息
2.按学号,分页显示用户信息
3.将查询到的结果分页显示

*/

/*
	待优化，开始时每次从头查找效率不高
*/
void infoListControl(userLink start, int i, int num) {
	char a;
	int j;
	j = showInfoByList(start, i, num,0);//显示信息
	while (1) {
		a = getchar();
		getchar();
		if (a == 'u'|| a == 'U') {//上页
			i--;
			j = showInfoByList(start, i, num,0);
			if (j != 0)
				i++;
		}
		else if (a == 'd'||a == 'D') {//下页
			i++;
			j = showInfoByList(start, i, num,0);
			if (j != 0)
				i--;
		}
		else if (a == 'e' || a == 'E') {//退出
			break;

		}
		else if (a == 'g' || a == 'G') {
			int d;
			printf("请输入要跳转的页面:\n");
			scanf("%d", &d);
			getchar();
			showInfoByList(start, d, num, 1);

		}
		else{
			printf("输入信息不合法,请重新输入\n");
			printf("\n\n按u(上)d(下)键翻页,输入e退出\n");
			printf("输入G可进行页面跳转\n");
		}
	}
}
//显示用户id信息
//通过栈保存上次页面信息,方便回退
int showInfoByList(userLink start,int i,int num,int flag) {//分页显示信息
//flag用于标识是否是直接查找
//从(i-1)*num+1开始,显示num个信息
//显示第i页的信息
//每页显示的信息条数
//课程信息,用户信息
	int j = 0;
	int counter = 0;
	userLink p = start->next;
	//找到开始位置

	if (i <= 0) {
		if (flag == 1)
			printf("查找信息页数的下标错误，请输入大于0的整数作为起始下标\n");
		else
			printf("当前已是首页\n");
		return -1;
	}
	system("cls");
	while (p&&j < ((i - 1)*num + 1)) {
		p = p->next;
		j++;
	}

	if (p) {
		while (p&&counter < num) {
			printf("学号%d ", p->info->id);
			printf("角色号%d ", p->info->roleId);
			printf("姓名%s ", p->info->name);
			printf("密码%s ", p->info->passwd);
			printf("学院%s ", p->info->institute);
			printf("电话号码%s ", p->info->phoneNum);
			printf("简介%s \n", p->info->synopsis);
			p = p->next;
			counter++;
		}
		while(counter < num+2) {
			printf("\n");//不够时填充\n
			counter++;
		}
		printf("                                             第%d页\n", i);
		printf("\n\n按u(上)d(下)键翻页,输入e退出\n");
		printf("输入G可进行页面跳转\n");
		return 0;
		/*
			将信息域进栈保存，方便翻页显示
		*/
	}
	else {
		printf("没有第%d页\n", i);
		printf("\n\n按u(上)d(下)键翻页,输入e退出\n");
		printf("输入G可进行页面跳转\n");
		return 1;
	}
}

//按信息模糊查找
/*
	返回子串str2在str1中出现的位置
*/
//朴素模式匹配
int getIndex(char* str1, char* str2) {
	int length1 = strlen(str1);
	int length2 = strlen(str2);
	int k, i,j;
	i = 0;
	while (i <=length1 - length2)
	{
		k = i;                        //记录匹配起始位置
		j = 0;
		while (j<=length2&&str2[i] == str1[j])
		{
			i++;
			j++;
		}
		if (j == length2) return k;   //查询成功
		i = k + 1;
	}
	return -1;                      //查询失败
}



userLink searchByStr(userLink start,char* str2) {//返回找到后的新链
	userLink newLink = (userLink)malloc(sizeof(userList));//新链的头节点
	userLink p = start->next;
	userLink r;
	newLink->next = NULL;
	r = newLink;
	//判断str2是否是某个信息的子串
	while (p) {
		/*
		//假设
		//按姓名查找
		*/
		if (getIndex(p->info->name,str2)!=-1) {//查找到后将信息拷贝到新链中
			//将新节点尾插到新链中
			userLink q = (userLink)malloc(sizeof(userList));
			q->info = p->info;
			q->flag = p->flag;
			q->next = NULL;
			r->next = q;
			r = q;
		}
		p = p->next;
	}
	return newLink;
}


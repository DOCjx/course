#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "struct.h"
int role;//用户角色
int userNum;//用户id
int isLogout;//标记是否是注销操作
userLink globalHead;
//conf
int systemStatus;//当前系统状态
int passLength;//密码长度
int loginTimes;//用户尝试登入次数
int Admin;//管理员用户名
char AdminPass[10];//管理员密码
int pageMax;//每页显示数据条数
#define USER_MAX_SIZE 24

//firstChild
//日期结构体类型
typedef struct datenode
{
    short year;
    short month;
    short day;
}date;

char *arr[23] = {
	"啊","芭","擦","搭","蛾","发","噶","哈","击","喀","垃","妈", "拿", "哦", "啪", "期", "然", "撒", "塌","挖","昔","压","匝"
};

char * fileArr[24] = {//用户信息存储文件数组
	"Data/users/user1.txt","Data/users/user2.txt","Data/users/user3.txt","Data/users/user4.txt","Data/users/user5.txt","Data/users/user6.txt","Data/users/user7.txt","Data/users/user8.txt",
	"Data/users/user9.txt","Data/users/user10.txt","Data/users/user11.txt","Data/users/user12.txt","Data/users/user13.txt","Data/users/user14.txt","Data/users/user15.txt","Data/users/user16.txt",
	"Data/users/user17.txt","Data/users/user18.txt","Data/users/user19.txt","Data/users/user20.txt","Data/users/user21.txt","Data/users/user22.txt","Data/users/user23.txt","Data/users/user24.txt"
};

char *roleArr[]={
                "学生",               //0
                "任课老师",           //1
                "教务处",             //2
                "超管",             //3
            };
char *systemStatusArr[]={
                "正常状态",    //0
                "选课状态",    //1
            };

void appStart();//开始选课系统
int login();//登入系统
int coursesSelect();//功能页入口
void showTitle(char *str, int n);//显示页头
void tip(char *str);//暂停提示
void linex(int x);//到第x行
int showMenu(char *arr[], int n);//输出菜单
void showtime(int k);//显示欢迎页
void clearInputBufer();//清除输入缓冲区


void readUserData(char* fileName, userLink uhead);//从文件读取用户信息
void readUserDataFromMultipleFiles(userSaveList usLink[]);//从多个文件中读取用户数据到用户信息存储链中
void writeInfoToFile(char* fileName, userLink head);//将信息写入用户文件
void writeUserLinkInfoToFile(userSaveList usLink[]);//将对应的按姓名排好序的文件写入到对应文件中

userLink UserSaveListToUserLink(userSaveList usLink[]);//将用户信息存储链转化为用户链

void quickSortById(userLink start); //对用户链按id快排
void quickSortByName(userLink start);//对用户链按姓名快排
int showInfoByList(userLink start, int i, int num,int flag);//用户信息分页显示，显示第i页(每页num）条信息
//注:目前分页函数只能分页显示所有查找到的信息，还应对登陆等信息保存
void infoListControl(userLink start, int i, int num);//用户信息显示控制函数
int getIndex(char* str1, char* str2);//朴素模式匹配，返回str2在str1中出现的起始位置

void insertToUserListByName(userLink head, userLink p);//将信息按姓名插入到用户链中
void insertToUserLinkById(userLink start, userLink uInfo);//将信息按id插入到用户链中
void insertToUserSaveList(userSaveList usLink[], userLink p);//插入信息到用户信息存储链表

void userInfoSort(userSaveList usLink[], userLink uLink);//用户信息存储按姓名链表排序
int getCorrectInsertIndex(char* name);//得到按姓名排序的文件对应的下标
userLink searchById(userLink start, userLink pre, int id);//按id查找用户,找到当前节点和其前一个节点,学号已有序
userLink searchByStr(userLink start, char* str2);//模糊查询,（目前功能)查找所有含str2的姓名,返回新链
void getnext(kmpstring p,int next[]);//求模式串p的next数组
int kmp(kmpstring t,kmpstring p,int next[]);//快速模式匹配算法
void showPlan(char *path);//输出培养方案
int creatPlan(plan *g,char *filename);//建立培养方案AOV网络的存储结构
void printPlan(plan g);//输出培养方案
instituteList getCourseNameById(int id, int type);//根据课程id找到名字，type 1 2 3分别是学院、专业、课程
void freeCourse(instituteList head);//清除带头节点的课程链
int fileToList(FILE *fp, instituteList head, int type);//将学院，专业和课程从文件中读成链表。传入带头节点空链表。type：1.2.3分别代表学院、专业、学科。返回读入数据条数
char* outMajorPlans(char s1[], int majorId);//根据专业id生成对应的保存路径，支持输入16进制和8进制
void findPlan(int action);//找到培养方案并返回
void sortCourses(instituteList head,int way,int flag);//对学院、专业和课程排序,传入带头结点链，第二个参数是按什么排序，第三个参数是降序还是升序
void planDetail(int path);//显示培养方案
int getCoursePage(instituteList head, int dateTotal, int type, int page);//培养方案分页函数
void strToArr(int arr[], char *str);//有序字符串转成数组
void searchCourse(instituteList head, int arr[], char temp[], int type);//根据用户输入进行查找
void courseShowByPage(instituteList head, int dateTotal, int type);//分页显示并进行相应操作
void printCourseRange(instituteList pageStart,instituteList pageEnd, int type);//打印一段范围的学院、专业和课程的信息
void delCourse(instituteList head, int arr[]);//删除数据操作
void managerCourse(int majorId);//安排课程
void addCoursesManager(int majorId);//添加学院中课程安排
classList printCourseManager(classList head, int courseId);//打印课程安排
void freeCourseManager(classList head);//删除课程安排链
void updataCourseManager(classList s, int type);//更新任课老师或时间
void deleteCourseManager(classList s, int type);//删除老师或时间
void addCourseManager(classList s, int type);//添加老师或时间
void readCourseFromFile(classList head, int courseId);//从文件中读取课程安排
void writeCourseToFile(classList head, int courseId);//将安排好的课程写如文件

void printNode(userLink u);//打印当前节点信
void searchByName(char * str);//通过名字精确查找用户
void freeUser(userLink start);//删除用户链
void searchManage(int i);//查找显示菜单
/*
void searchByName(char * str){
    int i;
	for (i = 0; i < USER_MAX_SIZE -2; i++) {
		if (strcmp(arr[0],str) >= 0)
			return 0;
		else if (strcmp(arr[USER_MAX_SIZE - 2],str) <= 0)
			return USER_MAX_SIZE - 1;
		else if (strcmp(arr[i],str) <= 0 && strcmp(arr[i + 1], str) > 0)
			return i + 1;

	}
	return -1;

}
*/
void freeUser(userLink start){
    userLink p,s;
    userNode* ip;
    coursePoint cp,cq;
    p = start;
    ip = p->info;
    s = p->next;
    free(ip);
    free(p);
    while(s){
        p = s;
        ip = p->info;
        cp = ip->firstChild;
        while(cp){
            cq = cp->next;
            free(cp);
            cp = cq;
        }
        s = s->next;
        free(ip);
        free(p);
    }
}

//在用户登陆时,每次先从用户名称文件中读取信息到链中，形成数据链,再从用户导入的文件中读取数据形成链
void readUserDataFromMultipleFiles(userSaveList usLink[]){//从多个文件中读取数据
    int i;
    userLink head;
    head = (userLink)malloc(sizeof(userList));
	for (i = 0; i < USER_MAX_SIZE; i++){
        head->info = NULL;
        head->next = NULL;
        readUserData(fileArr[i],head);
        usLink[i].userHead = head->next;
	}
	free(head);
}


//程序开始
void appStart(){
    //初始化是否注销
    isLogout = 0;
    //打印首页菜单
    char *menuArr[]={
                    "首页",
                    "登入",
                    ""
                };
    int loop=1;
    while( loop ){
        switch( showMenu(menuArr, 3) ){
            case 1: loop = login();
                    if( loop ) coursesSelect();//进入角色功能页
                    break;
            default: loop=0;
        }
        //初始化是否注销
        isLogout = 0;
    }
    showtime(1);
}
//清除输入缓冲区
void clearInputBufer(){
    char c;
    do{
            c = getchar();
    }while(c != '\n' && c != EOF);
}

//显示页头
void showTitle(char *str, int n){
    system("cls");
    linex(6);
    printf("\t\t\t%s",str);
    printf("\t\t\t=================================");
    while( n-- ) printf("=");
    printf("\n");
}

//暂停提示
void tip(char *str){
    int i;
    printf("%s ",str);
    for(i=0;i<5;i++){
        printf(">");
        Sleep(300);
    }
    for(i=0;i<6;i++){
        printf(">");
        Sleep(100);
    }
}
//到第n行
void linex(int x)
{
    int i;
    for (i=0;i<x-1;i++)
        putchar('\n');
}

/*
    @函数名称：showMenu      入口参数：arr第一项为菜单名字的数组，n为数组长度
    @函数功能：显示超市管理员菜单，返回用户选择
*/
int showMenu(char *arr[], int n)
{
    int c,i;
    system("cls");
    if( strcmp(arr[n-1],"") )printf("%s->%s",arr[n-1],arr[0]);
    linex(5);
    printf("\t\t\t  %s\n",arr[0]);
    printf("\t\t\t=================================\n");
    for(i=1; i<n-1; i++){
        printf("\t\t\t  %d\t%s\t\t\n",i,arr[i]);
    }
    printf("\t\t\t  0\t返回\t\t-1  注销\n");
    printf("\t\t\t=================================\n");
    printf("\t\t\t请输入选项[  ]\b\b\b");
    scanf("%d",&c);
    return c;
}


/*
    @函数名称：showtime          入口参数：int k模式选择
    @函数功能：显示时间欢迎
*/
void showtime(int k)
{
    time_t nowtime;
    struct tm *t;
    time(&nowtime);

    t=localtime(&nowtime);
    if (t->tm_hour>=5 && t->tm_hour<9)
        printf("早上好！");
    else
           if (t->tm_hour>=9 && t->tm_hour<12)
                  printf("上午好！");
           else
                   if (t->tm_hour>12 && t->tm_hour<18)
                        printf("下午好！");
                   else
                        printf("晚上好！");

    switch(k)
    {
        case 0: printf("欢迎进入选课系统！");        //进入系统时调用showtime(0);
            break;
        case 1: printf("谢谢使用选课系统！\n");      //退出系统时调用showtime(0);
                printf("当前时间: %s",  ctime(&nowtime));
            break;
    }
}

void readUserData(char* fileName, userLink uhead) {//读取用户课程信息

	FILE* fp;
	fp = fopen(fileName, "r");//fopen_s用法
									  /*
									  需要定义一个变量errno_t err,然后 err = fopen_s(&fp,filename,"w").fopen_s打开文件成功返回0，失败返回非0
									  */
	if (fp == NULL){
        printf("文件打开失败\n");
        return;
    }//文件打开失败
	else
	{
		int num;
		coursePoint head, p, q;
		userLink up;
		while (!feof(fp)) {//feof函数会多读一次,所以应该对第一次读取数据进行判断,验证是否为空
			up = (userLink)malloc(sizeof(userList));
			up->info = (userNode*)malloc(sizeof(userNode));
            up->info->firstChild = (coursePoint)malloc(sizeof(courseList));
            up->info->firstChild->next = NULL;
			up->flag = 0;
			up->flag1 = 0;
			fscanf(fp, "%d", &up->info->id);
            if (up->info->id == -1) {
				free(up->info);
				free(up);
				break;
			}
			fscanf(fp, "%d%s%s%s%s%s%d",
				&up->info->roleId,
				up->info->name,
				up->info->passwd,
				up->info->institute,
				up->info->phoneNum,
				up->info->synopsis,
				&up->info->counter
            );
			//fscanf(fp, "%d", &num);//读取总共有的课程数
								   /*
								   fscanf_s的用法,fscanf(fp,"%d",&var,sizeof(int))需要指定长度
								   */
            num = up->info->counter;
            if (num>0) {
                int i = 0;
                up->info->counter = num;
				head = up->info->firstChild;
				q = head;
				while (i<num) {
					p = (coursePoint)malloc(sizeof(courseList));
					//fscanf(fp, "%d", &p->counter);
					fscanf(fp, "%d", &p->courseId);
					fscanf(fp, "%s", p->time);
					q->next = p;
					q = p;
					i++;
				}
				q->next = NULL;
			}
			else
                up->info->counter = 0;
			up->next = uhead->next;
			uhead->next = up;
		}
		fclose(fp);
	}


}

void writeInfoToFile(char* fileName, userLink head) {//将信息写入文件
	FILE* fp;
	fp = fopen(fileName, "w");//fopen_s用法
	if (head) {//若用户链不为空,将信息写入到对应文件中
		if (fp == NULL) return;     //文件打开失败
		else {
			userLink p = head;
			while (p) {
				fprintf(fp, "%d %d %s %s %s %s %s %d ",
					p->info->id,
					p->info->roleId,
					p->info->name,
					p->info->passwd,
					p->info->institute,
					p->info->phoneNum,
					p->info->synopsis,
					p->info->counter
                );

				if (p->info->firstChild->next) {
                    coursePoint q = p->info->firstChild->next;
					while (q) {
						//fscanf(fp, "%d ", &q->counter);
						fprintf(fp, "%d ", q->courseId);
						fprintf(fp, "%s ", q->time);
						q = q->next;
					}
				}
				fprintf(fp, "\n");
				p = p->next;

			}
			fprintf(fp,"-1");
		}
    }
	else
		fprintf(fp, "-1");
    fclose(fp);

}

void writeUserLinkInfoToFile(userSaveLink usLink) {//将对应的按姓名排好序的文件写入到对应文件中
	int i;
	for (i = 0; i < USER_MAX_SIZE; i++){
		writeInfoToFile(fileArr[i], usLink[i].userHead);
    }
}


/*void login(userSaveList uLink[]) {//用户登陆界面
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
*/



//信息测试函数
void print(userLink uhead) {
	userLink up;
	up = uhead->next;
	while (up) {
		printNode(up);
		up = up->next;

	}
}


//对用户姓名排序函数进行测试
void usPrint(userSaveList uLink[]) {
    int i;
	for (i = 0; i <= USER_MAX_SIZE - 1; i++) {
		userLink up = uLink[i].userHead;
		while (up) {
			printf("%s  ", uLink[i].cName);
			printNode(up);
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
    quickSortById(start);
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
int getCorrectInsertIndex(char* name) {
    int i;
	for (i = 0; i < USER_MAX_SIZE -2; i++) {
		if (strcmp(arr[0], name) >= 0)
			return 0;
		else if (strcmp(arr[USER_MAX_SIZE - 2], name) <= 0)
			return USER_MAX_SIZE - 1;
		else if (strcmp(arr[i], name) <= 0 && strcmp(arr[i + 1], name) > 0)
			return i + 1;

	}
	return -1;
}

void insertToUserSaveList(userSaveList usLink[], userLink p){//插入p所指向的一个节点到用户信息链中
    int i;
	for ( i= 1; i < USER_MAX_SIZE - 1; i++) {
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
	int i;
	head = (userLink)malloc(sizeof(userList));
	for (i = 0; i < USER_MAX_SIZE; i++) {
		head->info = NULL;
		head->next = NULL;
		readUserData(fileArr[i],head);
		usLink[i].userHead = head->next;
	}
	head->next = NULL;
	//将用户存储信息链转化为用户链
	userLink p, pre;
	p = pre = NULL;
	for (i = 0; i < USER_MAX_SIZE; i++) {
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
	getchar();
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
	int j = 1;
	int counter = 0;
	userLink p = start->next;
	//找到开始位置

	if (i <= 0) {
		if (flag == 1){
			printf("查找信息页数的下标错误，请输入大于0的整数作为起始下标\n");
			printf("\n\n按u(上)d(下)键翻页,输入e退出\n");
            printf("输入G可进行页面跳转\n");
		}
		else{
            showInfoByList(start,i+1,num,flag);
			printf("当前已是首页\n");
		}
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
		if(flag == 0){
            tip("返回上一页");
            showInfoByList(start,i-1,num,flag);
		}
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
		while (j<length2&&str1[i] == str2[j])
		{
			i++;
			j++;
		}
		if (j == length2) return k;   //查询成功
		i = k+1;
	}
	return -1;                      //查询失败
}
//用户按学号查找
userLink searchById(userLink start,userLink pre,int id) {
    //if( !start->next ) return;
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
/*
  快速模式匹配KMP算法
*/

/*求模式p的next[]值*/
void getnext(kmpstring p,int next[])
{
    int i=0,j=-1;
    next[0]=-1;
    //开始扫描整个模式串
    while(i<p.length){
        if( j==-1||p.str[i]==p.str[j] ){
            //如果前一个位置的最长真前缀的后一个值和前一个位置相等那么当前位置的next[j]就是前一个位置的next[j]+1
            i++;
            j++;
            next[i]=j;
        }else{
            //如果前一个位置的最长真前缀的后一个值和前一个位置不相等那么继续与上一个位置的next[j]相比较，直到相等
            j=next[j];
        }
    }
    //for( i=0;i<p.length;i++ ) printf("%d",next[i]);
}
/*快速模式匹配算法*/
int kmp(kmpstring t,kmpstring p,int next[])
{
    int i=0,j=0;
    //i开始向后扫描
    while( i<t.length&&j<p.length ){
        if(j==-1||t.str[i]==p.str[j]){
            //在匹配开始或者串内在当前位置匹配成功则i向前走
            i++;
            j++;
        }
        else{
            //如果没有匹配上则将子串的next[j]开始重新在i匹配
            j=next[j];
        }
    }
    //如果j匹配到了末尾则说明模式串匹配成功
    if( j==p.length ) return (i-p.length);
    else return -1;
}
//将学院，专业和课程从文件中读成链表。传入带头节点空链表。type：1.2.3分别代表学院、专业、学科。返回读入数据条数
int fileToList(FILE *fp, instituteList head, int type){
    instituteList s;
    int counter = 0;
    s = head;
    while (!feof(fp)) {
        s = (instituteList)malloc(sizeof(instituteNode));
        fscanf(fp, "%d", &s->instituteId);
        if( s->instituteId==-1 ) {
            free(s);
            break;
        }
        fscanf(fp, "%s", s->instituteName);
        //如果是导入课程则添加课程简介
        if( type==3 ) fscanf(fp, "%s", s->synopsis);
        else strcpy(s->synopsis, "");
        s->next = head->next;
        head->next = s;
        counter++;
    }
    return counter;
}
//清除带头节点的课程链
void freeCourse(instituteList head){
    instituteList s;
    s = head;
    while( s ) {
        head = s->next;
        free(s);
        s = head;
    }
    free(head);
}
//根据课程id找到名字，type 1 2 3分别是学院、专业、课程
instituteList getCourseNameById(int id, int type){
    FILE *fp;
    instituteList head, s, pre;
    if( type==1 ){
        fp = fopen("Data\\courses\\institutes.txt", "r");
    }else if( type==2 ){
        fp = fopen("Data\\courses\\majors.txt", "r");
    }else{
        fp = fopen("Data\\courses\\courses.txt", "r");
    }
    head = (instituteList)malloc(sizeof(instituteNode));
    head->next = NULL;
    fileToList(fp, head, type);
    pre = head;
    s = head->next;
    while( s&&s->instituteId!=id ){
        pre = s;
        s = s->next;
    }
    //freeCourse(head);
    //printCourse(head->next);
    if( s ) {
        pre->next = s->next;
        s->next = NULL;
        freeCourse(head);
        return s;
    }
    else {
        freeCourse(head);
        return NULL;
    }
}
//输出培养方案
void printPlan(plan g)
{
    edgenode *p;
    int i;
    for (i=0;i<g.n;i++)
    {
        printf("\n%s", (getCourseNameById(g.courseList[i].courseId, 3)->instituteName));
        p = g.courseList[i].FirstEdge;
        while ( p )
        {
            printf("-->%s", (getCourseNameById(p->coursesId, 3)->instituteName));
            p=p->next;
        }
        printf("\n");
    }
    printf("\n");
    system("pause");

}
int  creatPlan(plan *g,char *filename)       /*建立培养方案AOV网络的存储结构*/
 {
    int i,j,k,l;
    edgenode  *s;
    FILE *fp;
    fp=fopen(filename,"r");
    if( fp==NULL ) {
        tip("\t\t\t培养方案文件不存在");
        return -1;
    }
    if (fp)
    {
        fscanf(fp,"%d%d%d",&g->majorId,&g->n,&g->e);  /*输入图中的顶点数与边数*/

        for(i=0;i<g->n;i++)                        /*输入顶点值*/
        {
            fscanf(fp,"%d",&g->courseList[i].courseId);
            g->courseList[i].FirstEdge=NULL;
            g->courseList[i].id=0;       /*入度初始化为0*/
        }
        for(k=0;k<g->e;k++)
        {
            fscanf(fp,"%d%d",&i,&j);
            s=(edgenode*)malloc(sizeof(edgenode));
            s->coursesId=j;
            for(l=0;l<g->n;l++){
                if( g->courseList[l].courseId==j ){
                    g->courseList[l].id++;
                    break;
                }
            }
            for(l=0;l<g->n;l++){
                if( g->courseList[l].courseId==i ){
                    s->next=g->courseList[l].FirstEdge;
                    g->courseList[l].FirstEdge=s;
                    break;
                }
            }
        }
    }
    return 1;
}
//输出培养方案
void showPlan(char *path){
    plan g;
    if( creatPlan(&g, path)!=-1 ){
        printPlan(g);
    }else{
        return;
    }

}
//根据专业id生成对应的保存路径,支持输入16进制和8进制
char* outMajorPlans(char s1[], int majorId){
    char temp[10];
    sprintf(temp, "%d", majorId);
    char s2[10] = ".dat";
    char *result = malloc(strlen(s1)+strlen(s2)+strlen(temp)+1);
    if (result == NULL) return NULL;

    strcpy(result, s1);
    strcat(result, temp);
    strcat(result, s2);
    return result;
}
//删除课程安排链
void freeCourseManager(classList head){
    classList s;
    s = head;
    while( s ) {
        head = s->next;
        free(s);
        s = head;
    }
    free(head);
}
//打印课程安排
classList printCourseManager(classList head, int courseId){
    classList s = head->next;
    courseTimePoint p;
    courseUserPoint q;
    while( s ){
        if( s->classId==courseId ){
            printf("\t\t\t课程号:%d  课程名：%s   容量:%d\n", s->classId, getCourseNameById(s->classId, 3)->instituteName, s->counter);
            p = s->timeFistChild;
            printf("\t\t\t任课老师：\n\t\t\t");
            q = s->userFistChild;
            while( q ){
                printf("%d\t", q->userId);
                q = q->next;
            }
            printf("\n\t\t\t时间：\n");
            while( p ){
                printf("\t\t\t%d  %s  是否老师已经选择：%d\n", p->id, p->time, p->isSelected);
                p = p->next;
            }
            break;
        }
        s = s->next;
    }
    if( !s ){
        s = (classList)malloc(sizeof(classNode));
        s->classId = courseId;
        s->counter = 0;
        s->timeFistChild = NULL;
        s->userFistChild = NULL;
        s->next = head->next;
        head->next = s;
        printf("\t\t\t课程号:%d  课程名：%s   容量:%d\n", s->classId, getCourseNameById(s->classId, 3)->instituteName, s->counter);
        p = s->timeFistChild;
        printf("\t\t\t任课老师：\n\t\t\t");
        q = s->userFistChild;
        while( q ){
            printf("%d\t", q->userId);
            q = q->next;
        }
        printf("\n\t\t\t时间：\n");
        while( p ){
            printf("\t\t\t%d  %s  是否老师已经选择：%d\n", p->id, p->time, p->isSelected);
            p = p->next;
        }
    }
    return s;
}
//删除老师或时间
void deleteCourseManager(classList s, int type){
    int userId, timeId;
    courseUserPoint pPre,p;
    courseTimePoint qPre,q;
    if( 0==type ){
        do{
            pPre = s->userFistChild;
            p = s->userFistChild;
            showTitle("请输入要删除老师的id：(-1退出)\n", 20);
            printf("\t\t\t[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%d", &userId);
            while( p&&p->userId!=userId ){
                pPre = p;
                p = p->next;
            }
            if( p||userId==-1 ) {
                break;
            }else{
                printf("\t\t\t");
                tip("要删除的Id不存在");
            }
        }while(userId!=-1);
        if( p ) {
            if( p==s->userFistChild ){
                s->userFistChild = p->next;
                free(p);
            }else{
                pPre->next = p->next;
                free(p);
            }
        }
    }else if( type==1 ){
        do{
            qPre = s->timeFistChild;
            q = s->timeFistChild;
            showTitle("请输入要删除时间编号：(-1退出)\n", 20);
            printf("\t\t\t[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%d", &timeId);
            while( q&&q->id!=timeId ) {
                qPre = q;
                q = q->next;
            }
            if( q||timeId==-1 ) {
                break;
            }else{
                printf("\t\t\t");
                tip("修改的编号不存在");
            }
        }while(timeId!=-1);
        if( q ) {
            if( q==s->timeFistChild ){
                s->timeFistChild = q->next;
                free(q);
            }else{
                qPre->next = q->next;
                free(q);
            }
        }
    }
}
//更新老师或时间
void updataCourseManager(classList s, int type){
    int userId, timeId;
    courseUserPoint p;
    courseTimePoint q;
    if(0==type){
        do{
            p = s->userFistChild;
            showTitle("请输入要修改老师的id：(-1退出)\n", 20);
            printf("\t\t\t[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%d", &userId);
            while( p&&p->userId!=userId ) p = p->next;
            if( p||userId==-1 ) {
                break;
            }else{
                printf("\t\t\t");
                tip("修改的Id不存在");
            }
        }while(userId!=-1);
        if( p ) {
            printf("\t\t\t输入修改后的id：[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%d", &userId);
            p->userId = userId;
        }
    }else if( type==1 ){
        do{
            q = s->timeFistChild;
            showTitle("请输入要修改时间编号：(-1退出)\n", 20);
            printf("\t\t\t[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%d", &timeId);
            while( q&&q->id!=timeId ) q = q->next;
            if( q||timeId==-1 ) {
                break;
            }else{
                printf("\t\t\t");
                tip("修改的Id不存在");
            }
        }while(timeId!=-1);
        if( q ) {
            printf("\t\t\t输入修改后的时间：[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%s", q->time);
        }
    }
}
//添加老师或时间
void addCourseManager(classList s, int type){
    int userId, timeId;
    courseUserPoint p;
    courseTimePoint q;
    if(0==type){
        do{
            p = s->userFistChild;
            showTitle("请输入要添加老师的id：(-1退出)\n", 20);
            printf("\t\t\t[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%d", &userId);
            while( p&&p->userId!=userId ) p = p->next;
            if( (!p||userId==-1)||userId>10000&&userId<=90000 ) {
                break;
            }else{
                printf("\t\t\t");
                if( userId>10000&&userId<=90000 ){
                    tip("添加的id已存在");
                }else{
                    tip("id不合法");
                }

            }
        }while(userId!=-1);
        if( !p&&userId!=-1 ) {
            p = (courseUserPoint)malloc(sizeof(courseUserList));
            p->userId = userId;
            p->next = s->userFistChild;
            s->userFistChild = p;
        }
    }else if( type==1 ){
        do{
            q = s->timeFistChild;
            showTitle("请输入要增加的时间编号：(-1退出)\n", 20);
            printf("\t\t\t[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%d", &timeId);
            while( q&&q->id!=timeId ) q = q->next;
            if( !q||timeId==-1 ) {
                break;
            }else{
                printf("\t\t\t");
                tip("时间的编号重复");
            }
        }while(timeId!=-1);
        if( !q&&timeId!=-1 ) {
            q = (courseTimePoint)malloc(sizeof(courseTimeList));
            q->isSelected = 0;
            q->id = timeId;
            printf("\t\t\t请输入时间：[                 ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%s", q->time);
            q->next = s->timeFistChild;
            s->timeFistChild = q;
        }
    }
}
//将安排好的课程写如文件
void writeCourseToFile(classList head, int courseId){
    FILE *fp;
    char *path;
    char prePath[40] = "Data\\courses\\courseManager\\";
    int counterUser, counterTime;
    classList s;
    courseUserPoint p;
    courseTimePoint q;

    path = outMajorPlans(prePath, courseId/1000);
    fp = fopen(path, "w");
    s = head->next;
    while(s){
        counterUser = 0;
        counterTime = 0;
        p = s->userFistChild;
        q = s->timeFistChild;
        while( p ){
            p = p->next;
            counterUser++;
        }
        while( q ){
            q = q->next;
            counterTime++;
        }
        fprintf(fp, "%d %d %d %d\n", s->classId, s->counter, counterUser, counterTime);
        p = s->userFistChild;
        q = s->timeFistChild;
        while( p ){
            fprintf(fp, "%d\n", p->userId);
            p = p->next;
        }
        while( q ){
            fprintf(fp, "%d %d %s\n", q->id, q->isSelected, q->time);
            q = q->next;
        }
        s = s->next;
    }
    fprintf(fp, "%s", "-1");
    fclose(fp);
}
//从文件中读取课程安排
void readCourseFromFile(classList head, int courseId){
    classList s;
    FILE *fp;
    char *path;
    char prePath[40] = "Data\\courses\\courseManager\\";
    int timeCounter, teaCounter, i, j;
    courseUserPoint p;
    courseTimePoint q;

    path = outMajorPlans(prePath, courseId/1000);
    //文件不存在则打开并写入结束标记
    fp = fopen(path, "r");
    if( fp==NULL ){
        fp = fopen(path, "w+");
        fprintf(fp, "%s", "-1");
    }
    fclose(fp);
    //查找当前学院课程
    fp = fopen(path, "r");
    while ( !feof(fp) ) {
        s = (classList)malloc(sizeof(classNode));
        s->timeFistChild = NULL;
        s->next = NULL;
        s->userFistChild =NULL;
        fscanf(fp, "%d", &s->classId);
        if( s->classId==-1 ) {
            free(s);
            break;
        }
        fscanf(fp, "%d", &s->counter);//班级总容量
        fscanf(fp, "%d", &teaCounter);//任课老师数
        fscanf(fp, "%d", &timeCounter);//时间段数
        for(i = 0; i < teaCounter; i++){
            p = (courseUserPoint)malloc(sizeof(courseUserList));
            fscanf(fp, "%d", &p->userId);
            p->next = s->userFistChild;
            s->userFistChild = p;
        }
        for(j = 0; j < timeCounter; j++){
            q = (courseTimePoint)malloc(sizeof(courseTimeList));
            fscanf(fp, "%d", &q->id);
            fscanf(fp, "%d", &q->isSelected);
            fscanf(fp, "%s", q->time);
            q->next = s->timeFistChild;
            s->timeFistChild = q;
        }
        s->next = head->next;
        head->next = s;
    }
    fclose(fp);
}
//添加学院中课程安排
void addCoursesManager(int courseId){
    classList head, s;
    unsigned int ch;
    char temp[40];
    int arr[3];
    head =  (classList)malloc(sizeof(classNode));
    head->next = NULL;
    readCourseFromFile(head, courseId);
    do{
        if( ch!=67 ) clearInputBufer();
        showTitle("对课程安排操作：\t(ESC退出)\n", 20);
        s = printCourseManager(head, courseId);
        printf("\t\t\t-----------------------------------------------------\n");
        printf("\t\t\t输入: c: 修改课程容量\tu: 更新\td: 删除\ta:增加\n");
        printf("\t\t\t如：\t[c-80] 更改容量为80\n");
        printf("\t\t\t\t[u-0/1] 更新任课老师或时间\n");
        printf("\t\t\t\t[d-0/1] 删除任课老师或时间\n");
        printf("\t\t\t\t[a-0/1] 增加任课老师或时间\n");
        printf("\t\t\t选择操作：[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        ch=getch();
        if (0==ch||0xe0==ch) ch|=getch()<<8;        //非字符键
        switch( ch ){
            case 67: case 99: {
                printf("%c",ch);
                gets(temp);
                strToArr(arr, temp);
                s->counter  = arr[0];
                printf("\t\t\t");
                tip("修改成功");
                ch = 67;
                break;//修改课程容量
            }
            case 85: case 117: {
                printf("%c",ch);
                gets(temp);
                strToArr(arr, temp);
                updataCourseManager(s, arr[0]);//更新任课老师或时间
                break;//更新
            }
            case 68: case 100: {
                printf("%c",ch);
                gets(temp);
                strToArr(arr, temp);
                deleteCourseManager(s, arr[0]);
                break;//删除
            }
            case 65: case 97: {
                printf("%c",ch);
                gets(temp);
                strToArr(arr, temp);
                addCourseManager(s, arr[0]);
                break;//增加
            }
        }
    }while( ch!=27 );
    writeCourseToFile(head, courseId);
    freeCourseManager(head);
}
//安排课程
void managerCourse(int majorId){
    FILE *fCourse;
    instituteList major, p, pre, s;
    int totalMajor, loop = 1;

    fCourse = fopen("Data\\courses\\courses.txt", "r");
    if( fCourse==NULL ) tip("打开专业文件失败");
    else{
        major = (instituteList)malloc(sizeof(instituteNode));
        major->next = NULL;
        totalMajor = fileToList(fCourse, major, 3);
        sortCourses(major, 0, 0);
        //过滤非本专业课程
        pre = major;
        p = major->next;
        while( p ){
            if( (p->instituteId / 1000) != (majorId / 1000) ){
                pre->next = p->next;
                free(p);
                p = pre->next;
                totalMajor--;
            }else{
                pre = p;
                p = p->next;
            }
        }
        if( !totalMajor ){
            printf("\t\t\t");
            tip("该专业还没有录入课程");
        }else{
            do{
                int counter=1;
                showTitle("选择课程（输入-1返回上级）\n", 35);
                s = major->next;
                while( s ){
                    printf("\t\t\t%d: %s", s->instituteId, s->instituteName);
                    if( counter%2==0 ) printf("\n");
                    counter++;
                    s = s->next;
                }
                printf("\n\t\t\t选择课程：[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                scanf("%d", &loop);
                if( loop!=-1 ){
                    s = major->next;
                    while( s&&s->instituteId!=loop ){
                        s = s->next;
                    }
                    if( s ) {
                        addCoursesManager(loop);
                    }else{
                        tip("\t\t\t请选择上表中课程");
                    }

                }
            }while(loop!=-1);
        }
        freeCourse(major);
    }
}
//对培养方案操作
void findPlan(int action){
    FILE *fp;
    unsigned short ch;
    int totalInstitute, page = 1, pageTotal;
    instituteList head;
    char temp[40];
    int arr[3];

    arr[2] = -1;
    fp = fopen("Data\\courses\\institutes.txt", "r");
    if( fp==NULL ) {
        tip("未导入学院");
        return;
    }
    else{
        head = (instituteList)malloc(sizeof(instituteNode));
        head->next = NULL;
        totalInstitute = fileToList(fp, head, 1);
        sortCourses(head, 0, 0);
        clearInputBufer();
        do{
            if( totalInstitute<=0 ) {
                tip("没有数据");
                return;
            }
            pageTotal = getCoursePage(head, totalInstitute, 1, page);
            printf("\t\t\t输入: s: 选择\tf: 查询\n");
            printf("\t\t\t如：\t[s-30001] 选择编号为30001的\n");
            printf("\t\t\t\t[f-30001] 查找编号为30001的记录\n");
            printf("\t\t\t\t[f-课程设计] 按名称模糊查找\n");
            printf("\t\t\t选择学院：[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            //根据用户输入调整page值调整分页
            ch=getch();
            if (0==ch||0xe0==ch) ch|=getch()<<8;        //非字符键
            switch( ch ){
                case 0x48E0: if( !(--page) ){
                                 page = 1;
                                 tip("\n\n\t\t\t已到顶");
                             }
                    break;//键盘上键
                case 0x50e0: if( (++page)>pageTotal ){
                                 page = pageTotal;
                                 tip("\n\n\t\t\t已到底");
                             }
                    break;//键盘下键
                case 102: case 70: {
                    printf("%c",ch);
                    gets(temp);
                    strToArr(arr, temp);
                    searchCourse(head, arr, temp, 1);//根据用户输入进行查找
                    break;//查询操作
                }
                case 115: case 83:{
                    FILE *fMajor;
                    printf("%c",ch);
                    instituteList major, p, pre, s;
                    int totalMajor, loop = 1;

                    gets(temp);
                    strToArr(arr, temp);
                    fMajor = fopen("Data\\courses\\majors.txt", "r");
                    if( fMajor==NULL ) tip("打开专业文件失败");
                    else{
                        major = (instituteList)malloc(sizeof(instituteNode));
                        major->next = NULL;
                        totalMajor = fileToList(fMajor, major, 2);
                        sortCourses(major, 0, 0);
                        //过滤非本学院专业
                        pre = major;
                        p = major->next;
                        while( p ){
                            if( (p->instituteId/1000)!=arr[0] ){
                                pre->next = p->next;
                                free(p);
                                p = pre->next;
                                totalMajor--;
                            }else{
                                pre = p;
                                p = p->next;
                            }
                        }
                        if( !totalMajor ){
                            printf("\t\t\t");
                            tip("该学院还没有录入专业");
                        }else{
                            do{
                                int counter=0;
                                showTitle("选择培养方案（输入-1返回上级）\n", 25);
                                s = major->next;
                                while( s ){
                                    printf("\t\t\t%d: %s", s->instituteId, s->instituteName);
                                    if( counter%2==0 ) printf("\n");
                                    counter++;
                                    s = s->next;
                                }
                                printf("\t\t\t选择专业：[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
                                scanf("%d", &loop);
                                if( loop!=-1 ){
                                    s = major->next;
                                    while( s&&s->instituteId!=loop ){
                                        s = s->next;
                                    }
                                    if( s ) {
                                        //标记是哪种情况使用了选择专业函数，避免调用时直接返回主菜单
                                        if( !action ) planDetail(loop);
                                        else{
                                            managerCourse(loop);
                                        }
                                    }else{
                                        tip("\t\t\t请选择上表中培养方案");
                                    }

                                }
                            }while(loop!=-1);
                        }
                        freeCourse(major);
                    }
                    break;//选择操作
                }
            }
        }while( ch!=27 );//ESC键退出
    }
}
void planDetail(int path){
    char *name;//培养方案文件名
    char s1[20] = "Data\\courses\\plans\\";
    name = outMajorPlans(s1, path);
    showPlan(name);//输出培养方案
}
//分页函数
int getCoursePage(instituteList head, int dateTotal, int type, int page){
    int moveTo, pageTotal, pageMaxNum, dateTotalNum;
    instituteList pageStart, pageEnd, forCounter;
    //重新统计链表长度防止递归调用时数据被删除，改变原来传入的值，
        dateTotalNum = 0;
        forCounter = head->next;
        while(forCounter) {
            dateTotalNum++;
            forCounter = forCounter->next;
        }
        //取统计的和传入的两个数值小的那一个
        if( dateTotalNum < dateTotal ){
            dateTotalNum = dateTotalNum;
        }else{
             dateTotalNum = dateTotal;
        }
        dateTotal = dateTotalNum;
        //根据每页显示条数pageMax计算总页数
        if( dateTotal % pageMax ==0 ) {
            //当数据总条数是每页显示页数的整数倍时需要修改计算规则
            pageTotal = (dateTotal-1) / pageMax + 1;
        }else{
            pageTotal = dateTotal / pageMax + 1;
        }
        //初始化pageStart和pageEnd指针
        pageStart = pageEnd = head->next;
        //初始化函数内部pageMax，避免修改掉全局的每页显示最大容量
        pageMaxNum = pageMax;
        //根据page值调整pageStart和pageEnd指针，同时防止递归调用时指针越界加入datetotalNum限制
        while(dateTotalNum--&&pageMaxNum--&&pageEnd){
            pageEnd = pageEnd->next;
        }
        moveTo = (page-1)*pageMax;
        while( moveTo-- ){
            pageStart = pageStart->next;
            if( pageEnd ) pageEnd = pageEnd->next;
        }
        //输出信息
        system("cls");
        showTitle("请输入相应操作\n",47);
        if( type==1 ){
            printf("\t\t\t学院编号\t学院\n");
        }else if( type==2 ){
            printf("\t\t\t专业编号\t专业\n");
        }else{
            printf("\t\t\t课程编号\t课程\t\t\t课程简介\n");
        }
        printf("\t\t\t--------------------------------------------------------------------------------\n");
        printCourseRange(pageStart, pageEnd, type);//打印一段范围的学院、专业和课程的信息
        printf("\t\t\t--------------------------------------------------------------------------------\n");
        printf("\t\t\t上一页（↑）  下一页（↓），ESC键结束显示。\t\t第%d页，共%d条，共%d页\n", page, dateTotal, pageTotal);
        return pageTotal;
}

//有序字符串转成数组
void strToArr(int arr[], char *str){
    char *p;
    p = strtok(str,"-");
    int counter=0;
    while( p ){
        arr[counter++] = atoi(p);
        p = strtok(NULL, "-");
    }
}

//根据用户输入进行查找
void searchCourse(instituteList head, int arr[], char temp[], int type){
    instituteList p;
    p = head;
    //如果用户输入的字符串第二个值格式化后为0则认为是通过名字查查询
    if( arr[0] ){
        while( p->next&&p->next->instituteId!=arr[0] ){
            p = p->next;
        }
        if( p->next ){
            if( arr[2]==0 ) courseShowByPage(p, 1, type);//递归调用本身显示查询结果
            else{
                printf("\n\t\t\t找到：%d: %s ", p->next->instituteId, p->next->instituteName);
                tip("");
            }
        }else{
            printf("\n\t\t\t");
            tip("未找到");
        }
    }else{
        //快速模式匹配模糊查找
        kmpstring t,m;
        int next[kmpmaxsize];
        //得到用户输入的模式串
        strcpy(m.str, strtok(temp,"-"));
        m.length = strlen(m.str);
        getnext(m,next);
        //对每一条数据的name字段进行模式匹配
        while( p->next ){
            strcpy(t.str, p->next->instituteName);
            t.length =  strlen(t.str);
            if( kmp(t, m, next)!=-1 ){
                printf("\n\t\t\t找到：%d: %s 包含 关键字[%s]", p->next->instituteId, p->next->instituteName, m.str);
                tip("");
                printf("\n");
            }
            p = p->next;
        }
        printf("\t\t\t");
        tip("查询结束");tip("");
    }
}
//打印一段范围的学院、专业和课程的信息
void printCourseRange(instituteList pageStart,instituteList pageEnd, int type){
    while( pageStart != pageEnd ){
        if( strcmp("", pageStart->synopsis)==0 ){
            printf("\t\t\t%d\t\t%s\n",pageStart->instituteId, pageStart->instituteName);
        }else{
            printf("\t\t\t%d\t\t%s\t%s\n",pageStart->instituteId, pageStart->instituteName, pageStart->synopsis);
        }
        pageStart = pageStart->next;
    }
}
//分页后用户进行的操作处理
void courseShowByPage(instituteList head, int dateTotal, int type){
    int page=1, pageTotal;
    unsigned short ch;
    clearInputBufer();
    do{
        if( dateTotal<=0 ) {
            tip("没有数据");
            return;
        }
        int arr[3];//保存用户输入的两个参数,和返回的一个参数
        arr[0] = arr[1] =-1;
        char temp[40];//用于保存用户输入的字符串
        pageTotal = getCoursePage(head, dateTotal, type, page);
        printf("\t\t\t输入:\tf: 查询\td: 删除\tu: 更新\ts: 排序\n");
        printf("\t\t\t如：\t[f-30001] 查找编号为30001的记录");
        printf("\n\t\t\t\t[f-课程设计] 按名称模糊查找");
        printf("\n\t\t\t\t[d-30001] 删除编号为30001的记录");
        printf("\n\t\t\t\t[d-30002-3] 删除当前排序下的3002后两条记录包含30001");
        printf("\n\t\t\t\t[u-30002] 编辑编号为30002的记录");
        printf("\n\t\t\t\t[s-0-0] 默认为0 0按照编号从小到大排序 [s-0-1] 按照编号从大到小排序");
        printf("\n\t\t\t\t[s-1-0] 默认为1 0按照名称从小到大排序 [s-1-1] 按照名称从大到小排序\n");
        printf("\t\t\t操作：[             ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        //根据用户输入调整page值调整分页
        ch=getch();
        if (0==ch||0xe0==ch) ch|=getch()<<8;        //非字符键
        switch( ch ){
            case 0x48E0: if( !(--page) ){
                             page = 1;
                             tip("\n\n\t\t\t已到顶");
                         }
                break;//键盘上键
            case 0x50e0: if( (++page)>pageTotal ){
                             page = pageTotal;
                             tip("\n\n\t\t\t已到底");
                         }
                break;//键盘下键
            case 100: case 68:{
                printf("%c",ch);//补充输出getch输入的值
                gets(temp);//获得用户输入
                strToArr(arr, temp);//将用户输入的字符串格式化成数组
                if( arr[1]<=dateTotal ) delCourse(head, arr);//删除数据操作
                else{
                    printf("\n\t\t\t");
                    tip("删除数据量不合法");
                }
                //printf("%d",arr[2]);
                dateTotal -= arr[2];
                break;//删除操作
            }
            case 102: case 70: {
                printf("%c",ch);
                gets(temp);
                strToArr(arr, temp);
                arr[2] = 0;
                searchCourse(head, arr, temp, type);//根据用户输入进行查找

                break;//查询操作
            }
            case 117: case 85:{
                printf("%c",ch);
                instituteList p,s;
                int inputId;
                p = head;
                int checkIdLength;
                gets(temp);
                strToArr(arr, temp);
                while( p->next&&p->next->instituteId!=arr[0] ){
                    p = p->next;
                }
                if( p->next ){
                    showTitle("请输入需要更改的值（输入-1退出，0不更改当前项）\n",47);
                    if( type==1 ){
                        printf("\t\t\t学院编号\t学院\n");
                        checkIdLength = 10;
                    }else if( type==2 ){
                        printf("\t\t\t专业编号\t专业\n");
                        checkIdLength = 10000;
                    }else{
                        printf("\t\t\t课程编号\t课程\t\t\t课程简介\n");
                        checkIdLength = 10000;
                    }
                    printf("\t\t\t--------------------------------------------------------------------------------\n");
                    if( strcmp("", p->next->synopsis)==0 ){
                        printf("\t\t\t%d\t\t%s\n",p->next->instituteId, p->next->instituteName);
                    }else{
                        printf("\t\t\t%d\t\t%s\t%s\n",p->next->instituteId, p->next->instituteName, p->synopsis);
                    }
                    do{
                        printf("\n\t\t\t请输入新编号:");
                        scanf("%d", &inputId);
                        if( inputId==-1||inputId==0 ) break;
                        if( inputId<checkIdLength ) tip("\t\t\t输入的编号太短\n");
                        s = head->next;
                        while( s&&s->instituteId!=inputId ){
                            s = s->next;
                        }
                        if( s ) tip("\t\t\t输入的编号已存在");
                    }while( inputId&&(inputId<checkIdLength||s) );
                    if( inputId==-1 ) break;
                    p->next->instituteId = inputId;
                    printf("\t\t\t请输入新名称:");
                    scanf("%s", temp);
                    if( strcmp(temp, "0")!=0 )  strcpy(s->next->instituteName, temp);
                    if( strcmp(p->next->synopsis, "")!=0 ){
                        printf("\t\t\t请输入新简介:");
                        scanf("%s", temp);
                        if( strcmp(temp, "0")!=0 ) strcpy(p->next->synopsis, temp);
                    }
                }else{
                    printf("\n\t\t\t");
                    tip("未找到");
                }
                break;//更新操作
            }
            case 115: case 83:{
                printf("%c",ch);
                gets(temp);
                strToArr(arr, temp);
                sortCourses(head, arr[0], arr[1]);//对学院、专业和课程排序
                break;//排序操作
            }
            case 27: break;
            default:{
                printf("\n\t\t\t");
                tip("操作不存在");
            }
        }
    }while( ch!=27 );//ESC键退出
}

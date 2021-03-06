﻿#pragma once
#define MAXSIZE 2000
#define COURSE_PLANS 20
/**
* @description:用户学习或者教授的课程结构体
*/
typedef struct courreadCourseFromFileseNode
{
	int courseId;
	char time[20];
	struct courseNode* next;
}courseList, *coursePoint;
/**
* @description:用户结构体
*/
typedef struct
{
	int id;
	int roleId;
	char name[20];
	char passwd[20];
	char institute[30];
	char phoneNum[20];
	char synopsis[100]; //摘要
	int counter;//用户课程数目
	coursePoint firstChild;

}userNode;
/*
ԃۧʭ؝˵ķ:0ìѧʺ,1Oʦì2ڜmԱ
*/
/**
* @description:顺序表存储读散列用户信息分片，在片内操作查找
*/

typedef struct userInfo
{
	userNode * info;
	struct userInfo * next;
	int flag;//用于学号快排
	int flag1;//用于姓名快排
}userList, *userLink;
//用户信息链，用于存储从文件中读取来的用户信息


/*
以此结构作为用户姓名排序后的存储链
*/
typedef struct userSaveInfo {
	char cName[2]; //姓名的首字母
	userLink userHead;//用户链
}userSaveList, *userSaveLink;


/**
* @description:课程的安排时间
*/
typedef struct courseTimeNode
{
    int id;
	char time[50];
	int isSelected;
	struct courseTimeNode* next;
}courseTimeList;
typedef courseTimeList *courseTimePoint;
/**
* @description:课程的任课老师
*/
typedef struct courseUserLink
{
	int userId;
	struct courseUserLink* next;
}courseUserList;
typedef courseUserList *courseUserPoint;
/**
* @description: 课程结构体
*/
typedef struct class_node
{
	int classId;
    int counter;
	courseUserPoint userFistChild;
	courseTimePoint timeFistChild;
	struct class_node *next;
}classNode;
typedef classNode *classList;


/**
* @description:学院、专业、课程结构体
*/
typedef struct institute_Node
{
	int instituteId;
	char instituteName[20];
	char synopsis[100];
	struct institute_Node* next;
}instituteNode;
typedef instituteNode* instituteList;

/**
* @description:培养方案aov网络结构体
*/
typedef struct node{
      int coursesId;
      struct node *next;
}edgenode;
typedef struct de{
   edgenode* FirstEdge;
   int courseId;
   int id;//存放入度
}vertexnode;

typedef struct{
      vertexnode courseList[COURSE_PLANS];
      int n,e;
      int majorId;
}plan;

/**
* @description:kmp算法使用
*/
#define kmpmaxsize 100
typedef struct{
      char str[kmpmaxsize];
      int length ;
} kmpstring;

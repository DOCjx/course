#pragma once
#pragma once
//int cName[25];//�����û���Ϣ�ļ���,��¼��ʮ��������ĸ��Ӧ�������±�λ��

/*
���ļ�����
1.�û��������������� Y
2.�����û������ð�����������ڽӱ��ĺ��� Y
3.�û���ѧ�������������������Ŀ����㷨
*/
#define _CRT_SECURE_NO_DEPRECATE
#define USER_MAX_SIZE 24
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "infoConst.h"

void quickSortById(userLink start); //���û�����id����
void quickSortByName(userLink start);//���û�������������

int showInfoByList(userLink start, int i, int num,int flag);//�û���Ϣ��ҳ��ʾ����ʾ��iҳ(ÿҳnum������Ϣ
//ע:Ŀǰ��ҳ����ֻ�ܷ�ҳ��ʾ���в��ҵ�����Ϣ����Ӧ�Ե�½����Ϣ����

void infoListControl(userLink start, int i, int num);//�û���Ϣ��ʾ���ƺ���
int getIndex(char* str1, char* str2);//����ģʽƥ�䣬����str2��str1�г��ֵ���ʼλ��
userLink searchByStr(userLink start, char* str2);//ģ����ѯ,��Ŀǰ����)�������к�str2������,��������
void readUserData(char* fileName, userLink uhead);//���ļ���ȡ�û��γ���Ϣ
int isCorrectInfo(userNode user, userSaveList uLink[]);//�û���½��֤����
void login(userSaveList uLink[]);//�û���½����
userLink searchById(userLink start, userLink pre, int id);//��id�����û�,�ҵ���ǰ�ڵ����ǰһ���ڵ�,ѧ��������


void insertToUserListByName(userLink head, userLink p);//����Ϣ���������뵽�û�����
void insertToUserLinkById(userLink start, userLink uInfo);//����Ϣ��id���뵽�û�����
void insertToUserSaveList(userSaveList usLink[], userLink p);//������Ϣ���û���Ϣ�洢����
userLink UserSaveListToUserLink(userSaveList usLink[]);//���û���Ϣ�洢��ת��Ϊ�û���
void userInfoSort(userSaveList usLink[], userLink uLink);//�û���Ϣ�洢��������������
int getCorrectInsertIndex(userLink p);//�õ�������������ļ���Ӧ���±�




void readUserData(char* fileName, userLink uhead) {//��ȡ�û��γ���Ϣ
	FILE* fp;
	errno_t err = fopen_s(&fp,fileName, "r");//fopen_s�÷�
									  /*
									  ��Ҫ����һ������errno_t err,Ȼ�� err = fopen_s(&fp,filename,"w").fopen_s���ļ��ɹ�����0��ʧ�ܷ��ط�0
									  */
	if (err != 0) return;     //�ļ���ʧ��
	else
	{
		int num, i = 0;
		coursePoint head, p, q;
		userLink up;
		while (!feof(fp)) {//feof��������һ��,����Ӧ�öԵ�һ�ζ�ȡ���ݽ����ж�,��֤�Ƿ�Ϊ��
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
			fscanf(fp, "%d", &num);//��ȡ�ܹ��еĿγ���
								   /*
								   fscanf_s���÷�,fscanf(fp,"%d",&var,sizeof(int))��Ҫָ������

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

void writeInfoToFile(char* fileName, userLink head) {//����Ϣд���ļ�
	FILE* fp;
	errno_t err;
	err = fopen_s(&fp,fileName, "w");//fopen_s�÷�
	if (head) {//���û�����Ϊ��,����Ϣд�뵽��Ӧ�ļ���
		if (err != 0) return;     //�ļ���ʧ��
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

void writeUserLinkInfoToFile(userSaveLink usLink) {//����Ӧ�İ������ź�����ļ�д�뵽��Ӧ�ļ���
	for (int i = 0; i < USER_MAX_SIZE; i++)
		writeInfoToFile(fileArr[i], usLink[i].userHead);
}


void login(userSaveList uLink[]) {//�û���½����
	userNode user;
	int type;//�û��������ͱ���
	int counter = 3;//����������ͳ���û���Ϣ����������
	printf("**************************************************************************\n");
	printf("**************************************************************************\n");
	printf("                      ѡ��ϵͳ�û���½:\n");
	printf("**************************************************************************\n");
	printf("**************************************************************************\n");
	printf("                 �����������û�����: 0 ѧ�� 1 ��ְ��\n");
	while (scanf("%d", &type) != EOF) {
		getchar();
		if (type >= 0 && type <3) {//�û�����������ȷ
			printf("�û���:\n");
			scanf("%s", &user.name);
			getchar();
			printf("����:\n");
			scanf("%s", &user.passwd);
			getchar();
			if (isCorrectInfo(user, uLink) == 1) {
				system("cls");
				printf("��ӭ��½\n");
				return;
			}
			else  if (isCorrectInfo(user, uLink) == 0) {
				while (counter >= 1) {
					printf("\n�����������,����������\n");
					printf("������%d�λ���\n", counter);
					printf("�û���:%s\n", user.name);
					printf("����:");
					scanf("%s", &user.passwd);
					getchar();
					counter--;
					if (isCorrectInfo(user, uLink)) {
						system("cls");
						printf("��ӭ��½\n");
						return;
					}

				}
				system("cls");
				break;

			}
			else {
				printf("�û���������\n");
				printf("�û�����:\n");
			}
		}
		else {
			printf("�������ʹ���,��������ȷ����������(0 ѧ�� 1 ��ְ��)\n");
			printf("�û�����:\n");
		}
	}
}

int isCorrectInfo(userNode user, userSaveList uLink[]) {//�û�������֤
														//�û��������ڷ���-1,������󷵻�0,�ɹ���½����1
	int i = USER_MAX_SIZE - 1;
	while (strcmp(user.name, uLink[i].cName)<0)
		//����ǰ�ڵ������ͷ�ڵ���ϢС��������
		i--;
	userLink u = uLink[i].userHead;
	while (u && strcmp(u->info->name, user.name) != 0) {
		u = u->next;
	}
	if (u) {//�ҵ����ϵ�����ʱ
		if (strcmp(user.passwd, u->info->passwd) == 0)
			return 1;
		else
			return 0;
	}
	return -1;

}


//��Ϣ���Ժ���
void print(userLink uhead) {
	userLink up;
	up = uhead->next;
	while (up) {
		if (up->info) {
			printf("ѧ��%d ", up->info->id);
			printf("��ɫ��%d ", up->info->roleId);
			printf("����%s ", up->info->name);
			printf("����%s ", up->info->passwd);
			printf("ѧԺ%s ", up->info->institute);
			printf("�绰����%s ", up->info->phoneNum);
			printf("���%s ", up->info->synopsis);
			coursePoint p;
			p = up->info->firstChild;
			if (p->next) {
				printf("��ǰ�γ���: \n");
				/*
				�˴���δ�Կγ���Ϣ���в���
				*/
			}
			else {
				printf("��ǰ�޿γ�\n");
			}
		}
		up = up->next;

	}
}


//���û��������������в���
void usPrint(userSaveList uLink[]) {
	for (int i = 0; i <= USER_MAX_SIZE - 1; i++) {
		userLink up = uLink[i].userHead;
		while (up) {
			printf("%s  ", uLink[i].cName);
			printf("ѧ��%d ", up->info->id);
			printf("��ɫ��%d ", up->info->roleId);
			printf("����%s ", up->info->name);
			printf("����%s ", up->info->passwd);
			printf("ѧԺ%s ", up->info->institute);
			printf("�绰����%s ", up->info->phoneNum);
			printf("���%s ", up->info->synopsis);
			coursePoint p;
			p = up->info->firstChild;
			if (p->next) {
				printf("��ǰ�γ���: \n");
				/*
				�˴���δ�Կγ���Ϣ���в���
				*/
			}
			else {
				printf("��ǰ�޿γ�\n");
			}
			up = up->next;

		}
	}
}

//����Ϣ���������뵽�û�����
//ǰ���������Ѿ�����
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

//����Ϣ���������뵽��Ϣ����
//ǰ����id�Ѿ�����
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

void quickSortById(userLink start) {//���û�����id����
	userLink p, q, pre;
	q = start->next;
	if (q && !q->flag) {//Ԫ�ز�ֻһ��ʱ
		pre = q;
		p = q->next;//p�������ұ�q��Ľڵ�
		q->flag = 1;
		q->flag1 = 0;
		while (p && !p->flag) {
			while (p && !p->flag&&p->info->id>q->info->id) {//���ҵ�һ������p->info��Ԫ��
				pre = p;
				p = p->next;
			}
			if (p && !p->flag) {//�ҵ�����ͷ��
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

void quickSortByName(userLink start) {//���û�������������
	userLink p, q, pre;
	q = start->next;
	if (q && !q->flag1) {//Ԫ�ز�ֻһ��ʱ
		pre = q;
		p = q->next;//p�������ұ�q��Ľڵ�
		q->flag1 = 1;
		q->flag = 0;
		while (p && !p->flag1) {
			while (p && !p->flag1&&strcmp(p->info->name,q->info->name)>0) {//���ҵ�һ������p->info��Ԫ��
				pre = p;
				p = p->next;
			}
			if (p && !p->flag1) {//�ҵ�����ͷ��
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


//�û���ѧ�Ų���
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
userLink searchByStr(userLink start,char* str2) {//�����ҵ��������
	userLink newLink = (userLink)malloc(sizeof(userList));//������ͷ�ڵ�
	userLink p = start->next;
	userLink r;
	newLink->next = NULL;
	r = newLink;
	//�ж�str2�Ƿ���ĳ����Ϣ���Ӵ�
	while (p) {
		/*
		//����
		//����������
		*/
		if (getIndex(p->info->name,str2)!=-1) {//���ҵ�����Ϣ������������
			//���½ڵ�β�嵽������
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
void userInfoSort(userSaveList usLink[], userLink uLink) {//�������û���Ϣ���������ֽ�������
	int i;
	//���û���Ϣ�����г�ʼ��
	for (i = 0; i <USER_MAX_SIZE; i++) {
		if (i == 0)
			strcpy(usLink[i].cName, " ");
		else
			strcpy(usLink[i].cName, arr[i - 1]);
		usLink[i].userHead = NULL;
	}
	//�������û���Ϣ�����б���,������뵽�洢�û���Ϣ����
	userLink p;//Ҫ����ڵ�
	p = uLink->next;
	while (p) {
		//ȡ�½ڵ㽫����뵽��Ӧ�Ĵ洢����
		uLink->next = p->next;
		p->next = NULL;
		insertToUserSaveList(usLink, p);
		p = uLink->next;
	}
}


/*
	�õ�������������ļ����±�
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

void insertToUserSaveList(userSaveList usLink[], userLink p){//����p��ָ���һ���ڵ㵽�û���Ϣ����

	for (int i = 1; i < USER_MAX_SIZE - 1; i++) {
		if (strcmp(usLink[i].cName, p->info->name) >= 0) {//����ǰ����С�ڰ�

			if (!usLink[i - 1].userHead)//��ǰͷ�ڵ�Ϊ��ʱֱ�Ӳ���
				usLink[i - 1].userHead = p;
			else {//��Ϊ��ʱ���ҵ����ʵĵط�����
				userLink q, pre; //q,pre�������Һ��ʵ�λ��
				pre = NULL;
				q = usLink[i - 1].userHead;
				while (q&& strcmp(p->info->name, q->info->name) > 0) {
					//����ǰ�ڵ�����С��Ҫ����ڵ�����ʱ�������
					pre = q;
					q = q->next;
				}
				if (pre) { //��������ڵ㲻�ǵ�һ���ڵ�
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
		else if (strcmp(usLink[USER_MAX_SIZE - 1].cName, p->info->name) <= 0) {//��һ����ͷ�������ڵ�ǰ��ͷ

			if (!usLink[USER_MAX_SIZE - 1].userHead)//��ǰͷ�ڵ�Ϊ��ʱֱ�Ӳ���
				usLink[USER_MAX_SIZE - 1].userHead = p;
			else {//��Ϊ��ʱ���ҵ����ʵĵط�����
				userLink q, pre; //q,pre�������Һ��ʵ�λ��
				pre = NULL;
				q = usLink[USER_MAX_SIZE - 1].userHead;
				while (q&& strcmp(p->info->name, q->info->name) > 0) {
					//����ǰ�ڵ�����С��Ҫ����ڵ�����ʱ�������
					pre = q;
					q = q->next;
				}
				if (pre) { //��������ڵ㲻�ǵ�һ���ڵ�
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
		else if (strcmp(usLink[i].cName, p->info->name) <= 0 && strcmp(usLink[i + 1].cName, p->info->name) > 0) {//���û���Ϣ���ڵ��ڵ�ǰͷ�ڵ���Ϣ
																												 //����С����һ��ͷ�ڵ���Ϣʱ���������
			if (!usLink[i].userHead)//��ǰͷ�ڵ�Ϊ��ʱֱ�Ӳ���
				usLink[i].userHead = p;
			else {//��Ϊ��ʱ���ҵ����ʵĵط�����
				userLink q, pre; //q,pre�������Һ��ʵ�λ��
				pre = NULL;
				q = usLink[i].userHead;
				while (q&& strcmp(p->info->name, q->info->name) > 0) {
					//����ǰ�ڵ�����С��Ҫ����ڵ�����ʱ�������
					pre = q;
					q = q->next;
				}
				if (pre) { //��������ڵ㲻�ǵ�һ���ڵ�
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
	int counter = 0;//���ڼ���
	head = (userLink)malloc(sizeof(userList));
	for (int i = 0; i < USER_MAX_SIZE; i++) {
		head->info = NULL;
		head->next = NULL;
		readUserData(fileArr[i],head);
		usLink[i].userHead = head->next;
	}
	head->next = NULL;
	//���û��洢��Ϣ��ת��Ϊ�û���
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
��ҳ��ʾ������
1.����������ҳ��ʾ�û���Ϣ
2.��ѧ��,��ҳ��ʾ�û���Ϣ
3.����ѯ���Ľ����ҳ��ʾ

*/

/*
	���Ż�����ʼʱÿ�δ�ͷ����Ч�ʲ���
*/
void infoListControl(userLink start, int i, int num) {
	char a;
	int j;
	j = showInfoByList(start, i, num,0);//��ʾ��Ϣ
	while (1) {
		a = getchar();
		getchar();
		if (a == 'u'|| a == 'U') {//��ҳ
			i--;
			j = showInfoByList(start, i, num,0);
			if (j != 0)
				i++;
		}
		else if (a == 'd'||a == 'D') {//��ҳ
			i++;
			j = showInfoByList(start, i, num,0);
			if (j != 0)
				i--;
		}
		else if (a == 'e' || a == 'E') {//�˳�
			break;

		}
		else if (a == 'g' || a == 'G') {
			int d;
			printf("������Ҫ��ת��ҳ��:\n");
			scanf("%d", &d);
			getchar();
			showInfoByList(start, d, num, 1);

		}
		else{
			printf("������Ϣ���Ϸ�,����������\n");
			printf("\n\n��u(��)d(��)����ҳ,����e�˳�\n");
			printf("����G�ɽ���ҳ����ת\n");
		}
	}
}
//��ʾ�û�id��Ϣ
//ͨ��ջ�����ϴ�ҳ����Ϣ,�������
int showInfoByList(userLink start,int i,int num,int flag) {//��ҳ��ʾ��Ϣ
//flag���ڱ�ʶ�Ƿ���ֱ�Ӳ���
//��(i-1)*num+1��ʼ,��ʾnum����Ϣ
//��ʾ��iҳ����Ϣ
//ÿҳ��ʾ����Ϣ����
//�γ���Ϣ,�û���Ϣ
	int j = 0;
	int counter = 0;
	userLink p = start->next;
	//�ҵ���ʼλ��

	if (i <= 0) {
		if (flag == 1)
			printf("������Ϣҳ�����±�������������0��������Ϊ��ʼ�±�\n");
		else
			printf("��ǰ������ҳ\n");
		return -1;
	}
	system("cls");
	while (p&&j < ((i - 1)*num + 1)) {
		p = p->next;
		j++;
	}

	if (p) {
		while (p&&counter < num) {
			printf("ѧ��%d ", p->info->id);
			printf("��ɫ��%d ", p->info->roleId);
			printf("����%s ", p->info->name);
			printf("����%s ", p->info->passwd);
			printf("ѧԺ%s ", p->info->institute);
			printf("�绰����%s ", p->info->phoneNum);
			printf("���%s \n", p->info->synopsis);
			p = p->next;
			counter++;
		}
		while(counter < num+2) {
			printf("\n");//����ʱ���\n
			counter++;
		}
		printf("                                             ��%dҳ\n", i);
		printf("\n\n��u(��)d(��)����ҳ,����e�˳�\n");
		printf("����G�ɽ���ҳ����ת\n");
		return 0;
		/*
			����Ϣ���ջ���棬���㷭ҳ��ʾ
		*/
	}
	else {
		printf("û�е�%dҳ\n", i);
		printf("\n\n��u(��)d(��)����ҳ,����e�˳�\n");
		printf("����G�ɽ���ҳ����ת\n");
		return 1;
	}
}

//����Ϣģ������
/*
	�����Ӵ�str2��str1�г��ֵ�λ��
*/
//����ģʽƥ��
int getIndex(char* str1, char* str2) {
	int length1 = strlen(str1);
	int length2 = strlen(str2);
	int k, i,j;
	i = 0;
	while (i <=length1 - length2)
	{
		k = i;                        //��¼ƥ����ʼλ��
		j = 0;
		while (j<=length2&&str2[i] == str1[j])
		{
			i++;
			j++;
		}
		if (j == length2) return k;   //��ѯ�ɹ�
		i = k + 1;
	}
	return -1;                      //��ѯʧ��
}



userLink searchByStr(userLink start,char* str2) {//�����ҵ��������
	userLink newLink = (userLink)malloc(sizeof(userList));//������ͷ�ڵ�
	userLink p = start->next;
	userLink r;
	newLink->next = NULL;
	r = newLink;
	//�ж�str2�Ƿ���ĳ����Ϣ���Ӵ�
	while (p) {
		/*
		//����
		//����������
		*/
		if (getIndex(p->info->name,str2)!=-1) {//���ҵ�����Ϣ������������
			//���½ڵ�β�嵽������
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

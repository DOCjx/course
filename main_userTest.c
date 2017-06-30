#include "heads/common.h"
#include "heads/stuCoursesSelect.h"
#include "heads/teaCoursesSelect.h"
#include "heads/affairsCoursesSelect.h"
#include "heads/admin.h"

void inputPassWord();//�����������
int checkLogin();//��֤�û���������
void initConf();//��ʼ������
void saveConf();//������ʱ�����ļ�����

int main()
{
    /*����*/
    //role = 3;
    initConf();
    saveConf();
    //affairsCoursesSelect();
    userSaveList s[24];
    globalHead = (userLink)malloc(sizeof(userList));
    globalHead->info = NULL;
    globalHead->next = NULL;
    readUserData("Data/users/user.txt",globalHead);
    userInfoSort(s,globalHead);

    //writeInfoToFile("Data/users/userstest.txt",q->next);

    writeUserLinkInfoToFile(s);
    globalHead = UserSaveListToUserLink(s);

    //usPrint(s);
//readCourse(1);



/*
    tip("��ȡ�����ļ�");
    //��ȡ�����ļ�
    initConf();*/
    //��ʼѡ��ϵͳ
    appStart();
    //��д�����ļ�
    system("pause");

    return 0;
}

/*
    @�������ƣ�checkLogin
    ��ڲ������û�������û���������
    ���ڲ���������״̬�롣0���û��������ڣ�1���������
    @�������ܣ���֤�û��������룬�ɹ��򱣴��û���Ϣ��ȫ��
*/
int checkLogin(char pass[]){
    userLink q,s;
    if(  userNum==Admin ) {
        if( strcmp(pass, AdminPass)==0 ) {
            role = 3;
            return 2;
        }else{
            return 1;
        }
    }
    q = (userLink)malloc(sizeof(userList));
    q->info = NULL;
    q->next = NULL;
    //TODO:�����û������ѧ�Ŷ�̬���������ļ�
    readUserData("Data/users/users.txt",q);
    if( q->next ){
        quickSortById(q);
        globalHead = q;
        s = searchById(q,NULL,userNum);
        if( !s ) return 0;
        else if( strcmp(s->info->passwd, pass)==0 ){
            role = s->info->roleId;
            return 2;
        }else{
            return 1;
        }
    }else{
        return 0;
    }
}
/*
    @�������ƣ�inputPassWord
    @�������ܣ�������󳤶�Ϊn������
*/
void inputPassWord(char password[])
{
    int i;
    char c;
    i=0;
    while (i<passLength)
    {
        c=getch();
        if (c=='\r') break;         //�س���
        if (c==8 && i>0 )           //�˸��
            {   printf("\b \b");
                i--;
            }
         else
            {   password[i++]=c;    //��Ч�����ַ�
                printf("*");        //����*��
            }
    }
    printf("\n");
    password[i]='\0';
}

/*
    @�������ƣ�login
    @�������ܣ������û��������Ϣ��������user.dat�ļ��в�ѯ�������û���ɫ
               �������û���������ʾ��ͬ�Ĳ˵�
*/

int login()
{
    char password[passLength+1];
    int checkCode;
    int counter = loginTimes;
    while (counter>0)
    {   system("cls");
        showtime(0);
        counter--;
        showTitle("��ӭ����������\n",0);
        printf("\t\t\t�û�����[              ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%d",&userNum);
        if( checkLogin("")==0&&(Admin!=userNum) ){
            printf("���û������ڣ�����%d�ε�¼���ᡣ\n",counter);
            if( !userNum ) clearInputBufer();
            getch();
            continue;
        }else{
            printf("\t\t\t��  �룺[              ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            inputPassWord(password);
            checkCode = checkLogin(password);
        }
        if( checkCode == 1 ){
            printf("������������󣬻���%d�ε�¼���ᡣ\n",counter);
            getch();
            continue;
        }else{
            return 1;
        }
    }
    return 0;
}

/*
    @�������ƣ�coursesSelect
    @�������ܣ������û���ɫ���й�����ת
*/
int coursesSelect(){
    if( !systemStatus ) return -1;
    switch( role ){
        case 0: stuCoursesSelect();break;
        case 1: teaCoursesSelect();break;
        case 2: affairsCoursesSelect();break;
        case 3: admin();break;
        default:
            tip("�û���ɫ�쳣����");
            break;
    }
    return 1;
}

/*
    @�������ƣ�initConf
    @�������ܣ���ʼ�������ļ�
*/
void initConf(){
    FILE *fp;

    fp=fopen("conf/conf.dat","rb");
    if (fp==NULL) {
        tip("�������ļ�ʧ��");
        return;
    }
    else
    {
        fscanf(fp,"%d%d%d%d%s", &systemStatus, &passLength, &loginTimes, &Admin, AdminPass);
        //printf("%d %d %d %d %s", systemStatus, passLength, loginTimes, Admin, AdminPass);
        //tip("aaa");
    }
    fclose(fp);
}

/*
    @�������ƣ�saveConf
    @�������ܣ�����ʱ�����ļ�����
*/
void saveConf(){
    FILE *fp;

    fp=fopen("conf/conf.dat","wb");
    if (fp==NULL) {
        tip("�������ļ�ʧ��");
        return;
    }
    else
    {   //printf("%d %d %d", systemStatus, passLength, loginTimes);
        fprintf(fp,"%d %d %d %d %s", systemStatus, passLength, loginTimes, Admin, AdminPass);

    }
    fclose(fp);
}
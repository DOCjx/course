#include "heads/common.h"
#include "heads/stuCoursesSelect.h"
#include "heads/teaCoursesSelect.h"
#include "heads/affairsCoursesSelect.h"
#include "heads/admin.h"

void inputPassWord();//�����������
int checkLogin(char pass[]);//��֤�û���������
void initConf();//��ʼ������
void saveConf();//������ʱ�����ļ�����

int main()
{
   /*����
   userNum = 30001;
   role = 0;
   initConf();
//showPlan("Data\\courses\\plans\\30001.dat");
//    instituteList tmp;
//    tmp = getCourseNameById(30, 1);
//    printf("%s", tmp->instituteName);
affairsCoursesSelect();
*/



/**/
    tip("��ȡ�����ļ�");
    //��ʼ��ϵͳ����
    initConf();
    //ϵͳ��ں���
    appStart();
    //���û�д
    saveConf();
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
    userSaveList us[USER_MAX_SIZE];
    readUserDataFromMultipleFiles(us);
    q = UserSaveListToUserLink(us);
    globalHead = q;
    if(  userNum==Admin ) {
        if( strcmp(pass, AdminPass)==0 ) {
            role = 3;
            return 2;
        }else{
            return 1;
        }
    }
    //TODO:�����û������ѧ�Ŷ�̬���������ļ�
    //readUserData("Data/users/users.txt",q);
    if( q->next ){
        quickSortById(q);
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

    fp=fopen("conf/conf.dat","r");
    if (fp==NULL) {
        tip("�������ļ�ʧ��");
        return;
    }
    else
    {

        fscanf(fp,"%d%d%d%d%s%d",
                &systemStatus,
                &passLength,
                &loginTimes,
                &Admin,
                AdminPass,
                &pageMax
        );
        //printf("%d %d %d %d %s %d", systemStatus, passLength, loginTimes, Admin, AdminPass, pageMax);
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

    fp=fopen("conf/conf.dat","w");
    if (fp==NULL) {
        tip("�������ļ�ʧ��");
        return;
    }
    else
    {   //printf("%d %d %d %d %s %d", systemStatus, passLength, loginTimes, Admin, AdminPass, pageMax);
        fprintf(fp,"%d %d %d %d %s %d", systemStatus, passLength, loginTimes, Admin, AdminPass, pageMax);

    }
    fclose(fp);
}
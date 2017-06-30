#include "heads/common.h"
#include "heads/stuCoursesSelect.h"
#include "heads/teaCoursesSelect.h"
#include "heads/affairsCoursesSelect.h"
#include "heads/admin.h"

void inputPassWord();//密码回显输入
int checkLogin();//验证用户名和密码
void initConf();//初始化配置
void saveConf();//将运行时配置文件存盘

int main()
{
    /*测试*/
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
    tip("读取配置文件");
    //读取配置文件
    initConf();*/
    //开始选课系统
    appStart();
    //回写配置文件
    system("pause");

    return 0;
}

/*
    @函数名称：checkLogin
    入口参数：用户输入的用户名和密码
    出口参数：返回状态码。0、用户名不存在，1、密码错误
    @函数功能：验证用户名、密码，成功则保存用户信息到全局
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
    //TODO:根据用户输入的学号动态查找所在文件
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
    @函数名称：inputPassWord
    @函数功能：输入最大长度为n的密码
*/
void inputPassWord(char password[])
{
    int i;
    char c;
    i=0;
    while (i<passLength)
    {
        c=getch();
        if (c=='\r') break;         //回车键
        if (c==8 && i>0 )           //退格键
            {   printf("\b \b");
                i--;
            }
         else
            {   password[i++]=c;    //有效密码字符
                printf("*");        //回显*号
            }
    }
    printf("\n");
    password[i]='\0';
}

/*
    @函数名称：login
    @函数功能：根据用户输入的信息与密码在user.dat文件中查询，返回用户角色
               并根据用户的身份显示不同的菜单
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
        showTitle("欢迎进入登入界面\n",0);
        printf("\t\t\t用户名：[              ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%d",&userNum);
        if( checkLogin("")==0&&(Admin!=userNum) ){
            printf("该用户不存在！还有%d次登录机会。\n",counter);
            if( !userNum ) clearInputBufer();
            getch();
            continue;
        }else{
            printf("\t\t\t密  码：[              ]\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            inputPassWord(password);
            checkCode = checkLogin(password);
        }
        if( checkCode == 1 ){
            printf("输入的密码有误，还有%d次登录机会。\n",counter);
            getch();
            continue;
        }else{
            return 1;
        }
    }
    return 0;
}

/*
    @函数名称：coursesSelect
    @函数功能：根据用户角色进行功能跳转
*/
int coursesSelect(){
    if( !systemStatus ) return -1;
    switch( role ){
        case 0: stuCoursesSelect();break;
        case 1: teaCoursesSelect();break;
        case 2: affairsCoursesSelect();break;
        case 3: admin();break;
        default:
            tip("用户角色异常！！");
            break;
    }
    return 1;
}

/*
    @函数名称：initConf
    @函数功能：初始化配置文件
*/
void initConf(){
    FILE *fp;

    fp=fopen("conf/conf.dat","rb");
    if (fp==NULL) {
        tip("打开配置文件失败");
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
    @函数名称：saveConf
    @函数功能：运行时配置文件存盘
*/
void saveConf(){
    FILE *fp;

    fp=fopen("conf/conf.dat","wb");
    if (fp==NULL) {
        tip("打开配置文件失败");
        return;
    }
    else
    {   //printf("%d %d %d", systemStatus, passLength, loginTimes);
        fprintf(fp,"%d %d %d %d %s", systemStatus, passLength, loginTimes, Admin, AdminPass);

    }
    fclose(fp);
}

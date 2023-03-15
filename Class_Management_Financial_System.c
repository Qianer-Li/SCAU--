#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<windows.h>
#include<conio.h>
#include<math.h>

/*全局变量*/
int lo;   //决定菜单
char na[200];   //在菜单上显示用户名字

/*存放账号密码*/
typedef struct The_users   //typedef定义结构体别名
{
    char id[11]; //账号
    char pwd[20]; //密码
    char name[15];//姓名
    char quan; //使用权限
long phone; //电话号码

} users;

/*班级成员信息*/
struct student
{
    char num[15];   //学号
    char name[20];  //姓名
    char sex;       //性别
    int age;       //年龄
    int clas;      //班级
    char mail[20];  //邮箱
    char number[13]; //电话号码

};

/*班级成员数据结构体*/
typedef struct node
{
    struct student data;
    struct node *next;
} s;


/*财务信息记录*/
typedef struct jilu
{
    char use[100];   //用途
    long shou;        //收入
    long zhi;         //支出
    char time1[100];  //收入时间
    char time2[100];  //支出时间
    char people[100]; //使用人
    struct jilu *next;

} ji;

/*函数类目*/
void in(s *head);            //信息的读取
void menu();                 //菜单1函数
void menu2();                //菜单2函数
void add(s *head);           //录入函数
void dele(s *head);          //删除函数
void mod(s *head);           //修改函数
void query(s *head);         //查询函数
void sort(s *head);          //排序函数
void account();              //财务收入
void print() ;               //显示总财务
void printall();             //显示所有学生信息
void out(s *head);           //信息的存储
void allsum();               //账目统计

/*创建储存用户账号密码的文件*/
void Create_File()
{
    FILE *fp;
    if ((fp = fopen("users.txt","rb"))==NULL)                 /*如果此文件不存在*/
    {
        if ((fp = fopen("users.txt","wb+"))==NULL)
        {
            printf("无法建立文件！\n");
            exit(0);

        }
    }
}

/*创建储存学生信息的文件*/
void Create_File2()
{
    FILE *fp;
    if ((fp = fopen("student.txt","rb"))==NULL)                 //如果此文件不存在
    {
        if ((fp = fopen("student.txt","wb+"))==NULL)
        {
            printf("无法建立文件！\n");
            exit(0);

        }
    }
}

/*注册账号*/
void registers()  //按结构体的大小，一次写入或者读入1个结构体大小
{
    int i;
    users a,b;//结构体The_users
    FILE *fp;
    char temp[20];
    int count = 0;
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("              *---------------------------------------------------------------*               \n");
    printf("              |                                                               |              \n");
    printf("              |                         欢迎注册 ！                           |              \n");
    printf("              |                                                               |              \n");
    printf("              *---------------------------------------------------------------*               \n\n");
    printf("              以下是注意事项：\n");
    printf("              1.管理员权限和班级成员权限不同，可使用系统内的功能也不同；\n");
    printf("              2.当输入密码错误达到五次，将启用修改密码功能；\n");
    printf("              3.修改密码需要输入绑定该账户的手机号，因此请务必输入正确的手机号。\n\n");
    Sleep(1000);
    fp = fopen("users.txt","r");
    fread(&b, sizeof(struct The_users), 1, fp); //读入一个结构体字符块到b，用来遍历文件
    printf("请输入账号：\n");
    scanf("%s",&a.id);
    while (1)                    //查找是否有注册过的账号
    {
        if (strcmp(a.id, b.id)) //如果两串不相等
        {
            if (!feof(fp))    //如果未到文件尾

            {
                fread(&b, sizeof(struct The_users), 1, fp);//则继续读取（格式化读取文件）
            }
            else              //到了文件尾也没有相同的账号
                break;
        }
        else
        {
            system("cls");
            printf("此用户名已存在，请重新注册！\n\n");//如果两串相等
            Sleep(1000);
            fclose(fp);
            system("cls");
            return  registers();
        }
    }
    printf("请输入姓名：\n");
    scanf("%s",&a.name);
    printf("请输入权限(a(管理员)/b(普通成员)）：\n");
    getchar();   //吸收回车符
    scanf("%c",&a.quan);
    do
    {
        if(a.quan != 'a' && a.quan != 'b')
        {
            printf("权限输入错误，请重新输入！\n");
            scanf("%c",&a.quan);
        }
    }
    while(a.quan != 'a' && a.quan != 'b'); //输入到成功才停止
    getchar();
    printf("请输入电话号码：\n");
    scanf("%ld",&a.phone);
    printf("请输入密码：\n");
    scanf("%s",&a.pwd);
    printf("请确认密码：\n");
    scanf("%s",&temp);
    do
    {
        if(!strcmp(a.pwd,temp))
        {
            fp = fopen("users.txt","a");
            fwrite(&a, sizeof(struct The_users), 1, fp);//如果两次密码相同，读入信息到文件
            printf("注册成功，欢迎登录！\n");
            Sleep(500);
            fclose(fp);
            system("cls");
            return Input_loin();
        }
        else
        {
            printf("两次密码不匹配，请重新输入！\n");//第二次不同，重新输入第一次的密码
            scanf("%s",&a.pwd);
            printf("请确认密码：\n");
            scanf("%s",&temp);
        }
    }
    while(1);
}

/*登录系统*/
void  Input_loin()
{
    system("cls");
    users a,b;//两个users类型的结构体
    int i;
    FILE *fp;
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("              *---------------------------------------------------------------*               \n");
    printf("              |                                                               |              \n");
    printf("              |                         欢迎登录 ！                           |              \n");
    printf("              |                                                               |              \n");
    printf("              *---------------------------------------------------------------*               \n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    Sleep(1000);
    fp = fopen("users.txt","r+");//注意这里要是r+，既可以读也可以写入
    fread(&b, sizeof(struct The_users), 1, fp); //从文件中读入一个结构体字符块到b
    printf("请输入账号：\n");
    scanf("%s",&a.id);

    while (1)
    {
        if (strcmp(a.id, b.id)==0)         //文件中有此用户名，找到该用户信息
        {
            strcpy(na,b.name);
            break;
        }

        else
        {
            if (!feof(fp))  //如果文件没有读完
            {
                fread(&b, sizeof(struct The_users), 1, fp);//再次读取一个结构体字符
            }
            else
            {
                printf("此用户名不存在！（如果要注册则输入1,继续登录则输入2）\n");//如果文件已经读完，还没找到该用户
                Sleep(500);
                fclose(fp);
                int i;
                scanf("%d",&i);

                if(i==1)
                {
                    system("cls");
                    return registers();
                }
                else if(i==2)
                {
                    system("cls");
                    return Input_loin();
                }
                else
                {
                    while(i!=1&&i!=2)
                    {
                        printf("无此选项，请重新输入！\n");
                        scanf("%d",&i);
                        if(i==1)
                        {
                            system("cls");
                            return registers();
                        }
                        else if(i==2)
                        {
                            system("cls");
                            return Input_loin();
                        }
                    }
                }

            }
        }
    }
    printf("请输入密码：\n");
    int sum=1;
    int sum2=0;
    char mima[200],temp[200];
    scanf("%s",&a.pwd);
    do
    {

        if (strcmp(a.pwd, b.pwd)!=0)            //如果密码匹配
        {
            sum++;
            printf("密码不正确，请重新输入密码：\n");
            scanf("%s",&a.pwd);


        }
        if(strcmp(a.pwd, b.pwd)==0)
        {
            printf("\n登录成功,欢迎使用!");
            Sleep(1000);
            if(b.quan=='a')                    //由账号中的权利决定进入哪个菜单
            {
                return menu();
            }
            else if(b.quan=='b')
            {
                return menu2();
            }
        }

        if(sum==5)
        {
            printf("密码已输入五遍，是否要修改密码(是输入1，否输入0）：\n");//密码输入错误达到五次就启动修改密码功能
            int u;
            scanf("%d",&u);
            if(u==1)
            {
                do
                {
                    if(sum2==3)
                    {
                        printf("输入错误已达三次！三秒后将返回主页面！\n");
                        Sleep(3000);
                        system("cls");
                        return first();
                    }
                    printf("请输入该账号绑定的电话号码：\n");//修改密码需要输入正确的手机号
                    scanf("%ld",&a.phone);
                    sum2++;

                }
                while(a.phone!=b.phone);
                printf("请输入新的密码：\n");
                scanf("%s",&mima);

                printf("请确认密码：\n");
                scanf("%s",temp);

                while(strcmp(temp,mima)!=0)
                {
                    printf("两次密码不匹配，请重新输入！\n");
                    scanf("%s",temp);
                    getchar();

                }

                strcpy(b.pwd,mima);//修改结构体b原来的密码
                fseek(fp,-sizeof(struct The_users),SEEK_CUR);//指针移至修改目标前
                fwrite(&b, sizeof(struct The_users), 1, fp);//重新写入，覆盖原来的数据
                fclose(fp);       //最后记得要关闭文件
                printf("密码修改成功，请重新登录！");
                Sleep(1000);
                system("cls");
                return first();
            }
            else if(u==0)
            {
                fclose(fp);
                system("cls");
                return  first();
            }
            else
            {
                printf("无此选项，三秒后将返回主页面！\n");
                fclose(fp);
                Sleep(3000);
                system("cls");
                return first();

            }
        }

    }
    while(strcmp(a.pwd, b.pwd)!=0);    //直到密码相同,注意是！=，不是==

}

/*读取学生信息*/
void in(s *head)
{
    FILE *fp;
    s *p,*q;
    fp = fopen("student.txt","r");
    while (!feof(fp))
    {
        p= (s*)malloc(sizeof(s));//给p分配结构体s空间
        fscanf(fp,"%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,&p->data.sex,&p->data.age,&p->data.clas,p->data.mail,p->data.number);//从文件中读取一个
        p->next=NULL;
        s *last=head->next; //注意head->next一开始为空
        if(last!=NULL)           //当链表不为空时 ，才可以让last=head
        {
            while(last->next)     //当while结束时，last指向最后一个结点
            {
                last=last->next;
            }
            last->next=p;//p接在最后一个结点后面
        }
        else
        {
            head->next=p;  //head->next为空，p是被指向的第一个
        }
    }

    fclose(fp);//关闭文件
}

/*读取账单信息*/
void in2(ji *head)
{
    FILE *fp;
    ji *p,*q;
    fp = fopen("account.txt","r");
    while (!feof(fp))
    {
        p= (ji*)malloc(sizeof(ji));//给p分配结构体s空间
        fscanf(fp,"使用人：%s\t用途：%s\t收入日期：%s\t支出日期：%s\t收入：%ld\t支出：%ld\n",p->people,p->use,p->time1,p->time2,&p->shou,&p->zhi);//存入文件，最后由有\n
        p->next=NULL;
        ji *last=head->next; //注意head->next一开始为空
        if(last!=NULL)           //当链表不为空时 ，才可以让last=head
        {
            while(last->next)     //当while结束时，last指向最后一个结点
            {
                last=last->next;
            }
            last->next=p;//p接在最后一个结点后面
        }
        else
        {
            head->next=p;  //head->next为空，p是被指向的第一个
        }
    }

    fclose(fp);//关闭文件
}


/*写入学生信息*/
void out(s *head)
{
    s *p;
    FILE *fp;
    system("cls");
    if((fp=fopen("student.txt","w"))==NULL)
    {
        printf("File open error!\n");
        exit(0);
    }
    for(p=head->next; p; p=p->next)  //把学生信息存进文件中，注意要从p->next开始，因为head没有储存学生信息
        fprintf(fp,"%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);
    fclose(fp);
}

void out2(ji *head)
{
    ji *p;
    FILE *fp;
    system("cls");
    if((fp=fopen("acoount.txt","w"))==NULL)
    {
        printf("File open error!\n");
        exit(0);
    }
    for(p=head->next; p; p=p->next)  //把学生信息存进文件中，注意要从p->next开始，因为head没有储存学生信息
        fprintf(fp,"使用人：%s\t用途：%s\t收入日期：%s\t支出日期：%s\t收入：%ld\t支出：%ld\n",p->people,p->use,p->time1,p->time2,p->shou,p->zhi);//存入文件，最后由有\n
    fclose(fp);
}

/*菜单1*/
void menu()
{
    lo=1;
    char ch,ch2;
    int i;
    system("cls");
    s *head=(s*)malloc(sizeof(s));
    head->next=NULL;
    ji *head2=(ji*)malloc(sizeof(ji));
    head2->next=NULL;

    printf("**------------------------------\n");
    printf("| 欢迎%s,您的身份是管理员      |\n",na);
    printf("+++--------------------------+++\n");
    printf("| 1.录入班级成员信息           |\n");
    printf("| 2.班级成员信息排序           |\n");
    printf("| 3.修改学生信息               |\n");
    printf("| 4.删除指定学号学生           |\n");
    printf("| 5.查找学生                   |\n");
    printf("| 6.添加财务信息               |\n");
    printf("| 7.查询班级财务记录           |\n");
    printf("| 8.统计班级财务情况           |\n");
    printf("| 9.财务用途支出排序           |\n");
    printf("| 10.显示所有学生信息          |\n");
    printf("| 11.返回主菜单                |\n");
    printf("| 12.退出系统                  |\n");
    printf("-------------------------------*\n");
    printf("\n请选择:");
    scanf("%d",&i);
    switch(i)
    {
    case 1:
        system("cls");
        add(head);
        break;
    case 2:
        system("cls");
        sort(head);
        break;
    case 3:
        system("cls");
        mod(head);
        break;
    case 4:
        system("cls");
        dele(head);
        break;
    case 5:
        system("cls");
        query(head);
        break;
    case 6:
        account();
        break;
    case 7:
        print();
        break;
    case 8:
        allsum(head2);
        break;
    case 9:
        sort2();
        break;
    case 10:
        printall();
        break;
    case 11:
        system("cls");
        return first();
    case 12:
        exit(0);
    default:
        while(i<1||i>12)//避免误输
        {
            printf("无此选项，请重新输入!\n");
            scanf("%d",&i);
        }
    }

    system("cls");


}

/*菜单2*/
void menu2()
{
    lo=2;
    char ch,*m,ch2;
    system("cls");
    s *head=(s*)malloc(sizeof(s));
    head->next=NULL;
    ji *head2=(ji*)malloc(sizeof(ji));
    head2->next=NULL;
    printf("**------------------------------------\n");
    printf("| 欢迎%s,您的身份是普通成员          |\n",na);
    printf("+++--------------------------------+++\n");
    printf("| 因为权限问题，您只能使用以下功能： |\n");
    printf("| 5.查找学生                         |\n");
    printf("| 6.添加财务信息                     |\n");
    printf("| 7.查询班级财务记录                 |\n");
    printf("| 8.统计班级财务情况                 |\n");
    printf("| 9.财务用途支出排序                 |\n");
    printf("| 10.显示所有学生信息                |\n");
    printf("| 11.返回主菜单                      |\n");
    printf("| 12.退出系统                        |\n");
    printf("-------------------------------------*\n");
    printf("\n请选择:");
    getchar();
    int i;
    scanf("%d",&i);
    switch(i)
    {
    case 5:
        system("cls");
        query(head);
        break;
    case 6:
        account();
        break;
    case 7:
        print();
        break;
    case 8:
        allsum(head2);
        break;
    case 9:
        sort2();
        break;
    case 10:
        printall();
        break;
    case 11:
        system("cls");
        return first();
    case 12:
        exit(0);
    default:
        while(i<5||i>12)
        {
            printf("无此选项，请重新输入!\n");
            scanf("%d",&i);
        }
    }


}

/*录入学生信息*/
void add(s *head)
{
    FILE *fp;
    int i,temp=0,sum;      //temp用来标记邮箱是否含@，sum用来标记电话号码的位数
    int x;
    system("cls");
    s *p;
    if((fp=fopen("student.txt","a"))==NULL)//在文件末尾追加
    {
        printf("File open error!\n");
        exit(0);
    }

    p=(s*)malloc(sizeof(s));    //申请一个内存;
    printf("请输入学号:\n");
    scanf("%s",p->data.num);
    s *q;
    in(head);    //构建链表
    q=head->next;
    while(q!=NULL)     //p已经指向尾部了,所以要定义一个别的指针来做for循环遍历
    {
        if(strcmp(p->data.num,q->data.num)==0)
        {
            getchar();
            printf("\n学号重复，请稍后重新录入!\n");
            Sleep(1000);
            return add(head);//这里要返回录入函数，是因为如果在循环里再次输入，而且再次输入的
        }                     //数字在前面已经出现过，系统不会提示已经重复
        q=q->next;

    }
    getchar();
    printf("\n请输入姓名:\n");
    scanf("%s",p->data.name);
    getchar();
    printf("\n请输入性别(男生填m，女生填w):\n");
    scanf("%c",&p->data.sex);
    while(1)
    {
        if((p->data.sex=='w')||(p->data.sex=='m'))
            break;
        else
        {
            getchar();   //要在每一项输入之后，读入任意一个字符才能下一步操作
            printf("性别符号输入错误，请重新输入:\n");  //防止出入其他符号
            scanf("%c",&p->data.sex);
        }
    }
    getchar();
    printf("\n请输入年龄:\n");
    scanf("%d",&p->data.age);
    getchar();
    printf("\n请填入班级，仅数字:\n");
    scanf("%d",&p->data.clas);
    getchar();
    printf("\n请输入邮箱(必须有@):\n");
    scanf("%s",p->data.mail);
    while(1)
    {
        for(i=0; p->data.mail[i]!='\0'; i++)//遍历找寻输入的字符串里面有没有@
        {
            if(p->data.mail[i]=='@')
            {
                temp=1;
            }
        }
        if(temp==0)
        {
            printf("邮箱中不包含@，请重新输入:\n");
            scanf("%s",p->data.mail);
        }
        else break;
    }
    getchar();
    printf("\n请输入电话号码，必须是11位:\n");
    scanf("%s",p->data.number);
    while(1)
    {
        sum=0;
        for(i=0; p->data.number[i]!='\0'; i++)//遍历字符串看是否为十一位
        {
            sum+=1;
        }
        if(sum!=11)
        {
            getchar();
            printf("号码位数超过11位或者少于11位，请重新输入:\n");
            scanf("%s",p->data.number);
        }
        else break;
    }
    getchar();
    printf("\n是否还要继续录入（是请输入1，否请输入0）：\n");
    scanf("%d",&x);
    if((fp=fopen("student.txt","a"))==NULL)//在文件末尾追加
    {
        printf("File open error!\n");
        exit(0);
    }
    fprintf(fp,"%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);//存储信息
    fclose(fp);
    printf("\n信息已经存入文件\n");
    system("pause");//待用户按下任意一个按键，使该程序从暂停状态返回到执行状态继续从刚才暂停的地方开始执行
    s *k;
    p=head->next;
    while(p!=NULL)       //清空链表，只剩head,方便之后的操作
    {
        k=p->next;
        free(p);
        p=k;
    }
    head->next=NULL;
    if(x==0)
    {

        if(lo==1)
        {
            return menu();
        }
        else if(lo==2)
        {
            return menu2();
        }
    }
    else if(x==1)
    {
        return add(head);
    }
    while(x!=1&&x!=0)
    {
        printf("输入错误，请重新输入\n");
        scanf("%d",&x);
        if(x==0)
        {

            if(lo==1)
            {
                return menu();
            }
            else if(lo==2)
            {
                return menu2();
            }
        }
        else if(x==1)
        {
            return add(head);
        }

    }

}


/*删除学生信息*/
void dele(s *head)
{
    int temp=0,i,flag2;
    in(head);   //信息的读取
    s *p,*q;
    char numb[15];
    FILE *fpw=fopen("tmp.txt","w");
    char ch1;
    ch1='-';
    system("cls");
    printf("请输入学号：");
    scanf("%s",numb);
    for(q=head,p=head->next; p; q=p,p=p->next) //遍历链表，条件是p存在
    {
        if(strcmp(numb,p->data.num)==0)
        {
            temp=1;
            system("cls");
            printf("学生信息如下：");
            printf("学号：%s\n",p->data.num);
            printf("姓名：%s\n",p->data.name);
            printf("性别：%c\n",p->data.sex);
            printf("年龄：%d\n",p->data.age);
            printf("班级：%d\n",p->data.clas);
            printf("邮箱：%s\n",p->data.mail);
            printf("电话号码：%s\n",p->data.number);
            for(i=1; i<=50; i++)   //分割线
            {
                printf("%c",ch1);
            }
            printf("\n");
            printf("是否要删除此学生信息？（是输入1|否输入2）\n");
            scanf("%d",&flag2);
            if(flag2==2)
            {
                printf("取消删除,三秒后返回主菜单");
                Sleep(3000);
                menu();
            }
            if(flag2==1)
            {
                if(q)
                {
                    q->next=p->next;   //将前一个指针指向要删除的后一个结点
                    out(head);  //清空文件，重新将学生信息写入文件
                }
                else
                {
                    head->next=p->next;
                    out(head);
                }
                free(p);
                printf("信息已删除");
                printf("三秒后返回主菜单");
                Sleep(3000);
                if(lo==1)
                {
                    return menu();
                }
                else if(lo==2)
                {
                    return menu2();
                }
            }
        }
    }
    if(temp==1)    //如果temp等于一说明信息已经删除，把改过后的链表重新写入文件中
    {
        out(head);
    }
    if(temp==0)     //没有找到学生的信息
    {

        printf("\n没有找到此学生信息！\n");
        printf("(输入1返回菜单)\n");
        int j;
        scanf("%d",&j);
        if(j==1)
        {
            if(lo==1)
            {
                return menu();
            }
            else if(lo==2)
            {
                return menu2();
            }
        }
        else
        {
            while(j!=1)
            {
                printf("输入错误，请重新输入！\n");//防止误输
                scanf("%d",&j);
            }
            if(lo==1)
            {
                return menu();
            }
            else if(lo==2)
            {
                return menu2();
            }

        }
    }
    s *k;
    p=head->next;
    while(p!=NULL)     //清空链表，只剩head,方便之后的操作
    {
        k=p->next;
        free(p);
        p=k;  //使p成为下一个
    }
    head->next=NULL; //重置head
}

/*修改学生信息*/
void mod(s *head)
{
    int nums;
    FILE *fp;
    system("cls");
    s *p,*q;        //作为链表中的指针
    in(head);
    char *m;        //用来控制修改的信息编号
    int temp=0;
    int i,sui,ban,j=1;     //代表修改的年龄班级
    char num1[15];
    char ch[8],xi;
    char xuehao[15],ming[20],xingbie,youxiang[20],haoma[20];//代表要修改的信息名
    printf("请输入要修改的学生的学号:\n");
    getchar();
    scanf("%s",num1);
    nums= atoi(num1);    //把字符串改为整数
    for(p=head->next; p; p=p->next)                //遍历列表，寻找与输入相同的学号
    {
        if(strcmp(num1,p->data.num)==0)
        {
            temp=1;        //找到信息后标记为1,标记为0说明没有该学生
            printf("该学生信息如下：\n");
            printf("1.学号：%s\n",p->data.num);
            printf("2.姓名：%s\n",p->data.name);
            printf("3.性别:%c\n",p->data.sex);  //找到后显示出完整信息
            printf("4.年龄：%d\n",p->data.age);
            printf("5.班级：%d\n",p->data.clas);
            printf("6.邮箱：%s\n",p->data.mail);
            printf("7.电话号码：%s\n",p->data.number);
            printf("0.退出\n");
            for(i=1; i<=50; i++) //分割线
            {
                printf("-");
            }
            printf("\n");
            printf("请输入要修改信息的相应序号(可多选)：\n");
            scanf("%s",ch);
            getchar();
            m=ch;
            for(; *m!='\0'; m++)      //用循环来解决修改多个学生信息的问题
            {
                switch(*m)
                {
                case '1':
                    printf("请输入新的学号:\n");
                    scanf("%s",xuehao);
                    strcpy(p->data.num,xuehao);
                    break;
                case '2':
                    printf("\n请输入新的姓名:\n");
                    scanf("%s",ming);
                    strcpy(p->data.name,ming);
                    break;
                case '3':
                    printf("\n请输入新的性别:\n");
                    scanf("%c",&xi);
                    p->data.sex=xi;
                    break;
                case '4':
                    printf("\n请输入新的年龄:\n");
                    scanf("%d",&sui);
                    p->data.age=sui;
                    break;
                case '5':
                    printf("\n请输入新的班级:\n");
                    scanf("%d",&ban);
                    p->data.clas=ban;
                    break;
                case '6':
                    printf("\n请输入新的邮箱:\n");
                    scanf("%s",youxiang);
                    strcpy(p->data.mail,youxiang);
                    break;
                case '7':
                    printf("\n请输入新的电话号码:\n");
                    scanf("%s",haoma);
                    strcpy(p->data.number,haoma);
                    break;

                case '0':
                    if(lo==1)
                    {
                        return menu();
                    }
                    else if(lo==2)
                    {
                        return menu2();
                    };
                default :
                    printf("抱歉，无此选项！\n");//防止误输后导致退出系统
                    continue;
                }
            }
            getchar();
            printf("修改后的信息如下:\n");
            printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);//输出修改后的信息
            system("pause");//防止闪屏
        }
    }
    if(temp==1)    //如果temp等于一说明信息已经删除，把改过后的链表重新写入文件中
    {
        out(head);
    }

    if(temp==0)    //没找到学生信息
    {
        printf("抱歉，没有此学生的信息!\n");
        system("pause");
    }
    s *k;
    p=head->next;
    while(p!=NULL)     //清空链表，只剩head,方便之后的操作
    {
        k=p->next;
        free(p);
        p=k;
    }
    head->next=NULL;
    if(lo==1)
    {
        return menu();
    }
    else if(lo==2)
    {
        return menu2();
    }

}

/*查询学生信息*/
void query(s *head)
{
    s *p;    //p用来遍历查找的内容
    in(head);
    p=head->next;
    system("cls");
    int i,sui,ban,temp=0;   //temp用来标记是否找到信息
    char ch;
    char xuehao[15],ming[20],xingbie,youxiang[20],haoma[20]; //用来输入查找的信息
    printf("=================\n") ;
    printf("| 1.学号        |\n");
    printf("| 2.姓名        |\n");
    printf("| 3.性别        |\n");
    printf("| 4.年龄        |\n");
    printf("| 5.班级        |\n");
    printf("| 6.邮箱        |\n");
    printf("| 7.电话号码    |\n");
    printf("| 0.退出        |\n");
    printf("=================\n");
    printf("\n");
    printf("请选择输入要查询的信息编号:\n");
    getchar();
    ch=getchar();
    int k1=0;
    if(ch=='1')
    {
        getchar();
        printf("请输入要查找的学号:\n");
        scanf("%s",xuehao);

        while(p)//p不为NULL
        {
            if(strcmp(xuehao,p->data.num)==0)
            {
                k1++;
                if(k1==1)
                {
                    printf("\n班级成员信息如下：\n");
                    printf("------------------------------------------------------------\n");
                    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话号码\n");
                }
                temp=1;
                printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);

            }
            p=p->next;
        }
    }
    if(ch=='2')
    {
        getchar();
        printf("请输入要查找的姓名:\n");
        scanf("%s",ming);

        while(p)
        {
            if(strcmp(ming,p->data.name)==0)
            {
                k1++;
                if(k1==1)
                {
                    printf("班级成员信息如下：\n");
                    printf("------------------------------------------------------------\n");
                    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话号码\n");
                }
                temp=1;
                printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);

            }
            p=p->next;
        }
    }
    if(ch=='3')
    {
        getchar();
        printf("请输入要查找的性别:\n");
        scanf("%c",&xingbie);

        while(p)
        {
            if(xingbie==p->data.sex)
            {
                k1++;
                temp=1;
                if(k1==1)
                {
                    printf("班级成员信息如下：\n");
                    printf("------------------------------------------------------------\n");
                    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话号码\n");
                }
                printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);

            }
            p=p->next;
        }
    }
    if(ch=='4')
    {
        getchar();
        printf("请输入要查找的年龄:\n");
        scanf("%d",&sui);

        while(p)
        {
            if(sui==p->data.age)
            {
                k1++;
                if(k1==1)
                {
                    printf("班级成员信息如下：\n");
                    printf("------------------------------------------------------------\n");
                    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话号码\n");
                }
                temp=1;
                printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);

            }
            p=p->next;
        }
    }
    if(ch=='5')
    {
        getchar();
        printf("请输入要查找的班级:\n");
        scanf("%d",&ban);
        temp=1;
        while(p)
        {
            if(ban==p->data.clas)
            {
                k1++;
                if(k1==1)
                {
                    printf("班级成员信息如下：\n");
                    printf("------------------------------------------------------------\n");
                    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话号码\n");
                }
                printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);

            }
            p=p->next;
        }
    }
    if(ch=='6')
    {
        getchar();
        printf("请输入要查找的邮箱:\n");
        scanf("%s",youxiang);

        while(p)
        {
            if(strcmp(youxiang,p->data.mail)==0)
            {
                k1++;
                if(k1==1)
                {
                    printf("班级成员信息如下：\n");
                    printf("------------------------------------------------------------\n");
                    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话号码\n");
                }
                temp=1;
                printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);

            }
            p=p->next;
        }
    }
    if(ch=='7')
    {
        getchar();
        printf("请输入要查找的姓名:\n");
        scanf("%s",haoma);

        while(p)
        {
            if(strcmp(haoma,p->data.number)==0)
            {
                k1++;
                if(k1==1)
                {
                    printf("班级成员信息如下：\n");
                    printf("------------------------------------------------------------\n");
                    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话号码\n");
                }
                temp=1;
                printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",p->data.num,p->data.name,p->data.sex,p->data.age,p->data.clas,p->data.mail,p->data.number);

            }
            p=p->next;
        }
    }
    if(ch=='0')
    {
        if(lo==1)
        {
            system("cls");
            return menu();
        }
        else if(lo==2)
        {
            system("cls");
            return menu2();
        }
    }
    if(temp==0)
    {
        printf("没有找到此学生的信息\n");
        printf("三秒后返回主菜单");
        Sleep(3000);
        if(lo==1)
        {
            system("cls");
            return menu();
        }
        else if(lo==2)
        {
            system("cls");
            return menu2();
        }
    }
    system("pause");
    s *k;
    p=head->next;
    while(p!=NULL)     //清空链表，只剩head,方便之后的操作
    {
        k=p->next;
        free(p);
        p=k;
    }
    head->next=NULL;
    printf("\n查询完毕！\n");
    printf("(输入1返回菜单)\n");
    int j;
    scanf("%d",&j);
    if(j==1)
    {
        if(lo==1)
        {
            return menu();
        }
        else if(lo==2)
        {
            return menu2();
        }
    }
    else
    {
        while(j!=1)
        {
            printf("输入错误，请重新输入！\n");//防止误输
            scanf("%d",&j);
        }
        if(lo==1)
        {
            return menu();
        }
        else if(lo==2)
        {
            return menu2();
        }

    }
}

/*学生信息排序*/
void sort(s *head)
{

    system("cls");
    s *p,*q;
    in(head);
    q=head;
    p=head->next;
    s *w;
    w=head->next;
    char ch;
    long x1,x2;
    printf("请输入要排序的内容：\n1.学号\n2.年龄\n");
    getchar();
    scanf("%c", &ch);
    int a;
    if (ch == '1')
    {
        printf("\n请选择正序还是倒序(正序即学号由小到大）：\n1.正序\n2.倒序\n");
        scanf("%d",&a);
        if(a==1)
        {
            s *temp = (s*)malloc(sizeof(s));
            while (p != NULL)
            {
                while (p->next != NULL)     //学号由小到大
                {
                    x1=strlen(p->data.num);
                    x2=strlen(p->next->data.num);//注意位数，是字符之间比较，而strcmp函数只比较第一个字符大小
                    if(x1==x2)
                    {
                        if (strcmp(p->data.num, p->next->data.num)>0)
                        {
                            temp->data = p->data;
                            p->data = p->next->data;
                            p->next->data = temp->data;
                        }
                    }
                    else if(x1>x2)
                    {
                            temp->data = p->data;
                            p->data = p->next->data;
                            p->next->data = temp->data;
                    }
                    p = p->next;
                }
                p = q->next;
                q = p;
            }
        }
        else if(a==2)
        {
            s *temp = (s*)malloc(sizeof(s));
            while (p != NULL)
            {
                while (p->next != NULL)     //学号由大到小
                {
                    x1=strlen(p->data.num);
                    x2=strlen(p->next->data.num);
                    if(x1==x2)
                    {
                        if (strcmp(p->data.num, p->next->data.num)>0)
                        {
                            temp->data = p->data;
                            p->data = p->next->data;
                            p->next->data = temp->data;
                        }
                    }
                    else if(x1>x2)
                    {
                            temp->data = p->data;
                            p->data = p->next->data;
                            p->next->data = temp->data;
                    }
                    p = p->next;
                }
                p = q->next;
                q = p;
            }

        }
        else
        {
            printf("无此选项，两秒后将返回主菜单！\n");
            Sleep(2000);
            system("cls");
            if(lo==1)
            {
                return menu();
            }
            else if(lo==2)
            {
                return menu2();
            }
        }


    }
    else if(ch=='2')
    {
        printf("\n请选择正序还是倒序(正序即年龄由小到大）：\n1.正序\n2.倒序\n");
        scanf("%d",&a);
        s *temp = (s*)malloc(sizeof(s));
        if(a==1)
        {
            while (p != NULL)
            {
                while (p->next != NULL)    //年龄由小到大
                {
                    if (p->data.age > p->next->data.age)
                    {
                        temp->data = p->data;
                        p->data = p->next->data;
                        p->next->data = temp->data;
                    }
                    p = p->next;
                }
                p = q->next;
                q = p;
            }
        }
        else if(a==2)
        {
            while (p != NULL)
            {
                while (p->next != NULL)    //年龄由大到小
                {
                    if (p->data.age < p->next->data.age)
                    {
                        temp->data = p->data;
                        p->data = p->next->data;
                        p->next->data = temp->data;
                    }
                    p = p->next;
                }
                p = q->next;
                q = p;
            }

        }
        else
        {
            printf("无此选项，两秒后将返回主菜单！\n");
            Sleep(2000);
            system("cls");
            if(lo==1)
            {
                return menu();
            }
            else if(lo==2)
            {
                return menu2();
            }
        }

    }

    else
    {
        printf("无此选项，两秒后将返回主菜单！\n");
        Sleep(2000);
        system("cls");
        if(lo==1)
        {
            return menu();
        }
        else if(lo==2)
        {
            return menu2();
        }
    }

    printf("\n排序后的信息如下:\n");
    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话\n");
    while (w != NULL)       //将排序后的链表输出
    {
        printf("%s\t%s\t%c\t%d\t%d\t%s\t%s\n",w->data.num,w->data.name,w->data.sex,w->data.age,w->data.clas,w->data.mail,w->data.number);
        w = w->next;
    }
    system("pause");  //停留在这个操作
    out(head);
    s *k;
    p=head->next;
    while(p!=NULL)     //清空链表，只剩head,方便之后的操作
    {
        k=p->next;
        free(p);
        p=k;
    }
    head->next=NULL;

    if(lo==1)
    {
        return menu();
    }
    else if(lo==2)
    {
        return menu2();
    }

}

/*账目记录*/
void account()
{
    system("cls");
    int n;
    char date[25];
    char item[40];
    char s1[45];
    char count[12];
    FILE *fp;
    ji *p;
    if((fp=fopen("account.txt","a"))==NULL)//在文件后追加数额
    {
        printf("Cannot open file strike any key exit!");
        getch();
        exit(1);
    }
    printf("请输入录入账单次数：\n");
    scanf("%d",&n);
    while(1)
    {
        if(n>0&&n<99999)
        {
            break;
        }
        else
        {
            getchar();    //要在每一项输入之后，读入任意一个字符才能下一步操作
            printf("输入错误，请重新输入：\n");  //防止出入其他符号
            scanf("%d",&n);
        }
    }
    while(n)
    {
        p= (ji*)malloc(sizeof(ji));//分配一个结构体空间
        printf("\n请输入使用人:\n");
        scanf("%s",p->people);
        getchar();
        printf("请输入用途:\n");
        scanf("%s",p->use);
        getchar();
        printf("请输入收入日期(格式如：2021.06.07):\n");
        scanf("%s",p->time1);
        getchar();
        printf("请输入支出日期(格式如：2021.06.07):\n");
        scanf("%s",p->time2);
        getchar();
        printf("请输入收入金额:\n");
        scanf("%ld",&p->shou);
        getchar();
        printf("请输入支出金额:\n");
        scanf("%ld",&p->zhi);
        getchar();
        fprintf(fp,"使用人：%s\t用途：%s\t收入日期：%s\t支出日期：%s\t收入：%ld\t支出：%ld\n",p->people,p->use,p->time1,p->time2,p->shou,p->zhi);//存入文件，最后由有\n
        n--;

    }
    fclose(fp);
    printf("\n信息已录入！\n");
    system("pause");
    if(lo==1)
    {
        return menu();
    }
    else if(lo==2)
    {
        return menu2();
    }

}

/*班级财务统计*/
void allsum(ji  *head2)
{
    int m;
    system("cls");
    long sum1=0,sum2=0,sum3=0,sum4=0,sum5=0,sum6=0,sum7=0,sum8=0,sum9=0,sum10=0,sum11=0,sum12=0;
    long summ1=0,summ2=0,summ3=0,summ4=0,summ5=0,summ6=0,summ7=0,summ8=0,summ9=0,summ10=0,summ11=0,summ12=0;
    long su1=0,su2=0,su3=0,su4=0,su5=0,su6=0,su7=0,su8=0,su9=0,su10=0,su11=0,su12=0;
    printf("+--------------------------+\n");
    printf("+ 请选择要查询的内容：     +\n");
    printf("+==========================+\n");
    printf("+ 1.班级每月收入、支出     + \n");
    printf("+--------------------------+\n");
    printf("+ 2.班级整个学期收入、支出 + \n");
    printf("+--------------------------+\n");
    getchar();
    scanf("%d",&m);
    in2(head2); //读取文件信息
    ji *q,*p;
    p=head2->next;
    while(p!=NULL)
    {

        char c=p->time1[5];//收入月份
        char ch=p->time1[6];

        if(c=='0')
        {

            if(ch=='1')
            {

                sum1=sum1+p->shou;

            }
            else if(ch=='2')
            {
                sum2=sum2+p->shou;

            }
            else if(ch=='3')
            {

                sum3=sum3+p->shou;
            }
            else if(ch=='4')
            {

                sum4=sum4+p->shou;
            }
            else if(ch=='5')
            {

                sum5=sum5+p->shou;
            }
            else if(ch=='6')
            {
                sum6=sum6+p->shou;

            }
            else if(ch=='7')
            {
                sum7=sum7+p->shou;
            }
            else if(ch=='8')
            {
                sum8=sum8+p->shou;

            }
            else if(ch=='9')
            {

                sum9=sum9+p->shou;

            }

        }
        else if(c=='1')
        {

            if(ch=='0')
            {
                sum10=sum10+p->shou;
            }
            else if(ch=='1')
            {
                sum11=sum11+p->shou;
            }
            else if(ch=='2')
            {
                sum12=sum12+p->shou;

            }
        }

        char c2=p->time2[5];
        char ch2=p->time2[6];  //支出月份

        if(c2=='0')
        {

            if(ch2=='1')
            {
                summ1=summ1+p->zhi;
            }
            else if(ch2=='2')
            {
                summ2=summ2+p->zhi;
            }
            else if(ch2=='3')
            {
                summ3=summ3+p->zhi;

            }
            else if(ch2=='4')
            {
                summ4=summ4+p->zhi;
            }
            else if(ch2=='5')
            {
                summ5=summ5+p->zhi;

            }
            else if(ch2=='6')
            {
                summ6=summ6+p->zhi;
            }
            else if(ch2=='7')
            {
                summ7=summ7+p->zhi;
            }
            else if(ch2=='8')
            {
                summ8=summ8+p->zhi;

            }
            else if(ch2=='9')
            {
                summ9=summ9+p->zhi;
            }

        }
        else if(c2=='1')
        {

            if(ch2=='0')
            {
                summ10=summ10+p->zhi;
            }
            else if(ch2=='1')
            {
                summ11=summ11+p->zhi;
            }
            else if(ch2=='2')
            {
                summ12=summ12+p->zhi;
            }
        }
        p=p->next;

    }
    su1=sum1-summ1,su2=sum2-summ2,su3=sum3-summ3,su4=sum4-summ4,su5=sum5-summ5,su6=sum6-summ6;//每个月的总额
    su7=sum7-summ7,su8=sum8-summ8,su9=sum9-summ9,su10=sum10-summ10,su11=sum11-summ11,su12=sum12-summ12;
    long sua,suma,summa;
    suma=sum1+sum2+sum3+sum4+sum5+sum6+sum7+sum8+sum9+sum10+sum11+sum12;//学期总收入
    summa=summ1+summ2+summ3+summ4+summ5+summ6+summ7+summ8+summ9+summ10+summ11+summ12;//学期总支出
    sua=suma-summa;//学期总额
    switch(m)
    {
    case 1:
        system("cls");
         printf("+---------------------------------------------+\n");
        printf("+ 以下是班级每月收入/支出（单位:元）\n");
        printf("+==============================================\n");
        printf("+ 一月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum1,summ1,su1);
        printf("+----------------------------------------------\n");
        printf("+ 二月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum2,summ2,su2);
        printf("+----------------------------------------------\n");
        printf("+ 三月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum3,summ3,su3);
        printf("+----------------------------------------------\n");
        printf("+ 四月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum4,summ4,su4);
        printf("+----------------------------------------------\n");
        printf("+ 五月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum5,summ5,su5);
        printf("+----------------------------------------------\n");
        printf("+ 六月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum6,summ6,su6);
        printf("+----------------------------------------------\n");
        printf("+ 七月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum7,summ7,su7);
        printf("+----------------------------------------------\n");
        printf("+ 八月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum8,summ8,su8);
        printf("+----------------------------------------------\n");
        printf("+ 九月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum9,summ9,su9);
        printf("+----------------------------------------------\n");
        printf("+ 十月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum10,summ10,su10);
        printf("+----------------------------------------------\n");
        printf("+ 十一月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum11,summ11,su11);
        printf("+----------------------------------------------\n");
        printf("+ 十二月：\n+ 收入：%ld 支出：%ld 总额：%ld\n",sum12,summ12,su12);
        printf("+----------------------------------------------\n");
        break;
    case 2:
        system("cls");
        printf("+---------------------------------------+\n");
        printf("+ 以下是班级整个学期收入/支出（单位:元）+\n");
        printf("+=======================================+\n");
        printf("+ 总收入：%ld                           +\n",suma);
        printf("+---------------------------------------+\n");
        printf("+ 总支出：%ld                           +\n",summa);
        printf("+---------------------------------------+\n");
        printf("+ 总额：%ld                             +\n",sua);
        printf("+---------------------------------------+\n");
        break;

    }
    system("pause");
    ji *k;
    p=head2->next;
    while(p!=NULL)       //清空链表，只剩head,方便之后的操作
    {
        k=p->next;
        free(p);
        p=k;
    }
    head2->next=NULL;
    if(lo==1)
    {
        return menu();
    }
    else if(lo==2)
    {
        return menu2();
    }

}

/*财务分类输出*/
void sort2()
{
    system("cls");
    FILE *fp;
    ji p;//注意这里要定义结构体，不是指针*p
    int i=0,j,k;
    char pe[500][50],y[500][200],ti1[500][50],ti2[500][50];//分别来记录用途相同的财务记录
    long sh[500],zh[500];
    if((fp=fopen("account.txt","r"))==NULL)
    {
        printf("File open error!\n");
        exit(0);
    }
    printf("+============================+\n");
    printf("|请输入要查找的用途：        |\n");
    printf("|(用途将按支出由高到低排序） |\n");
    printf("+============================+\n");
    char yo[200];
    scanf("%s",yo);
    getchar();
    int flag=0;
    while(1)
    {

        if(EOF== fscanf(fp,"使用人：%s\t用途：%s\t收入日期：%s\t支出日期：%s\t收入：%ld\t支出：%ld\n",p.people,p.use,p.time1,p.time2,&p.shou,&p.zhi))//格式化读取文件
        {
            break;
        }

        if(strcmp(yo,p.use)==0)
        {
            flag=1;
            strcpy(pe[i],p.people);
            strcpy(y[i],p.use);
            strcpy(ti1[i],p.time1);
            strcpy(ti2[i],p.time2);
            sh[i]=p.shou;
            zh[i]=p.zhi;
            i++;
        }
    }
    fclose(fp);
    char t1[50],t2[200],t3[50],t4[50];
    long t5,t6;
    for(j=0; j<i-1; j++)
    {
        for(k=0; k<i-1; k++)
        {
            if(zh[k]<zh[k+1])//冒泡排序，使支由大到小排序
            {
                strcpy(t1,pe[k]);
                strcpy(pe[k],pe[k+1]);
                strcpy(pe[k+1],t1);
                strcpy(t2,y[k]);
                strcpy(y[k],y[k+1]);
                strcpy(y[k+1],t2);
                strcpy(t3,ti1[k]);
                strcpy(ti1[k],ti1[k+1]);
                strcpy(ti1[k+1],t3);
                strcpy(t4,ti2[k]);
                strcpy(ti2[k],ti2[k+1]);
                strcpy(ti2[k+1],t4);
                t5=sh[k];
                sh[k]=sh[k+1];
                sh[k+1]=t5;
                t6=zh[k];
                zh[k]=zh[k+1];
                zh[k+1]=t6;
            }
        }
    }
    if(flag==1)
    {
        printf("\n+===-----------------------------------------------------------------------------------------------------===+\n");
        for(j=0; j<i; j++)
        {
            printf("使用人：%s\t用途：%s\t收入日期：%s\t支出日期：%s\t收入：%ld\t支出：%ld\n",pe[j],y[j],ti1[j],ti2[j],sh[j],zh[j]);
        }
        system("pause");
        if(lo==1)
        {
            return menu();
        }
        else if(lo==2)
        {
            return menu2();
        }
    }
    else
    {
        printf("无此用途，请重新输入！\n");
        Sleep(1000);
        system("cls");
        return sort2();
    }


}

/*打印财务记录数据*/
void print()
{
    system("cls");
    char str[10000];
    FILE *fp;
    int qq;
    if((fp=fopen("account.txt","rt"))==NULL)
    {
        printf("Cannot open file strike any key exit!");
        getch();
        exit(1);
    }
    char ch;
    while(EOF!=(ch=fgetc(fp)))
    {
        putchar(ch);
    }
    printf("\n");
    fclose(fp); //关闭文件
    system("pause");
    if(lo==1)
    {
        return menu();
    }
    else if(lo==2)
    {
        return menu2();
    }

}

/*打印所有学生信息*/
void printall()
{
    system("cls");
    char str[1000];
    FILE *fp;
    int qq;
    printf("学号\t姓名\t性别\t年龄\t班级\t邮箱\t电话\n");
    if((fp=fopen("student.txt","rt"))==NULL)
    {
        printf("Cannot open file strike any key exit!");
        getch();
        exit(1);
    }
    while((fgets(str,1024,fp))!=NULL)//遇到\n停止

    {
        printf(str);
    }
    fclose(fp);
    printf("\n");
    system("pause");
    if(lo==1)
    {
        return menu();
    }
    else if(lo==2)
    {
        return menu2();
    }
}




void first()
{
    system("cls");
    system("color 6");//控制台字体设置为黄色
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("              ------------------------------------------------------------------               \n");
    printf("              ||                    欢迎使用财务管理系统                      ||              \n");
    printf("              ||                                                              ||              \n");
    printf("              ||                请选择：    1注册       2登录                 ||              \n");
    printf("              ------------------------------------------------------------------               \n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    int i;
    scanf("%d",&i);

    if(i==1)
    {
        Sleep(300);
        system("color 7"); // 恢复控制台的颜色
        system("cls");
        return registers();
    }
    else if(i==2)
    {
        Sleep(300);
        system("color 7");
        system("cls");
        return Input_loin();
    }
    else
    {
        while(i!=1&&1!=2)
        {
            printf("无此选项，请重新选择！\n");
            getchar();
            scanf("%d",&i);
            if(i==1)
            {
                Sleep(300);
                system("color 7");
                system("cls");
                return registers();
            }
            else if(i==2)
            {
                Sleep(300);
                system("color 7");
                system("cls");
                return Input_loin();
            }
        }
    }

}

int main()
{

    first();          //进入系统界面

}

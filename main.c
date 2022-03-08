/******************************************************************
** 文件名: experiment8
** 创建人: 张思龙
** 日 期: 2020年6月20日
** 修改人: 
** 日 期: 
** 描 述: 人事管理系统V4.0，可实现对员工的基本信息进行管理
**-----------------------------------------------------------------
 ******************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 30
typedef struct date
{
    int year;
    int month;
    int day;
} Date;
struct Employ
{
    char name[15];
    long int ID;
    Date hire;
    int salary;
};
void Input_record (struct Employ employee[N],int n,FILE *fp);
void Sort_by_ID (struct Employ employee[N],int n);
void Sort_by_name(struct Employ employee[N],int n);
void Search_by_ID (struct Employ employee[N],int n);
void Search_by_name(struct Employ employee[N],int n);
void List_record (struct Employ employee[N],int n);
void Delete_record(struct Employ employee[N],int n,FILE *fp);
void Search_by_hire_date(struct Employ employee[N],int n);
void Modify_record(struct Employ employee[N],int n,FILE *fp);
void Statistic(struct Employ employee[N],int n);
void Sort_by_hire_date(struct Employ employee[N],int n);
int main()
{
    int c,k;
    struct Employ employee[N];
    FILE *fp;
    printf("Number=190310313\nsubject No.8-program No.1\n\n");
    do
    {
        if((fp=fopen("staff.txt","r"))==NULL)
        {
            printf("Failure to open staff.txt!\n");
            exit(0);
        }
        for (k=0; !feof(fp); k++)
        {
            fscanf(fp,"%9ld%15s%6d/%2d/%2d%7d",&employee[k].ID,employee[k].name,&employee[k].hire.year,&employee[k].hire.month,&employee[k].hire.day,&employee[k].salary);
        }
        fclose(fp);
        printf("1.Input record\n2.Delete record\n3.Search by name\n4.Search by ID\n5.Search by hire date\n6.Modify record\n7.Statistic\n8.Sort record in descending by ID\n9.Sort record in descending by name\n10.Sort record in descending by hire date\n11.List record\n0.Exit\n");      /*输出菜单并选择选项*/
        printf("=========================================================\n");
        printf("Please input your choice:");
        scanf("%d",&c);
        switch (c)
        {
        case 1:
            Input_record(employee,k,fp);
            printf("=========================================================\n");
            break;
        case 2:
            Delete_record(employee,k,fp);
            printf("=========================================================\n");
            break;
        case 3:
            Search_by_name(employee,k);
            printf("=========================================================\n");
            break;
        case 4:
            Search_by_ID(employee,k);
            printf("=========================================================\n");
            break;
        case 5:
            Search_by_hire_date(employee,k);
            printf("=========================================================\n");
            break;
        case 6:
            Modify_record(employee,k,fp);
            printf("=========================================================\n");
            break;
        case 7:
            Statistic(employee,k);
            printf("=========================================================\n");
            break;
        case 8:
            Sort_by_ID(employee,k);
            printf("=========================================================\n");
            break;
        case 9:
            Sort_by_name(employee,k);
            printf("=========================================================\n");
            break;
        case 10:
            Sort_by_hire_date(employee,k);
            printf("=========================================================\n");
            break;
        case 11:
            List_record(employee,k);
            printf("=========================================================\n");
            break;
        case 0:
            printf("Program end!\n");
            printf("=========================================================\n");
            break;
        }
    }
    while(c!=0);
    return 0;
}
void Input_record (struct Employ employee[N],int n,FILE *fp)
{
    getchar();
    printf("Input employee's name:");
    gets(employee[n].name);
    printf("Input employee's ID,wage(ID,wage):");
    scanf("%ld,%d",&employee[n].ID,&employee[n].salary);
    while (employee[n].salary<5000||employee[n].salary>20000)
    {
        printf("5000<=wage<=20000,Please input again:");
        scanf("%ld,%d",&employee[n].ID,&employee[n].salary);
    }
    printf("Input employee's entry date(xxxx/xx/xx):");
    scanf("%d/%d/%d",&employee[n].hire.year,&employee[n].hire.month,&employee[n].hire.day);
    if((fp=fopen("staff.txt","a"))==NULL)
    {
        printf("Failure to open staff.txt!\n");
        exit(0);
    }
    fprintf(fp,"\n%9ld%15s%6d/%02d/%02d%7d",employee[n].ID,employee[n].name,employee[n].hire.year,employee[n].hire.month,employee[n].hire.day,employee[n].salary);
    fclose(fp);
}
void Delete_record(struct Employ employee[N],int n,FILE *fp)
{
    long int a;
    int b=-1,i;
    printf("Please input the employee's ID:");
    scanf("%ld",&a);
    do
    {
        b++;
        if(a==employee[b].ID)
            break;
    }
    while(b<=n-1);
    do
    {
        employee[b]=employee[b+1];
        b++;
    }
    while(b<=(n-1));
    if((fp=fopen("staff.txt","w"))==NULL)
    {
        printf("Failure to open staff.txt!\n");
        exit(0);
    }
    for(i=0; i<n-2; i++)
    {
        fprintf(fp,"%9ld%15s%6d/%02d/%02d%7d\n",employee[i].ID,employee[i].name,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day,employee[i].salary);
    }
    fprintf(fp,"%9ld%15s%6d/%02d/%02d%7d",employee[i].ID,employee[i].name,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day,employee[i].salary);
    fclose(fp);
}
void Search_by_ID (struct Employ employee[N],int n)
{
    long int x;
    int i;
    printf("Input the number you want to search:");
    scanf("%ld",&x);
    for(i=0; i<=n-1; i++)
    {
        if (x==employee[i].ID)
        {
            printf("%s  NO.%-15ldwage:%d    hire date:%d/%02d/%02d\n",employee[i].name,employee[i].ID,employee[i].salary,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day);
            break;
        }
    }
    if (i==n)
        printf("Not found!\n");
}
void Search_by_name (struct Employ employee[N],int n)
{
    char str[50];
    int i;
    getchar();
    printf("Input the employee's name you want to search:");
    gets(str);
    for(i=0; i<=n-1; i++)
    {
        if (strcmp(str,employee[i].name)==0)
        {
            printf("%s  NO.%-15ldwage:%d    hire date:%d/%02d/%02d\n",employee[i].name,employee[i].ID,employee[i].salary,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day);
            break;
        }
    }
    if (i==n)
        printf("Not found!\n");
}
void Search_by_hire_date(struct Employ employee[N],int n)
{
    int y,m,d,i;
    printf("Input the hire date you want to search(year/month/day):");
    scanf("%d/%d/%d",&y,&m,&d);
    for (i=0; i<=n-1; i++)
    {
        if (employee[i].hire.year==y&&employee[i].hire.month==m&&employee[i].hire.day==d)
        {
            printf("%s  NO.%-15ldwage:%d    hire date:%d/%02d/%02d\n",employee[i].name,employee[i].ID,employee[i].salary,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day);
            break;
        }
    }
    if (i==n)
        printf("Not found!\n");
}
void Modify_record(struct Employ employee[N],int n,FILE *fp)
{
    long int a;
    int i;
    printf("Input the employee's ID you want to modify the salary:");
    scanf("%ld",&a);
    for (i=0; i<=n-1; i++)
    {
        if (employee[i].ID==a)
        {
            printf("Input the employee's new salary:");
            scanf("%d",&employee[i].salary);
            if((fp=fopen("staff.txt","w"))==NULL)
            {
                printf("Failure to open staff.txt!\n");
                exit(0);
            }
          for(i=0; i<n-1; i++)
    {
        fprintf(fp,"%9ld%15s%6d/%02d/%02d%7d\n",employee[i].ID,employee[i].name,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day,employee[i].salary);
    }
    fprintf(fp,"%9ld%15s%6d/%02d/%02d%7d",employee[i].ID,employee[i].name,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day,employee[i].salary);
     fclose(fp);
            break;
        }
    }
    if (i==n)
        printf("Not found!\n");
}
void Statistic(struct Employ employee[N],int n)
{
    float t=0,a;
    int i;
    printf("The number of employees:%d\n",n);
    for (i=0; i<=n-1; i++)
    {
        t=t+employee[i].salary;
    }
    a=t/n;
    printf("Total salary is %.2f,average salary is %.2f.\n",t,a);
}
void Sort_by_name(struct Employ employee[N],int n)
{
    struct Employ a;
    int i,j;
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(strcmp(employee[i].name,employee[j].name)>=0)
            {
                a=employee[i];
                employee[i]=employee[j];
                employee[j]=a;
            }
        }
    }
    for(i=0; i<n; i++)
    {
        printf("%s  NO.%-15ldwage:%d    hire date:%d/%02d/%02d\n",employee[i].name,employee[i].ID,employee[i].salary,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day);
    }
}
void Sort_by_ID(struct Employ employee[N],int n)
{
    int i,j;
    struct Employ a;
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if(employee[j].ID>employee[i].ID)
            {
                a=employee[i];
                employee[i]=employee[j];
                employee[j]=a;
            }
        }
    }
    for(i=0; i<n; i++)
    {
        printf("%s  NO.%-15ldwage:%d    hire date:%d/%02d/%02d\n",employee[i].name,employee[i].ID,employee[i].salary,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day);
    }
}
void Sort_by_hire_date(struct Employ employee[N],int n)
{
    int i,j;
    struct Employ a;
    for(i=0; i<n-1; i++)
    {
        for(j=i+1; j<n; j++)
        {
            if((employee[j].hire.year>employee[i].hire.year)||(employee[j].hire.year==employee[i].hire.year&&employee[j].hire.month>employee[i].hire.month)||(employee[j].hire.year==employee[i].hire.year&&employee[j].hire.month==employee[i].hire.month&&employee[j].hire.day>employee[i].hire.day))
            {
                a=employee[i];
                employee[i]=employee[j];
                employee[j]=a;
            }
        }
    }
    for(i=0; i<n; i++)
    {
        printf("%s  NO.%-15ldwage:%d    hire date:%d/%02d/%02d\n",employee[i].name,employee[i].ID,employee[i].salary,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day);
    }
}
void List_record (struct Employ employee[N],int n)
{
    int i;
    for(i=0; i<n; i++)
    {
        printf("%s  NO.%-15ldwage:%d    hire date:%d/%02d/%02d\n",employee[i].name,employee[i].ID,employee[i].salary,employee[i].hire.year,employee[i].hire.month,employee[i].hire.day);
    }
}

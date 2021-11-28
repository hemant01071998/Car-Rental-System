#include<string.h>
#include<stdio.h>
#include"conio2.h"
#include"car.h"
#include <stdlib.h>
#include<windows.h>

void addAdmin()
{
    FILE *fp=fopen("admin.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("admin.bin","wb");
        User u[2]={{"admin","test","test"},{"admin 2","demo","test"}};
        fwrite(u,sizeof(u),1,fp);
    }
    fclose(fp);

}
User*getInput()
{
    int i;
    clrscr();
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(32,5);
    printf("* LOGIN PANEL *");
    gotoxy(1,7);
    textcolor(LIGHTCYAN);
    for(i=0;i<80;i++)
    printf("%c",247);
    gotoxy(1,15);
    for(i=0;i<80;i++)
    printf("%c",247);
    gotoxy(60,8);
    textcolor(WHITE);
    printf("Press 0 to exit");
    textcolor(LIGHTCYAN);
    gotoxy(25,10);
    printf("Enter userid:");
    textcolor(WHITE);
    static User u;
    fflush(stdin);
    fgets(u.userid,20,stdin);
    char*pos;
    pos=strchr(u.userid,'\n');
    if(pos!=NULL)
    {
        *pos='\0';
    }
    if(strcmp(u.userid,"0")==0)
    {
      textcolor(LIGHTRED);
      gotoxy(30,17);
      printf("Login Cencelled");
      getch();
      textcolor(YELLOW);
      return NULL;
    }
    textcolor(LIGHTCYAN);
    gotoxy(25,11);
    printf("Enter password:");
    fflush(stdin);
    i=0;
    textcolor(WHITE);
    for(;;)
    {
        u.pwd[i]=getch();
        if(u.pwd[i]==13)
          {
            break;
          }
        else if(u.pwd[i]==8)
        {

            printf("\b \b");
            i=i-1;
        }
        else
        {
            printf("*");
            i++;
        }

    }
    u.pwd[i]='\0';
    if(strcmp(u.pwd,"0")==0)
    {
      textcolor(LIGHTRED);
      gotoxy(30,17);
      printf("Login Cencelled");
      getch();
      textcolor(YELLOW);
      return NULL;
    }
   // getch();
    return &u;
}
int checkUserExist(User u,char *usertype)
{
    if(strlen(u.userid)==0||strlen(u.pwd)==0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Both fields are mandatory.Try again ");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t");
        return 0;
    }
    FILE *fp;
    if(strcmp(usertype,"admin")==0)
    {
        fp=fopen("admin.bin","rb");
    }
    else
    {
        fp=fopen("emp.bin","rb");

    }
    if(fp==NULL)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Sorry ! cann't open the file");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t");
        return -1;
    }
    int found=0;
    User user;
    while(fread(&user,sizeof(user),1,fp)==1)
    {
        if((strcmp(u.userid,user.userid)==0) && (strcmp(u.pwd,user.pwd)==0))
        {
            found=1;
            break;
        }
    }

    if(found==0)
    {
        gotoxy(28,20);
        textcolor(LIGHTRED);
        printf("Invalid Userid/password.Try again");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t");

    }
    else
    {
        gotoxy(28,20);
        textcolor(GREEN);
        printf("Login successfully!");
        getch();
        gotoxy(28,20);
        printf("\t\t\t\t");
    }
     fclose(fp);
     return found;
}


int adminMenu()
{
    int i,choice;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("ADMIN MENU\n");
    for(i=0;i<80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1.Add Employee");
    gotoxy(32,9);
    printf("2.Add Car Details");
    gotoxy(32,10);
    printf("3.Show Employee");
    gotoxy(32,11);
    printf("4.Show Car Details");
    gotoxy(32,12);
    printf("5.Delete Employee");
    gotoxy(32,13);
    printf("6.Delete Car Details");
    gotoxy(32,14);
    printf("7.Exit");
    gotoxy(32,16);
    printf("Enter choice :");
    textcolor(WHITE);
    scanf("%d",&choice);
    return choice;

}


void addEmployee()
{
  char empid[10]={"EMP-"};
  char temp[10];
  char choice;
  char *pos;
  User u;
  FILE *fp=fopen("emp.bin","ab+");
  fseek(fp,0,SEEK_END);
  long total_rec=ftell(fp)/sizeof(User);
  if(total_rec!=0)
  {
      fseek(fp,-60,SEEK_END);
      fread(temp,sizeof(temp),1,fp);
     // printf("temp is %s",temp);
   //  getch();
      pos=strchr(temp,'-');
      total_rec=atoi(pos+1);                     //atoi=ASCII to integer(it change string no. to integer no.)ex-"25"=25
    //  printf("\ntotal rec is %ld",total_rec);
    //  getch();
  }
  total_rec++;
  sprintf(temp,"%ld",total_rec);
  strcat(empid,temp);
  strcpy(u.userid,empid);
  fseek(fp,0,SEEK_END);
  do
  {
      clrscr();
      gotoxy(32,2);
      textcolor(LIGHTRED);
      printf("CAR RENTAL APP");
      textcolor(LIGHTGREEN);
      int i;
      gotoxy(1,3);
      for(i=0;i<80;i++)
        printf("~");
      textcolor(WHITE);
      gotoxy(25,5);
      printf("**ADD EMPLOYEE DETAILS**");
      gotoxy(1,8);
      textcolor(YELLOW);
      printf("Enter Employee Name:");
      fflush(stdin);
      textcolor(WHITE);
      fgets(u.name,20,stdin);
      char*pos;
      pos=strchr(u.name,'\n');
      if(pos!=NULL)
      {
          *pos='\0';
      }
      textcolor(YELLOW);
      printf("Enter Employee Pwd:");
      fflush(stdin);
      textcolor(WHITE);
      fgets(u.pwd,20,stdin);
      pos=strchr(u.pwd,'\n');
      if(pos!=NULL)
      {
          *pos='\0';
      }
      fwrite(&u,sizeof(u),1,fp);
      gotoxy(30,15);
      textcolor(LIGHTGREEN);
      printf("EMPLOYEE ADDED SUCCESSFULLY!");
      printf("\nEMPLOYEE ID is %s",u.userid);
      getch();
      gotoxy(1,20);
      textcolor(LIGHTRED);
      printf("Do you want add more employees (Y/N):");
      textcolor(WHITE);
      fflush(stdin);
      scanf("%c",&choice);
      if(choice=='N'||choice=='n')
        break;
      total_rec++;
      sprintf(u.userid,"EMP-%ld",total_rec);

  }while(1);
  fclose(fp);
}


void addCarDetails()
{
  int temp;
    Car c;
   int i;
   char choice,*pos;
   FILE *fp=fopen("car.bin","ab+");
   fseek(fp,0,SEEK_END);
   long total_rec =ftell(fp)/sizeof(Car);
   if( total_rec!=0)
{
   fseek(fp,-68,SEEK_END);
   fread(&temp,sizeof(temp),1,fp);
   printf("\nlast car id is %d",temp);
   getch();

    printf("\ntotal car is %ld",total_rec);
    total_rec=temp;
   getch();
}
   total_rec++;
   c.car_id=total_rec;
   fseek(fp,0,SEEK_END);
do
{
    clrscr();
    gotoxy(32,2);
    textcolor(LIGHTRED);
    printf("CAR RENTAL APP\n");
    textcolor(LIGHTGREEN);
   for(i=0;i<80;i++)
   {   printf("~");   }
   gotoxy(25,6);
   textcolor(WHITE);
   printf("**ADD CAR DETAILS**");
   gotoxy(1,9);
   textcolor(YELLOW);
   printf("Enter Car Model:");
   fflush(stdin);
   textcolor(WHITE);
   fgets(c.car_name,20,stdin);
   pos=strchr(c.car_name,'\n');
   if(pos!=NULL)
   *pos='\0';
   gotoxy(1,10);
    textcolor(YELLOW);
   printf("Enter Car Capacity:");
   fflush(stdin);
   textcolor(WHITE);
   scanf("%d",&c.capacity);
   gotoxy(1,11);
   textcolor(YELLOW);
   printf("Enter Car Count:");
   fflush(stdin);
    textcolor(WHITE);
   scanf("%d",&c.car_count);
   gotoxy(1,12);
   textcolor(YELLOW);
  printf("Enter Car Price:");
   fflush(stdin);
   textcolor(WHITE);
   scanf("%d",&c.price);
  fwrite(&c,sizeof(c),1,fp);
   gotoxy(32,15);
  textcolor(LIGHTGREEN);
  printf("CAR ADDED SUCESSFULLY\n");
  printf("CAR ID IS: %d",c.car_id);
  gotoxy(1,18);
  textcolor(LIGHTRED);
  printf("DO YOU WANT TO ADD MORE CAR(Y/N)?:");
  textcolor(WHITE);
  fflush(stdin);
  scanf("%c",&choice);
 if(choice=='n'||choice=='N')
   break;
  total_rec++;
 c.car_id=total_rec;

}while(choice=='Y'||choice=='y');
fclose(fp);
}

void viewEmployee()
{
    FILE *fp=fopen("emp.bin","rb");
    User ur;
    int i;
    textcolor(LIGHTRED);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",247);
    }
    gotoxy(31,5);
    textcolor(LIGHTRED);
    printf("EMPLOYEE DETAILS");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",247);
    }
    if(fp==NULL)
    {
        gotoxy(31,9);
        textcolor(LIGHTRED);
        printf("Sorry! No employees added yet!");
        getch();
        return ;
    }
    gotoxy(1,8);
    textcolor(LIGHTGREEN);
    printf(" Employee ID\t\t\tName\t\t\tPassword");
    gotoxy(1,9);
    for(i=1;i<=80;i++)
    {
        printf("%c",247);
    }
    int row=10;
    textcolor(YELLOW);
    while(fread(&ur,sizeof(ur),1,fp)==1)
    {
        gotoxy(2,row);
        printf("%s",ur.userid);
        gotoxy(33,row);
        printf("%s",ur.name);
        gotoxy(57,row);
        printf("%s",ur.pwd);
        row++;
    }
    fclose(fp);
    getch();
}

void showCarDetails()
{
    FILE *fp=fopen("car.bin","rb");
    int i;
    Car car;
    gotoxy(32,1);
    textcolor(YELLOW);
    printf("CAR RENTAL SYSTEM\n");
    for(i=1;i<=80;i++)
      {
        printf("%c",247);
      }
    gotoxy(32,4);
    textcolor(YELLOW);
    printf("* ALL CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<=80;i++)
    printf("%c",247);

     if(fp==NULL)
    {
        gotoxy(31,9);
        textcolor(LIGHTGREEN);
        printf("Sorry! No Car added yet!");
        getch();
        return;
    }
    gotoxy(1,8);
    printf(" Car ID\t     Modal\t     Capacity\t     Available\t     Price/Day");
    gotoxy(1,9);
    for(i=0;i<=79;i++)
     printf("%c",247);
    int row=10;
    textcolor(YELLOW);
    while(fread(&car,sizeof(car),1,fp)==1)
    {
        gotoxy(2,row);
        printf("%d",car.car_id);
        gotoxy(15,row);
        printf("%s",car.car_name);
        gotoxy(32,row);
        printf("%d",car.capacity);
        gotoxy(49,row);
        printf("%d",car.car_count);
        gotoxy(65,row);
        printf("%d",car.price);
        row++;
    }
    fclose(fp);
    getch();
}


int deleteEmp()
{
    FILE *fp1=fopen("emp.bin","rb");
    char empid[10];
    int i,result;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    for(i=0;i<80;i++)
    {
        printf("%c",247);
    }
    gotoxy(29,5);
    printf("* DELETE EMPLOYEE RECORD *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",247);
    }
    gotoxy(1,12);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
    {
        printf("%c",247);
    }
    if(fp1==NULL)
    {
        textcolor(LIGHTGREEN);
        gotoxy(32,10);
        printf("No employee added yet");
        return -1;

    }
    FILE *fp2=fopen("temp.bin","wb");
    if(fp2==NULL)
    {
        textcolor(LIGHTGREEN);
        gotoxy(32,10);
        printf("Sorry! Cann't create temp file");
        return -1;

    }
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter employee id to delete the record:");
    textcolor(WHITE);
    scanf("%s",empid);
    User u;
    int found=0;
    while(fread(&u,sizeof(u),1,fp1)==1)
    {
        if(strcmp(u.userid,empid)!=0)
            fwrite(&u,sizeof(u),1,fp2);
        else
            found=1;
    }
    fclose(fp1);
    fclose(fp2);
    if(found==0)
    {
        remove("temp.bin");

    }
    else
    {
       result=remove("emp.bin");
       if(result!=0)
        return 2;
       result=rename("temp.bin","emp.bin");
       if(result!=0)
        return 2;
    }
    return found;
}
int deleteCarModel()
{
    FILE *fp1 = fopen("car.bin","rb");
    int i,result;
    int carid;
    textcolor(YELLOW);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM");
    gotoxy(1,2);
    for(i = 1 ; i <= 80 ; i++)
        printf("%c",247);
    gotoxy(29,5);
    printf("* DELETE CAR MODEL *");
    textcolor(LIGHTGREEN);
    gotoxy(1,7);
    for(i = 1; i<= 80 ; i++)
        printf("%c",247);
    gotoxy(1,12);
    for( i = 1 ; i <= 80 ; i++)
        printf("%c",247);
    if(fp1 == NULL)
    {
        textcolor(LIGHTRED);
        gotoxy(32,9);
        printf("No Car Added Yet!");
        return -1;
    }
    FILE *fp2 = fopen("temp.bin","wb+");
    gotoxy(10,9);
    textcolor(YELLOW);
    printf("Enter Car Id to delete the record :");
    textcolor(WHITE);
    scanf("%d",&carid);
    Car c;
    int found = 0;
    while(fread(&c,sizeof(c),1,fp1)== 1)
    {
       if(carid != c.car_id)
       fwrite(&c,sizeof(c),1,fp2);
       else
       found = 1;
    }

    fclose(fp1);
    fclose(fp2);
    if(found == 0)
        remove("temp.bin");
    else{
        result = remove("car.bin");
        if(result != 0 )
            return 2;
        result = rename("temp.bin","car.bin");
        if(result != 0)
            return 2;
    }
    return found;
}
int empManu()
{
    int choice,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(34,6);
    printf("EMPLOYEE MANU\n");
    for(i=0;i<80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    printf("1.Rent A Car");
    gotoxy(32,9);
    printf("2.Booking Details");
    gotoxy(32,10);
    printf("3.Available car Details");
    gotoxy(32,11);
    printf("4.All Car details");
    gotoxy(32,12);
    printf("5.Return car");
    gotoxy(32,13);
    printf("6.Exit");
    gotoxy(32,16);
    textcolor(WHITE);
    printf("Enter Choice :");
    scanf("%d",&choice);
    return choice;
}
int SelectcarModel()
{
    FILE *fp=fopen("car.bin","rb");
    int flag;
    int choice,rowno=9;
    Car C;
    gotoxy(34,rowno);
    int carcount=0;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_count>0)
        {
            printf("%d. %s",C.car_id,C.car_name);
            gotoxy(34,++rowno);
            ++carcount;
        }
    }
    if(carcount==0)
        {
            fclose(fp);
          return -2;
        }
    gotoxy(34,rowno+2);
    printf("Enter your choice (0 to quit):");
    while(1)
    {
        flag=0;
        if(choice==0)
        {
            fclose(fp);
            return 0;
        }

        scanf("%d",&choice);
        rewind(fp);
        while(fread(&C,sizeof(C),1,fp)==1)
        {
            if(C.car_id==choice && C.car_count>0)
            {
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            fclose(fp);
            return choice;
        }
        gotoxy(35,rowno+4);
        textcolor(LIGHTRED);
        printf("Wrong Input");
        getch();
        gotoxy(35,rowno+4);
        printf("\t\t\t");
        gotoxy(52,rowno+2);
        printf("\t\t\t");
        gotoxy(52,rowno+2);
        textcolor(WHITE);
    }
}
int isValidDate(struct tm dt)
{
   if(dt.tm_year>=2021 && dt.tm_year<=2022)
   {
       if(dt.tm_mon>=1 && dt.tm_mon<=12)
       {
           if((dt.tm_mday>=1 && dt.tm_mday<=31) && (dt.tm_mon==1 || dt.tm_mon==3 || dt.tm_mon==5 || dt.tm_mon==7 || dt.tm_mon==8 || dt.tm_mon==10 || dt.tm_mon==12))
            return 1;
           else if((dt.tm_mday>=1 && dt.tm_mday<=30) && (dt.tm_mon==4 || dt.tm_mon==6 || dt.tm_mon==9 || dt.tm_mon==11))
            return 1;
           else if( (dt.tm_mday>=1 && dt.tm_mday<=28)&&dt.tm_mon==2)
            return 1;
           else if((dt.tm_mday>=1&&dt.tm_mday<=29)&&dt.tm_mon==2&&(dt.tm_year%400==0||(dt.tm_year%4==0 && dt.tm_year%100!=0)))
            return 1;
       }
   }
   return 0;
}

 void updateCarCount(int c_id)
{
    FILE *fp=fopen("car.bin","rb+");
    if(fp==NULL)
    {
        printf("Sorry! File Cannot be opened !");
        getch();
        return ;
    }
    Car C;
    while(fread(&C,sizeof(Car),1,fp)==1)
    {
        if(C.car_id==c_id)
        {
            int x=C.car_count;
            x--;
            fseek(fp,-8,SEEK_CUR);
            fwrite(&x,sizeof(int),1,fp);
            break;

        }
    }
    fclose(fp);
}
void bookedCarDetails()
{
    clrscr();
    FILE *fp=fopen("customer.bin","rb");
    Customer_Car_Details CC;
    int i;
    gotoxy(32,1);
    textcolor(LIGHTRED);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(LIGHTCYAN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(30,5);
    printf("* BOOKED CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    gotoxy(1,8);
    printf("Mode\t   Cust Name\t   Pick Up\t   Drop\t\t  S_Date\t  E_Date");
    gotoxy(1,9);
    textcolor(LIGHTGREEN);
    for(i=1;i<=80;i++)
        printf("%c",247);
    int row=10;
    textcolor(YELLOW);
    while(fread(&CC,sizeof(Customer_Car_Details),1,fp)==1)
    {
        gotoxy(1,row);
        printf("%s",getCarName(CC.car_id));

        gotoxy(13,row);
        printf("%s",CC.cust_name);

        gotoxy(27,row);
        printf("%s",CC.pickup);

        gotoxy(44,row);
        printf("%s",CC.drop);

        gotoxy(58,row);
        printf("%d-%d-%d",CC.sd.tm_mday,CC.sd.tm_mon,CC.sd.tm_year);

        gotoxy(70,row);
        printf("%d-%d-%d",CC.ed.tm_mday,CC.ed.tm_mon,CC.ed.tm_year);

        row++;
    }
    fclose(fp);
    getch();
}
char *getCarName(int c_id)
{
    FILE *fp=fopen("car.bin","rb");
    if(fp==NULL)
    {
        printf("Sorry! File cannot be opened");
        return NULL;
    }
    static Car C;
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_id==c_id)
        {
            break;
        }
    }
    fclose(fp);
    return C.car_name;
}
int rentCar()
{
    Customer_Car_Details CC;
    int c,i;
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MANU\n");
    for(i=1;i<=80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(32,8);
    c=SelectcarModel();
    if(c==0||c==-2)
    {
        return c;
    }
    CC.car_id=c;
    clrscr();
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM");
    textcolor(LIGHTGREEN);
    gotoxy(35,6);
    printf("EMPLOYEE MANU\n");
    for(i=1;i<=80;i++)
        printf("*");
    gotoxy(1,17);
    for(i=1;i<=80;i++)
        printf("*");
    textcolor(YELLOW);
    gotoxy(27,9);
    printf("Enter customer name :");
    fflush(stdin);
    textcolor(WHITE);
    fgets(CC.cust_name,30,stdin);
    char *pos;
    pos=strchr(CC.cust_name,'\n');
    *pos='\0';
    textcolor(YELLOW);
    gotoxy(27,10);
    printf("Enter pickup point :");
    textcolor(WHITE);
    fflush(stdin);
    fgets(CC.pickup,30,stdin);
    pos=strchr(CC.pickup,'\n');
    *pos='\0';
    textcolor(YELLOW);
    gotoxy(27,11);
    printf("Enter drop point :");
    textcolor(WHITE);
    fflush(stdin);
    fgets(CC.drop,30,stdin);
    pos=strchr(CC.drop,'\n');
    *pos='\0';
    gotoxy(27,12);
    textcolor(YELLOW);
    printf("Enter start date(dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.sd.tm_mday,&CC.sd.tm_mon,&CC.sd.tm_year);
      // int datevalid=isValidDate(CC.sd);
      // if(datevalid==1)
        int datevalide2= isValidDate2(CC.sd);
         if(datevalide2==1)
            break;
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Wrong Date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t");
        gotoxy(56,12);
        printf("\t\t\t");
        gotoxy(56,12);
        textcolor(WHITE);

    }while(1);
    gotoxy(27,13);
    textcolor(YELLOW);
    printf("Enter end date(dd/mm/yyyy):");
    textcolor(WHITE);
    do
    {
        scanf("%d/%d/%d",&CC.ed.tm_mday,&CC.ed.tm_mon,&CC.ed.tm_year);
       // int datevalid=isValidDate(CC.ed);
      //  if(datevalid==1)
       int datevalid3= isValidDate3(CC.sd,CC.ed);
        if(datevalid3==1)
            break;
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Wrong Date!");
        getch();
        gotoxy(27,18);
        printf("\t\t\t");
        gotoxy(54,13);
        printf("\t\t\t");
        gotoxy(54,13);
        textcolor(WHITE);
    }while(1);
    //now validate the date against current date as well as against each other
    FILE *fp;
    fp=fopen("customer.bin","ab");
    if(fp==NULL)
    {
        gotoxy(27,18);
        textcolor(LIGHTRED);
        printf("Sorry! File cannot be opened!");
        return -1;
    }
    fwrite(&CC,sizeof(Customer_Car_Details),1,fp);
     gotoxy(27,18);
     textcolor(WHITE);
     printf("Booking done for car %d",CC.car_id);
     printf("\nPress any key to continue");
     getch();
     fclose(fp);
     updateCarCount(c);
     bookedCarDetails();
     return 1;
}
void availCarDetails()
{
    FILE *fp=fopen("car.bin","rb");
    Car C;
    int i;
    textcolor(LIGHTRED);
    gotoxy(32,1);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(YELLOW);
    for(i=0;i<80;i++)
        printf("%c",247);
    gotoxy(29,5);
    textcolor(LIGHTRED);
    printf("* AVAILABLE CAR DETAILS *");
    gotoxy(1,7);
    textcolor(LIGHTGREEN);
    for(i=0;i<80;i++)
        printf("%c",247);
    if(fp==NULL)
        {
          gotoxy(32,8);
          textcolor(LIGHTRED);
          printf("Sorry! File cannot be opened!");
          getch();
          return ;
        }
    gotoxy(1,8);
    printf("Car ID\t   Model\t\t   Capacity\tAvailable\tPrice/Day");
    gotoxy(1,9);
    for(i=0;i<80;i++)
        printf("%c",247);
    int row=10;
    textcolor(YELLOW);
    while(fread(&C,sizeof(C),1,fp)==1)
    {
        if(C.car_count>0)
        {
            gotoxy(2,row);
            printf("%d",C.car_id);
            gotoxy(13,row);
            printf("%s",C.car_name);
            gotoxy(35,row);
            printf("%d",C.capacity);
            gotoxy(50,row);
            printf("%d",C.car_count);
            gotoxy(68,row);
            printf("%d",C.price);
            row++;

        }
    }
      fclose(fp);
      getch();
}
int isValidDate2(struct tm dt)
{
    SYSTEMTIME stime;
    GetSystemTime(&stime);
    if(dt.tm_mday>=stime.wDay&&dt.tm_mday<=31&&dt.tm_mon>=stime.wMonth&&dt.tm_mon<=12&&dt.tm_year>=stime.wYear&&dt.tm_year<=2022)
        return 1;
    else if(dt.tm_mday<=stime.wDay&&dt.tm_mon>stime.wMonth&&dt.tm_mon<=12&&dt.tm_year>=stime.wYear&&dt.tm_year<=2022)
        return 1;
    else
        return 0;

}
int isValidDate3(struct tm dt,struct tm dtt)
{
    SYSTEMTIME  stime;
GetSystemTime(&stime);
//if(dt.tm_mday>=stime.wDay&&dt.tm_mon>=stime.wMonth&&dt.tm_year>=stime.wYear)
//{
    if(dtt.tm_mday>=dt.tm_mday&&dtt.tm_mday<=31&&dtt.tm_mon>=dt.tm_mon&&dtt.tm_mon<=12&&dtt.tm_year>=stime.wYear&&dtt.tm_year<=2022)
         return 1;
     else if(dtt.tm_mday<dt.tm_mday&&dtt.tm_mon>dt.tm_mon&&dtt.tm_mon<=12&&dtt.tm_year>=stime.wYear&&dtt.tm_year<=2022)
        return 1;
    else
        return 0;

}
/*void return_car()
{

    FILE * fp = fopen("customer.bin","rb");
    if(fp==NULL)
    {
        gotoxy(34,22);
        printf("File can not open");
    }
    //int arr[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    time_t now = time(0);
    struct tm *ptr_now = localtime(&now);
    struct tm temp;
    int i;
    int carid;

    int current_day = ptr_now->tm_yday;
    int current_year = ptr_now->tm_year + 1900;
    int current_month= ptr_now->tm_mon+1;
    int end_day;
    Customer_Car_Details cc;
    while( fread(&cc,sizeof(cc),1,fp) == 1)
    {
        end_day = 0;
        temp= cc.ed;
    //    id = cc.car_id;

        for(i = 0 ; i <= temp.tm_mon-2 ; i++)
            end_day += arr[i];

        end_day += temp.tm_mday;


        if((current_day >= end_day ) && (current_year == temp.tm_year))
        {
            returnUpdateCarCount(cc.car_id);
        }
        else if(current_year > temp.tm_year)
        {
            returnUpdateCarCount(cc.car_id);
        }

    }
    fclose(fp);
    getch();
}
void return_car()
{
    int carid;
    Customer_Car_Details cc;
    clrscr();
  FILE *fp1 = fopen("customer.bin","rb");
    if(fp1==NULL)
    {
        gotoxy(34,22);
        printf("File can not open");
    }
    textcolor(LIGHTRED);
    gotoxy(32,2);
    printf("CAR RENTAL SYSTEM\n");
    textcolor(YELLOW);
    for(int i=1;i<=80;i++)
       {
            printf("%c",247);
       }

    gotoxy(30,6);
    textcolor(WHITE);
    printf("* RETURN CAR DETAILS *\n\n");
    textcolor(LIGHTGREEN);
    for(int i=1;i<=80;i++)
        {
            printf("*");
        }
    FILE *fp2=fopen("temp.bin","wb+");
    gotoxy(1,15);
    for(int i=1;i<=80;i++)
        {
            printf("*");
        }
    gotoxy(6,10);
    textcolor(YELLOW);
     printf("Enter car id whose you want to return :");
     textcolor(WHITE);
     scanf("%d",&carid);
     Car c;
     while(fread(&c,sizeof(c),1,fp1) == 1)
     {
         if(carid==cc.car_id)
         {
             returnUpdateCarCount(cc.car_id);
         }
     }
        fclose(fp1);
        fclose(fp2);

        getch();

}*/
void return_car()
{
    clrscr();
    int i,c_id,flag=0,ans;
    struct tm s;
    Car c;
    Customer_Car_Details CC;
      FILE *fp1=fopen("customer.bin","rb");
    gotoxy(30,1);
    textcolor(RED);
    printf("CAR RENTAL SYSTEM\n");
    for(int i=1;i<=80;i++)
       {
            printf("%c",247);
       }
    gotoxy(63,3);
    textcolor(WHITE);
    printf("Press 0 to return ");
    gotoxy(33,5);
    textcolor(LIGHTCYAN);
    printf("CAR RETURN PANEL");
    gotoxy(28,6);
    for(i=1;i<=28;i++)
        printf("%c",247);
    if(fp1==NULL)
    {
        gotoxy(23,12);
        textcolor(LIGHTRED);
        printf("No Car Has Been Rented ! Rent a car first");
        getch();
        return ;
    }
    char name[20];
    gotoxy(1,8);
    textcolor(YELLOW);
    printf("Enter Customer  name : ");
    gotoxy(1,9);
    textcolor(YELLOW);
    printf("Enter Car Id : ");
    textcolor(WHITE);
    do
    {
           fflush(stdin);
          gotoxy(23,8);
          fgets(name,20,stdin);
          char *pos;
          pos=strchr(name,'\n');
          *pos='\0';
           if(strcmp(name,"0")==0)
           {
           fclose(fp1);
           return ;
           }
         gotoxy(16,9);
         scanf("%d",&c_id);
         if(c_id==0)
         {
             fclose(fp1);
             return ;
         }
         while(fread(&CC,sizeof(CC),1,fp1)==1)
             {
                 if(CC.car_id==c_id&&strcmp(name,CC.cust_name)==0)
                   {
                       flag=1;
                        break;
                   }
             }

        if(flag==0)
        {
            gotoxy(2,12);
            textcolor(LIGHTRED);
            printf("There are no booking details for this car id/Customer !");
            getch();
            gotoxy(2,12);
            printf("\t\t\t\t\t\t\t");
            gotoxy(23,8);
            printf("\t\t\t\t");
            gotoxy(16,9);
            printf("\t\t\t\t");
            textcolor(WHITE);
            rewind(fp1);
            continue;
        }
            textcolor(YELLOW);
            gotoxy(1,10);
            printf("Car Return Date : ");
            textcolor(WHITE);
            do
            {
                scanf("%d/%d/%d",&s.tm_mday,&s.tm_mon,&s.tm_year);
                ans=isValidDate(s);
                if(ans==1)
               // ans=isCorrectDate(CC.sd,s);//Compare with start date vailidation;
               ans=isValidDate3;
                if(ans==0)
                {
                   gotoxy(30,15);
                   textcolor(RED);
                   printf("Invaild Date ! Try again");
                    getch();
                   gotoxy(30,15);
                    printf("\t\t\t\t\t");
                   gotoxy(19,10);
                   printf("\t\t\t\t");
                 gotoxy(19,10);
                 textcolor(WHITE);
                }
            }while(ans==0);

               ans=isValidDate3(s,CC.ed);//Compare with End date for warning;
                 if(ans==0)
               {
                 textcolor(LIGHTRED);
                 gotoxy(5,15);
                 printf("Your are late to return the car so you will be charged extra\n\n\t\t1day= Car rent per/day+240.34Rs.Extra");
                 getch();
                }
            FILE *fp2=fopen("car.bin","rb+");
            FILE *fp3=fopen("temp.bin","wb");
            rewind(fp1);
            while(fread(&CC,sizeof(CC),1,fp1)==1)
            {
                if(CC.car_id==c_id&&strcmp(CC.cust_name,name)==0)
                continue;
                fwrite(&CC,sizeof(CC),1,fp3);
            }
            fclose(fp1);
            fclose(fp3);
            remove("customer.bin");
            rename("temp.bin","customer.bin");
               while(fread(&c,sizeof(c),1,fp2)==1)
                          {
                             if(c_id==c.car_id)
                               {
                                  fseek(fp2,-8,SEEK_CUR);
                                 int temp_count=c.car_count;
                                 temp_count++;
                                 fwrite(&temp_count,sizeof(int),1,fp2);
                                 fclose(fp2);
                                  break;


                                }
                         }
    }while(flag==0);

    gotoxy(33,20);
    textcolor(LIGHTGREEN);
    printf("Car Returned");
    getch();
}
void return_car_Delete()
{
    FILE *fp1 = fopen("customer.bin","rb");
    FILE *fp2 = fopen("temp.bin","wb+");

    Customer_Car_Details cc;

    while(fread(&cc,sizeof(cc),1,fp1) == 1)
    {
        fwrite(&cc,sizeof(cc),1,fp2);
    }
    fclose(fp1);
    fclose(fp2);

    FILE * temp1 = fopen("temp.bin","rb");
    FILE *temp2 = fopen("temp2.bin","wb");

    int found = 0;
    int result;

    int arr[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    time_t now = time(0);
    struct tm *ptr_now = localtime(&now);
     struct tm temp;
    int i;
    //int id;

    int current_day = ptr_now->tm_yday;
    int current_year = ptr_now->tm_year + 1900;
    int end_day;

    while( fread(&cc,sizeof(cc),1,temp1) == 1)
    {
        end_day = 0;
        temp= cc.ed;
    //    id = cc.car_id;

        for(i = 0 ; i <= temp.tm_mon-2 ; i++)
            end_day += arr[i];

        end_day += temp.tm_mday;
        if(((current_day >= end_day ) && (current_year == temp.tm_year)) ||(current_year > temp.tm_year))
        {
            found = 1;

        }
        else
        {
      fwrite(&cc,sizeof(cc),1,temp2);
            printf("\nNot Match Date\n");
            getch();
        }
    }
        fclose(temp1);
        fclose(temp2);


    if(found == 0)
    {
        remove("temp2.bin");
        remove("temp.bin");
    }
    else{
        result = remove("temp1.bin");
        remove("customer.bin");
        if(result != 0 )
        {
            printf("\nremove\n");
            getch();
        }
        result = rename("temp2.bin","customer.bin");
        if(result != 0)
        {
            printf("\nremove\n");
            getch();
        }
    }
}
void returnUpdateCarCount(int c_id)
{
    FILE * fp = fopen("car.bin","rb+");
    if(fp == NULL)
    {
        textcolor(LIGHTRED);
        return ;
    }
    Car c;
    while(fread(&c,sizeof(c),1,fp) == 1)

    {
      if(c.car_id == c_id)
        {
            int x = c.car_count;
            ++x;
            fseek(fp,-8,SEEK_CUR);
            fwrite(&x,sizeof(int),1,fp);
            break;
        }
    }
    fclose(fp);
}

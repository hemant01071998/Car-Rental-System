
#include <stdlib.h>
#include"conio2.h"
#include"car.h"

int main()
{
    int i,choice;
    int type,k;
    int result;
    User*usr;
   gotoxy(25,10);
   textcolor(YELLOW);
   printf("WELCOME TO THE RENTAL SYSTEM");
   gotoxy(20,13);
   textcolor(LIGHTGREEN);
   printf("* RENT A CAR AND GO WHEREVER YOU NEED *");
   getch();
   textcolor(YELLOW);
   addAdmin();

   while(1)
   {
       clrscr();
       textcolor(LIGHTRED);
       gotoxy(32,2);
       printf("CAR RENTAL SYSTEM\n");
       for(i=0;i<80;i++)
       {
           printf("%c",247);
       }
       gotoxy(1,8);
       textcolor(YELLOW);
       for(i=0;i<80;i++)
       {
           printf("*");
       }
       gotoxy(1,18);
       for(i=0;i<80;i++)
       {
           printf("*");
       }
       gotoxy(32,10);
       textcolor(YELLOW);
       printf("1.Admin");
       gotoxy(32,12);
       printf("2.Employee");
       gotoxy(32,14);
       printf("3.Quit");
       gotoxy(32,16);
       textcolor(WHITE);
       printf("Select your role:");
       do
       {
           scanf("%d",&type);
           if(type==1)
           {

               do
               {
                 usr=getInput();
                 if(usr==NULL)
                 {
                     break;
                 }

                 else
                  {
                     k=checkUserExist(*usr,"admin");
                  }
               }while(k==0);
               if(k==-1 || usr==NULL)
                {
                    break;
                }
                if(k==1)
                {
                    gotoxy(1,20);
                    textcolor(WHITE);
                    printf("Press any key to continue");
                    _getch();
                    while(1)
                    {
                        clrscr();
                        choice=adminMenu();
                        if(choice==7)
                            break;
                        switch(choice)
                        {
                        case 1:
                                clrscr();
                                addEmployee();
                                break;
                        case 2:
                                clrscr();
                                addCarDetails();
                                break;
                        case 3:
                                clrscr();
                                viewEmployee();
                                break;
                        case 4:
                                clrscr();
                                showCarDetails();
                                break;
                        case 5:
                                clrscr();
                                result=deleteEmp();
                                gotoxy(15,14);
                                if(result==0)
                                {
                                    textcolor(LIGHTRED);
                                    printf("Sorry! No record of given emp found");

                                }
                                else if(result==1)
                                {
                                   textcolor(LIGHTGREEN);
                                    printf("Rec. deleted successfully!");
                                }
                                else if(result==2)
                                {
                                    textcolor(LIGHTRED);
                                    printf("Error in deletion");
                                }
                                textcolor(WHITE);
                                printf("\nPress any key to go back to the main menu:");
                                getch();
                                break;
                        case 6:
                                clrscr();
                                result=deleteCarModel();
                                gotoxy(15,14);
                          if(result==0)
                          {
                              textcolor(LIGHTRED);
                              printf("Sorry! No record of the given car found");
                          }
                          else if(result==1)
                          {
                              textcolor(LIGHTGREEN);
                              printf("Record delete successfully!");

                          }
                          else if(result==2)
                          {

                              textcolor(LIGHTGREEN);
                              printf("Error in deletion");

                          }
                          textcolor(WHITE);
                          printf("\nPress any key to go back to the menu");
                          getch();
                                break;
                        default:

                                textcolor(LIGHTRED);
                                printf("Wrong choice!\n");
                                getch();
                                clrscr();
                                break;
                        }
                    }
                    break;
                }

           }
           else if(type==2)
           {
               //code for employee login
               do
               {
                   usr=getInput();
                   if(usr==NULL)
                   {
                       break;
                   }

                   else
                   {
                     k=checkUserExist(*usr,"emp");

                   }
               }while(k==0);
               if(k==-1||usr==NULL)
                  break;
               if(k==1)
               {
                   gotoxy(1,20);
                   textcolor(WHITE);
                   printf("Press any key to continue");
                   _getch();
                   while(1)
                   {
                       clrscr();
                       choice=empManu();
                       if(choice==6)
                            break;
                       switch(choice)
                       {
                         case 1:
                                clrscr();
                                int rentresp;
                                rentresp=rentCar();
                                if(rentresp==-2)
                                {
                                    gotoxy(35,9);
                                    textcolor(LIGHTRED);
                                    printf("Sorry! All cars booked.Try later");
                                    getch();

                                }
                                else if(rentresp==0)
                                {
                                    gotoxy(27,18);
                                    textcolor(LIGHTRED);
                                    printf("You did not choose any car");
                                    getch();
                                }
                                break;
                        case 2:
                                clrscr();
                                bookedCarDetails();
                                break;

                        case 3:
                                clrscr();
                                availCarDetails();
                                break;
                        case 4:
                                clrscr();
                                showCarDetails();
                                break;
                        case 5:
                                clrscr();
                                return_car();
                                break;

                        default:
                               break;
                       }

                   }
                   if(choice==6)
                    break;
               }
           }
           else if(type==3)
           {
               clrscr();
               textcolor(GREEN);
               gotoxy(30,12);
               printf("Thank you for using the app");
               getch();
               exit(0);
           }
           else
           {
               textcolor(RED);
               gotoxy(30,20);
               printf("Invalid Choice");
               getch();
               gotoxy(30,20);
               printf("\t\t\t");
               gotoxy(49,16);
               printf("\t\t\t");
               textcolor(WHITE);
               gotoxy(49,16);
           }


       }while(1);
       getch();

   }
    return 0;
}

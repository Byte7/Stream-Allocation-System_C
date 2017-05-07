#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>

/*Structure for storing criteria of marks*/
struct marks_criteria
{
int sc_min,com_min,arts_min, seat_sc, seat_com, seat_arts;
}crit;

/*Function-Reads criteria from administrator*/
void read_criteria()
{
    FILE *fin;
	fin=fopen("criteria.DAT" ,"r");
	fread(&crit,sizeof(struct marks_criteria),1,fin);
	fclose(fin);
}

/*Function-Returns the stream alloted for a student*/
char *stream_name(int strm)
{
	switch(strm)
	{
	case -1:
		return("Not assigned");
	    break;
	case 0:
		return("Nill");
	     	break;
	case 1:
		return("Science");
        break;
	case 2:
		return("Commerce");
	     	break;
	case 3:
		return("Arts");
            break;
	    default:
		return("None");
	}
}

/*Structure for administrator*/
struct administrator
{
	char user_name[10];
	char password[10];
}admin;

/*Structure for student*/
struct student
{
char name[20];
int regno,m_eng,m_math,m_sc,m_sst,m_lang;
int pref_code, stream;   // Sc=1, Com=2, Arts=3
}s,sr[100],t;

/*Function-Displays details of student*/
void display(struct student *s)
{

	printf("\n============================================\n");
	printf("\n\tNAME		:%s ",s->name);
	printf("\n\tREGISTRATION NO. :%d ",s->regno);
	printf("\n\tPERCENTAGE OF MARKS :%d ",( (s->m_eng+s->m_math+s->m_sc+s->m_sst+s->m_lang)/5));
	printf("\n\tSTREAM APPLIED FOR :%s  ",stream_name(s->pref_code));
       //	printf<<"\n\tSTREAM ALLOTED	: "<<stream_name(stream);
	printf("\n============================================\n");

}

/*Function -returns percentage of marks for a student*/
int show_per(struct student *s)
{
	return((s->m_eng+s->m_math+s->m_sc+s->m_sst+s->m_lang)/5);
}

/*Function-Welcome screen*/
void welcome()
{
     system("cls");
     int z;
	/* printf( "\t%%      %%      ");
      printf( "\n\t%%      %%      %%%%%%% %%      %%%%%%  %%%%%% %%%%  %%%% %%%%%%%");
       printf( "\n\t%%      %%      %%      %%      %%      %%  %% %%  %%% %% %%       ");
       printf( "\n\t%%  %%   %%     %%%%%   %%      %%      %%  %% %%  %%% %% %%%%%      ");
       printf( "\n\t%%  %%   %%     %%      %%      %%      %%  %% %%      %% %%           ");
       printf( "\n\t%%%%%%%%%%      %%%%%%% %%%%%%% %%%%%%% %%%%%% %%      %% %%%%%%%     ");*/
       printf("\n\t\t\t\t  WELCOME\n");

       printf( "\n\n\n\tSPA   PROJECT  (********  ON STREAM ALLOCATION  *******)");
       printf( "\n\n\t\t\t\t       BY  :-");
       printf( "\n\n\t\t\t  SAGAR R. PATIL\t  FEIT ");
       printf( " \n\n\n\t\tpress any number and 'ENTER' to continue: ");
       scanf("%d",&z);
}
/*Function-For logging into administrator settings*/
void assign_user()
{
    strcpy(admin.user_name, "srp");
	strcpy(admin.password, "srp");
}

/*Function-For verifying administrator user*/
int verify_password()
{
	char u_name[10];
	char u_pwd[10],temp[2];
	int x=1;
	printf("\n\n   Enter user name : ");
	fflush(stdin);
	gets(u_name);//scanf("%s",&u_name);
	printf("\n\n   Enter Password : ");
	gets(u_pwd);//scanf("%s",&u_pwd);
	x=strcmp(admin.user_name,u_name);
	if (x==0)
	{
		x=strcmp(admin.password,u_pwd);
    }
	gets(temp);
	return(x);
}

/*Function-Allots stream for a student by comparing with minimum criteria*/
void allot_stream(struct student *s)
{
	int	per=(s->m_eng+s->m_math+s->m_sc+s->m_sst+s->m_lang)/5;
	read_criteria();
    switch(s->pref_code)
	{
		case 1:
				if(per>=crit.sc_min)
					s->stream=s->pref_code;
				else
					s->stream=0;
                break;

		case 2:
				if(per>=crit.com_min)
					s->stream=s->pref_code;
				else
					s->stream=0;
				break;

		case 3:
				if(per>=crit.arts_min)
					s->stream=s->pref_code;
				else
					s->stream=0;
				break;
	}
}

/*Function-Returns stream for a student*/
int get_stream(struct student *s)
{
	return(s->stream);
}

/*Function-Takes criteria input from administrator*/
void input_criteria()
{
	FILE *fout;
	fout=fopen("criteria.DAT" ,"a+");
	printf("\nEnter  the  required marks for SCIENCE stream(in percentage)");
	scanf("%d",&crit.sc_min);
	printf("\nEnter  No. of Seats for SCIENCE stream");
	scanf("%d",&crit.seat_sc);
	printf("\nEnter  the  required marks for COMMERCE stream(in percentage)");
	scanf("%d",&crit.com_min);
	printf("\nEnter  No. of Seats for COMMERCE stream");
	scanf("%d",&crit.seat_com);
	printf("\nEnter  the  required marks for ARTS stream(in percentage)");
	scanf("%d",&crit.arts_min);
	printf("\nEnter  No. of Seats for ARTS stream");
	scanf("%d",&crit.seat_arts);
	fwrite(&crit,sizeof(struct marks_criteria),1,fout);
	fclose(fout);
}

/*Function-Inputs data of a student -appending data in file*/
void input_data(struct student *s)
{
    system("cls");
	FILE *fin;
	fin=fopen("student.DAT","a+");
	char t[2],ans;
	while(1)
	{
	printf("\nEnter  the  name of the  student  :  ");
	fflush(stdin);
	gets(s->name);
	printf("\n\nEnter  the roll of the  student  :  ");
	scanf("%d",&(s->regno));
	printf("\n\nEnter  marks in eng  :  ");
	scanf("%d",&(s->m_eng));
	printf("\n\nEnter  marks in math  :  ");
	scanf("%d",&(s->m_math));
	printf("\n\nEnter  marks in science  :  ");
	scanf("%d",&(s->m_sc));
	printf("\n\nEnter  marks in sst  :  ");
	scanf("%d",&(s->m_sst));
	printf("\n\nEnter  marks in language  :  ");
	scanf("%d",&(s->m_lang));
	printf("==================STREAM  PREFERED?================ \n");
	printf("\t[1] for SCIENCE\n");
	printf("\t[2] for COMMERCE\n");
	printf("\t[3] for ARTS ");
	printf("\n================================================= \n\tENTER PREFERENCE CODE : ");
	scanf("%d",&s->pref_code);
	s->stream=-1;
	fwrite(&s,sizeof(struct student),1,fin);
	gets(t);
	printf("\n\tEnter More Student ? (y/n)");
		scanf("%c",&ans);
	if (ans=='n')
		break;
	}
	fclose(fin);
}

/*Function-Inputs data of a student -creating new file and reading data in file*/
void new_file(struct student *s)
{   system("cls");
	FILE *fin;
	fin=fopen("student.DAT","w");
	char t[2],ans;
	while(1)
	{
	printf("\nEnter  the  name of the  student  :  ");
	fflush(stdin);
	gets(s->name);
	printf("\n\nEnter  the roll of the  student  :  ");
	scanf("%d",&s->regno);
	printf("\n\nEnter  marks in eng  :  ");
	scanf("%d",&s->m_eng);
	printf("\n\nEnter  marks in math  :  ");
	scanf("%d",&s->m_math);
	printf("\n\nEnter  marks in science  :  ");
	scanf("%d",&s->m_sc);
	printf("\n\nEnter  marks in sst  :  ");
	scanf("%d",&s->m_sst);
	printf("\n\nEnter  marks in language  :  ");
	scanf("%d",&s->m_lang);
	printf("==================STREAM  PREFERED?================ \n");
	printf("\t[1] for SCIENCE\n");
	printf("\t[2] for COMMERCE\n");
	printf("\t[3] for ARTS ");
	printf("\n================================================= \n\tENTER PREFERENCE CODE : ");
	scanf("%d",&s->pref_code);
	s->stream=-1;
	fwrite(&s,sizeof(struct student),1,fin);
	gets(t);
	printf("\n\tEnter More Student ? (y/n)");
		scanf("%c",&ans);
	if (ans=='n')
		break;
	}
	fclose(fin);
}

/*Function - Reads all students data from file*/
void read_student()
{
	FILE *fin;
	char c;
	fin=fopen("student.DAT" ,"w");
	while(fread(&s,sizeof(struct student),1,fin))
	{
			display(&s);
			printf("\n\tPress any no. to continue ");
			scanf("%c",&c);
			printf("\n");
	}
	fclose(fin);
}

/*Function-Reads data of students from science stream-already alloted stream earlier*/
void read_eligible_sc()
{
	char ans;
    FILE *fout;
	fout=fopen("elig_sc.DAT","w");
	fseek(fout,0,SEEK_SET);
	while(fread(&s,sizeof(struct student),1,fout))
	{
		display(&s);
		printf("\n\t Continue (y/n)? ");
        scanf("%c",&ans);
		if (ans=='n')
			break;
    }
	fclose(fout);
}

/*Function-Reads data of students from commerce stream-already alloted stream earlier*/
void read_eligible_com()
{
	char ans;
	FILE *fout;
	fout=fopen("eligcom.DAT","w");

	while(fread(&s,sizeof(struct student),1,fout))
	{
		display(&s);
		printf("\n\t Continue (y/n)? ");
        scanf("%c",&ans);
        if (ans=='n')
			break;

	}
	fclose(fout);
}

/*Function-Reads data of students from arts stream-already alloted stream earlier*/
void read_eligible_arts()
{
    char ans;
	FILE *fout;
	fout=fopen("eligart.DAT","w");

	while(fread(&s,sizeof(struct student),1,fout))
	{
		display(&s);
		printf("\n\t Continue (y/n)? ");
        scanf("%c",&ans);
		if (ans=='n')
			break;
    }
	fclose(fout);
}

/*Function - clears console screen*/
void clear()
{
        system("cls");
}

/*Function- Gives list of eligible students*/
void select_list( char *in_file, char *out_file)
{
	FILE *sel,*fin;
	int n=0, i,j;
	//student sl[100], t;

		sel=fopen(out_file, "rb");
		fin=fopen(in_file,"wb");

		while(fread(&sr[n],sizeof(struct student),1,fin))
		{
			n++;
        }
		printf("\nNo of Eligible Students  = %d\n",n);
		for(i=0;i<n;i++)
		{
			for(j=i+1;j<=n;j++)
			{
				if (show_per(&sr[i])<show_per(&sr[j]))
				{
					t=sr[j];
					sr[j]=sr[i];
					sr[i]=t;
				}
			}
		}
		for(i=0;i<n;i++)
		{
			fprintf(sel,(char*)&sr[i]);//fwrite(&sr[i],sizeof(struct student),1,fin)
		}
	fclose(sel);
	fclose(fin);

}

/*Function-Thank you Screen*/
void thanks()
{       int w;
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\n\t*******   T H A N K   Y O U   F O R   W O R K I N G   *******");
		printf("\n\n\n\n\n\n\n\t\t\tpress any number and then 'ENTER' to exit");
		scanf("%d",&w);
}

/*main Function*/
int main()
{


     system("cls");
     welcome();      //calls function welcome

FILE *fin;//*fout;
FILE *fsc,*fcom,*farts;
int opt=1, ch;

while(opt!=8)
{
    /*Main menu*/
	clear();
	printf("\n\t======================  MAIN   MENU  =======================\n");
	printf("\n\t[1] CREATE / MODIFY  ADMISSION  CRITERIA(Administrator only)");
	printf("\n\n\t[2] ENTER STUDENT'S DATA ");
	printf("\n\n\t[3] ALLOTMENT OF  STREAM");
	printf("\n\n\t[4] DISPLAY CRITERIA FOR SELECTION");
	printf("\n\n\t[5] DISPLAY ALLOTMENT OF  STUDENT'S STREAM");
	printf("\n\n\t[6] DISPLAY ALL  STUDENT'S REGISTERED");
	printf("\n\n\t[7] CREATE / DISPLAY MERIT LIST");
	printf("\n\n\t[8] QUIT");
	printf("\n\t=============================================================\n");
	printf("\n\n\t\tEnter your  choice : ");
	scanf("%d",&opt);
	int p,option;
	switch(opt)
	{
        case 1:/*Administrator use*/
                assign_user();
                p=verify_password();
                if(p==0)
                {
                    input_criteria();
                }
                else
                {
                    printf("\n\tYou are not authorised user.");
                }
                break;

        case 2:/*input Students data*/
                system("cls");
                printf("\nWhat do you want --\n\n\n\n\n\tCreate  a new student information  file or Append to the existing file?\n\n\t(press 1 for new creation and 2 for appending)");
                scanf("%d",&option);
                if(option==1)
                {
                    new_file(&s);
                }
                else
                {
                    input_data(&s);
                }
                break;

        case 3:/*allotment of stream*/
                system("cls");
                fin=fopen("student.DAT" ,"a+");       //reads data of student
                fsc=fopen("elig_sc.DAT","w");
                fcom=fopen("eligcom.DAT","w");
                farts=fopen("eligart.DAT","w");

                while((ch = getchar())!= EOF)
                {
                        allot_stream(&s);
                        get_stream(&s);

				//if(s.get_stream()==0)
				     //  printf< <"\nApplication Rejected. Not Eligible\n";

                        if(get_stream(&s)==1)
                            fwrite(&s,sizeof(struct student),1,fsc);
                        if(get_stream(&s)==2)
                            fwrite(&s,sizeof(struct student),1,fcom);
                        if(get_stream(&s)==3)
                            fwrite(&s,sizeof(struct student),1,farts);
                }
                        fclose(fin);
                        fclose(fsc);
                        fclose(fcom);
                        fclose(farts);
                        printf("\n*******************************************");
                        printf("\n\n\tSTREAM ALLOCATION DONE.");
                        printf("\n*******************************************");
                        break;

        case 4: /*Displays criteria for admission/selection*/
                read_criteria();    //	clear();
                printf("\n Sc : %d",crit.sc_min);
                printf("\n Com : %d",crit.com_min);
                printf("\n Sc : %d",crit.arts_min);
                break;

        case 5:/*Displays allotment of students stream*/
                printf("\n Enter 1 for Sc, 2 for Com, 3 for Arts  :  ");
                scanf("%d",&ch);
                if (ch==1)
                    read_eligible_sc();
                if (ch==2)
                    read_eligible_com();
                if (ch==3)
                    read_eligible_arts();
                break;

        case 6:/*Displays all students registered*/
                system("cls") ;
                read_student();
                break;

        case 7:/*Creates/Displays merit list*/
                {
                char u;
                int k=1;
                printf("\n****************************************");
                printf("\n****************************************");
                printf("\n    M E R I T  L I S T");
                printf("\n    ==================");
                printf("\n\tEnter 1 for MERIT LIST SCIENCE ");
                printf("\n\tEnter 2 for MERIT LIST COMMERCE ");
                printf("\n\tEnter 3 for MERIT LIST ARTS \t");
                printf("\n****************************************");
                printf("\n****************************************");
                scanf("%d",&k);
                if (k==1)
                {
                    select_list("elig_sc","sell_sc");
                    fin=fopen("sell_sc.DAT","r");
                }
                if (k==2)
                {
                    select_list("eligcom","sellcom");
                    fin=fopen("sellcom.DAT","r");
                }
                if (k==3)
                {
                    select_list("eligart","sellart");
                    fin=fopen("sellart.DAT","r");
                }
                if(k>=1&&k<=3)
                {
                        while(fread(&s,sizeof(struct student),1,fin))
                        {
                            display(&s);
                            printf("\n\t Continue (y/n)?");
                            scanf("%c",&u);
                            if(u=='n')
                                break;
                        }
                }
            }
                fclose(fin);
                fclose(fin);
                fclose(fin);
                break;

        case 8:/*End program*/
                    thanks();
                    break;


    }          //end of while loop

}
return 0;
}      // end of main

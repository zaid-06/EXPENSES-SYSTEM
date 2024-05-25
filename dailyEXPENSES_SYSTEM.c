#include<stdio.h>
//#include<conio.h>
#include<process.h>
//#include <graphics.h>
struct Product
  {
       int pid;         //Product ID
       char pname[30];  //Product Name
       int qty;        //Poduct Qty
       double  price;	//Product Price
		double  Total;
  };

   
    double SubTotal;
       
insertRecord(){											// insert record
	FILE *fp, *fp2;
	char ch;

	struct Product Item, Item2;
	system("cls");
//	if(fp==NULL)
//    {
//		 printf("\nFile Not Exists....");
//		 exit(0);
//    }
    system("cls");
	  
     do
    {
    	system("cls");
		l1:
		color("lblue");
	    printf("\n\n\tPID\t\tNAME\t\tQTY\t\tPrice\n\t");
	  	color("white");
	    scanf("%d\t\t%s\t\t%d\t\t%lf",&Item.pid,Item.pname,&Item.qty,&Item.price);
	    fp2  = fopen("Stock.dat","rb");
		while(fread(&Item2, sizeof(Item2),1,fp2)>0)
		{
			if(Item2.pid == Item.pid)
			{
				system("cls");
				color("red");
				printf("\n\tThis Product id allrady taken.\ttry again");
				fclose(fp2);
				goto l1;
			}	
		}
		fclose(fp2);
		fp =   fopen("Stock.dat","ab");
	    Item.Total=Item.qty *Item.price;
	    fwrite(&Item,sizeof(Item),1,fp);//To Write Structure into File in Secondary
	    color("red");
	    
	    printf("\nDo You Want to Add New Record[y/Y]:");ch=getche();
	    fclose(fp);
    } while(ch=='y'||ch=='Y');
    color("green");
       printf("\nData Saved Sucessfully....");
       
}

search()										// search
{
	FILE *fp;
	int P_id;
	struct Product Item;
	
	fp=fopen("Stock.dat","rb");
	system("cls");
	color("red");
	printf("\n\n\t\tEnter Product id: ");
	scanf("%d",&P_id);
	while(fread(&Item, sizeof(Item),1,fp)>0)
	{
		if(Item.pid == P_id)
		{
			color("lblue");
			printf("\nPID\t\tNAME\t\tQTY\t\tPrice\t\t\tTotal\n");
			color("green");
			printf("%d\t\t%s\t\t%d\t\t%lf\t\t%lf\n",Item.pid,Item.pname,Item.qty,Item.price,Item.Total);
			break;
		}		
	}	
	fclose(fp);	
}
dspRecord()									//	display record
{
	FILE *fp;
	char ch;

	struct Product Item;
	
	fp=fopen("Stock.dat","rb");
	system("cls");
	color("lblue");
	printf("\n__________________________________________________________________________________");
    printf("\nPID\t\tNAME\t\tQTY\t\tPrice\t\t\tTotal\n");
    color("white");
   	while(fread(&Item, sizeof(Item),1,fp)>0)
	{
		
		printf("%d\t\t%s\t\t%d\t\t%lf\t\t%lf\n",Item.pid,Item.pname,Item.qty,Item.price,Item.Total);
			
	}
	fclose(fp);
		
}
Delete()
{
	FILE *fp, *fp2;
	char ch;
	int p_id, count =0;
	struct Product Item;
	
	fp=fopen("Stock.dat","rb");
	fp2=fopen("copy.dat","wb");
	color("red");
	printf("Enter product id to delete record: ");
	scanf("%d",&p_id);
	
	while(fread(&Item, sizeof(Item),1,fp)>0)
	{
		if (Item.pid!= p_id)
			fwrite(&Item, sizeof(Item),1,fp2);
		else
		{
			color("green");
			printf("\n\t\tRecord Deleted Sucessfully....");
			count=1;
		}
//		printf("%d\t\t%s\t\t%d\t\t%lf\t\t%lf\n",Item.pid,Item.pname,Item.qty,Item.price,Item.Total);		
	}
	fclose(fp);
	fclose(fp2);
	if(count == 0)
	{
		color("red");
		printf("\n\t\tNo record");
	}
	remove("Stock.dat");
    rename("copy.dat","Stock.dat");
	
}
void color(char clor[]) {
	if (!strcmp("red",clor))
  		printf("\033[1;31m");
  	else if (!strcmp("green",clor))
  		printf("\033[1;32m");
  	else if (!strcmp("lblue",clor))
  		printf("\033[1;36m");
  	else if (!strcmp("blue",clor))
  		printf("\033[1;34m");
  	else if (!strcmp("white",clor))
  		printf("\033[0m");
  	
}

int select(char choice[])								// select
{
	if(!strcmp("addrecord",choice))
		return (1);
	else if(!strcmp("displayall",choice))
		return (2);
	else if(!strcmp("search",choice))
		return (3);
	else if(!strcmp("edit",choice))
		return (4);
	else if(!strcmp("delete",choice))
		return (5);	
	else if(!strcmp("exit",choice))
		return (0);
}


int main()										//	main
{
//	clrscr();
	FILE *fp;
	char ch;
	char  choice[20];
	struct Product Item;
	
	do{
		system("cls");
		color ("lblue");
	
		printf("\n\t\t   %c%c%c%c%c DAILY EXPENSES SYSTEM %c%c%c%c%c",178,176,176,176,176,176,176,176,176,178);
		printf("\n\t\t_______________________________________\n");
		color ("red");
		printf("\n\t\t   [addrecord]");
		printf("\t\t[displayall]");
		printf("\n\n\t\t    [search]");
		printf("\t\t [edit]");
		printf("\n\n\t\t    [delete]");
		printf("\t\t [exit]");
		color ("white");
		printf("\n\t\t_______________________________________\n");
		
		printf("\n\t\tEnter option: ");
		scanf("%s",&choice);
		 switch(select(choice))
		    {
			 case 1:
			 	insertRecord();
			 	break;
			 case 2:
			 	dspRecord();
			 	break;
			 case 3:
			 	search();
			 break;
			 case 4:
			 	
			 break;
			 case 5:
			 	Delete();
			 	break;
			 case 0:
				exit(0);
			 	break;
			 default:
			 break;
		    }
		    color("red");
		    printf("\n\nDo You Want to do more operation [y/Y]:");ch=getche();
    } while(ch=='y'||ch=='Y');
		
}     
	       
	       
	       
	       

#include<stdio.h>
#include<mysql.h>
#include<string.h>
int main(int argc,char *argv[])
{ 
        MYSQL *connection;
        MYSQL_RES *result;
        MYSQL_ROW *row;


char *server = "localhost";//Since system itself acts as the server
//Credentials initialization
char *user = "root";
char *password = "";//Must 
char *database = "new";//valid
int numfields,Inno_flag=0,CSV_flag=0,c;
char choice;
int sum=0,no;

do
{
    system("clear");//To clear the terminal screen
    sum=0;
    connection = mysql_init(NULL);
    if(!mysql_real_connect(connection,server,user,password,database,0,NULL,0))//Connection establishment
    {
        printf("\nConnection error:");
        fprintf(stderr,"%s\n",mysql_error(connection));//Error
    }
    if(mysql_query(connection,"show engines"))
    {
        printf("\nQuery execution failed:");
        fprintf(stderr,"%s\n",mysql_error(connection));//Error
    }
    result = mysql_use_result(connection);//Fetching result
    numfields = mysql_num_fields(result);
    //printf("\nNumber of fields:%d\n",numfields);//Number of fields
    printf("What do you want to check?\nPress 1 for InnoDB\nPress 2 for CSV support\nYour choice: ");
    scanf("%d",&c);
    //
    while((row = mysql_fetch_row(result)) != NULL)//Iterating result row
            {
                if((strcmp(row[0], "InnoDB") == 0) && (strcmp(row[1], "DEFAULT") == 0 || strcmp(row[1],"YES")))//Innodb plug in checking
                        Inno_flag=1;
                    if((strcmp(row[0], "CSV") == 0) && strcmp(row[1], "YES") == 0)//CSV support checking
                        CSV_flag=1;
            }
    switch(c)
    {
        case 1:

            if(!Inno_flag)
                printf("InnoDB plug-in is not installed\n");
            else
                printf("InnoDB plug-in is installed\n");
                mysql_free_result(result);//Freeing the buffer 
                //To fetch Total Disk writes by MySQL 
                if(mysql_query(connection, "show global status like 'Innodb%writ%'"))
                {
                printf("\nQuery execution failed:");
                    fprintf(connection, "%s\n", mysql_error(connection));
                    exit(1);
                }

                result = mysql_use_result(connection);//fetching result 
                while((row = mysql_fetch_row(result)) != NULL)//Iterating result row
                {
                     //if(strcmp(row[0], "Innodb_data_written") == 0)
                    	no=atoi(row[1]);
                     sum+=no;
                     	/*printf("Total number of Disk Writes by MySQL:");
                    
                     	printf("%d,%d",no,sum);
                     	printf("\n");
                     //printf("Total number of Disk Writes by MySQL: %d\n", row[1]);*/
                  
                 }
                 printf("Total number of disk writes by MySQL:%d\n",sum);
            break;
        case 2:
            if(!CSV_flag)
                                    printf("CSV support is not there.\n");
                            else
                                    printf("CSV support is there.\n");

            break;
        default:printf("\nInvalid choice\n");

    }
    mysql_free_result(result);//Freeing the buffer
        mysql_close(connection);//closing the connection 
    printf("\nDo you want to continue?(Y/N):");
    scanf("%s",&choice);
}while(choice =='Y' || choice =='y' );
return 0;
    }

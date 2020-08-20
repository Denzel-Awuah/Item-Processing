/*  
| Denzels Food Mart
|
| Name: lab2_script.c
|
| Written by: Denzel Awuah - February 2020
|
| Purpose: Read in product codes and quantities to detemine items being purchased.
|
| usage: ./a.out #directory_of_items_list_file
| e.g. ./a.out item_list_1.txt
|
|
| Description of parameters:
| argv[1] - the path of the items list file
|
|
| Subroutines/libraries required:
| See include statements.
|
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>


//Structure to read the database
struct sku {
	char description[40];
	char unitofmeasure[15];
	float price;
      } sku_record;

//Structure to read the items list file
struct items {
	char productcode[3];
	char quantity[3];
} getitems;



int main(int argc, char *argv[])
{

time_t now;  //For displaying the time
time(&now);  // gettting the current time

char *testfile = "grocery_items.db";   //setting testfile to the database file
char *file = argv[1];  	 // getting the file sent from the command line (items list file)
char buffer[40];   	 
int fd;   	
ssize_t nread;
FILE *fp;
int pcode; 	//for storing the product code
int quantity;	//for storing the quantity







//Store Styling
printf("===================================================================================================\n");


printf("  		        Welcome to Denzel's Food Mart! \n");

printf("                                                                       %s\n", ctime(&now));

printf("Description             Unit of Measure        Unit Price        # Of items     Extended Price\n");
printf("---------------         -----------------      -----------       -----------    ---------------\n");





	//Opening the database file

   if((fd = open(testfile, O_RDONLY )) == -1)  //if cannot open file
        {
        printf("Could not open file %s\n", testfile); //print error message
        exit(1);   //exit program
        }




 //Opening the argument file (items list file)
FILE* ptr = fopen(argv[1], "r");   
if(ptr == NULL)		//if couldnt open the file
{
	printf("No such file\n");
	return 0;
}


char line[50];  
int size = 0;   // number of items in list file
char c;
fp = fopen(argv[1], "r");  //opening the items list file to get the number of items 
for(c = getc(fp); c!= EOF; c = getc(fp)) //used to count lines in file
   if(c == '\n')
      size = size + 1;

fclose(fp);  





int chk =0;   //check number of items in the file 
float *t;
float atotal; //stores the total price of items
t = &atotal;

while(chk <= size){ //run while chk if less than or equal to the size 
	
	if( (fscanf(ptr,"%s %s", getitems.productcode, getitems.quantity))==2){  //reading the product code and quantity from the items_list file	
	
	float price;   //store the price
	float unitprice; // store the unit price
	pcode = atoi(getitems.productcode);  //converting the product code from string to int
	quantity = atoi(getitems.quantity);  //converting the quantity from string to int
	lseek(fd, pcode*60, SEEK_SET);       //setting the file descriptor
        if( (nread = read(fd, &sku_record, sizeof(sku_record))) > 0){  // reading the database to get product and storing into sku_record structure
//     	         printf("Description: %s  ", sku_record.description);
//        	 printf("  Unit Of Measure: %s ", sku_record.unitofmeasure);
//          	 printf("  Price: %.2f \n", sku_record.price);
      }
	else
	{
	printf("Your file contains an invalid product code\n");
	exit(1);
	}
	
	unitprice = sku_record.price*(float)quantity; //calculating unit price


//printing items
printf("%-20s    %15s    %15.2f    %13d    %15.2f \n", sku_record.description, sku_record.unitofmeasure,  sku_record.price, quantity, unitprice);

atotal += unitprice;
}
chk = chk + 1;	// increment after each item

	
}
//printing total
printf("                                                                                --------------\n ");
printf("                                                                                Total: $ %.2f\n", *t );





printf("                                 Thank You for purchasing %d items from Denzels Food Mart!\n", size);
printf("                                                   Enjoy the rest of your day\n");
printf("===================================================================================================\n");

        


        


   //fclose(fp);
   exit(0);

}

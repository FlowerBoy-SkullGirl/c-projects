#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ABIGNEGNUM -999999999999
#define MAXSTR 255
#define SIGDIG 2 //Significant digits


//hopefully flush illegal input
void flush(void){
int c;
while ((c = getchar()) != '\n' && c != EOF);

}


//CONCATENATES A CHARACTER TO A STRING
void my_charcat(char *dest, char *src){
	while(*dest != '\0'){
		*dest++;
	}
	*dest++ = *src;
	*dest = '\0';

}

//CONCATENATES A STRING TO A STRING
void my_strcat(char *dest, char *src){
	while(*dest != '\0'){
		*dest++;
	}
	while(*src != '\0'){
		*dest++ = *src++;
	}
	*dest = '\0';
}

//CHECKS IF THE STRING CONTAINS AN EQUALS SIGN
int validform(char *in){
	while(*in != '\0'){
		if(*in=='='){
			return 1;
		}
		in++;
	}
	return 0;
}

//CONVERTS A STRING TO AN INT
int my_atoi(char str[]){
	int i = 0;
	int value=0;
	//remove non-digit characters
	while( ( str[i]<'0' || str[i]>'9' ) && str[i] != '\0' && str[i] != '\n' ){
		i++;
	}
	//copy value of digit characters to int by subtracting '0'
	for(;str[i]>='0' && str[i]<='9'; i++){
	value = (value*10) + (str[i] - '0');
	}
	return value;
}

//CONVERTS A STRING TO A DOUBLE, RETURNS AN UNLIKELY VALUE AS A FAILURE
double my_atof(char str[]){
	int i = 0;
	double value=0;
	int decadj = 1;
	int valid = 0;
	int unary = 1;
	//remove non-digit characters
	while( ( str[i]<'0' || str[i]>'9' ) && str[i] != '\0' && str[i] != '\n' ){
		if(str[i] == '-'){
			unary = -1;
		}
		i++;
	}
	//copy value of digit characters to int by subtracting '0'
	for(;str[i]>='0' && str[i]<='9'; i++){
	value = (value*10) + (str[i] - '0');
	valid = 1;
	}
	if(str[i]=='.'){
		i++;
		for(;str[i]>='0' && str[i]<='9'; i++){
			value = (value*10) + (str[i] - '0');
			decadj *= 10;
		}
	}
	if(valid){
		return((unary*value)/decadj);
	}else{
		return(ABIGNEGNUM);
	}
}

char *my_itoa(char* dest, int src){
	int i = 0;
	int j = 0;
	char temp[MAXSTR];
	for(j = 0; src > 0; j++){
		temp[j] = (src%10) + '0';
		src /= 10;
	}
	*(temp+j) = '\0';
	i = j;
	i--;
	j=0;
	for(j=0; i>=0; j++){
		*(dest+i) = *(temp+j);
		i--;
	}
	*(dest+j) = '\0';
}
//Converts a float/double to a string, requires a number of significant digits
char *my_ftoa(char *dest, double src, int dec){
	int i = 0;
	double dechelp = 1;
	char beforestr[MAXSTR];
	char afterstr[MAXSTR];
	char decsign[MAXSTR] = ".";
	//split double into before . and after .
	int before = src;
	double after = (src - before);
	int afterint;

	for(i=0; i< dec ; i++){
		dechelp *=10;
	}
	after *= dechelp;
	afterint = after;

	my_itoa(beforestr, before);
	my_itoa(afterstr, after);
	my_strcat(dest, beforestr);
	my_strcat(dest, decsign);
	my_strcat(dest, afterstr);

}

//TODO, Make sure input is valid
//TAKES USER INPUT AND CONCATENATES IT TO THE SPECIFIED STRING BY USING MY_STRCAT, RETURNS BOTH TOGETHER AS POINTER
char *usrnums(char *dest){
	char input[MAXSTR];
	char equal[MAXSTR] = "=";
	printf("No current data for: %s\nPlease input data: \n", dest);
	scanf("%s", &input);
	flush();
	my_strcat(dest, equal);
	my_strcat(dest, input);
}

//A LITTLE CONFUSING TO LOOK AT, TAKES A FILENAME, PUTS ALL LINES INTO BUFFER, ACCEPTS A STRING TO SEARCH FOR AND MODIFY BEFORE INSERTING INTO THE BUFFER ARRAY, THEN REWRITES FILE WITH ALL LINES IN TACT
void buffs(char *filen, char *src, FILE *fp, int changeval){
		char rlines[MAXSTR][MAXSTR];
		int rhelp=0;
		int rhelpfin=0;
		char emptyl[MAXSTR]="\n";
		char equal[MAXSTR] = "=";
		char temp[MAXSTR];
		char templ[MAXSTR];
		char tempchange[MAXSTR];

		//Make a copy of setting and an additional copy with a newline character
		strcpy(temp, src);
		temp[strcspn(src, "=")] = 0;
		my_strcat(temp, equal);

		strcpy(templ, temp);
		my_strcat(templ, emptyl);

		//Use new pointer and set cursor to beginning of file
		FILE *buffs = fp;
		fseek(fp, 0, SEEK_SET);
	
		//Safety check
		if(buffs ==NULL){
			printf("Error, buffs returned null\n");
		}else{

		//Collect all lines into the buffer
		while( fgets(rlines[rhelp], MAXSTR, buffs) != NULL && rhelp<MAXSTR ){
			//This copies the new usrnums value into the buffer if it is the last line
			if( strcmp(temp, rlines[rhelp]) ==0 ){
				strcpy(rlines[rhelp], src);
			//This copies the new usrnums value into the buffer if it is any line but the last
			}else if(strcmp(templ, rlines[rhelp])==0){
					my_strcat(src, emptyl);
					strcpy(rlines[rhelp], src);

					//Accounts for lines that already have values that the user wants to change
					}else if(changeval == 1){
						strcpy(tempchange, rlines[rhelp]);
						tempchange[strcspn(tempchange, "=")] = 0;
						my_strcat(tempchange, equal);
						if( strcmp(temp, tempchange) == 0 ){
							strcpy(rlines[rhelp], src);
							my_strcat(rlines[rhelp], emptyl);
						}
					}

			rhelp++;
		}


			} //safety NULL check
		rhelpfin=rhelp;

		//We write the new buffer into the original file, leaving all lines in tact. We also remove all empty lines, as a stylistic choice
		buffs = fopen(filen, "w");

		for(rhelp=0;rhelp<rhelpfin;rhelp++){
			if( strcmp(rlines[rhelp], emptyl) !=0){
				fprintf(buffs, "%s", rlines[rhelp]);

				}else if( strcmp(rlines[rhelp], emptyl) ==0 && rhelp+1>=rhelpfin){
					rhelpfin--;
			}
		}
		fclose(buffs);
	}



//Takes input from user, compares it to username list, and writes a new user if the name does not match
int getnames(char *input){
	int usr = 0;
	int i = 0;
	char line[MAXSTR];
	char placeholder[MAXSTR];
	char *ptr = placeholder;
	char filen[MAXSTR] = "users.txt";

	//add a newline to input through ptr pointing to placeholder
	while(*input != '\0'){
		*ptr++ = *input++;
	}
	*ptr++ = '\n';
	*ptr = '\0';

	//Compare the placeholder input name to every line in file, write new line if does not exist
	FILE * fp = fopen(filen, "a+");
	while(fgets(line, MAXSTR, fp) != NULL && usr==0){
		i++;
		if( strcmp(line, placeholder) == 0 ){
			usr = i;
		}
	}

	if(usr == 0){
		fputs(placeholder, fp);
		usr = i+1;
	}

	fclose(fp);

	return usr;
}

//Compares the given setting value to the lines existing in their info file, checks to see if they already have a value, and sends the user to usrnums func if it doesn't or if they want to change the value
double settingfinder(char usr, char *setting, int changeval){
	double total = ABIGNEGNUM;
	char filen[MAXSTR] = "info_user";
	char filet[MAXSTR] = ".txt";
	char *filefinder = filen;
	char *ptr = &usr;
	char line[MAXSTR];
	char temp[MAXSTR];
	int sizeln = 0;
	int curfp = 0;
	//add user number to the end of filename
	my_charcat(filen, ptr);
	my_strcat(filen, filet);

	FILE *fp = fopen(filen, "r+");
	while(fgets(line, MAXSTR, fp) != NULL){
		strcpy(temp, line);
		//check if the line has an = and terminate the temp copy at the = if so
		if(validform(line)){
		temp[strcspn(temp, "=")] = 0;
		}

		//find our desired setting
		if(strcmp(temp, setting) == 0){
			//curfp = ftell(fp);
			//sizeln = strlen(line);
			total = my_atof(line);
			//if we have an empty value for setting, pass the setting to usrnum to be assigned a value, then pass the results to buffs to write it into the file without overwriting the following line
			if(total<=ABIGNEGNUM || changeval==1){
				usrnums(setting);
				buffs(filen, setting, fp, changeval);
				//fseek(fp, 0-sizeln, SEEK_CUR);  UNUSED, BUT STILL MAYBE SOMETHING WORTHWHILE TO LEARN
				//fputs(setting, fp);
				total = my_atof(setting);
				printf("%s\n", setting);
				}else{
					printf("%s\n", line);
			}
		}
	}
	fclose(fp);

	return total;
}

//Creates a settings file for each user
//TO DO: Add a master settings list as an external array
int filecreate(char usr){
	char filen[MAXSTR] = "info_user";
	char filet[MAXSTR] = ".txt";
	char *filefinder = filen;
	char *ptr = &usr;
	char line[MAXSTR];
	char temp[MAXSTR];
	int newusr = 0;
	//add user number to the end of filename
	my_charcat(filen, ptr);
	my_strcat(filen, filet);

	FILE *fp;
	if( ( fp = fopen(filen, "r") )== NULL){
		newusr = 1;
		fp = fopen(filen, "w");
		fputs("current_balance=", fp);
	}
	fclose(fp);
	return newusr;
}

//Sits after each value fetch to see if the user wants to update the value
int changer(){
	puts("Would you like to edit this value?(y/n)");
	char c = getchar();
	flush();

	if(c=='y' || c=='Y'){
		return 1;
	}else if(c=='n' || c=='N'){
		return 0;
	}else{
		puts("Invalid response, value will remain unchanged.");
	}
}

//Finds the user's balance by passing arguments to settingfinder
double balance(char usr){
	double total = ABIGNEGNUM;
	char setting[MAXSTR] = "current_balance";
	int changeval = 0;

	total = settingfinder(usr, setting, changeval);
	changeval = changer();
	if(changeval == 1){
		total = settingfinder(usr, setting, changeval);
	}

	return total;
}

//Finds the user's expenses by passing arguments to settingfinder
double expense(char usr/*, int *month*/){
	double total = ABIGNEGNUM;
	char setting[MAXSTR] = "monthly_expense";
	int changeval = 0;

	total = settingfinder(usr, setting, changeval);
	changeval = changer();
	if(changeval == 1){
		total = settingfinder(usr, setting, changeval);
	}

	return total;
}

//Calculates the user's income
//TODO pass value directly to buffs, usrnums, or something else to write it directly to the file
double calculator(){
	char c;
	int answer = 0;
	int done = 0;
	double hourly = 0;
	double hours = 0;
	double total = 0;
	double tax = 1;
	char temp[MAXSTR];
	puts("Would you like to use the income calculator?(y/n)");
	c = getchar();
	flush();
	if(c=='y' || c=='Y'){
		answer = 1;
	}else if(c=='n' || c=='N'){
		answer = 0;
	}else{
		puts("Invalid response, calculator will not be used");
	}
	if(answer){
		while(done==0){
			puts("Please enter your hourly wage");
			scanf("%s", temp);
			flush();
			hourly = my_atof(temp);
			puts("Please enter the estimated amount of hours you will work this month");
			scanf("%s", temp);
			flush();
			hours = my_atof(temp);
			puts("Estimate the percent of tax to be taken out of your pay");
			scanf("%s", temp);
			tax = my_atof(temp);
			flush();
			if(tax>100 || tax<0){
				tax = 1;
			}else{
				tax = 100 - tax;
				tax /= 100;
			}
			total = total + (hourly*hours*tax);
			printf("Your total wages this month will be: %.2f\nDo you have more hourly income to report?(y/n)\n", total);
			c = getchar();
			flush();
			if(c=='y' || c=='Y'){
				done = 0;
			}else if(c=='n' || c=='N'){
				done = 1;
			}else{
				puts("Invalid response. No more input will be taken.");
				done = 1;
			}
		}
	}
	return total;
}
//Finds the user's income by passing arguments to settingfinder
double getinc(char usr){
	double total = ABIGNEGNUM;
	char setting[MAXSTR] = "monthly_income";
	int changeval = 0;
	double inccalc = 0;
	char equal[MAXSTR] = "=";
	//For calculator to pass to buffs
	char filen[MAXSTR] = "info_user";
	char filet[MAXSTR] = ".txt";
	char *filefinder = filen;
	char *ptr = &usr;
	//add user number to the end of filename
	my_charcat(filen, ptr);
	my_strcat(filen, filet);

	inccalc = calculator();
	if(inccalc){
		changeval = 1;
		my_strcat(setting, equal);
		my_ftoa(setting, inccalc, SIGDIG);
		printf("%s\n", setting);
		FILE * fp = fopen(filen, "r+");
		buffs(filen, setting, fp, changeval);
		fclose(fp);
	}else{
		total = settingfinder(usr, setting, changeval);
		changeval = changer();
		if(changeval == 1){
			total = settingfinder(usr, setting, changeval);
		}
	}
	return total;
}

//Simply adds all the values of other functions to give the user an estimate of their remaining balance at the end of the month
double fin_balance(double bal, double exp, double inc/* int *month */){
	double total = ABIGNEGNUM;

	total = bal + inc - exp;
	return total;
}


int main(){

	int usr;
	char input[MAXSTR];
	double real_balance = ABIGNEGNUM;
	double real_expense = ABIGNEGNUM;
	double real_income = ABIGNEGNUM;
	double final_total = ABIGNEGNUM;
	char menu;
	//mock database for usrname
	printf("Welcome! Enter username: \n");
	scanf("%s", &input);

	usr = getnames(input);
	char usrc = usr + '0';
	//hopefully disallow spaces in names
	flush();
	//determine date
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	//tm.tm_mon + 1, tm.tm_mday, tm.tm_year + 1900
	
	//Write info file if does not exist for user
	if(filecreate(usrc)){
		puts("Welcome, new user");
	}else{
		puts("Welcome back!");
	}


	while(menu!='0'){
		puts("Menu\n0. Quit\n1. Balance\n2. Expenses\n3. Income\n4. Total at end of month");
		menu = getchar();
		flush();
		switch(menu){

		//exits while loop
		case '0':
		break;

		case '1':
		//fetch current balance
		real_balance = balance(usrc);
		break;

		case '2':
		//add all expenses
		real_expense = expense(usrc);
		break;

		case '3':
		//allower user to state income
		real_income = getinc(usrc);
		break;

		//calculate balance at end of month based on balance+getinc-expense

		case '4':
		//Check that all values are valid first
		//TODO THIS DOESN'T WORK IF THE VALUES AREN'T FETCHED DURING RUNTIME
		if(real_balance>ABIGNEGNUM && real_expense>ABIGNEGNUM && real_income>ABIGNEGNUM){

		final_total = fin_balance(real_balance, real_expense, real_income);
		printf("Total balance at end of month will be: %.2f\n", final_total);


		}else{
			puts("Please provide valid values for your balance, expenses, and income before proceeding");
		}
		break;

		default:
		puts("Invalid options, please try again");
		}//switch

	}//menu loop

return 0;
}
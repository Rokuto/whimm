/*
	AUTHORS:
	Anton Dominique Cruz
	Gauven Roy Pascua
	
	PROGRAMME NAME:
	WHIMM FOR ICS-OS

	CURRENT LIMITATIONS:
		Up to 20 lines only
		Up to only 75 characters per line
		When no filename was specified from arguments, filename length is only limited to 16 characters
*/

#include "../../sdk/dexsdk.h"


void printWelcome();
void printHelp();
void printText();
void dumpFile();
void fileSave();
void backspaceHandler();
void keyPressHandler();
void saveFileHandler();
void showFooter();

int editing=0;
int i=0,j=0,chr,iPr;
char buffer[20][77];
char* filename;
char tmp1,tmp2;
FILE *fileOpen;
FILE *fileWrite;

int main(int argc, char** argv) {
	for(i=0;i<20;i++) for(j=0;j<77;j++) buffer[i][j] = 0;
	i=0;
	j=0;

	/*This check if the arguments satisfy the allowed parameters of the program*/
	if(argc == 2){ // Openning / Creating named text file
		filename = (char *)malloc(sizeof(char)*strlen(argv[1]));
		strcpy(filename,argv[1]);
		fileOpen = fopen(filename,"r");
		if (fileOpen == NULL){
			editing = 1;
			printText();
			showFooter();
		}
		else{
			editing = 1;
			dumpFile();
			printText();
			showFooter();
			fclose(fileOpen);
		}
		fclose(fileOpen);
	}
	else if(argc == 1) // Creating a unnamed text fle 
		printWelcome();
	else {// Error handling
		printf("usage: whimm.exe <filename>\n");
		return 1;
	}
	
	// Accept user inputs
	while(1){
		chr = getchar();
		if(chr==16){
			//Ctrl-Q was pressed
			break;
		}
		if(chr==7){
			//Ctrl-H was pressed
			printHelp();
			clrscr();
			if(editing==0)
				printWelcome();
			else{
				printText();
				showFooter();
			}
		}
		if(chr==18){
			//Ctrl-S was pressed
			saveFileHandler();
		}
		if((chr>=65&&chr<=90)||(chr>=97&&chr<=122)||(chr==32)||
		(chr==96)||(chr==126)||(chr==49)||(chr==33)||(chr==50)||
		(chr==64)||(chr==51)||(chr==35)||(chr==52)||(chr==36)||
		(chr==53)||(chr==37)||(chr==54)||(chr==94)||(chr==55)||
		(chr==38)||(chr==56)||(chr==42)||(chr==57)||(chr==40)||
		(chr==48)||(chr==41)||(chr==45)||(chr==95)||(chr==61)||
		(chr==43)||(chr==91)||(chr==92)||(chr==93)||(chr==123)||
		(chr==124)||(chr==125)||(chr==58)||(chr==59)||(chr==34)||
		(chr==39)||(chr==60)||(chr==44)||(chr==62)||(chr==46)||
		(chr==47)||(chr==63)
		){
			//a key that's used to input text was pressed
			keyPressHandler();
			showFooter();
		}
		if(chr==8){
			//backspace was pressed
			backspaceHandler();
			showFooter();
		}
		if(chr==9){
			//tab was pressed
		}
		if(chr==10){
			//enter/return key was pressed
			if(editing==1){
				i++;
				j=0;
				//add downward moving of lines here later
			}
			enterHandler();
			showFooter();
		}
		if(chr==-105){
			//up arrow key was pressed
			if(editing==1){
				if(((i!=0)&&(buffer[i-1][0]!=0)))
					i--;
				else if(buffer[i][j]==0)
					j = (strlen(buffer[i]));
				printText();
				showFooter();
			}
		}
		if(chr==-104){
			//down arrow key was pressed
			if(editing==1){
				if(((i!=19)&&(buffer[i+1][0]!=0)))
					i++;
				else if(buffer[i][j]==0)
					j = (strlen(buffer[i]));
				printText();
				showFooter();
			}	
		}
		if(chr==-106){
			//left arrow key was pressed
			if(editing==1){
				if((j==0)&&(i!=0)){
					i--;
					j = (strlen(buffer[i]));
				}
				else if(j!=0){
					j--;
				}
				printText();
				showFooter();
			}
		}
		if(chr==-103){
			//right arrow key was pressed
			if(editing==1){
				if((j==strlen(buffer[i]))&&(i!=19)){
					i++;
					j=0;
				}
				//do nothing if reached end of buffer/file
				else if((j==strlen(buffer[i]))&&(i==19));
				else {
					j++;
				}
				printText();
				showFooter();
			}
		}
	}

	/*Reset all data before closing*/
	for(i=0;i<20;i++) for(j=0;j<77;j++) buffer[i][j] = 0;
	if(filename!=NULL) free(filename);

	clrscr();
  	return 0;
}

//function that handles key presses to enter text into the text buffer
void keyPressHandler(){
	int _i,_j;
	if(editing==0){
		/*Render the text input of the user to the screen*/
		clrscr();
		editing = 1;
		buffer[i][j] = (char)chr;
		j++;
	}
	else{
		if(buffer[i][j] == 0)
			buffer[i][j] = (char)chr;
		else {
			/*Use for inserting a text input in the array*/
			tmp1 = buffer[i][j];
			buffer[i][j] = (char)chr;
			tmp2 = tmp1;
			/*Move the succeeding elements as the user adds an input*/
			for(_i=i;_i<20;_i++){
				if(_i==i){
					for(_j=j+1;_j<77;_j++){
						if(_j==76) //Maximum capacity of an array
							break;
						tmp1 = buffer[_i][_j];
						buffer[_i][_j] = tmp2;
						tmp2 = tmp1;
					}
					if(_j<76) //Maximum capacity of an array
						break;
				}
				else{
					for(_j=0;_j<77;_j++){
						if(_j==76) //Max Capacity
							break;
						tmp1 = buffer[_i][_j];
						buffer[_i][_j] = tmp2;
						tmp2 = tmp1;
					}
					if(tmp2==0) // Stop swapping
						break;
				}
			} 			
		}
		j++;
		//go to the next line if the line is maxed out
		if(j==76){
			i++;
			j=0;
		}
	}
	printText();
	return;
}

//function that handles backspace presses
void backspaceHandler(){
	int _i,_j;
	if(editing==1){
		/*Decrement*/
		if(j==0&&(i!=0)&&(buffer[i][j]==0)){
			j = strlen(buffer[i-1]);
			i--;
			printText();
			return;
		}
		//do nothing if cursor is on the start of the buffer/file
		if(j==0&&i==0){
			printText();
			return;
		}
		/*Remove the element on i, j*/
		if(buffer[i][j]==0) // remove last element
			buffer[i][j-1] = 0;
		else{
			/*Remove a non-last element*/
			buffer[i][j-1] = buffer[i][j];
			tmp1 = buffer[i][j+1];
			// Moving of elements
			for(_i=i;i<20;i++){
				if(_i==i){
					for(_j=j+1;_j<77;_j++){
						if(_j==76)
							break;
						buffer[_i][_j-1] = tmp1;
						tmp1 = buffer[_i][_j+1];
					}
					if(tmp1==0)
						break;
				}
				else{
					for(_j=0;_j<77;_j++){
						if(_j==76)
							break;
						buffer[_i][_j-1] = tmp1;
						tmp1 = buffer[_i][_j+1];
					}
					if(tmp1==0)
						break;
				}
			}
		}
		j--;
		printText();
	}
	return;
}

//function that handles saving of file
void saveFileHandler(){
	if(editing==1){
		if(filename==NULL){
			//prompt user for filename
			filename = (char *)malloc(sizeof(char)*16);
			printText();
			printf("\n\n\tPlease enter a filename: ");
			gets(filename);
		}
		fileSave();
		printText();
		printf("\n\n\tFile saved as %s!\n\n",filename);
	}
	chr = 0;
	return;
}

//function that saves the text buffer into file
void fileSave(){
	int _i,_j;
	fileWrite = fopen(filename,"w");
	for(_i=0;_i<20;_i++){
		for(_j=0;_j<77;_j++){
			if(buffer[_i][_j]==0){
				fputc('\n',fileWrite);
				break;
			}
			else
				fputc(buffer[_i][_j],fileWrite);
		}
	}
	fclose(fileWrite);
	return;
}

//function that dumps the file contents to the text buffer
void dumpFile(){
	int _i=0,_j=0;
	tmp1 = fgetc(fileOpen);
	for (_i=0;_i<20;_i++){
		for(_j=0;_j<77;_j++){
			if(tmp1=='\n'){
				break;
			}
			else
				buffer[_i][_j] = tmp1;
			tmp1 = fgetc(fileOpen);
			if (tmp1==EOF)
				break;
		}
		if(tmp1=='\n') tmp1 = fgetc(fileOpen);
		if(tmp1==EOF) break;
	}
	i = _i;
	j = _j;
	return;
}

//function that prints the text in the text buffer
void printText(){
	int _j=0;
	clrscr();
	for(iPr=0;iPr<20;iPr++){
		if(iPr==i){
			printf("~ ");
			for(_j=0;_j<77;_j++){
				if(j==_j) printf("_");
				else printf("%c",buffer[i][_j]);
			}
			printf("\n");
		}
		else
			printf("~ %s\n",buffer[iPr]);
	}
	return;
}

//function that shows the footer
void showFooter(){
	printf("\nCTRL-S to Save\n");
	printf("CTRL-H for Help\n");
	printf("CTRL-Q to Quit\n");
	return;
}

//function that loads the HELP details
void printHelp(){
	while(1){
		clrscr();
		printf("~\n");
		printf("~\n");
		printf("~\t\t\t\t\t\t\t\t\t\t\tWHIMM HELP\n");
		printf("~\n");
		printf("~\n");
		printf("~\tWHIMM is a simple text editor for ICS-OS that was inspired by NANO and VIM\n");
		printf("~\tfrom your usual *NIX OS.\n");
		printf("~\n");
		printf("~\tTo start writing, just press any letter or number key on your keyboard!\n");
		printf("~\n");
		printf("~\n");
		printf("~\tTo save your file, just press CTRL-S.\n");
		printf("~\tTo resume typing or to go back to the main screen, press Q.\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");
		printf("~\n");

		chr = getchar();
		if(chr==81||chr==113) // return on q or Q press
			break;
	}
	chr = 0; // reset
	return;
}

//function that shows the welcome screen
void printWelcome(){
	clrscr();
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~                      *********************************\n");
	printf("~                      *        WELCOME TO WHIMM!      *\n");
	printf("~                      *                               *\n");
	printf("~                      *  Press any key to enter text  *\n");
	printf("~                      *     Enter CTRL-H for Help     *\n");
	printf("~                      *     Enter CTRL-Q to  Quit     *\n");
	printf("~                      *********************************\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
	printf("~\n");
}

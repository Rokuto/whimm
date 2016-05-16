/*
	WHIMM FOR ICS-OS
	Anton Dominique Cruz
	Gauven Roy Pascua
	Up to 77 characters, excluding new line character, per line
*/

#include "../../sdk/dexsdk.h"


void printWelcome();
void printHelp();
void printText();
void keyPressHandler();
void saveFileHandler();
void showFooter();

int editing=0;
int i=0,j=0,chr,iPr;
char buffer[20][78];
char tmp1,tmp2;

int main(int argc, char** argv) {
	for(i=0;i<20;i++) for(j=0;j<78;j++) buffer[i][j] = 0;
	
	if(argc == 2){
		//print opening or creating a file here later
		printf("%s\n",argv[1]);
		return 0;
	}
	else if(argc == 1)
		printWelcome();
	else {
		printf("usage: whimm.exe <filename>\n");
		return 1;
	}
	
	while(1){
		chr = getchar();
		if(editing==0)
			printf("%c - %d\n",chr,chr);
		if(chr==16){
			break;
		}
		if(chr==7){
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
			saveFileHandler();
		}
		///*
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
			//for all the valid keys on the keyboard
			keyPressHandler();
			showFooter();
		}
		if(chr==8){
			//backspace
			if(editing==1){
				clrscr();
				if(j!=0){
					buffer[i][j-1] = 0;
					j--;
				}
				if((j==0)&&(i!=0)){
					//if the 'cursor' is in the first column and if it's not in the first line
					//add upward moving of lines here later
				}
				printText();
				showFooter();
			}
		}
		if(chr==9){
			//tab equivalent to four white spaces
		}
		if(chr==10){
			//enter
		}
		//*/
	}

	for(i=0;i<20;i++) for(j=0;j<78;j++) buffer[i][j] = 0;
	
	clrscr();
  	return 0;
}

//function that handles key presses to enter text into the text buffer
void keyPressHandler(){
	int _i,_j;
	if(editing==0){
		clrscr();
		editing = 1;
		buffer[i][j] = (char)chr;
		j++;
	}
	else{
		//go to the next line if the line is maxed out
		if(j==77){
			i++;
			j=0;
		}
		clrscr();
		if(buffer[i][j] == 0)
			buffer[i][j] = (char)chr;
		else {
			tmp1 = buffer[i][j];
			buffer[i][j] = (char)chr;
			tmp2 = tmp1;
			for(_i=i;_i<20;_i++){
				for(_j=j+1;_j<78;_j++){
					if(buffer[_i][_j] == 0)
						break;
					tmp1 = buffer[_i][_j];
					buffer[_i][_j] = tmp2;
					tmp2 = tmp1;
				}
				if(_j<78)
					break;
				_j = 0;
			} 			
		}
		j++;
	}
	printText();
	return;
}

//function that handles saving of file
void saveFileHandler(){
	if(editing==1){
		//save file prompt here
	}
}

//function that prints the text in the text buffer
void printText(){
	int _j=0;
	for(iPr=0;iPr<20;iPr++){
		if(iPr==i){
			printf("~ ");
			for(_j=0;_j<78;_j++){
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

		int chr = getchar();
		if(chr==81||chr==113)
			break;
	}
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


/*
This file is: ga_war.c 

CHANGES: 6/19/2000
It's been a couple of years without any changes
but I was running this for old times sake and 
fix a few tiny bugs that cause bluemoon segfaults.
This changes the population pool so numbering 
starts at 0 instead of 1.


by jason boer 3/20/97
jason@ezmo.com 

Hello, 
	This is a program to evolve REDCODE 
programs for Corewars using a closed system of
unnatural selection.  To maximize portability these
are the instructions for this program. You are free
to do whatever you want with it.  You will not owe
me even a nickel if you do, but in no case will
I owe you if you grind your harddrive to dust.
This program does tons of file accesses and is
intended to be run from a ramdisk and NOT from
a harddrive.  To use this code place it in a 
directory of your choice, then make a directory
under that called valhalla.  You then need to 
copy "plant.red" and "ga_war.cfg" into a file
they are listed below.  Then compile this file.
It was made with DJGPP 2.01 a DOS port of gcc.
I have tried to make this as portable as possible
and in most cases changing the path_symbol in 
the "ga_war.cfg" file should be all that is need.
So type "gcc -Wall -O2 ga_war.c", OK if that
didn't work then goodluck. I am not able help you
with this kind of problem. Now you have a.exe or
a.out so run it.  Wait did I say you need to 
have "pmars" in your path and I can't stress too
much this should!!! be a ramdisk.  If you don't
have a ramdisk try simtel there are some there.
Now run the code it will create a population
of REDCODE programs and begin the process of
unnatural selection on them.  The code should be
fairly clear in showing the exact way it is 
doing this.  If you make any big breakthroughs
with this or make a super new improvement to
this code feel free to let me know and tell me
what you did.  But you are not obligated to do
so.
 
Put this in a file called:
"plant.red"
cut here-------------------------
;redcode-94
;name plant
;assert CORESIZE == 8000
spl.x  #  0,#  0
end
cut here-------------------------

Put this in a file called:
"ga_war.cfg"
cut here-------------------------
;the form of this must not be changed
;the parser is very-very-very dumb
;
; value can be {0,1}
create_new_population=1
; value must be {n>1} or else
population_size=25
; value must be {n>1} or else
number_of_cycles=250
; value must be {n>=0}
starting_cycle=0
; value must be {0<n<100}
max_instructions=10
; value must be {n<=999} 
max_number_size=10
; values should be {0...100}
mutation_rate=25
insertion_rate=5
removal_rate=5
resurrection_rate=2
;value must be {n>0}
number_of_battles=3
; 2 letters only...dumb
population_name=xx
; OK, dos use \\ unix use //
path_symbol=\\
cut here-------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/********************/

static unsigned long number_of_opcodes=17; 

static char * opcodes[]={\
		"dat","mov","add","sub",\
		"mul","div","mod","jmp",\
		"jmz","jmn","djn","spl",\
		"slt","cmp","seq","sne",\
		"nop"};

static unsigned long number_of_modifiers=7; 

static char * modifiers[]=
		{".a ",".b ",".ab",".ba",".f ",".x ",".i "};

static unsigned long number_of_address_modes=7; 

static char * address_modes[]=
		{"#","$","@","<",">","*","{","}"};

/************************************/
/*these are set from the config file*/

static char path_symbol[32]="";

static int create_new_population=0;
static char population_name[32]="";
static int population_size=0;

static int starting_cycle=0;
static int number_of_cycles=0;

static int number_of_battles=0;

static int mutation_rate=0;
static int resurrection_rate=0;
static int insertion_rate=0;
static int removal_rate=0;

static int max_number_size=0;
static int max_instructions=0;

/********************/

static int * valhalla_record=0;

/********************/

int a_random_integer(int range){

	return (int)range-(rand()%(range*2));
}

int a_random_number(int range) {

	return (int)rand()%range;
}

/********************/

int a_mutation() {
	return ((a_random_number(100)+1)<=mutation_rate);
}

int a_resurrection() {
	return ((a_random_number(100)+1)<=resurrection_rate);
}

int a_insertion() {
	return ((a_random_number(100)+1)<=insertion_rate);
}

int a_removal() {
	return ((a_random_number(100)+1)<=removal_rate);
}

/********************/

void fprint_header(FILE * file,char * file_name) {

	fprintf(file,";redcode-94\n");
	fprintf(file,";assert CORESIZE == 8000\n");
	fprintf(file,";name %s\n",file_name);		
}

/********************/

void fprint_body(FILE * target_file,FILE * source_file) {

	char buffer[256];

	strcpy(buffer,";");
	while (strstr(buffer,";")!=0)   
		fgets (buffer,255,source_file);		

	while (strstr(buffer,"end")==0) {  
		fprintf(target_file,"%s",buffer);
		fgets (buffer,255,source_file);		
	}
}

/********************/

void fprint_end(FILE * target_file,int score) {

	fprintf(target_file,"end\n");
	fprintf(target_file,";%d\n",score);
}


/********************/

void file_copy(char * source_name,char *target_name) {

	FILE * target_file=0;
	FILE * source_file=0;

	char buffer[256];
	
	if (0==(target_file=fopen(target_name,"w+")))
		exit(0);
	if (0==(source_file=fopen(source_name,"r")))
		exit(0);

	while (fgets(buffer,255,source_file)!=0)   
		fprintf(target_file,"%s",buffer);
		
	fclose(target_file);
	fclose(source_file);	
}	

/********************/

void update_cycle_file(int cycle) {

	FILE * file=0;
	int index;
	
	if (0==(file=fopen("cycle.txt","w+")))
		exit(0);

	fprintf(file,"%d\n",cycle);

	fprintf(file,"create_new_population=%d\n",create_new_population);
	fprintf(file,"population_size=%d\n",population_size);
	fprintf(file,"number_of_cycles=%d\n",number_of_cycles);
	fprintf(file,"starting_cycle=%d\n",starting_cycle);
	fprintf(file,"max_instructions=%d\n",max_instructions);
	fprintf(file,"max_number_size=%d\n",max_number_size);
	fprintf(file,"mutation_rate=%d\n",mutation_rate);
	fprintf(file,"insertion_rate=%d\n",insertion_rate);
	fprintf(file,"removal_rate=%d\n",removal_rate);
	fprintf(file,"resurrection_rate=%d\n",resurrection_rate);
	fprintf(file,"number_of_battles=%d\n",number_of_battles);
	fprintf(file,"population_name=%s\n",population_name);
	fprintf(file,"path_symbol=%s\n",path_symbol);

	for (index=0;index<population_size;index++)
		fprintf(file,"%d %d\n",index,valhalla_record[index]);

	fclose(file);
}		

/********************/

void setup(void){

	FILE * config_file=0;
	time_t t;	
	int index;
 	char buffer[256];
	char * parm_ptr=0;
	
	/*seed the random numbers*/
	srand((unsigned int) time(& t));

	/*set defaults*/
	create_new_population=1;
	population_size=25;
	number_of_cycles=250;
	starting_cycle=0;
	max_instructions=10;
	max_number_size=10;
	mutation_rate=25;
	insertion_rate=5;
	removal_rate=5;
	resurrection_rate=2;
	number_of_battles=3;

	strcpy(population_name,"ga");
	strcpy(path_symbol,"\\");

	/*read config file if there*/
	if (0==(config_file=fopen("ga_war.cfg","r"))){
		printf("ga_war.cfg not found using defaults.\n");
	}else {
		while (fgets(buffer,255,config_file)!=0) {   
			
			/*ignore this line*/
			if(strstr(buffer,";")!=0) continue;

			if(strstr(buffer,"create_new_population")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					create_new_population=atoi(++parm_ptr);
				continue;
			}
	
			if(strstr(buffer,"population_size")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					population_size=atoi(++parm_ptr);
				continue;
			}

			if(strstr(buffer,"starting_cycle")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					starting_cycle=atoi(++parm_ptr);
				continue;
			}
			
			if(strstr(buffer,"number_of_cycles")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					number_of_cycles=atoi(++parm_ptr);
				continue;
			}
	
			if(strstr(buffer,"max_instructions")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					max_instructions=atoi(++parm_ptr);
				continue;
			}
			
			if(strstr(buffer,"max_number_size")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					max_number_size=atoi(++parm_ptr);
				continue;
			}

		
			if(strstr(buffer,"mutation_rate")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					mutation_rate=atoi(++parm_ptr);
				continue;
			}

			if(strstr(buffer,"insertion_rate")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					insertion_rate=atoi(++parm_ptr);
				continue;
			}
			
			if(strstr(buffer,"removal_rate")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					removal_rate=atoi(++parm_ptr);
				continue;
			}
			
			if(strstr(buffer,"resurrection_rate")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					resurrection_rate=atoi(++parm_ptr);
				continue;
			}
			
			if(strstr(buffer,"number_of_battles")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					number_of_battles=atoi(++parm_ptr);
				continue;
			}

			if(strstr(buffer,"population_name")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					strncpy(population_name,++parm_ptr,2);		
				continue;
			}

			if(strstr(buffer,"path_symbol")!=0) {
				parm_ptr=strstr(buffer,"=");
				if (parm_ptr!=0)
					strncpy(path_symbol,++parm_ptr,2);
				continue;
			}


		}/*while*/

		fclose(config_file);  
	}

	/*print the values*/	
	printf("create_new_population=%d\n",create_new_population);
	printf("population_size=%d\n",population_size);
	printf("number_of_cycles=%d\n",number_of_cycles);
	printf("starting_cycle=%d\n",starting_cycle);
	printf("max_instructions=%d\n",max_instructions);
	printf("max_number_size=%d\n",max_number_size);
	printf("mutation_rate=%d\n",mutation_rate);
	printf("insertion_rate=%d\n",insertion_rate);
	printf("removal_rate=%d\n",removal_rate);
	printf("resurrection_rate=%d\n",resurrection_rate);
	printf("number_of_battles=%d\n",number_of_battles);
	printf("population_name=%s\n",population_name);
	printf("path_symbol=%s\n",path_symbol);

	/*init the valhalla score*/
	valhalla_record=(int*) malloc(sizeof(int)*population_size);

	/*clear valhalla_record*/
	for (index=0;index<population_size;index++)
		valhalla_record[index]=0;

}

/********************/

static char new_line[256];

char * new_line_of_code(void) {

	sprintf(new_line,"%s%s %s%3d,%s%3d",
			opcodes[rand()%number_of_opcodes],
			modifiers[rand()%number_of_modifiers],
			address_modes[rand()%number_of_address_modes],
			a_random_integer(max_number_size),
			address_modes[rand()%number_of_address_modes],
			a_random_integer(max_number_size));
				
	printf("$$$$$ %s\n",new_line);
		
	return new_line;

}/*new_line_of_code()*/

/********************/

int test_viable(char * file_name) {

	FILE * file=0;

	char command[256];
	char buffer[256]="";
	char * s_ptr=0;

	int count=0;

	/*test length*/
	if ((file=fopen(file_name,"r"))==0) exit(0);
	
	strcpy(buffer,";");

	while (strstr(buffer,";")!=0)
		fgets (buffer,255,file);
	
	while (strstr(buffer,"end")==0) {
		fgets (buffer,255,file);
		count++;
	}

	fclose(file);

	if (count==0||count>max_instructions) {
		printf(";;;;; %s\n",file_name);
		return 0;
	}	


	/*test with plant*/
	sprintf(command,"pmars -b -o plant.red %s > temp.txt",file_name);
	
	system(command);

	if ((file=fopen("temp.txt","r"))==0) exit(0);
	
	while (strstr(buffer,file_name)==0)
		fgets (buffer,255,file);
	
	fclose(file);

	s_ptr=(strstr(buffer,"scores"));		
		
	s_ptr+=7;

	if (atoi(s_ptr)<1) {
		printf("===== %s %s",file_name,s_ptr);
		return 0;
	} else {
		printf("===== %s %s",file_name,s_ptr);
		return 1;
	}

}/*test_viable()*/

/********************/

void create_seed_population(int population_size,char * population_name) {
	
	FILE * file=0;

	int index;

	char buffer[256];	
	char file_name[256];

	for (index=0;index<population_size;index++) {
		
		CREATE:

			sprintf(file_name,"%s_%d.red",population_name,index);
			printf("%s\n",file_name);

			file=fopen(file_name,"w+");
			if (0==file)
				exit(0);
		
			fprint_header(file,file_name);
		
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());
			fprintf(file,"%s\n",new_line_of_code());

			fprint_end(file,0);
	
			fclose(file);

		if (test_viable(file_name)==0) goto CREATE;

		sprintf(buffer,".%svalhalla%s%s",path_symbol,path_symbol,file_name);
	
		printf("%s\n",buffer);
		file_copy(file_name,buffer);
		
		}

}/*create_seed_population()*/

/********************/

char * evolve_a_line(char * old_line) {
	
	char * new_line_ptr;
	char * old_line_ptr;

	strcpy(new_line,"");	

	new_line_ptr=new_line;
	old_line_ptr=old_line;

	/*opcode*/
	if (a_mutation()) 
		strncpy(new_line_ptr,opcodes[rand()%number_of_opcodes],3);
	else 
		strncpy(new_line_ptr,old_line_ptr,3);

	new_line_ptr+=3;	
	old_line_ptr+=3;	
	
	/*modifiers*/
	if (a_mutation()) 
		strncpy(new_line_ptr,modifiers[rand()%number_of_modifiers],3);
	else 
		strncpy(new_line_ptr,old_line_ptr,3);

	new_line_ptr+=3;	
	old_line_ptr+=3;
	
	strcpy(new_line_ptr," ");	
	
	new_line_ptr+=1;	
	old_line_ptr+=1;
		
	/*address mode*/
	if (a_mutation()) 
		strncpy(new_line_ptr,address_modes[rand()%number_of_address_modes],1);
	else 
		strncpy(new_line_ptr,old_line_ptr,1);

	new_line_ptr+=1;	
	old_line_ptr+=1;	
	
	/*number*/
	if (a_mutation()) 
		sprintf(new_line_ptr,"%3d,",a_random_integer(max_number_size));
	else 
		strncpy(new_line_ptr,old_line_ptr,4);

	new_line_ptr+=4;	
	old_line_ptr+=4;	
	
	/*address mode*/
	if (a_mutation()) 
		strncpy(new_line_ptr,address_modes[rand()%number_of_address_modes],1);
	else 
		strncpy(new_line_ptr,old_line_ptr,1);

	new_line_ptr+=1;	
	old_line_ptr+=1;	

	/*number*/
	if (a_mutation()) 
		sprintf(new_line_ptr,"%3d",a_random_integer(max_number_size));
	else 
		strncpy(new_line_ptr,old_line_ptr,3);

	new_line_ptr+=3;

	strcpy(new_line_ptr,"");	
	
	printf("----- %s\n",new_line);

	return new_line;

}/*evolve_a_line()*/

/********************/

void create_successor(char * source_name,char * target_name) {

	FILE * target_file=0;
	FILE * source_file=0;

	char buffer[256];

	CREATE:
	
	if (0==(target_file=fopen(target_name,"w+")))
		exit(0);
	if (0==(source_file=fopen(source_name,"r")))
		exit(0);
		
	fprint_header(target_file,target_name);
	
	strcpy(buffer,";");
	while (strstr(buffer,";")!=0)
		fgets (buffer,255,source_file);
	
	while (strstr(buffer,"end")==0) {
		
		if (a_insertion())
			fprintf(target_file,"%s\n",new_line_of_code());

		if (a_removal()) 
			printf("]]]]] %s",buffer);
		else { 
			printf("***** %s",buffer);
			fprintf(target_file,"%s\n",evolve_a_line(buffer));
		}
		
		fgets (buffer,255,source_file);
	}

	if (a_insertion())
		fprintf(target_file,"%s\n",new_line_of_code());
	
	fprint_end(target_file,0);
	
	fclose(target_file);		
	fclose(source_file);

	if (test_viable(target_name)==0) goto CREATE;

}/*create_successor()*/

/********************/

#define TOTAL_WIN	 2
#define TOTAL_LOSS	-2
#define	WIN		 1
#define	LOSS		-1
#define TIE		 0


int run_competion(char * source_name,char * t_name) {

	FILE * file=0;

	char command[256];
	char buffer[256]="";
	char * s_ptr=0;
	
	int t_score=0;
	int s_score=0;
	
	sprintf(command,"pmars -r %d -b -o %s %s > temp.txt",
				number_of_battles,source_name,t_name);
	
	system(command);

	if ((file=fopen("temp.txt","r"))==0) exit(0);
	
	fgets (buffer,255,file);

	if (strstr(buffer,source_name)==0) {
		s_ptr=(strstr(buffer,"scores"));				
		s_ptr+=7;
		t_score=atoi(s_ptr);
	} else {
		s_ptr=(strstr(buffer,"scores"));				
		s_ptr+=7;
		s_score=atoi(s_ptr);
	}

	fgets (buffer,255,file);

	if (strstr(buffer,source_name)==0) {
		s_ptr=(strstr(buffer,"scores"));				
		s_ptr+=7;
		t_score=atoi(s_ptr);
	} else {
		s_ptr=(strstr(buffer,"scores"));				
		s_ptr+=7;
		s_score=atoi(s_ptr);
	}

	fclose(file);

	printf("^^^^^%9s %9s:%d %d\n",source_name,t_name,s_score,t_score);
	
	if (s_score>=(3*number_of_battles)) return TOTAL_WIN;
	if (t_score>=(3*number_of_battles)) return TOTAL_LOSS;
	if (s_score>t_score) return WIN;
	if (s_score<t_score) return LOSS;
	return TIE;

}

/********************/

void straight_replace(char * source_name,char * target_name) {

	FILE * target_file=0;
	FILE * source_file=0;
	
	if (0==(target_file=fopen(target_name,"w+")))
		exit(0);
	if (0==(source_file=fopen(source_name,"r")))
		exit(0);
	
	fprint_header(target_file,target_name);
	
	fprint_body(target_file,source_file);

	fprint_end(target_file,0);

	fclose(source_file);
	fclose(target_file);
		
	printf("!!!!! %s -> %s\n",source_name,target_name);	
}

/********************/

int valhalla_score(char * file_name) {

	FILE * file=0;
	char buffer[256];	

	if (0==(file=fopen(file_name,"r")))
		exit(0);

	strcpy(buffer,";");
	
	while (strstr(buffer,"end")==0) 
		fgets (buffer,255,file);

	fgets (buffer,255,file);
		
	fclose(file);

	return atoi((buffer+1));		

}/*valhalla_score()*/

/********************/

void send_to_valhalla(int source_number,char * source_file_name) {

	char target_file_name[256];

	/*make vahalla file name*/
	sprintf(target_file_name,".%svalhalla%s%s",path_symbol,path_symbol,source_file_name);

	/*is this one better than the current valhalla file*/
	if(valhalla_score(target_file_name)>=valhalla_record[source_number]) 
		return;


	/*it not better,so copy the file to valhalla*/

	file_copy(source_file_name,target_file_name);
	
	valhalla_record[source_number]=0;
	
	printf(">>>>> %s\n",source_file_name+1);

}/*send_to_valhalla()*/

/********************/

void return_from_valhalla(char * target_file_name) {
	
	FILE * source_file=0;
	FILE * target_file=0;

	char source_file_name[256];	

	sprintf(source_file_name,".%svalhalla%s%s",path_symbol,path_symbol,target_file_name);

	/*is this one better than the current valhalla file*/
	if(valhalla_score(source_file_name)<=valhalla_score(target_file_name)) 
		return;
	
	if (0==(target_file=fopen(target_file_name,"w+")))
		exit(0);
	if (0==(source_file=fopen(source_file_name,"r")))
		exit(0);
	
	fprint_header(target_file,target_file_name);
	
	fprint_body(target_file,source_file);

	fprint_end(target_file,0);

	fclose(target_file);
	fclose(source_file);

	printf("<<<<< %s\n",target_file_name);

}/*return_from_valhalla()*/

/********************/
	
void add_to_valhalla_score(char * file_name,int target_number,int score) {
			
	FILE * source_file=0;
	FILE * target_file=0;

	valhalla_record[target_number]+=score;

	if (0==(source_file=fopen(file_name,"r")))
		exit(0);
	if (0==(target_file=fopen("temp.red","w+")))
		exit(0);
	
	fprint_header(target_file,file_name);

	fprint_body(target_file,source_file);

	fprint_end(target_file,valhalla_record[target_number]);

	fclose(source_file);
	fclose(target_file);

	/*replace it*/
	file_copy("temp.red",file_name);

}/*add_to_valhalla_score()*/

/********************/

void run_one_cycle(int population_size,char * population_name) { 

	int source_number;
	int target_number;
	
	char source_name[256];
	char target_name[256];

	/*index through whole population*/
	for (source_number=0;source_number<population_size;source_number++) {
		
		/*pick a target*/
		target_number=source_number;
		while (target_number==source_number)
			target_number=(a_random_number(population_size));

		/*make file names*/
		sprintf(source_name,"%s_%d.red",population_name,source_number);
		sprintf(target_name,"%s_%d.red",population_name,target_number);

		
		switch (run_competion(source_name,target_name)) {
			
			case  TOTAL_WIN	: 
				add_to_valhalla_score(source_name,source_number,3);
				send_to_valhalla(target_number,target_name);
				straight_replace(source_name,target_name);
				break;

			case  TOTAL_LOSS : 
				add_to_valhalla_score(target_name,target_number,3);				
				send_to_valhalla(source_number,source_name);				
				straight_replace(target_name,source_name);
				break;
	
			case  WIN : 
				add_to_valhalla_score(source_name,source_number,1);
				send_to_valhalla(target_number,target_name);
				create_successor(source_name,target_name);	
				break;

			case  LOSS : 
				add_to_valhalla_score(target_name,target_number,1);				
				send_to_valhalla(source_number,source_name);
				create_successor(target_name,source_name);				
				break;
			
			case   TIE :					
				if (a_resurrection())					
					return_from_valhalla(source_name);
				else 
					if (a_mutation()) { 						
						send_to_valhalla(source_number,source_name);
						create_successor(source_name,"temp.red");
						straight_replace("temp.red",source_name);
					}				
				break;			
			default	:
				break;
		}/*switch*/
	}/*for*/
}/*run_one_cycle()*/




/********************/

int main() {

	int index;
	
	setup();	

	if (create_new_population)
		create_seed_population(population_size,population_name);
		
	for (index=starting_cycle;index<(starting_cycle+number_of_cycles);index++) {
		
		printf("..... %d ..... %d ..... %d .....%d\n",index,index,index,index);	
		printf("..... %d ..... %d ..... %d .....%d\n",index,index,index,index);	
		printf("..... %d ..... %d ..... %d .....%d\n",index,index,index,index);	
		
		update_cycle_file(index);
		
		run_one_cycle(population_size,population_name);
	}

	return 1;

}


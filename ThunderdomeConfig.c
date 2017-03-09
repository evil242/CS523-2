#include "obj_war.h"
#include "Sorting.h"

#define TOTAL_WIN  2
#define TOTAL_LOSS -2
#define WIN     1
#define LOSS   -1
#define TIE     0

#define NOCROSS 0
#define ONEPTCROSS 1
#define UNIFORMCROSS 2

#define ROULETTE 0
#define TOURNAMENT 1
#define RANDOMSEL 2


/************************************/
/*these are set from the config file*/

 char path_symbol[32]="/";

 int create_new_population=1;
 char population_name[32]="DD";
 int population_size=25;

 int starting_cycle=0;
 int number_of_cycles=25;
 int seed_cycles=10;

 int number_of_battles=3;

 int mutation_rate=5;

 float TSprob=.75;

 int resurrection_rate=2;
 int insertion_rate=5;
 int removal_rate=5;

 int max_number_size=10;
 int max_instructions=10;

 int CrossType = ONEPTCROSS; 
 int SelecType = ROULETTE;


/************************************/

void setup(void){

   FILE * config_file=0;
   time_t t;
   int index;
    char buffer[256];
   char * parm_ptr=0;

   /*seed the random numbers*/
   srand((unsigned int) time(& t));

   /*set defaults*/
   CrossType = ONEPTCROSS; // (ONEPTCROSS,UNIFORMCROSS,NOCROSS)
   create_new_population=1;
   population_size=25;
   number_of_cycles=25;
   starting_cycle=0;
   max_instructions=10;
   max_number_size=10;
   mutation_rate=25;
   insertion_rate=5;
   removal_rate=5;
   resurrection_rate=2;
   number_of_battles=3;
   seed_cycles=10;

   strcpy(population_name,"DD");
   strcpy(path_symbol,"/");

   /*read config file if there*/
   if (0==(config_file=fopen("Obj_Warrior.cfg","r"))){
      printf("Obj_Warrior.cfg not found using defaults.\n");
   }else {
      while (fgets(buffer,255,config_file)!=0) {

         /*ignore this line*/
         if(strstr(buffer,";")!=0) continue;

         if(strstr(buffer,"SelecType")!=0) {
            parm_ptr=strstr(buffer,"=");
            if (parm_ptr!=0)
               SelecType=atoi(++parm_ptr);
            continue;
         }

         if(strstr(buffer,"CrossType")!=0) {
            parm_ptr=strstr(buffer,"=");
            if (parm_ptr!=0)
               CrossType=atoi(++parm_ptr);
            continue;
         }

         if(strstr(buffer,"TSprob")!=0) {
            parm_ptr=strstr(buffer,"=");
            if (parm_ptr!=0)
               TSprob=atof(++parm_ptr);
            continue;
         }

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

         if(strstr(buffer,"seed_cycles")!=0) {
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
               strncpy(path_symbol,++parm_ptr,1);
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
   printf("CrossType=%d\n",CrossType);
   printf("SelecType=%d\n",SelecType);

}

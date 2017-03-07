#include "obj_war.h"
#include "Sorting.h"

#define TOTAL_WIN  2
#define TOTAL_LOSS   -2
#define  WIN       1
#define  LOSS     -1
#define TIE     0

int a_random_integer(int range){
        return (int)range-(rand()%(range*2));
}

int a_random_number(int range) {
        return (int)rand()%range;
}

int Thunderdome(Warrior A, Warrior B){
   FILE * file=0;

   char command[256];
   char buffer[256]="";
   char * s_ptr=0;

   int b_score=0;
   int a_score=0;

   const char *aname = A.SMNB();
   const char *bname = B.SMNB();

   A.fprint();
   B.fprint();

   sprintf(command, "./pmars -r %d -b -o %s %s > temp.txt",
				number_of_battles,aname,bname);

   system(command);

   if ((file=fopen("temp.txt","r"))==0) exit(0);

   fgets (buffer,255,file);

   if (strstr(buffer,aname)==0) {
      s_ptr=(strstr(buffer,"scores"));
      s_ptr+=7;
      b_score=atoi(s_ptr);
   } else {
      s_ptr=(strstr(buffer,"scores"));
      s_ptr+=7;
      a_score=atoi(s_ptr);
   }

   fgets (buffer,255,file);

   if (strstr(buffer,aname)==0) {
      s_ptr=(strstr(buffer,"scores"));
      s_ptr+=7;
      b_score=atoi(s_ptr);
   } else {
      s_ptr=(strstr(buffer,"scores"));
      s_ptr+=7;
      a_score=atoi(s_ptr);
   }

   fclose(file);

   printf("^^^^^%9s %9s:%d %d\n",aname,bname,a_score,b_score);

   if (a_score>=(3*number_of_battles)) return TOTAL_WIN;
   if (b_score>=(3*number_of_battles)) return TOTAL_LOSS;
   if (a_score>b_score) return WIN;
   if (a_score<b_score) return LOSS;
   return TIE;

   


}


// Inter-Tribe warrior fitness
void Bartertown(vector<Warrior> &tribe) {
   int source_number;
   int target_number;
   int pop_size = tribe.size();
   char source_name[256];
   char target_name[256];

  //index through whole population
  for (source_number=0;source_number<pop_size;source_number++) {

   //pick a target
   target_number=source_number;
   while (target_number==source_number)
         target_number=(a_random_number(population_size - 1));

            //Two Men Enter
      switch (Thunderdome(tribe[source_number],tribe[target_number])) {

         case  TOTAL_WIN   :
            //tribe[source_number] [One Man] leaves the Thunderdome
            tribe[source_number].scores(3);
            //straight replace B with A
            //tribe[target_number] = tribe[source_number];
            break;

         case  TOTAL_LOSS :
            //tribe[target_number] [One Man] leaves the Thunderdome
            tribe[target_number].scores(3);
            //straight replace A with B
            //tribe[source_number] = tribe[target_number];
            break;

         case  WIN :
            tribe[source_number].scores(1);
            //create_successor(source_name,target_name);
            break;

         case  LOSS :
            tribe[target_number].scores(1);
            //create_successor(target_name,source_name);
            break;

         case   TIE :
            //if (a_resurrection())
               //return_from_valhalla(source_name);
            //else
               //if (a_mutation()) {
                  //send_to_valhalla(source_number,source_name);
                  //create_successor(source_name,"temp.red");
                  //straight_replace("temp.red",source_name);
               //}
            break;
         default  :
            break;
      }//switch

      


	} //for pop

	

} 




void mixMatch (vector<Warrior> &tribe) {
  int i;
  int count = tribe.size() - 1;
  int size = tribe.size();
  int midpoint = size / 2;
  int j=count;
  for(i=0; i<midpoint; i+=2){
      tribe[i] = tribe[j] + tribe[j-1];
      tribe[i+1] = tribe[j-1] + tribe[j];
      j -=2;

  }
}


int main () {

   srand(time(NULL));

    int i; //for counting dont forget to init

    string tribe_name = "dd";

    //Empty Vector
    vector<Warrior> tribe;

    //Create new Warriors up to pop size default 5
    for (i=0; i<population_size; i++) {

         //pushes new Warrior into the trib, uses Warrior construct to 
         //create random baseline of redcode
         tribe.push_back(Warrior(tribe_name,i));
    }

    //simple print of current tribe members 
    for (i=0; i<tribe.size(); i++) {
      tribe[i].print();
    }

    cout << "Tribe size " << tribe.size() << endl;
    //mixMatch(tribe, tribe_name);
    // printf("Tribe Size = %lu\n", tribe.size());
    for (i=starting_cycle; i<number_of_cycles; i++) {
      //mixMatch(tribe, tribe_name);
      Bartertown(tribe);
      BottomUpMergeSort(tribe);
      mixMatch(tribe);
      }
    //printf("Tribe Size = %lu\n", tribe.size());
    // simple print of current tribe members 
    for (i=0; i<tribe.size(); i++) {
      tribe[i].print();
      }

    
/*     tribe[4].print();
     tribe[4] = tribe[0] + tribe[1];
     tribe[0].print();
     tribe[1].print();
     tribe[4].print();
     tribe[4].test_viable();

     tribe[3].print();
     tribe[3] = tribe[1] + tribe[0];
     tribe[0].print();
     tribe[1].print();
     tribe[3].print();
     tribe[3].test_viable();
*/     
     


    return 0;

}



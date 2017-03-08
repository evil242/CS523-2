#include "obj_war.h"
#include "Sorting.h"

#define TOTAL_WIN  2
#define TOTAL_LOSS -2
#define WIN     1
#define LOSS   -1
#define TIE     0

int a_random_integer(int range){
        return (int)range-(rand()%(range*2));
}

int a_random_number(int range) {
        return (int)rand()%range;
}


int Thunderdome(Warrior A, Warrior B){

   char command[256];
   char buffer[256]="";
   char * s_ptr=0;

   int b_score=0;
   int a_score=0;

   const char *aname = A.SMNB();
   const char *bname = B.SMNB();


   sprintf(command, "./pmars -r %d -b -o %s %s",
            number_of_battles,aname,bname);

   //FILE * file=0;
   //system(command);
   //if ((file=fopen("temp.txt","r"))==0) exit(0);

   FILE *file = popen(command,"r");

   fgets(buffer,255,file);

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

   pclose(file);

   //printf("^^^^^%9s %9s:%d %d\n",aname,bname,a_score,b_score);

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

    for (int i=0; i<pop_size; i++) {
      tribe[i].fprint();
    }

  //index through whole population
  for (source_number=0;source_number<pop_size - 1;source_number++) {

  /*
   // This while uses random once through population to determine fitness
   //pick a target
   target_number=source_number;
   while (target_number==source_number)
         target_number=(a_random_number(population_size - 1)); */

   for (target_number=source_number+1; target_number < pop_size; target_number++) {
       if (target_number != source_number) {

            //Two Men Enter
         switch (Thunderdome(tribe[source_number],tribe[target_number])) {
   
            case  TOTAL_WIN   :
               //tribe[source_number] [One Man] leaves the Thunderdome
               tribe[source_number].scores(3);
               break;
   
            case  TOTAL_LOSS :
               //tribe[target_number] [One Man] leaves the Thunderdome
               tribe[target_number].scores(3);
               break;
            case  WIN :
               tribe[source_number].scores(1);
               break;
            case  LOSS :
               tribe[target_number].scores(1);
               break;
            case   TIE :
               break;
            default  :
               break;
         }//switch
   }//else 
      } //for target_number
    }//for source_number

} 


int RouletSelection (vector<Warrior> &tribe) {
  int i;
  int count = tribe.size() - 1;
  int size = tribe.size();
  int midpoint = size / 2;
  int j=count;
  int sumfit=1; // set to 1 so never div by 0
  int BPC=0;
  long prob_i;

  Warrior BPair[2];
  BPair[0] = tribe[count];
  BPair[1] = tribe[count-1];

  //Calc Sum(Fit_i)
  for (i=0; i<count; i++ ) { 
       sumfit += tribe[i].TwoFit();
  }

  //Select by Roulet chance for breed Out lower half of pop (sorted by MergeSort)
        for(i=0; i<midpoint; i+=2){
          prob_i = 1/rand() ;
          if((tribe[i].TwoFit() / sumfit) < prob_i ) {
            switch (CrossType) {
               case ONEPTCROSS :
                  tribe[i] = BPair[0] + BPair[1];
                  break;
               case UNIFORMCROSS :
                  tribe[i] = BPair[0] * BPair[1];
                  break;
               default : //same as NOCROSS
                  break;
            }
          }
          if((tribe[i+1].TwoFit() / sumfit) < prob_i ) {
            switch (CrossType) {
              case ONEPTCROSS :
                  tribe[i+1] = BPair[1] + BPair[0];
                  break;
               case UNIFORMCROSS :
                  tribe[i+1] = BPair[1] * BPair[0];
                  break;
               default : //same as NOCROSS
                  break;
          
            }
          }
        }

  return sumfit;
}//end RouletSelection


int TournSelection (vector<Warrior> &tribe) {
  int i;
  int count = tribe.size() - 1;
  int size = tribe.size();
  int midpoint = size / 2;
  int j=count;
  int sumfit=0;
  int BPC=0;
  long prob_i;

  Warrior BPair[2];

  //TSprob = .75 from Config.h
  do { 
    sumfit=0;
    BPC=0;
    for (i=0; i<size; i++ ) { 
        int currTM = count - i;
        prob_i = 1/rand();
        if (TSprob * ((1 - TSprob)^i) > prob_i) {
           BPair[BPC] = tribe[currTM];
           BPC++;
        }

       //Calc Sum(Fit_i)
       sumfit += tribe[i].TwoFit();
    }// end for size
  } while (BPC > 1); // make sure we got two breeding pair

  //Select by chance for breed Out lower half of pop (sorted by MergeSort)
  for(i=0; i<midpoint; i+=2){
            switch (CrossType) {
               case ONEPTCROSS :
                  tribe[i] = BPair[0] + BPair[1];
                  break;
               case UNIFORMCROSS :
                  tribe[i] = BPair[0] * BPair[1];
                  break;
               default : //same as NOCROSS
                  break;
            }
            switch (CrossType) {
              case ONEPTCROSS :
                  tribe[i+1] = BPair[1] + BPair[0];
                  break;
               case UNIFORMCROSS :
                  tribe[i+1] = BPair[1] * BPair[0];
                  break;
               default : //same as NOCROSS
                  break;
          
            }
  }

  return sumfit;
}//end TournSelection

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

void Oblong(vector<Warrior> &tribe) {
    int size=tribe.size();
    for (int i=0; i<size; i++) {
       if (mutation_rate > rand() % 100) {
         tribe[i].Mutation(); 
       }
    }

}

void Game(vector<Warrior> &tribe) {
    int size=tribe.size();
    for (int i=0; i<size; i++) {
         tribe[i].PutMeInCoach(); 
    }

}

void TribeReset (vector<Warrior> &tribe) {
    int size=tribe.size();
    for (int i=0; i<size; i++) {
       tribe[i].ResetBMF(); 
       tribe[i].reset_scores(); 
    }

}


void TribeBMFReset (vector<Warrior> &tribe) {
    int size=tribe.size();
    for (int i=0; i<size; i++) {
       tribe[i].ResetBMF(); 
    }

}

int main () {

setup();

    ofstream logfile("./GA_War_Sumfit.log");

   srand(time(NULL));

    int i; //for counting dont forget to init

    int sumfit; //for getting return of tribe fitness


    //Empty Vector
    vector<Warrior> tribe;

    //Create new Warriors up to pop size default 5
    for (i=0; i<population_size; i++) {

         //pushes new Warrior into the trib, uses Warrior construct to 
         //create random baseline of redcode
         tribe.push_back(Warrior(population_name,i));
    }

    //simple print of current tribe members 
    for (i=0; i<tribe.size(); i++) {
      tribe[i].print();
    }

    cout << "Tribe size " << tribe.size() << endl;

    for (i=starting_cycle; i<seed_cycles; i++) {
      TribeReset(tribe);
      Oblong(tribe);  // test for mutation
      Bartertown(tribe);  // Fitness against each other held in Warrior::Rank
      BottomUpMergeSort(tribe);//highest fitness based on rank at largest element
      RouletSelection(tribe); // call crossover
    }


    for (i=starting_cycle; i<number_of_cycles; i++) {
       do {
         TribeReset(tribe);
         Oblong(tribe);  // test for mutation
         Game(tribe);  // Fitness against each other held in Warrior::Rank
         BottomUpMergeSort(tribe);//highest fitness based on rank at largest element
         sumfit = RouletSelection(tribe); // call crossover
         logfile << sumfit << endl;
       } while (sumfit < (5 * NumOWilkies));  // stop criteria 
    }
      // sumfit is the sumation of the fitness for the whole tribe
      // If 5 out of 25 warriors had winning score of 5, sumfit = 25


      Game(tribe);  // Fitness against each other held in Warrior::Rank

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



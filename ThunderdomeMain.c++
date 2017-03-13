#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
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


int Thunderdome(Warrior &A, Warrior &B){

   char command[256];
   char buffer[256]="";
   char * s_ptr=0;

   int b_score=0;
   int a_score=0;

   const char *aname = A.SMNB();
   const char *bname = B.SMNB();


   sprintf(command, "./pmars -r %d -b -o %s %s",
            number_of_battles,aname,bname);


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
   A.scores(a_score);
   B.scores(b_score);

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
   */
   for (target_number=source_number+1; target_number < pop_size; target_number++) {
       if (target_number != source_number) {

            //Two Men Enter
         switch (Thunderdome(tribe[source_number],tribe[target_number])) {
   
            case  TOTAL_WIN   :
               //tribe[source_number] [One Man] leaves the Thunderdome
               //tribe[source_number].scores(3);
               break;
   
            case  TOTAL_LOSS :
               //tribe[target_number] [One Man] leaves the Thunderdome
               //tribe[target_number].scores(3);
               break;
            case  WIN :
               //tribe[source_number].scores(1);
               break;
            case  LOSS :
               //tribe[target_number].scores(1);
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

float RouletSelection (vector<Warrior> &tribe) {
  int i,a,b;
  int count = tribe.size() - 1;
  int size = tribe.size();
  int midpoint = size / 2;
  int j;
  float sumfit=0;
  int BPC=0;
  float prob_i;
  float tribe_prob[size];
  float total_prob = 0;
  int bTribe[size];
  Warrior BTribe[size];
  int canBreed=0;
  float div;
  float min = size;
  //Calc Sum(Fit_i)
  for (i=0; i<size; i++ ) {
       sumfit += tribe[i].TwoFit();
  }
  if(sumfit < 1) sumfit = 1;
    //printf("Sumfit = %f\n", sumfit);  
  //Calculate individual probabilities
  for(i=0; i<size; i++){
      div = tribe[i].TwoFit();
      tribe_prob[i] = total_prob +( div/ sumfit);
      // printf("Tribe Member Probability = %f\n", tribe_prob[i]);
      total_prob = tribe_prob[i];
      div = (rand()% size) +1;
      prob_i = 1/div;
      // printf("Divisor = %f\n", div);
      // printf("Prob_i = %f\n", prob_i);
    
      if(tribe_prob[i] > prob_i) {
	bTribe[i] = 0;
        BTribe[canBreed]= tribe[i];
	canBreed++;
	//printf("Selected for breeding\n");
      }
      else {
        tribe[i].reset_scores();
	bTribe[i] = 1;
	//printf("Rejected for breeding\n");
      }
  }

  BottomUpMergeSort(tribe);//highest fitness based on rank at lowest element


	  
      if(canBreed > 2) {
	//printf("Can Breed\n");
      for(i = canBreed; i < (size-1); i+=2){	  
          if(bTribe[i]) {
             a = rand()%canBreed;
             b = rand()%canBreed;
             while (a == b) 
                b =rand()%canBreed;
            switch (CrossType) {
               case ONEPTCROSS :
		 tribe[i] = BTribe[a]+ BTribe[b];
		 tribe[i+1] = BTribe[b]+ BTribe[a];
                  break;
               case UNIFORMCROSS :
		 tribe[i] = BTribe[a] * BTribe[b];
		 tribe[i+1] = BTribe[b] * BTribe[a];
                  break;
               default : //same as NOCROSS
                  break;
	    }
           tribe[i].Mutation(); 
           tribe[i+1].Mutation(); 
	  }
      }
      }
         
  return sumfit;
}//end RouletSelection


float TournSelection (vector<Warrior> &tribe) {
  int i,a,b;
  int count = tribe.size() - 1;
  int size = tribe.size();
  int midpoint = 1;
  int j=count;
  float sumfit=0;
  int BPC=0;
  float prob_i;
  float average;
  int maxfit=0;
  float fit=0;

  // Calculate Average and capture Max Fit (not used but may use later)
  for (i=0; i<size; i++ ) { 
       sumfit += tribe[i].TwoFit();
       if (maxfit < tribe[i].TwoFit()) {
              maxfit = tribe[i].TwoFit();
       }
  }

  // Average Tribe fitness, for selecting below average
  average = sumfit / size;

   //cout << "Average = " << average << endl;


   // Start selecting against below average
  for (i=0; i<size; i++ ) { 
      if (tribe[i].TwoFit() < average) {
          tribe[i].reset_scores();  // if not already zero, set to zero
      } else { midpoint++; } // cout << "tribe[" << i << "] = " << tribe[i].TwoFit() << endl;}

  }
  
   //cout << "Average = " << average << ", Midpoint = " << midpoint << endl;

  //Select by chance for breed Out lower half of pop (sorted by MergeSort)
  for(i=midpoint; i< (size-1) ; i+=2){
       a = 0;
       b = 0;
       while (a == b) 
          b = rand() % midpoint;
       //cout << "a = " << a << ", b = " << b << endl;
       if ( (float)tribe[i].TwoFit() < (float)(sumfit / size)){
            switch (CrossType) {
               case ONEPTCROSS :
                  tribe[i] = tribe[a] + tribe[b];
                  tribe[i+1] = tribe[b] * tribe[b];
                  break;
               case UNIFORMCROSS :
                  tribe[i] = tribe[a] * tribe[b];
                  tribe[i+1] = tribe[b] * tribe[b];
                  break;
               default : //same as NOCROSS
                  break;
            }
         tribe[i].Mutation(); 
         tribe[i+1].Mutation(); 
      }
  }

  return sumfit;
}//end TournSelection

float ReplaceBottomHalf (vector<Warrior> &tribe) {
  int i;
  int count = tribe.size() - 1;
  int size = tribe.size();
  int midpoint = size / 2;
  float sumfit=0;
  int j=0;


    for (i=0; i<size; i++) {
       sumfit += tribe[i].TwoFit();
    }

  for(i=midpoint; i<(size-1); i+=2){
      tribe[i] = tribe[j] + tribe[j+1];
      tribe[i+1] = tribe[j+1] + tribe[j];
      tribe[i].Mutation(); 
      tribe[i+1].Mutation(); 
      j +=2;

  }

  return sumfit;
}

float Oblong(vector<Warrior> &tribe) {
  //Calc Sum(Fit_i)
    int size=tribe.size();
    float sumfit=0;

    for (int i=0; i<size; i++) {
       sumfit += tribe[i].TwoFit();
       if (mutation_rate > rand() % 100) {
         tribe[i].Mutation(); 
       }
    }

   return sumfit;

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
    int CyclesTIllSwap = insertion_rate; //for counting 
    int GenPop = 0; //count generations

    float sumfit; //for getting return of tribe fitness
    float sumfit2; //2nd IslandGA
    float percentfit;
    float MaxTribeFit = 0.0;
    float MaxDiff,DiffRate;


    //Empty Vector
    vector<Warrior> tribe;
    vector<Warrior> tribe2;
    vector<Warrior> RockyTribe;

    //Create new Warriors up to pop size default 5
    for (i=0; i<population_size; i++) {

         //pushes new Warrior into the trib, uses Warrior construct to 
         //create random baseline of redcode
         tribe.push_back(Warrior(population_name,i));
         tribe2.push_back(Warrior(population_name,i+population_size+5));
    }
         RockyTribe.push_back(Warrior("RagnarLothbrok",1));
         RockyTribe.push_back(Warrior("GrepSedAwk",2));

    //simple print of current tribe members 
    //for (i=0; i<tribe.size(); i++) {
      //tribe[i].print();
    //}

    cout << "Tribe size " << tribe.size() << endl;

     switch (SelecType) {
       case ROULETTE :
            cout << "Running ROULETTE Selection with ";
            break;
       case TOURNAMENT :
            cout << "Running TOURNAMENT Selection with ";
            break;
       default : //same as NOCROSS
            cout << "Running REPLACE 1/2 Selection with ";
            break;
     }

     switch (CrossType) {
       case ONEPTCROSS :
            cout << "1-POINT Crossover" << endl;
            break;
       case UNIFORMCROSS :
            cout << "UNIFORM Crossover" << endl;
            break;
       default : //same as NOCROSS
            cout << "Mutation Only" << endl;
            break;
     }

    cout << "Creating seed population via Battle Royale in the Thunder Dome for " << seed_cycles << " cycles" << endl;
    cout << "Tribe size " << tribe.size() << endl;

    for (i=starting_cycle; i<seed_cycles; i++) {
      TribeReset(tribe);
      TribeReset(tribe2);
      Bartertown(tribe);  // Fitness against each other held in Warrior::Rank
      Bartertown(tribe2);  // Fitness against each other held in Warrior::Rank
      BottomUpMergeSort(tribe);//highest fitness based on rank at lowest element
      BottomUpMergeSort(tribe2);//highest fitness based on rank at lowest element
         switch (SelecType) {
               case ROULETTE :
                  // call Slection and chance for child mutation
                  sumfit = RouletSelection(tribe);
                  break;
               case TOURNAMENT :
                  // call Selection and chance for child mutation
                  sumfit = TournSelection(tribe); 
                  break;
               default : //same as NOCROSS
                  sumfit = ReplaceBottomHalf(tribe);  // down at the chmical spill mutate tribe
                  break;
            }
      //Oblong(tribe);  // test for mutation
         percentfit = (sumfit/((float)tribe.size() * 75));  
         cout << "Sumfit = " << sumfit << ", Percentfit = " 
                 << percentfit << endl;
         logfile << "Sumfit = " << sumfit << ", Percentfit = " 
                 << percentfit << endl;
    }


     switch (SelecType) {
       case ROULETTE :
            cout << "Running ROULETTE Selection with ";
            break;
       case TOURNAMENT :
            cout << "Running TOURNAMENT Selection with ";
            break;
       default : //same as NOCROSS
            cout << "Running REPLACE 1/2 Selection with ";
            break;
     }

     switch (CrossType) {
       case ONEPTCROSS :
            cout << "1-POINT Crossover" << endl;
            break;
       case UNIFORMCROSS :
            cout << "UNIFORM Crossover" << endl;
            break;
       default : //same as NOCROSS
            cout << "Mutation Only" << endl;
            break;
     }

    cout << "Created seed population via Battle Royale in the Thunder Dome for " << seed_cycles << " cycles" << endl;
    cout << "Tribe size " << tribe.size() << endl;
    cout << "Starting GA against Benchmark REDCODE Warriors: " << endl;
    cout << "Will stop after Annealing Rate " << annealing_rate 
         << " hits for " << number_of_cycles << " cycles." << endl;

    cout << "To exit out of this loop, exec cmd touch HALT" << endl
         << "   Example: $ touch HALT" << endl;

    // Do while fitness still moving loop inside of for number_of_cycles
    // As fitness starts to chill below annealing_rate cycle loop counts down
    for (i=number_of_cycles; i>starting_cycle; i--) {
       do {
         GenPop++;
         TribeReset(tribe);
         TribeReset(tribe2);
         Game(tribe);  // Fitness against each other held in Warrior::Rank
         Game(tribe2);  // Fitness against each other held in Warrior::Rank

         //highest fitness based on rank at lowest element
         BottomUpMergeSort(tribe);
         BottomUpMergeSort(tribe2);

         //Make Island Swap
         if (CyclesTIllSwap-- < 1) {
             CyclesTIllSwap = insertion_rate;
              tribe[tribe.size()  - 1] = RockyTribe[1];
             tribe2[tribe2.size() - 1] = RockyTribe[0];
         }

         if (tribe[0].TwoFit() >  RockyTribe[0].TwoFit() ) {
            RockyTribe[0] = tribe[0];
            RockyTribe[0].fprint();
         }
         if (tribe2[0].TwoFit() >  RockyTribe[1].TwoFit() ) {
            RockyTribe[1] = tribe2[0];
            RockyTribe[1].fprint();
         }

         switch (SelecType) {
               case ROULETTE :
                  // call Slection and chance for child mutation
                  sumfit = RouletSelection(tribe);  
                  sumfit2 = RouletSelection(tribe2);  
                  break;
               case TOURNAMENT :
                  // call Slection and chance for child mutation
                  sumfit = TournSelection(tribe);
                  sumfit2 = TournSelection(tribe2);
                  break;
               default : //same as NOCROSS
                  // down at the chmical spill mutate tribe
                  sumfit = ReplaceBottomHalf(tribe);  
                  sumfit2 = ReplaceBottomHalf(tribe2);  
                  break;
            }

         percentfit = (sumfit/((float)tribe.size() * (75 * NumOWilkies))*100);

         MaxDiff = sumfit - MaxTribeFit;

         if (sumfit > MaxTribeFit) MaxTribeFit = sumfit;

         DiffRate = ((float)abs((long)MaxDiff) + MaxTribeFit) / MaxTribeFit;

         logfile << "GenPop = " << GenPop << " : Sumfit = " << sumfit 
                 << " : Percentfit = " << percentfit << " : DiffRate = " 
                 << DiffRate << " : Sumfit2 = " << sumfit2 << endl;

       if (access( "HALT", F_OK ) != -1) {
          cerr << "HALT FILE DETECTED, SAVING FILES AND EXITING" << endl;
          DiffRate = 0.0; i = -1;
       }
        //printf("Sumfit = %f\n", percentfit);
       } while ( DiffRate > annealing_rate );  
              if (DiffRate == 1) {
                 cout << "System has chilled" << endl;
                 i = 0;
              }
  // stop criteria 
         cout << "GenPop = " << GenPop << ": Sumfit = " << sumfit 
              << ", Percentfit = " << percentfit << ", DiffRate = " 
              << DiffRate << endl;
         cout << "Will stop after Annealing Rate " << annealing_rate 
              << " hits for " << i << " cycles." << endl;
    }
      // sumfit is the sumation of the fitness for the whole tribe
      // If 5 out of 25 warriors had winning score of 5, sumfit = 25

    //last fitness and sort
    TribeReset(tribe);
    Game(tribe);  
    TribeReset(tribe2);
    Game(tribe2);  
    //Bartertown(tribe);
    BottomUpMergeSort(tribe);//highest fitness based on rank at lowest element
    BottomUpMergeSort(tribe2);//highest fitness based on rank at lowest element

    if (tribe[0].TwoFit() >  RockyTribe[0].TwoFit() ) {
           RockyTribe[0] = tribe[0];
    }
    if (tribe2[0].TwoFit() >  RockyTribe[1].TwoFit() ) {
           RockyTribe[1] = tribe2[0];
    }
    if (tribe[1].TwoFit() >  RockyTribe[0].TwoFit() ) {
           RockyTribe[0] = tribe[1];
    }
    if (tribe2[1].TwoFit() >  RockyTribe[1].TwoFit() ) {
           RockyTribe[1] = tribe2[1];
    }



    //printf("Tribe Size = %lu\n", tribe.size());
    // simple print of current tribe members 
    for (i=0; i<tribe.size(); i++) {
      tribe[i].fprint();
      //tribe[i].print();
    }
    for (i=0; i<tribe2.size(); i++) {
      tribe2[i].fprint();
      //tribe2[i].print();
    }

    for (i=0; i<RockyTribe.size(); i++) {
       RockyTribe[i].print();
       RockyTribe[i].fprint();
    }
    

    return 0;

}



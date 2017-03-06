#include "obj_war.h"

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

void Bartertown(vector<Warrior> &tribe) {
  int source_number;
  int target_number;
  int pop_size = tribe.size();

  char source_name[256];
  char target_name[256];

  int i = -1;
  int j;
  /*index through whole population*/
  while (tribe.size()>population_size) {
    j = tribe.size()-1;
    if(i >= j){
      i = 0;
    }
    else i ++;
    printf("Tribe size = %d\n", j);
    printf("i = %d\n", i);
    // j = tribe.size()-1;
    /*pick a target*/
    Warrior a = tribe[i];
    Warrior b = tribe[j];

    //Two Men Enter
    switch (Thunderdome(a,b)) {

    case  TOTAL_WIN   :
      //tribe[source_number] [One Man] leaves the Thunderdome
      tribe[i].scores(2);
      tribe[i].rank+=2;
      tribe.pop_back();
      //straight replace B with A
      
      break;

    case  TOTAL_LOSS :
      //tribe[target_number] [One Man] leaves the Thunderdome
      tribe[j].scores(2);
      //straight replace A with B
      tribe[j].rank+=2;
      tribe[i] = tribe[j];
      tribe.pop_back();
      break;

    case  WIN :
      tribe[i].scores(1);
      tribe[i].rank++;
      tribe.pop_back();
      //create_successor(source_name,target_name);
      break;

    case  LOSS :
      tribe[j].scores(1);
      tribe[j].rank++;
      tribe[i] = tribe[j];
      tribe.pop_back();
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
    }/*switch*/




  } /*for pop*/



}

/*
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
            tribe[target_number] = tribe[source_number];
            break;

         case  TOTAL_LOSS :
            //tribe[target_number] [One Man] leaves the Thunderdome
            tribe[target_number].scores(3);
            //straight replace A with B
            tribe[source_number] = tribe[target_number];
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

	

	} */

void crossover1(Warrior a, Warrior b, Warrior c, Warrior d,
		vector<Warrior> &tribe, string name, int sn) {
  int i;
  int j;
  //to do write better constructor for speed
  //Warrior c = Warrior(name, sn);
  c.serno = sn;
  c.fname = name + "_" + to_string(c.serno) + ".red";
  c.body.clear();
  d.serno = sn + 1;
  d.fname = name + "_" + to_string(d.serno) + ".red";
  d.body.clear();
  for(i=0, j=5;  i<5; i++) {
    c.body.push_back(a.body[i]);
    d.body.push_back(a.body[j]);
    j++;	     
    }
    for(j=5, i=0; j<10; j++) {
    c.body.push_back(b.body[j]);
    d.body.push_back(b.body[i]);
    i++;
    }

    if( c.test_viable()) tribe.push_back(c);
    if(d.test_viable()) tribe.push_back(d);
    // printf("TEST A = \n");
    // a.print();
    // printf("TEST B = \n");
    // b.print();
    // printf("TEST C = \n");
    //c.print();
    

}
void crossover2(Warrior a, Warrior b, Warrior c, Warrior d,
		vector<Warrior> &tribe, string name, int sn) {
  int i;
  int j;
  int k;
  int size = tribe.size();
  for(i=0; i<size; i++){
    c = tribe[i];
    d = tribe[i];  
    c.serno = sn;
    c.fname = name + "_" + to_string(c.serno) + ".red";
    d.serno = sn + 1;
    d.fname = name + "_" + to_string(d.serno) + ".red";
  
    for(j=0;  j<size; i++) {
      k = rand() % size;
      c.body[k] = tribe[k].body[k];
      d.body[j] = tribe[k].body[k];
      if( c.test_viable()) tribe.push_back(c);
      if(d.test_viable()) tribe.push_back(d);
     }
  }

    
    // printf("TEST A = \n");
    // a.print();
    // printf("TEST B = \n");
    // b.print();
    // printf("TEST C = \n");
    //c.print();
}

void mixMatch (vector<Warrior> &tribe, string name) {
  int i;
  int j;
  Warrior c = Warrior(name, 100);
  Warrior d = Warrior(name, 100);
  int count = tribe.size();
  int size = tribe.size();
  for(i=0; i<count -1; i++){
    for(j=i+1; j <count; j++){
      crossover1(tribe[i], tribe[j], c, d, tribe, name, size);
      // crossover2(tribe[i], tribe[j], c, d, tribe, name, size);
      size+=2;
    }
  }
}




int main () {

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
      mixMatch(tribe, tribe_name);
      Bartertown(tribe);
      }
    
    //printf("Tribe Size = %lu\n", tribe.size());
    // simple print of current tribe members 
    for (i=0; i<tribe.size(); i++) {
      tribe[i].print();
      }


    return 0;

}



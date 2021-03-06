/*** File obj_war.c ***/
#include "obj_war.h"



string Warrior::new_line_of_code(){

      // creates new string of "opcode.opmod addrmode #,addrmode #"
     string new_line =  opcodes[rand()%number_of_opcodes] +
                        modifiers[rand()%number_of_modifiers] + " " +
                        address_modes[rand()%number_of_address_modes] + " " +
                        to_string(a_random_integer(max_number_size)) + "," +
                        address_modes[rand()%number_of_address_modes] + " " +
                        to_string(a_random_integer(max_number_size)) + "\n";

        //cout << "$$$$$ " << new_line;

        return new_line;

}/*new_line_of_code()*/

int Warrior::test_viable() {
/****
test_viable ganked from ga_war.c by jason@ezmo.com 
Modified for Warrior class
****/

        fprint();


        char command[256];
        char buffer[256]="";
        char * s_ptr=0;

        int count=0;

        /*test length*/
        FILE * file=0;
        if ((file=fopen(fname.c_str(),"r"))==0) exit(0);

        strcpy(buffer,";");

        while (strstr(buffer,";")!=0)
                fgets (buffer,255,file);

        while (strstr(buffer,"end")==0) {
                fgets (buffer,255,file);
                count++;
        }

        fclose(file);

        if (count==0||count>max_instructions) {
                printf(";;;;; %s\n",fname.c_str());
                return 0;
        }


        /*test with plant*/
        sprintf(command,"./pmars -b -o plant.red %s",fname.c_str());

        //system(command);
        file = popen(command,"r");

        //if ((file=fopen("temp.txt","r"))==0) exit(0);

        while (strstr(buffer,fname.c_str())==0)
                fgets (buffer,255,file);

        pclose(file);

        s_ptr=(strstr(buffer,"scores"));

        s_ptr+=7;

        if (atoi(s_ptr)<1) {
                //printf("===== %s %s",fname.c_str(),s_ptr);
                return 0;
        } else {
                //printf("===== %s %s",fname.c_str(),s_ptr);
                return 1;
     }

}/*test_viable()*/ 


// Initial construction of a new Warrior
//  Takes String n "simple name eg dt, or dd"
// and serial number sn eg 0-9 for pop of 10
Warrior::Warrior(string n, int sn)
: BenchmarkFit(0), TribeRank(0), serno(sn) {

  header = ";redcode-94\n;assert CORESIZE == 8000\n;author Damion Terrell and Dominic Paul Delvecchio\n";
  tail = "end;";

  fname = n + "_" + to_string(serno) + ".red";

  do {
    loc=0;
    body.clear();

    // now nets build a body of code 10 lines long
    for(int i=0; i<max_instructions; i++) {

      // fetch string of "opcode.opmod addrmode #,addrmode #"
      body.push_back(new_line_of_code());
      loc++;  // incr lines of code
    }

   // did warrior come alive?
  } while (test_viable() ==0);  // keep creating body until it works
      
}
//Warrior constructor for new Warrior child
Warrior::Warrior(long gen, string n, int sn)
  : BenchmarkFit(0), TribeRank(0), serno(sn) {

  header = ";redcode-94\n;assert CORESIZE == 8000\n;author Damion Terrell and Dominic Paul Delvecchio\n";
  tail = "end;";

  fname = n + "_" + to_string(serno) + ".red";
  generation = gen;

 
  // test_viable();

}

Warrior::Warrior()
  : BenchmarkFit(0), TribeRank(0) {
  body.clear();
  fname = "temp.red";
  header = ";redcode-94\n;assert CORESIZE == 8000\n;author Damion Terrell and Dominic Paul Delvecchio\n";
  tail = "end;";

}

void Warrior::fprint() {
    ofstream fileh(fname.c_str());
    fileh << header;
    fileh << ";Rank " << TribeRank << endl;
    fileh << ";BenchmarkFit " << BenchmarkFit << endl;
    fileh << ";name " << fname << endl;
    for(int i=0; i<loc; i++) {
      fileh << body[i];
    }
    fileh << tail << endl;
    fileh.close();
  
}


void Warrior::print() {
    cout << header;
    cout << ";Rank " << TribeRank << endl;
    cout << ";BenchmarkFit " << BenchmarkFit << endl;
    cout << ";name " << fname << endl;
    for(int i=0; i<loc; i++) {
      cout << body[i];
    }
    cout << tail << endl;
}

// This replaces file_copy
// and straight_replace
/*Warrior::Warrior(const Warrior &rhs) {
  fname = "temp.red";
  header = ";redcode-94\n;assert CORESIZE == 8000\n;author Damion Terrell and Dominic Paul Delvecchio\n";
  tail = "end;";
  //TribeRank = 0;
  TribeRank = rhs.TribeRank;
  BenchmarkFit = rhs.BenchmarkFit;
  loc = rhs.loc;
  body = rhs.body;

}*/

// This replaces file_copy
// and straight_replace
Warrior &Warrior::operator=(const Warrior &rhs) {
  //TribeRank = 0;
  TribeRank = rhs.TribeRank;
  BenchmarkFit = rhs.BenchmarkFit;
  loc = rhs.loc;
  body = rhs.body;

  return *this;
}

//1-point crossover p =5
Warrior &Warrior::operator+(const Warrior &rhs) {
    // loop incr
    int i;
    int this_size = body.size();
    int rhs_size = rhs.body.size();

    int thismid = this_size/2;
    int rhsmid = rhs_size/2;

    Warrior *newar = new Warrior;

    //print();
    //rhs.print();
     
    for (i=0; i<thismid; i++) {
       newar->body.push_back(body[i]);
    }
    for (i=rhsmid; i<rhs_size; i++) {
       newar->body.push_back(rhs.body[i]);
   } 
   newar->loc=newar->body.size();

  
   // did warrior come alive?
      i=thismid;
   // keep tweeking body until it works
      while(newar->test_viable() == 0 && i < newar->loc){   
        newar->body[i] = body[i]; 
        i++;
      }

   //newar->print();

   return *newar;
}


//uniform crossover probability = 0.5
Warrior &Warrior::operator*(const Warrior &rhs) {
  // loop incr
  int i;
  int this_size = body.size();
  int rhs_size = rhs.body.size();
  int j;
                     
  Warrior *newar = new Warrior;

  for (i=0; i<body.size(); i++) {
    
    newar->body.push_back(body[i]);
  }
  for(i=0; i<rhs_size; i++) {
    if(rand() % 2) {
      newar->body[i]= rhs.body[i];
    }
  }
  newar->loc=newar->body.size();

  //newar->print();

  // did warrior come alive? If not return to old body
    i=0;
    while(newar->test_viable() == 0 && i < newar->loc){   
      newar->body[i] = body[i];
      i++;
    }

  return *newar;
}

void Warrior::Mutation() {

  if (mutation_rate < rand() % 100) return;

  // Passed mutation rate, mutate

   //cout << "Mutating " << serno << endl;

  int this_size = body.size();
  int i;
  
  //tweek body unit it works
  do {
    i = rand() % this_size;
    body[i] = new_line_of_code();
    
  } while (test_viable() ==0);
   
}


void Warrior::PutMeInCoach() {


   FILE * file=0;

   char command[256];
   char buffer[256]="";
   char * s_ptr=0;

   int a_score=0;
   int b_score=0;

   const char * aname = fname.c_str();
   string bname;

   fprint();

   //for (int BMtest=0; BMtest < NumOWilkies; BMtest++) {
     bname = Benchmarktest; //WilkiesBenchDir + "/" + WilkiesBench[BMtest]; 


      sprintf(command, "./pmars -r %d -b -o %s %s",
                                number_of_battles,aname,bname.c_str());
   
      //system(command);
      file = popen(command,"r");
 
      //if ((file=fopen("temp.txt","r"))==0) exit(0);
    while (fgets(buffer,255,file)!=0) {
 
      //fgets (buffer,255,file);
      if (strstr(buffer,aname)!=0) {
      //cout << "buffer " << aname << " " << buffer << endl; 
         s_ptr=(strstr(buffer,"scores"));
         s_ptr+=7;
         a_score=atoi(s_ptr);
      }
      }
   
      pclose(file);
   
      //printf("^^^^^%s: %d\n",aname,a_score);
   
         BenchmarkFit += a_score; 
         //if (a_score>=(3*number_of_battles)) BenchmarkFit += 5;
         //if (a_score>b_score) BenchmarkFit += 3;
         //if (a_score == b_score) BenchmarkFit += 1;
   //}




}

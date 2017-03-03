/*** File obj_war.c ***/
#include "obj_war.h"

int a_random_integer(int range){
        return (int)range-(rand()%(range*2));
}

int a_random_number(int range) {

        return (int)rand()%range;
}



string Warrior::new_line_of_code(){
      //sprintf(new_line,"%s%s %s%3d,%s%3d",
     string new_line =  opcodes[rand()%number_of_opcodes] +
                        modifiers[rand()%number_of_modifiers] + " " +
                        address_modes[rand()%number_of_address_modes] + " " +
                        to_string(a_random_integer(max_number_size)) + "," +
                        address_modes[rand()%number_of_address_modes] + " " +
                        to_string(a_random_integer(max_number_size)) + "\n";

        cout << "$$$$$ " << new_line;

        return new_line;

}/*new_line_of_code()*/

int Warrior::test_viable() {
/****
test_viable ganked from ga_war.c by jason@ezmo.com 
Modified for Warrior class
****/

        fprint();

        FILE * file=0;

        char command[256];
        char buffer[256]="";
        char * s_ptr=0;

        int count=0;

        /*test length*/
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
        sprintf(command,"./pmars -b -o plant.red %s > temp.txt",fname.c_str());

        system(command);

        if ((file=fopen("temp.txt","r"))==0) exit(0);

        while (strstr(buffer,fname.c_str())==0)
                fgets (buffer,255,file);

        fclose(file);

        s_ptr=(strstr(buffer,"scores"));

        s_ptr+=7;

        if (atoi(s_ptr)<1) {
                printf("===== %s %s",fname.c_str(),s_ptr);
                return 0;
        } else {
                printf("===== %s %s",fname.c_str(),s_ptr);
                return 1;
     }

}/*test_viable()*/ 


// Initial construction of a new Warrior
//  Takes String n "simple name eg dt, or dd"
// and serial number sn eg 0-9 for pop of 10
Warrior::Warrior(string n, int sn)
: rank(0), serno(sn) {

  header = ";redcode-94\n;assert CORESIZE == 8000\n;author Damion Terrell and Dominic Paul Delvecchio\n";
  tail = "end;";

  fname = n + "_" + to_string(serno) + ".red";

  do {
    loc=0;
    body.clear();

    // now nets build a body of code 10 lines long
    for(int i=0; i<10; i++) {

      // fetch string of "opcode.opmod addrmode #,addrmode #"
      body.push_back(new_line_of_code());
      loc++;  // incr lines of code
    }

   // did warrior come alive?
  } while (test_viable() ==0);  // keep creating body until it works
   	
}


void Warrior::fprint() {
    ofstream fileh(fname.c_str());
    fileh << header;
    fileh << ";name " << fname << endl;
    for(int i=0; i<loc; i++) {
      fileh << body[i];
    }
    fileh << tail << endl;
    fileh.close();
  
}


void Warrior::print() {
    cout << header;
    cout << ";name " << fname << endl;
    for(int i=0; i<loc; i++) {
      cout << body[i];
    }
    cout << tail << endl;
}

// This replaces file_copy
// and straight_replace
Warrior &Warrior::operator=(const Warrior &rhs) {
  rank = 0;

  loc = rhs.loc;

  body = rhs.body;
}


Warrior &Warrior::operator+(const Warrior &rhs) {


}


int main () {
    int i;
    string tribe_name = "dt";
    vector<Warrior> tribe;
    for (i=0; i<population_size; i++) {
      tribe.push_back(Warrior(tribe_name,i));
    }
    for (i=0; i<tribe.size(); i++) {
      tribe[i].print();
    }
    cout << "Tribe size " << tribe.size() << endl;
      tribe[4] = tribe[0];
    for (i=0; i<tribe.size(); i++) {
      tribe[i].print();
    }

}



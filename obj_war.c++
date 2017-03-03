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
        sprintf(command,"pmars -b -o plant.red %s > temp.txt",fname.c_str());

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



Warrior::Warrior(string n, int sn)
: rank(0), serno(sn), loc(0) {
  tail = "end;";
  header = ";redcode-94\n;assert CORESIZE == 8000\n;author Damion Terrell and Dominic Paul Delvecchio\n";

  fname = n + "_" + to_string(serno) + ".red";

  do {
    for(int i=0; i<10; i++) {
      body[i] = new_line_of_code();
      loc = i;
    }
    fprint();
  } while (test_viable() ==0);
   	
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



int main () {

    Warrior First("dt", 0);
    First.print();

}



#include "obj_war.h"

int a_random_integer(int range){
        return (int)range-(rand()%(range*2));
}

int a_random_number(int range) {
        return (int)rand()%range;
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



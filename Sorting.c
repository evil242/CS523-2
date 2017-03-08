#include "obj_war.h"
#include "Sorting.h"

//ganked and modified from Wiki
void BottomUpMergeSort(vector<Warrior> &TribeA) {

  int n = TribeA.size();

  vector<Warrior> TribeB = TribeA;
  //cout << "Merge Sort TribeB size " << TribeB.size() << endl;

   // print B
   /*for (int z=0; z <TribeB.size(); z++) {
      TribeB[z].print();
   }*/

  for (int width = 1; width < n; width = 2 * width) {
        for (int i = 0; i < n; i = i + 2 * width) {
                BottomUpMerge(TribeA, i, min(i+width, n), min(i+2*width,n), TribeB);
        }


        CopyTribe(TribeB,TribeA,n);
   }
}

void BottomUpMerge(vector<Warrior> &TribeA,int iLeft, int iRight, int iEnd, vector<Warrior> &TribeB) {
        int i = iLeft; int j = iRight;
        for (int k = iLeft; k < iEnd; k++) {
                if (i < iRight && (j >= iEnd || TribeA[i].TwoFit() <= TribeA[j].TwoFit())) {
                        TribeB[k] = TribeA[i];
                        i++;
                } else {
                        TribeB[k] = TribeA[j];
                        j++;
                }
        }
}

void CopyTribe(vector<Warrior> &TribeB, vector<Warrior> &TribeA, int n) {
        for (int i = 0; i < n; i++ )
                TribeA[i] = TribeB[i];
}

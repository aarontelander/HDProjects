#include <iostream>
#include <bitset>
using namespace std;

/* Input:
a hexadecimal long, n

Calculation: 
turn n into a 16-bit binary bitset, oldbin
figure out hamming bits for oldbin
fill 21-bit bitset, newbin, with hamming bits and proper oldbin values

Output:
newbin as a hexadecimal long */
long hamming(long n)
{
  bitset<16> oldbin(n); // this is the 16-bit binary
  bitset<21> newbin; // this will become our 21-bit hamming code

  int hamarray[5] = {}; // this array holds ham1, ham2, ham4, ham8, han16 respectively
  
  /* bitsets index zero as the rightmost bit
    These comments reference the "first bit" as the leftmost bit*/
  if (oldbin[15]) { // if the first bit is 1, then that affects ham1 and ham2
    ++hamarray[0];
    ++hamarray[1];
  }

  if (oldbin[14]) { // if the second bit is 1, then that affects ham1 and ham4
    ++hamarray[0];
    ++hamarray[2];
  }

  if (oldbin[13]) { // if the third bit is 1, then that affects ham2 and ham4
    ++hamarray[1];
    ++hamarray[2];
  }

  if (oldbin[12]) { // if the fourth bit is 1, then that affects ham1, ham2, and ham4
    ++hamarray[0];
    ++hamarray[1];
    ++hamarray[2];
  }

  if (oldbin[11]) { // if the fifth bit is 1, then that affects ham1 and ham8
    ++hamarray[0];
    ++hamarray[3];
  }

  if (oldbin[10]) { // if the sixth bit is 1, then that affects ham2 and ham8
    ++hamarray[1];
    ++hamarray[3];
  }

  if (oldbin[9]) { // if the seventh bit is 1, then that affects ham1, ham2, and ham8
    ++hamarray[0];
    ++hamarray[1];
    ++hamarray[3];
  }

  if (oldbin[8]) { // if the eighth bit is 1, then that affects ham4 and ham8
    ++hamarray[2];
    ++hamarray[3];
  }

  if (oldbin[7]) { // if the ninth bit is 1, then that affects ham1, ham4, and ham8
    ++hamarray[0];
    ++hamarray[2];
    ++hamarray[3];
  }

  if (oldbin[6]) { // if the tenth bit is 1, then that affects ham2, ham4, and ham8
    ++hamarray[1];
    ++hamarray[2];
    ++hamarray[3];
  }

  if (oldbin[5]) { // if the eleventh bit is 1, then that affects ham1, ham2, ham4, and ham8
    ++hamarray[0];
    ++hamarray[1];
    ++hamarray[2];
    ++hamarray[3];
  }

  if (oldbin[4]) { // if the twelfth bit is 1, then that affects ham1 and ham16
    ++hamarray[0];
    ++hamarray[4];
  }

  if (oldbin[3]) { // if the thirteenth bit is 1, then that affects ham2 and ham16
    ++hamarray[1];
    ++hamarray[4];
  }

  if (oldbin[2]) { // if the fourteenth bit is 1, then that affects ham1, ham2, and ham16
    ++hamarray[0];
    ++hamarray[1];
    ++hamarray[4];
  }

  if (oldbin[1]) { // if the fifteenth bit is 1, then that affects ham4 and ham16
    ++hamarray[2];
    ++hamarray[4];
  }

  if (oldbin[0]) { // if the sixteenth bit is 1, then that affects ham1, ham4, and ham16
    ++hamarray[0];
    ++hamarray[2];
    ++hamarray[4];
  }

  // This loop makes sure that ham1, ham2, ham4, ham8, and ham16 are parity bits
  for (int i=0; i<=4; i++)
    hamarray[i] = hamarray[i] % 2;

  // This loop fills our new bitset, putting the hamming bits in the proper places
  int oldbin_index = 0; // this keeps track of our old bitset
  for (int it=0; it<=20; it++) {
    if (it == 20) // ham1 goes in the first bit
      newbin[it] = hamarray[0];
    else if (it == 19) // ham2 goes in the second bit
      newbin[it] = hamarray[1];
    else if (it == 17) // ham4 goes in the fourth bit
      newbin[it] = hamarray[2];
    else if (it == 13) // ham8 goes in the eighth bit
      newbin[it] = hamarray[3];
    else if (it == 5) // ham16 goes in the sixteenth bit
      newbin[it] = hamarray[4];
    else { // all other bits get filled with the old bitset
      newbin[it] = oldbin[oldbin_index];
      ++oldbin_index;
    }
  }

  // we need to turn our bitset back into a long
  return newbin.to_ulong();
}

int main()
{
  cin.setf(ios::hex, ios::basefield);
  cout.setf(ios::hex, ios::basefield);
  long hex;
  cout << "Enter a four-digit hexadecimal value: ";
  cin >> hex;
  cout << "The hamming code is: ";
  cout << hamming(hex) << endl;
  return 0;
}

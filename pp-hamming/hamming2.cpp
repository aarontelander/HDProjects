#include <iostream>
#include <bitset>
using namespace std;

/* Input:   
a corrupted hamming code in the form of a hexadecimal long, n

Calculation:
turn n into a 21-bit binary bitset, oldbin
extract the hamming bits, oldhamarray
extract the corrupt 16-bit binary data, data
calculate what hamming bits would be off of corrupt data, store values in newhamarray
compare oldhamarray and newhamarray, figure out which bit is corrupt
build newbin with original hamming bits and corrected data bit

Output:   
newbin as a hexadecimal long */
long hamming(long n)
{
  bitset<21> oldbin(n); // this is the 21-bit binary for the incorrect hamming code
  bitset<16> data; // this is the 16-bit data
  bitset<21> newbin; // this will become our fixed 21-bit hamming code
  int oldhamarray[5] = {}; // this array holds ham1, ham2, ham4, ham8, ham16 respectively
  int newhamarray[5] = {}; // this array will hold our fixed ham1, ham2, ham4, ham8, ham16 respectively

  // this loop extracts our hamming bits and fills our 16-bit data
  int data_index = 0; // this keeps track of the old bitset
  for (int i = 0; i < 21; i++) {
    if (i == 20) // han1 is in the first bit
      oldhamarray[0] = oldbin[i];
    else if (i == 19) // ham2 is in the second bit
      oldhamarray[1] = oldbin[i];
    else if (i == 17) // ham4 is in the fourth bit 
      oldhamarray[2] = oldbin[i];
    else if (i == 13) // ham8 is in the eighth bit
      oldhamarray[3] = oldbin[i];
    else if (i == 5) // ham16 is in the sixteenth bit
      oldhamarray[4] = oldbin[i];
    else { // all other bits go into our data
      data[i] = oldbin[i];
      ++data_index;
    }
  }

  /* bitsets index zero as the rightmost bit
     These comments reference the "first bit" as the leftmost bit*/
  if (data[15]) { // if the first bit is 1, then that affects ham1 and ham2
    ++newhamarray[0];
    ++newhamarray[1];
  }

  if (data[14]) { // if the second bit is 1, then that affects ham1 and ham4
    ++newhamarray[0];
    ++newhamarray[2];
  }

  if (data[13]) { // if the third bit is 1, then that affects ham2 and ham4
    ++newhamarray[1];
    ++newhamarray[2];
  }

  if (data[12]) { // if the fourth bit is 1, then that affects ham1, ham2, and ham4
    ++newhamarray[0];
    ++newhamarray[1];
    ++newhamarray[2];
  }

  if (data[11]) { // if the fifth bit is 1, then that affects ham1 and ham8
    ++newhamarray[0];
    ++newhamarray[3];
  }

  if (data[10]) { // if the sixth bit is 1, then that affects ham2 and ham8
    ++newhamarray[1];
    ++newhamarray[3];
  }

  if (data[9]) { // if the seventh bit is 1, then that affects ham1, ham2, and ham8
    ++newhamarray[0];
    ++newhamarray[1];
    ++newhamarray[3];
  }

  if (data[8]) { // if the eighth bit is 1, then that affects ham4 and ham8
    ++newhamarray[2];
    ++newhamarray[3];
  }

  if (data[7]) { // if the ninth bit is 1, then that affects ham1, ham4, and ham8
    ++newhamarray[0];
    ++newhamarray[2];
    ++newhamarray[3];
  }

  if (data[6]) { // if the tenth bit is 1, then that affects ham2, ham4, and ham8
    ++newhamarray[1];
    ++newhamarray[2];
    ++newhamarray[3];
  }

  if (data[5]) { // if the eleventh bit is 1, then that affects ham1, ham2, ham4, and ham8
    ++newhamarray[0];
    ++newhamarray[1];
    ++newhamarray[2];
    ++newhamarray[3];
  }

  if (data[4]) { // if the twelfth bit is 1, then that affects ham1 and ham16
    ++newhamarray[0];
    ++newhamarray[4];
  }

  if (data[3]) { // if the thirteenth bit is 1, then that affects ham2 and ham16
    ++newhamarray[1];
    ++newhamarray[4];
  }

  if (data[2]) { // if the fourteenth bit is 1, then that affects ham1, ham2, and ham16
    ++newhamarray[0];
    ++newhamarray[1];
    ++newhamarray[4];
  }

  if (data[1]) { // if the fifteenth bit is 1, then that affects ham4 and ham16
    ++newhamarray[2];
    ++newhamarray[4];
  }

  if (data[0]) { // if the sixteenth bit is 1, then that affects ham1, ham4, and ham16
    ++newhamarray[0];
    ++newhamarray[2];
    ++newhamarray[4];
  }

  // This loop makes sure that ham1, ham2, ham4, ham8, and ham16 are parity bits
  for (int i=0; i<=4; i++)
    newhamarray[i] = newhamarray[i] % 2;
  
  int wrong_bit_pos = 21;
  // figure out which hamming bits are wrong
  bool ham1_is_corrupt = (oldhamarray[0] != newhamarray[0]);
  bool ham2_is_corrupt = (oldhamarray[1] != newhamarray[1]);
  bool ham4_is_corrupt = (oldhamarray[2] != newhamarray[2]);
  bool ham8_is_corrupt = (oldhamarray[3] != newhamarray[3]);
  bool ham16_is_corrupt = (oldhamarray[4] != newhamarray[4]);
  
  // adjust the position of the corrupt bit, given incorrect hamming bits
  if (ham1_is_corrupt)
    wrong_bit_pos = wrong_bit_pos - 1;
  if (ham2_is_corrupt)
    wrong_bit_pos = wrong_bit_pos - 2;
  if (ham4_is_corrupt)
    wrong_bit_pos = wrong_bit_pos - 4;
  if (ham8_is_corrupt)
    wrong_bit_pos = wrong_bit_pos - 8;
  if (ham16_is_corrupt)
    wrong_bit_pos = wrong_bit_pos - 16;

  // This loop fills our new bitset, putting the hamming bits in the proper places
  int data_index2 = 0; // this keeps track of our old bitset
  for (int it=0; it<=20; it++) {
    if (it == wrong_bit_pos)
      newbin[it] = (data[wrong_bit_pos]) ? false : true;
    else if (it == 20) // ham1 goes in the first bit
      newbin[it] = oldhamarray[0];
    else if (it == 19) // ham2 goes in the second bit
      newbin[it] = oldhamarray[1];
    else if (it == 17) // ham4 goes in the fourth bit
      newbin[it] = oldhamarray[2];
    else if (it == 13) // ham8 goes in the eighth bit
      newbin[it] = oldhamarray[3];
    else if (it == 5) // ham16 goes in the sixteenth bit
      newbin[it] = oldhamarray[4];
    else { // all other bits get filled with the old bitset
      newbin[it] = data[data_index2];
      ++data_index2;
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
  cout << "Enter a hexadecimal hamming code that has a 1-bit error: ";
  cin >> hex;
  cout << "The correct hamming code is: ";
  cout << hamming(hex) << endl;
  return 0;
}

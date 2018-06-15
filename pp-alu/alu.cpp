#include <iostream>
#include "blogic.H"
using namespace std;

int carry_out(int enable, int carry_in, int A, int B)
{
  return bor(band(enable, A, B),band(enable, bxor(A, B), carry_in));
}

int output(int enable_0, int enable_1, int enable_2, int enable_3, int carry_in, int A, int B)
{
  return 2*bor(band(band(A, B), enable_0), band(bor(A, B), enable_1), band(bnot(B), enable_2),band(bxor(carry_in, bxor(A, B)), enable_3));
}

int alu(int F_0, int F_1, int INVA, int ENA, int ENB, int carry_in, int A, int B)
{
  int A_result = bxor(INVA, band(A, ENA));
  int B_result = band(B, ENB);
  int enable_0 = band(bnot(F_0), bnot(F_1));
  int enable_1 = band(bnot(F_0), F_1);
  int enable_2 = band(F_0, bnot(F_1));
  int enable_3 = band(F_0, F_1);
  return carry_out(enable_3, carry_in, A_result, B_result)+output(enable_0, enable_1, enable_2, enable_3, carry_in, A_result, B_result);
}

void print_call(int F_0, int F_1, int INVA, int ENA, int ENB, int carry_in, int A, int B)
{
  cout << "alu(" << F_0 << ", " << F_1 << ", " << INVA << ", " << ENA << ", " << ENB << ", " << carry_in << ", " << A << ". " << B << ") --> " << alu(F_0, F_1, INVA, ENA, ENB, carry_in, A, B) << endl;
}

void print_section(int F_0, int F_1, int INVA, int ENA, int ENB)
{
  cout << endl;
  cout << "F0=" << F_0 << ", F1=" << F_1 << ", INVA=" << INVA << ", ENA=" << ENA << ", ENB=" << ENB << endl;
  print_call(F_0, F_1, INVA, ENA, ENB, 0, 0, 0);
  print_call(F_0, F_1, INVA, ENA, ENB, 0, 0, 1);
  print_call(F_0, F_1, INVA, ENA, ENB, 0, 1, 0);
  print_call(F_0, F_1, INVA, ENA, ENB, 0, 1, 1);
  print_call(F_0, F_1, INVA, ENA, ENB, 1, 0, 0);
  print_call(F_0, F_1, INVA, ENA, ENB, 1, 0, 1);
  print_call(F_0, F_1, INVA, ENA, ENB, 1, 1, 0);
  print_call(F_0, F_1, INVA, ENA, ENB, 1, 1, 1);
}

int main()
{
  // cout << alu(1, 1, 0, 1, 1, 1, 1, 1) << endl;
  print_section(0, 0, 0, 0, 0);
  print_section(0, 0, 0, 0, 1);
  print_section(0, 0, 0, 1, 0);
  print_section(0, 0, 0, 1, 1);
  print_section(0, 0, 1, 0, 0);
  print_section(0, 0, 1, 0, 1);
  print_section(0, 0, 1, 1, 0);
  print_section(0, 0, 1, 1, 1);
  print_section(0, 1, 0, 0, 0);
  print_section(0, 1, 0, 0, 1);
  print_section(0, 1, 0, 1, 0);
  print_section(0, 1, 0, 1, 1);
  print_section(0, 1, 1, 0, 0);
  print_section(0, 1, 1, 0, 1);
  print_section(0, 1, 1, 1, 0);
  print_section(0, 1, 1, 1, 1);
  print_section(1, 0, 0, 0, 1);
  print_section(1, 0, 0, 1, 0);
  print_section(1, 0, 0, 1, 1);
  print_section(1, 0, 1, 0, 0);
  print_section(1, 0, 1, 0, 1);
  print_section(1, 0, 1, 1, 0);
  print_section(1, 0, 1, 1, 1);
  print_section(1, 1, 0, 0, 0);
  print_section(1, 1, 0, 0, 1);
  print_section(1, 1, 0, 1, 0);
  print_section(1, 1, 0, 1, 1);
  print_section(1, 1, 1, 0, 0);
  print_section(1, 1, 1, 0, 1);
  print_section(1, 1, 1, 1, 0);
  print_section(1, 1, 1, 1, 1);
  return 0;
}


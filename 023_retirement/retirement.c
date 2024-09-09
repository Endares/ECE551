#include <stdio.h>
#include <stdlib.h>

typedef struct _retire_info {
  int months;  //the number of months it is applicable to
  double
      contribution;  //  how many dollars are contributed (or spent if negative) from the account permonth
  double
      rate_of_return;  //the rate of returns  (which we will assume to be "after inflation").
} retire_info;

void retirement(int startAge,         //in months
                double initial,       //initial savings in dollars
                retire_info working,  //info about working
                retire_info retired)  //info about being retired
{
  double account_balance = initial;
  int age = startAge;  //in months
  for (; age < working.months + startAge; ++age) {
    printf("Age %3d month %2d you have $%.2f\n", age / 12, age % 12, account_balance);
    account_balance =
        account_balance + account_balance * working.rate_of_return + working.contribution;
  }

  for (; age < retired.months + working.months + startAge; ++age) {
    printf("Age %3d month %2d you have $%.2f\n", age / 12, age % 12, account_balance);
    account_balance =
        account_balance + account_balance * retired.rate_of_return + retired.contribution;
  }
  return;
}

int main() {
  retire_info working = {489, 1000, 0.045 / 12};
  retire_info retired = {384, -4000, 0.01 / 12};
  retirement(327, 21345, working, retired);
  return 0;
}

// header files here
#include <stdio.h>
#include <stdlib.h>

// _retire_info
struct _retire_info {
  int months;  // number of months it is applicable to
  double contribution; // how many dollars are contributed/spent per month
  double rate_of_return;  // rate of returns after inflation
};

typedef struct _retire_info retire_info;


double calculateAccountBalance(double balance, retire_info retirement) {
  balance += (balance * (retirement.rate_of_return / 12));
  balance += retirement.contribution;
  return balance;
}


// main function
// stageAge: in months
// initial: initial savings
// working: info about working
// retired: info about retired
double retirementFlow(int startAgeMonths, double balance, retire_info retirement) {
  int endMonths = (startAgeMonths + retirement.months);
  for (int i = startAgeMonths; i < endMonths; i ++) {
    printf("Age %3d month %2d you have $%.2f\n", (i / 12), ((i % 12) + 1), balance);
    balance = calculateAccountBalance(balance, retirement);

  }
  return balance;
}


void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double workingBalance = retirementFlow(startAge, initial, working);
  startAge += working.months;
  retirementFlow(startAge, workingBalance, retired);
}


int main() {
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;

  int startAge = 327;  // 27 years, 3 months
  double initial = 21345;
  retirement(startAge, initial, working, retired);
  return (EXIT_SUCCESS);
}

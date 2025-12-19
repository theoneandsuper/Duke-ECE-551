#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
	int months;
	double contribution;
	double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement (int startAge, double initial, retire_info working, retire_info retired ){
	int work_age = startAge;

	double balance = initial;

	for (int i = 0; i < working.months; i++) {
      		printf("Age %3d month %2d you have $%.2f\n",
		        work_age / 12, work_age % 12, balance);
     
		balance += balance * working.rate_of_return + working.contribution;

		work_age++;
	}

	for (int i = 0; i < retired.months; i++) {	
		printf("Age %3d month %2d you have $%.2f\n",
			work_age / 12, work_age % 12, balance);

		balance += balance * retired.rate_of_return + retired.contribution;

		work_age++;
	}
}

int main(void) {
	retire_info working = {489, 1000.0, 0.045 / 12};

	retire_info retired = {384, -4000.0, 0.01 / 12};

	retirement(327, 21345.0, working, retired);

	return 0;
}	


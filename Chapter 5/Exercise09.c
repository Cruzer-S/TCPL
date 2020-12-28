#include <stdio.h>

int day_of_year(int year, int month, int day);
int month_day(int year, int yearday, int *pmonth, int *pday);

int main(void)
{
	int year, month, day, pm, pd;

	printf("YYYY-MM-DD: ");
	scanf("%d %d %d", &year, &month, &day);

	pm = day_of_year(year, month, day);
	if (pm == -1)
		printf("failed to day_of_year(%d, %d ,%d)\n", year, month, day);
	else
		printf("day_of_year: %d \n", pm);

	

	printf("YYYY-YOD: ");
	scanf("%d %d", &year, &day);
	if (month_day(year, day, &pm, &pd))
		printf("Month: %d\tDay: %d\n", pm, pd);
	else
		printf("failed to month_day(%d %d, &X, &Y)\n", year, day);

	return 0;
}

static char daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30 ,31, 30, 31 }
};

int day_of_year(int year, int month, int day)
{
	char *dtp;
	int leap, i;

	if (month < 1 || month > 12)
		return -1;

	if (day < 1 || day > 31)
		return -1;

	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1, dtp = *(daytab + leap) + 1;
		 i < month; i++, dtp++)
		day += *dtp;

	return day;
}

int month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;
	char *dtp;

	if (yearday < 1 || yearday > 365) {
		*pmonth = *pday = -1;
		return 0;
	}

	leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);

	for (dtp = *(daytab + leap) + 1;
		 yearday > *dtp; dtp++)
		yearday -= *dtp;

	*pmonth = dtp - *(daytab + leap);
	*pday = yearday;

	return 1;
}


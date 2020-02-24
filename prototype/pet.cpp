#include <stdio.h>
#include <time.h>

#define TEEN 120
#define ADULT 180
#define SENIOR 650
#define GHOST 1000

// Pet attributes
time_t time_now, time_born, time_ate;
int age = 0;
int hunger = 100;

// Pet milestones
bool evolve_teen = true;
bool evolve_adult = true;
bool evolve_senior = true;

void delay(int number_of_seconds)
{
    clock_t start_time = clock();

    // Loop until number_of_seconds passed
    while (clock() < start_time + number_of_seconds * CLOCKS_PER_SEC);
}
void petAction()
{
  char c;
  scanf(" %c",&c);
  if (c == 'c')
  {
    time(&time_ate);
    printf("I ate a carrot! Yummy!\n");
  }
}

int main() {

  printf("I am born!\n");

  time(&time_born);

  time(&time_ate);

  while(1)
  {
    petAction();

    time(&time_now);

    age = time_now - time_born;
    hunger = 100 - (time_now - time_ate);

    int hunger_meter = 100 - hunger;

    printf("I am %d seconds old, and %d%% hungry.\n",age,hunger_meter);

    if (age >= GHOST || hunger <= 0)
    {
      printf("RIP\n");
      break;
    }
    else if (evolve_senior && age >= SENIOR)
    {
      printf("I'm a senior!\n");
      evolve_senior = false;
    }
    else if (evolve_adult && age >= ADULT)
    {
      printf("I'm an adult!\n");
      evolve_adult = false;
    }
    else if (evolve_teen && age >= TEEN) {
      printf("I'm a teen!\n");
      evolve_teen = false;
    }

    delay(1);
  }
   return 0;
}

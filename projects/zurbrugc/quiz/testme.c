#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // TODO: rewrite this function
	char r1 = (rand() % 95) + 32;
    return r1;
}

char *inputString()
{
    // TODO: rewrite this function
	char randChar1, randChar2, randChar3, randChar4, randChar5;
	//random number 0 to 100
	int r1 = rand() % 101;
	if (r1 == 64) {
		//make sure the string is reset occasionally
		char stringArray[] = { 'r', 'e', 's', 'e', 't', '\0' };
		return stringArray;
	}
	else {
			randChar1 = (rand() % 95) + 32;
			randChar2 = (rand() % 95) + 32;
			randChar3 = (rand() % 95) + 32;
			randChar4 = (rand() % 95) + 32;
			randChar5 = (rand() % 95) + 32;
			char stringArray[] = { randChar1, randChar2, randChar3, randChar4, randChar5, '\0' };
			return stringArray;
	}
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

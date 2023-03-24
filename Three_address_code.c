//Habel Saju Zachariah
//CS20B1037

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 63

int t_count = 1;
int stack[MAX_SIZE];     
int top = -1;            

int is_empty() 
{
   if(top == -1)
      return 1;
   else
      return 0;
}
   
int is_full() 
{
   if(top == MAX_SIZE)
      return 1;
   else
      return 0;
}

int peek() 
{
   return stack[top];
}

int pop() 
{
   int data;
   if(!is_empty()) 
   {
      data = stack[top];
      top = top - 1;   
      return data;
   }
    else 
   {
	  printf("Could not delete data, Stack is empty.\n");
	  exit(1);
   }
	 return -1;
}

void push(int data) 
{
   if(!is_full()) 
   {
      top = top + 1;   
      stack[top] = data;
   } 
   else 
   {
      printf("Could not insert data, Stack is full.\n");
	  exit(1);
   }
}

void mixed(char *exp, int i)
{
	int len = strlen(exp);
	int end = 0;
	if(i+4 == len)
    {
		end = 1;
	}
	if(!end)
    {
		if(is_empty())
        {
		printf("T%d = %c %c %c\n", t_count++, exp[i+1], exp[i+2], exp[i+3]);
		printf("T%d = %c %c T%d\n", t_count, exp[i-1] , exp[i], t_count - 1);
		}
        else
        {
			int data = pop();
			printf("T%d = %c %c %c\n", t_count++, exp[i+1], exp[i+2], exp[i+3]);
			printf("T%d = T%d %c T%d\n", t_count, data , exp[i], t_count - 1);
		}
	}
    else
    {
		if(is_empty())
        {
			printf("T%d = %c %c %c\n", t_count++, exp[i+1], exp[i+2], exp[i+3]);
			printf("out = %c %c T%d\n", exp[i-1] , exp[i], t_count - 1);
		}
        else
        {
			int data = pop();
			printf("T%d = %c %c %c\n", t_count++, exp[i+1], exp[i+2], exp[i+3]);
			printf("out = T%d %c T%d\n",  data , exp[i], t_count - 1);
		}
	}
	push(t_count);
	t_count+=1;
}

void div_mul(char *exp, int i)
{
	int len = strlen(exp);
	int end = 0;
	if(i+2 == len)
    {
		end = 1;
	}
	if(!end)
    {
		if(is_empty())
        {
		printf("T%d = %c %c %c\n", t_count, exp[i-1], exp[i], exp[i+1]);
		}
        else
        {
			int data = pop();
			printf("T%d = T%d %c %c\n", t_count, data, exp[i], exp[i+1]);
		}
	}
    else
    {
		if(is_empty())
        {
		printf("out = %c %c %c\n", exp[i-1], exp[i], exp[i+1]);
		}
        else
        {
			int data = pop();
			printf("out = T%d %c %c\n", data, exp[i], exp[i+1]);
		}
	}
	push(t_count);
	t_count+=1;
}

void add_sub(char *exp, int i)
{
	int len = strlen(exp);
	int end = 0;
	if(i+2 == len)
    {
		end = 1;
	}
	if(!end)
    {
		if(is_empty())
        {
		printf("T%d = %c %c %c\n", t_count, exp[i-1], exp[i], exp[i+1]);
		}
        else
        {
			int data = pop();
			printf("T%d = T%d %c %c\n", t_count, data, exp[i], exp[i+1]);
		}
	}
    else
    {
		if(is_empty())
        {
		printf("out = %c %c %c\n", exp[i-1], exp[i], exp[i+1]);
		}
        else
        {
			int data = pop();
			printf("out = T%d %c %c\n", data, exp[i], exp[i+1]);
		}
	}
	push(t_count);
	t_count+=1;
}



int main()
{
	char exp[MAX_SIZE];
	printf("\nEnter the exp with arithmetic operator[without assignment]: ");
	scanf("%s", exp);
	int len = strlen(exp);

	for(int i = 0; i < len; i++)
    {
		if(exp[i] == '+' || exp[i] == '-')
        {
			if(exp[i+2] == '*' || exp[i+2] == '/')
            {
				mixed(exp, i);
				i+=2;
			}
            else
            {
				add_sub(exp, i);
			}
		}
        else if(exp[i] == '*' || exp[i] == '/')
        {
			div_mul(exp, i);
		}
	}
	return 0;
}
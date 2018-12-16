#include <stdio.h>

#define MAX 200

long long stack[MAX];    
int top;    

void init_stack(void){
	top = -1;
}

void push(long long t){
	if (top >= MAX - 1){
		printf("Stack full\n");
		return;
	}
	stack[++top] = t;
}

long long pop(void){
	if (top < 0){
		printf("Stack empty\n");
		return -1;
	}
	return stack[top--];
}

long long get_stack_top(void){
	return (top < 0) ? -1 : stack[top];
}

int is_stack_empty(void){
	return (top < 0);
}

int is_operator(int k){
	return (k == '+' || k == '-' || k == '*' || k == '/');
}

int precedence(long long op){
	if (op == '(') 
		return 0;
	if (op == '+' || op == '-') 
		return 1;
	if (op == '*' || op == '/') 
		return 2;
	else 
		return 3;
}

void postfix(char *dst, char *src){
	init_stack();
	
	while (*src){
		if (*src == '('){
			push(*src);
			src++;
		}
		else if (*src == ')'){
			while (get_stack_top() != '('){
				*dst++ = (char)pop();
				*dst++ = ' ';
			}
			pop();
			src++;
		}
		else if (is_operator(*src)){
			while (!is_stack_empty() && precedence(get_stack_top()) >= precedence(*src)){
				*dst++ = (char)pop();
				*dst++ = ' ';
			} 
			push(*src);
			src++;
		}
		else if (*src >= '0' && *src <= '9'){
			do{
				*dst++ = *src++;
			} while (*src >= '0' && *src <= '9');
			*dst++ = ' ';
		}
		else{
			src++;
		}
	}

	while (!is_stack_empty()){
		*dst++ = (char)pop();
		*dst++ = ' ';
	}
	dst--;
	*dst = 0;
}

long long calc(char *p){
	long long i;

	init_stack();
	
	while (*p){
		if (*p >= '0' && *p <= '9'){
			i = 0;
			do{
				i = i * 10 + *p - '0';
				p++;
			} while (*p >= '0' && *p <= '9');
			push(i);
		}
		else if (*p == '+'){
			push(pop() + pop());
			p++;
		}
		else if (*p == '*'){
			push(pop() * pop());
			p++;
		}
		else if (*p == '-'){
			i = pop();
			push(pop() - i);
			p++;
		}
		else if (*p == '/'){
			i = pop();
			push(pop() / i);
			p++;
		}
		else{
			p++;
		}
	}
	return pop();
}

int main(void){
	char exp[201];
	char pf[256];

	scanf("%s", exp);
	postfix(pf, exp);
	printf("%lld\n", calc(pf));

	return 0;
}

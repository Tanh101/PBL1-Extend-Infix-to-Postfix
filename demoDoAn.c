#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#define SIZE 100            
float stack[SIZE];
int top=-1;
void Push(float);
float Pop();
int pr(char);
char *str(char *, char *, char *);
int inToPost(char *, char *, char *);
float value(char *,int *);
void SetColor(int, int);
void show();
int main(){
    char infix[SIZE], postfix[SIZE], tmp1[SIZE];
    int kt = 1;
	show();
	SetColor(0,9);
	char ch = 'c';
	while(ch != 'k'){
		SetColor(0, 10);
		printf("\n\n\n\n\t\t\t\t\t--------- DO AN LAP TRINH TINH TOAN ----------");
		SetColor(0, 11);
		printf("\n\n\n\n\n\n\t\t\t\tInfix:\t\t\t\t");
		gets(infix);
		
		if(inToPost(infix, postfix, tmp1) == 0)
			printf("\n\n\n\n\t\t\t\t\t\tBieu thuc trung to khong hop le!");
		else{
			printf("\n\n\t\t\t\tPostfix:\t\t\t%s", tmp1);
			value(postfix, &kt);
			if(kt == 0){		
				printf("\n\n\n\t\t\t\tValue of postfix:\t\tBieu thuc co dang vo dinh!");
			}
			else
				printf("\n\n\n\t\t\t\tValue of postfix:\t\t%5.5f", value(postfix, &kt));	
		}
		
		SetColor(0, 7);
		printf("\n\n\n\n\n\n\n\t\t\t\t\t\tBan co muon tiep tuc khong c/k : ");
		ch = getch();
		system("cls");
	}
    return 0;
}
/*---------------------------------------------------------------------------------------------------------------------------*/
void SetColor(int backgound_color, int text_color){
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}
/*---------------------------------------------------------------------------------------------------------------------------*/
void show(){
	SetColor(0,10);
	printf("\n\n\n\n\t\t\t\t\t--------- DO AN LAP TRINH TINH TOAN ----------");
	printf("\n\n\n\n\tDE TAI 803:\tBIEN DOI BIEU THUC TRUNG TO SANG BIEU THUC HAU TO ROI TINH GIA TRI CUA BIEU THUC DO");
	SetColor(0,11);
    printf("\n\n\n\n*---------------------------------------------------------------------------------------------------------------------*");
	printf("\n*\t\t\t\t\t\t\t\t\t\t\t\t\t\t      *");
	printf("\n*\t\t\t\t\t\t\t\t\t\t\t\t\t\t      *");
	printf("\n*\t\t\tGiang Vien Huong Dan:\t\t\t\tThS. Nguyen Van Nguyen\t\t\t      *");
	printf("\n*\t\t\t\t\t\t\t\t\t\t\t\t\t\t      *");
	printf("\n*\t\t\t\t\t\t\t\t\t\t\t\t\t\t      *");
    printf("\n*\t\t\tNhom SV Thuc Hien:\t\t\t\tLy Van Tanh\t\t\t\t      *");
    printf("\n*\t\t\t\t\t\t\t\t\t\t\t\t\t\t      *");
	printf("\n*\t\t\t\t\t\t\t\t\tNgo Duc Quoc Khanh\t\t\t      *");
   	printf("\n*\t\t\t\t\t\t\t\t\t\t\t\t\t\t      *");
   	printf("\n*\t\t\t\t\t\t\t\t\t\t\t\t\t\t      *");
    printf("\n*---------------------------------------------------------------------------------------------------------------------*");
	SetColor(0, 7);
	printf("\n\n\n\t\t\t\t\tNhan phim bat ky de tiep tuc...");
	getch();
	system("cls");
	
}
/*---------------------------------------------------------------------------------------------------------------------------*/
void Push(float ele){
	stack[++top] = ele;
}
/*---------------------------------------------------------------------------------------------------------------------------*/
//lay 1 ptu dinh cua stack
float Pop(){
	return(stack[top--]);
	
}
/*---------------------------------------------------------------------------------------------------------------------------*/
//do uu tien toan tu
int pr(char x){            
	if (x == '(' )
		return 1;
	if (x == '+' || x == '-')
		return 2;
	if (x == '*' || x == '/')
		return 3;
	if(x == '^')
		return 4;
	if(x >= 'a' && x <= 'z')
		return 5;
	return -1;
}
/*---------------------------------------------------------------------------------------------------------------------------*/
//replace cac ky trong chuoi tu thanh chuoi cac ham sin, cos, tan,...
char *str(char *s, char *s1, char *s2){
	int len = strlen (s);
	int len1 = strlen (s1);
	int len2 = strlen (s2);
	int i = 0, j, luu;
	if (len1 != 0)
		while (i < len){
			if (s[i] == s1[0]){
				j = 0;
				luu = i;
				while (s1[++j] == s[++luu] && j < len1);
				if (j == len1){
					memmove(&s[i + len2], &s[i + len1], len - i - len1 + 1);
					memcpy(&s[i], s2, strlen(s2));
					len = len - len1 + len2;
					i += len2;
				}
				else i++;
			}else i++;
		}
	return s;
}
/*---------------------------------------------------------------------------------------------------------------------------*/
//bien doi ve dang hau to, tmp1 de luu full chuoi duoi dang hau to roi dua ra ma hinh
//ham return 0 khi input khong thoa man
int inToPost(char infix[], char postfix[], char tmp1[]){
	int i, k = 0;
	char token;
 	for(i = 0; infix[i] != '\0'; i++){
 		while(infix[i] == ' ')	i++;
 		token = infix[i];
        if( token == '('){
			Push(token);
		} 
        else if(token >= '0' && token <= '9'){
			postfix[k++]=token;
		}
		else if(token == '.'){
			if(isdigit(infix[i - 1]) && isdigit(infix[i+1]))
				postfix[k++] = token;
			else return 0;
		}
        else if( token == ')'){
            while( stack[top] != '(')
                 postfix[k++]=Pop();
           	Pop();
        }
        else if(infix[i] >= 'a' && infix[i] <= 'z'){
        	char tmp[50];
        	int l = 0;
        	while(infix[i] >= 'a' && infix[i] <= 'z'){
        		tmp[l++] = infix[i++];
			}
			tmp[l] = '\0';
			//moi ky tu dai dien cho mot ham de Push và stack
			if(strcmp(tmp, "sin") == 0)		Push('q');
			else if(strcmp(tmp, "cos") == 0)	Push('w');
			else if(strcmp(tmp, "tan") == 0)	Push('e');
			else if(strcmp(tmp, "cot") == 0)	Push('d');
			else if(strcmp(tmp, "ln") == 0)		Push('p');
			else if(strcmp(tmp, "log") == 0)	Push('x');
			else if(strcmp(tmp, "sqrt") == 0)	Push('h');
			else if(strcmp(tmp, "asin") == 0)	Push('y');
			else if(strcmp(tmp, "acos") == 0)	Push('u');
			else if(strcmp(tmp, "atan") == 0)	Push('f');
			else if(strcmp(tmp, "pi") == 0)		Push('j');
			else return 0;
			i--;
		}
        else {
        	if(pr(token) == -1)	return 0;
        	while( pr(stack[top]) >= pr(token) && top > -1 )
                postfix[k++]=Pop();
            Push(token);
            postfix[k++] = ' ';
        }
    }
    
    while( stack[top] != '\0'){
        postfix[k++]=Pop();
	}
    postfix[k]='\0';
//copy 1 chuoi de bien doi dua ra output, con 1 chuoi de tinh toan value postfix
    strcpy(tmp1, postfix);
//bien cac ky tu dac trung thanh cac chuoi tuong ung
    str(tmp1, "q", " sin");
    str(tmp1, "w", " cos");
    str(tmp1, "e", " tan");
    str(tmp1, "d", " cot");
    str(tmp1, "p", " ln");
    str(tmp1, "x", " log");
    str(tmp1, "h", " sqrt");
    str(tmp1, "y", " asin");
    str(tmp1, "u", " acos");
    str(tmp1, "f", " atan");
    str(tmp1, "j", " pi");
    return 1;
}
/*---------------------------------------------------------------------------------------------------------------------------*/
//tinh Value
//con tro *kt de ktra xem co bi suy bien khi tinh toan khong, vd 1/0 , tan(90), log(x) voi x<0,...
float value(char postfix[],int *kt){
	float op1, op2, result; 
	int i = 0;
	while (postfix[i] != '\0'){
		while (postfix[i] ==' ' || postfix[i] == '\t'){
			i++;
		}
		if (isdigit(postfix[i])){
			char tmp2[100];
			int  l = 0;
			while(isdigit(postfix[i])){
				tmp2[l++] = postfix[i++];
			}
			if(postfix[i] == '.' && isdigit(postfix[i+1])){
				tmp2[l++] = postfix[i++];
			}
			while(isdigit(postfix[i])){
				tmp2[l++] = postfix[i++];
			}
			tmp2[l] = '\0';
			Push(atof(tmp2));
		//pi la 1 so nen can duyet de push vao stack
		}else if(postfix[i] == 'j'){
			Push(M_PI);
			i++;
		}	
		else if(postfix[i] >= 'a' && postfix[i] <= 'z'){
			float op3 = Pop();
			switch(postfix[i]){
				case 'q': 
					result = sin(op3*M_PI/180);
					break;
				case 'w':
					result = cos(op3*M_PI/180);
					break;
				case 'e':
					if(op3 == 90)	*kt = 0;
					result = tan(op3*M_PI/180);
					break;
				case 'd':
					if(op3 == 0)	*kt = 0;
					result = 1/tan(op3*M_PI/180);
					break;
				case 'p':
					if(op3 <= 0)	*kt = 0;
					result = log(op3);
					break;
				case 'x':
					if(op3 <= 0)	*kt = 0;
					result = log10(op3);
					break;
				case 'h':
					if(op3 < 0)	*kt = 0;
					result = sqrt(op3);
					break;
				case 'y':
					if(op3 < -1 || op3 > 1)		*kt = 0;
					result = asin(op3)*180/M_PI;
					break;
				case 'u':
					if(op3 <-1 || op3 > 1) *kt = 0;
					result = acos(op3)*180/M_PI;
					break;
				case 'f':
					result = atan(op3)*180/M_PI;
					break;	
			}
			Push(result);
				i++;
		}
		else{
			op1 = Pop();
			op2 = Pop();
			switch (postfix[i++]){
			case '+':
				result = op2 + op1;		break;
			case '-':
				result = op2 - op1;		break;
			case '/':
				if(op1 == 0)
					*kt = 0;
				result = op2 / op1;		break;
			case '*':
				result = op2 * op1;		break;
			case '^':
				result = pow(op2,op1);
			}
			Push(result);
		}
	}
	result = Pop();
	return result;
}

//sin(30) + cos(0) - sqrt(4)
// 1.5
// log(10)*tan(45)-sin(90)+12.33*sin(30)

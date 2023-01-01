//극장 예약 시스템
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h> //strcmp() 함수 사용하기 위해 필요한 헤더 파일
#define SIZE 5 //최대 회원의 수
#define ID_SIZE 21 //아이디의 최대 길이

int rest = 100;  //남은 좌석의 수
int num = 0; //회원의 수
int i = 0; //회원 정보를 배열에 차례로 저장하기 위한 전역변수

void print_seats(int a[10][10]);  //좌석의 예약 상태를 출력하는 함수
void seat_reservation(int a[10][10]);  //좌석을 예약하는 함수
void signup_login(); //회원가입과 로그인을 하는 함수

struct member
{
	char id[ID_SIZE];
	int pw;
};

int main(void)
{
	char ans1, ans2;
	int seats[10][10] = { 0 };

	signup_login();

	while (1)
	{
		printf("\n좌석을 예약하시겠습니까? (y 또는 n) ");
		scanf(" %c", &ans1);  //반복문에서 문자를 입력받을 때는 %c 앞에 공백을 하나 주기 (문자를 입력할 때 문자를 입려한 뒤 enter키도 입력하기 때문)

		if (ans1 == 'y')
		{
			print_seats(seats);

			seat_reservation(seats);

		}
		else if (ans1 == 'n')
		{
			num++; //회원의 수가 기존보다 1명 증가함

			if (num < SIZE) //회원의 수가 최대 회원의 수보다 작아서 회원가입이 더 가능할 경우
			{
				printf("\n프로그램을 종료하시겠습니까? (y 또는 n) ");
				scanf(" %c", &ans2);

				if (ans2 == 'y')
				{
					printf("\n프로그램을 종료합니다.");
					break;
				}
				else if (ans2 == 'n') //다른 사람이 회원가입을 할 수 있도록 전환됨
				{
					printf("\n");
					signup_login();
				}
				else
					printf("y 또는 n을 입력해주십시오.\n");
			}
			else
			{
				printf("\n프로그램이 종료되었습니다.\n"); //현재 회원의 수가 최대 회원의 수보다 크면 프로그램이 종료됨
				break;
			}
		}
		else
			printf("y 또는 n을 입력해주십시오.\n");
	}

	return 0;
}

void print_seats(int a[10][10]) //좌석의 예약 상태를 출력하는 함수
{
	printf("\n----------------------------------\n");
	printf("< 예약 >");
	printf("\n----------------------------------\n");
	printf("     1 2 3 4 5 6 7 8 9 10\n\n");

	int r = 1;

	for (int i = 0; i < 10; i++)
	{
		printf("%2d   ", r);
		r++;

		for (int j = 0; j < 10; j++)
			printf("%d ", a[i][j]);

		printf("\n");
	}

	printf("\n");
}

void seat_reservation(int a[10][10]) //좌석을 예약하는 함수
{
	int n, r, c; //n:예약할 인원 수, r:예약할 좌석을 행, c:예약할 좌석을 열
	int i = 0, N = 1;  //while (i != N)에서 초기화된 변수를 사용하기 위함

	while (i != N)  //"현재 예약 가능한 최대 인원은 %d명 입니다.\n" 다음에 "예약하실 인원 수를 입력해주십시오. "로 가기 위함
	{
		printf("예약하실 인원 수를 입력해주십시오. ");
		scanf("%d", &n);

		if (n > rest)
		{
			printf("현재 예약 가능한 최대 인원은 %d명 입니다.\n", rest);  //남은 좌석의 수를 초과하는 인원을 예약받을 수 없도록 하기
		}
		else
			for (i; i < n; i++)
			{
				printf("\n몇 번째 행의 몇 번째 열 좌석을 예약하시겠습니까? (행 열): ");
				scanf("%d %d", &r, &c);

				if (r < 1 || r > 10 || c < 1 || c > 10)
				{
					printf("1부터 10 사이의 숫자를 입력하시오.\n");
					n++;  //존재하지 않는 좌석을 예약하려고 시도한 경우는 예약한 횟수에 포함시키지 않음
				}

				else if (a[r - 1][c - 1] == 0)
				{
					a[r - 1][c - 1] = 1;
					rest = rest - 1;
					printf("예약되었습니다.\n");
				}
				else
				{
					printf("이미 예약된 좌석입니다.\n");
					n++;  //이미 예약된 좌석을 예약하려고 시도한 경우는 예약한 횟수에 포함시키지 않음
				}
			}
		N = n;  //while (i != N)을 사용하기 위함
	}
}

void signup_login() //회원가입과 로그인을 하는 함수
{
	struct member m[SIZE];

	char ID[ID_SIZE]; //아이디를 저장
	int PW; //비밀번호를 저장
	int check = 0; //비밀번호가 올바른지 확인

	printf("< 회원가입 >\n");

	printf("아이디를 입력하시오(최대 %d글자): ", ID_SIZE - 1);
	gets_s(m[i].id, ID_SIZE);

	printf("비밀번호를 입력하시오: ");
	scanf("%d%*c", &m[i].pw); //비밀번호를 입력한 후에 입력할 개행문자('\n')를 버퍼에서 없애주기 위해 '%d' 뒤에 '%*c'를 붙임

	printf("회원가입이 완료되었습니다.\n\n");

	printf("< 로그인 >\n");

	while (check != 2)
	{
		printf("아이디를 입력하시오: ");
		gets_s(ID, ID_SIZE);

		printf("비밀번호를 입력하시오: ");
		scanf("%d", &PW);

		if ((strcmp(m[i].id, ID)) == 0) //strcmp(s1, s2) : 문자열 s1과 문자열 s2를 비교하여 문자열이 같으면 0을 반환
			check++;

		if (m[i].pw == PW)
			check++; //비밀번호가 동일하면 check는 2가 됨

		if (check == 2)
			printf("로그인이 완료되었습니다.\n");
		else
			printf("아이디 또는 비밀번호가 올바르지 않습니다.\n");
	}

	i++; //다음 회원 정보를 다음 배열에 저장하기 위함
}
#define _CRT_SECURE_NO_WARNINGS //scanf 에러 발생을 방지하기 위해 선언
#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

int** create_matrix(int row, int col); //matrix 배열의 틀을 만드는 함수
void print_matrix(int** matrix, int row, int col); //만들어진 matrix 배열을 출력하는 함수
int free_matrix(int** matrix, int row, int col); //동적 메모리 할당을 통해 만든 배열(행렬) 메모리 해제 함수
int fill_data(int** matrix, int row, int col); //0~19 사아의 정수값으로 이루어진 배열(행렬)을 만드는 함수
int addition_matrix(int** matrix_a, int** matrix_b, int row, int col); //matrix a와 b의 합을 출력하는 함수
int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col); //matrix a와 b의 차를 출력하는 함수
int transpose_matrix(int** matrix, int** matrix_t, int row, int col); //matrix a의 전치행렬을 출력하는 함수
int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col); //matrix a와 a의 전치행렬의 곱을 출력하는 함수

int main()
{

    char command;
    printf("[----- [김수영]  [2020039042] -----]\n");

    int row, col; //배열의 행과 열
    srand(time(NULL)); //srand() 함수를 이용하여 프로그램이 작동할 때마다 새로운 값들이 나오도록 함
                       //즉, 반복되는 결과값이 나오지 않게 함

    printf("Input row and col : ");
    scanf("%d %d", &row, &col);
    int** matrix_a = create_matrix(row, col); //matrix a 생성
    int** matrix_b = create_matrix(row, col); //matrix b 생성
    int** matrix_a_t = create_matrix(col, row); //matrix a의 전치행렬 생성

    printf("Matrix Created.\n");

    if (matrix_a == NULL || matrix_b == NULL) {return -1;} //만약 matrix a와 matrix b가 비었다면 -1을 리턴

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Matrix Manipulation                        \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Matrix   = z           Print Matrix        = p \n");
        printf(" Add Matrix          = a           Subtract Matrix     = s \n");
        printf(" Transpose matrix_a  = t           Multiply Matrix     = m \n");
        printf(" Quit                = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //명령어 입력

        switch(command) {
        case 'z': case 'Z':
            printf("Matrix Initialized\n");
            fill_data(matrix_a, row, col); //앞의 create_matrix() 함수에서 만들어진 matrix a에 row와 col 정보를 이용하여 행렬에 값을 채워넣음
            fill_data(matrix_b, row, col); //앞의 create_matrix() 함수에서 만들어진 matrix b에 row와 col 정보를 이용하여 행렬에 값을 채워넣음
            break;
        case 'p': case 'P':
            printf("Print matrix\n");
            printf("matrix_a\n");
            print_matrix(matrix_a, row, col); //matrix a 출력
            printf("\n");
            printf("\nmatrix_b\n"); 
            print_matrix(matrix_b, row, col); //matrix b 출력
            printf("\n");
            break;
        case 'a': case 'A':
            printf("Add two matrices\n");
            addition_matrix(matrix_a, matrix_b, row, col); //matrix a와 b 합 출력
            printf("\n");
            break;
        case 's': case 'S':
            printf("Subtract two matrices \n");
            subtraction_matrix(matrix_a, matrix_b, row, col); //matrix a와 b 차 출력
            printf("\n");
            break;
        case 't': case 'T':
            printf("Transpose matrix_a \n");
            printf("matrix_a\n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix a의 전치행렬 생성
            print_matrix(matrix_a_t, col, row); //matrix a의 전치행렬 출력
            printf("\n");
            break;
        case 'm': case 'M':
            printf("Multiply matrix_a with transposed matrix_a \n");
            transpose_matrix(matrix_a, matrix_a_t, col, row); //matrix a의 전치행렬 생성
            multiply_matrix(matrix_a, matrix_a_t, row, col); //matrix a와 전치행렬의 곱 생성 및 출력
            printf("\n");
            break;
        case 'q': case 'Q':
            printf("Free all matrices..\n");
            free_matrix(matrix_a_t, col, row); //matrix a의 전치행렬 메모리 해제
            free_matrix(matrix_a, row, col); //matrix a의 메모리 해제
            free_matrix(matrix_b, row, col); //matrix b의 전치행렬 생성
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    }while(command != 'q' && command != 'Q'); //q 또는 Q가 입력될 때까지 해당 while문 반복

    return 1; //프로그램 종료 시 1리턴
}

int** create_matrix(int row, int col)
{   
    if(row <= 0 || col <=0) //row 또는 col값이 0보다 작으면 null리턴(행렬의 행과 열은 0보다 작을 수 없기 때문)
    {
        printf("Check the sizes of row and col!\n"); 
        return NULL;
    }
    int** matrix;
    matrix = (int**)malloc(row*sizeof(int*)); //2차원 배열은 1차원 배열의 1차원 배열이며, 배열의 행 포인터들에 (int형 크기*row)만큼 동적할당 받음
    for(int i=0; i<row; i++)
    {
        matrix[i] = (int*)malloc(col*sizeof(int)); //위에서 생성한 배열의 각 index에 malloc을 이용하여 배열 생성
    }
    return matrix; //matrix는 row x col 배열이 됨
}

void print_matrix(int** matrix, int row, int col)
{
    for(int i=0; i<row; i++)
    {
        printf("\n");
        for(int j=0; j<col; j++) 
        {
            printf("%3d ",matrix[i][j]); //3자리를 맞추어 가독성을 높임
            //열을 한 바퀴돌고 나면 다음 행으로 이동하면서 값을 출력 -> fill_data()에서 만든 행렬을 출력
        }
    }
}

int free_matrix(int** matrix, int row, int col)
{
    for(int i=0; i<row; i++) //free(matrix) -> 메모지 해제 안 됨(matrix는 int형 이중포인터라는 것을 알아야함)
    {
        free(matrix[i]);
        //col개의 연속된 공간을 row번 할당을 해주어 메모리를 할당한 것이므로
        //matrix[]라는 1차원 배열에서 row번 메모리를 먼저 해제함
    }
    free(matrix);
    //1차적인 메모리 해제 후 남은 데이터 해제
}

int fill_data(int** matrix, int row, int col)
{
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            int num = rand()%20; //0~19 정수들만 입력받게 됨
            matrix[i][j] = num; //열을 한 바퀴 돌고 다음 행으로 이동하면서 정수들을 채워넣음
        }
    }
}

int addition_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    for(int i=0; i<row; i++) //matrix a와 b는 size가 같음
    {
        printf("\n");
        for(int j=0; j<col; j++) //즉, a11+b11처럼 같은 위치에 있는 entry끼리 합함
        {
            printf("%3d ",matrix_a[i][j] + matrix_b[i][j]); //이를 일반화하게 되면 matrix_a[i][j]+matrix_b[i][j]
        }
    }
}

int subtraction_matrix(int** matrix_a, int** matrix_b, int row, int col)
{
    for(int i=0; i<row; i++) //matrix a와 b는 size가 같음
    {
        printf("\n");
        for(int j=0; j<col; j++) //즉, a11-b11처럼 같은 위치에 있는 entry끼리 뺌
        {
            printf("%3d ",matrix_a[i][j] - matrix_b[i][j]); //이를 일반화하게 되면 matrix_a[i][j]-matrix_b[i][j]
        }
    }
}

int transpose_matrix(int** matrix, int** matrix_t, int row, int col)
{
    for(int i=0; i<col; i++) //전치행렬은 행렬의 행은 열로, 열은 행으로 이동하면서 만들어짐
    {
        for(int j=0; j<row; j++) //따라서 matrix a의 row와 col을 반대로 하여 for문을 돌림
           matrix_t[j][i]=matrix[i][j]; //matrix a의 행과 열이 바뀐 상태로 전치행렬에 저장
    }
}

int multiply_matrix(int** matrix_a, int** matrix_t, int row, int col)
{
    int **matrix_axt;
    matrix_axt = (int**)malloc(row*sizeof(int*)); //matrix a와 그 전치행렬의 곱을 담을 새로운 matrix를 생성
    for(int x=0; x<row; x++)
    {
        matrix_axt[x] = (int*)malloc(row*sizeof(int));
        //m x n matrix와 n x m matrix의 결과는 m x m matrix가 됨
        //따라서 배열의 행 포인터와 그 후의 열 포인터에 메모리를 할당할 때, matrix a의 행을 곱한만큼 메모리 할당
    }
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<row; j++)
        {
            matrix_axt[i][j] = 0; //row x row matrix인 matrix_axt의 모든 entry를 0으로 초기화
            for(int y=0; y<col; y++)
            {
                matrix_axt[i][j] += matrix_a[i][y] * matrix_t[y][j]; 
                //행렬의 곱은 (matrix a의 1번째 row * 전치행렬의 1번째 col) -> matrix_axt의 entry t11
                //           (matrix a의 1번째 row * 전치행렬의 2번째 col) -> matrix_axt의 entry t12
                //이런 식으로 반복되고 이를 일반화한 것이 위의 반복문임
            }
        }
    }
    for(int a=0; a<row; a++)
    {
        printf("\n");
        for(int b=0; b<row; b++) //row x row matrix이기에 각 for문은 row번 반복
        {
            printf("%3d ", matrix_axt[a][b]); //matrix_axt 출력
        }
    }
    for(int z=0; z<row; z++)
    {
        free(matrix_axt[z]); 
        //2차원 배열 = 1차원 배열의 1차원 배열이므로 먼저 row번 메모리를 해제
    }
    free(matrix_axt);
    //나머지 메모리를 해제
}


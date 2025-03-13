#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

typedef struct{
    int height;
    int length;
    int **grid;
    int rows;
    int columns;
}Matrix;

Matrix init(int R, int C){
    Matrix matrix;
    matrix.height=0;
    matrix.length=0;
    matrix.grid=(int **)malloc(R*sizeof(int *));
    for (int i = 0; i < R; i++)
    {
        matrix.grid[i]=(int *)malloc(C*sizeof(int));
    }
    matrix.rows=R;
    matrix.columns=C;
    return matrix; 
}

Matrix copy(Matrix matrix){
    Matrix copied=init(matrix.rows,matrix.columns);
    for (int i = 0; i < matrix.height; i++)
    {
        for (int j = 0; j < matrix.length; j++)
        {
            copied.grid[i][j]=matrix.grid[i][j];
        }
    }
    copied.height=matrix.height;
    copied.length=matrix.length;
    return copied;
}

void clear(Matrix *matrix){
    matrix->height=0;
    matrix->length=0;
}

void delete(Matrix *matrix){ 
    for (int i = 0; i < matrix->height; i++)
    {
        free(matrix->grid[i]);
    }
    free(matrix->grid);
    matrix->grid=NULL;
    matrix->height=0;
    matrix->length=0;
    matrix->rows=0;
    matrix->columns=0;
}

bool isEmpty(Matrix matrix){
    return matrix.height==0 && matrix.length==0;
}

bool isFull(Matrix matrix){
    return matrix.height==matrix.rows && matrix.length==matrix.columns;
}

bool isSquare(Matrix matrix){
    return matrix.height==matrix.length;
}

bool isIn(Matrix matrix, int value){
    for (int i = 0; i < matrix.height; i++)
    {
        for (int j = 0; j < matrix.length; j++)
        {
            if(matrix.grid[i][j]==value) return true;   
        }
    }
    return false;
}

void traverse(Matrix matrix){
    for (int i = 0; i < matrix.height; i++)
    {
        for (int j = 0; j < matrix.length; j++)
        {
            printf("%2d ",matrix.grid[i][j]);
        }
        printf("\n");
    }
    printf(" : (%dx%d)/(%dx%d)\n",matrix.height,matrix.length,matrix.rows,matrix.columns);
}

Matrix slice(Matrix matrix, int fromRow, int toRow, int fromColumn, int toColumn){
    Matrix sliced=init(matrix.rows,matrix.columns);
    for (int i = fromRow; i < toRow; i++)
    {
        sliced.length=0;
        for (int j = fromColumn; j < toColumn; j++)
        {
            sliced.grid[sliced.height][sliced.length]=matrix.grid[i][j];
            sliced.length++;
        }
        sliced.height++;
    }
    return sliced;
}

Matrix exclude(Matrix matrix, int remRow, int remColumn){
    Matrix reduced=init(matrix.rows,matrix.columns);
    for (int i = 0; i < matrix.height; i++){
        if(i==remRow) continue;
        reduced.length=0;
        for (int j = 0; j < matrix.length; j++){
            if(j==remColumn) continue;
            reduced.grid[reduced.height][reduced.length]=matrix.grid[i][j];
            reduced.length++;
        }
        reduced.height++;
    }
    return reduced;
}

void fill(Matrix *matrix, int value){
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            matrix->grid[i][j]=value;
        }
    }
    matrix->height=matrix->rows;
    matrix->length=matrix->columns;
}

void random(Matrix *matrix, int min, int max){
    srand(time(0));
    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            matrix->grid[i][j]=rand()%(max-min)+min;
        }
    }
    matrix->height=matrix->rows;
    matrix->length=matrix->columns;
}

void shuffle(Matrix *matrix){
    srand(time(0));
    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->length; j++)
        {
            swap(&matrix->grid[i][j],&matrix->grid[rand()%matrix->height][rand()%matrix->length]);
        }
    }
}

void transpose(Matrix *matrix){
    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < i; j++)
        {
            swap(&matrix->grid[i][j],&matrix->grid[j][i]);
        }
    }
}

int get(Matrix matrix, int row, int column){
    return matrix.grid[row][column];
}

void set(Matrix *matrix, int value, int row, int column){
    matrix->grid[row][column]=value;
}

void replace(Matrix *matrix, int new, int old){
    for (int i = 0; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->length; j++)
        {
            if(matrix->grid[i][j]==old)
            {
                matrix->grid[i][j]=new;
            }   
        }
    }
}

int count(Matrix matrix, int value){
    int freq=0;
    for (int i = 0; i < matrix.height; i++)
    {
        for (int j = 0; j < matrix.length; j++)
        {
            if(matrix.grid[i][j]==value) freq++;   
        }
    }
    return freq;
}

void swapRow(Matrix *matrix, int row1, int row2){
    for (int j = 0; j < matrix->length; j++)
    {
        swap(&matrix->grid[row1][j],&matrix->grid[row2][j]);
    }
}

void swapColumn(Matrix *matrix, int col1, int col2){
    for (int i = 0; i < matrix->height; i++)
    {
        swap(&matrix->grid[i][col1],&matrix->grid[i][col2]);
    }
}

void insertRow(Matrix *matrix, int row){
    for (int i = matrix->height; i > row; i--)
    {
        for (int j = 0; j < matrix->length; j++)
        {
            matrix->grid[i][j]=matrix->grid[i-1][j];
        }
    }
    matrix->height++;
    int element;
    for (int j = 0; j < matrix->length; j++)
    {
        printf(">");
        scanf("%d",&element);
        matrix->grid[row][j]=element;
    }
}

void insertColumn(Matrix *matrix, int column){
    for (int j = matrix->length; j > column; j--)
    {
        for (int i = 0; i < matrix->height; i++)
        {
            matrix->grid[i][j]=matrix->grid[i][j-1];
        }
    }
    matrix->length++;
    int element;
    for (int i = 0; i < matrix->height; i++)
    {
        printf(">");
        scanf("%d",&element);
        matrix->grid[i][column]=element;
    }
}

void deleteRow(Matrix *matrix, int row){
    matrix->height--;
    for (int i = row; i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->length; j++)
        {
            matrix->grid[i][j]=matrix->grid[i+1][j];
        }
    }
}

void deleteColumn(Matrix *matrix, int column){
    matrix->length--;
    for (int j = column; j < matrix->length; j++)
    {
        for (int i = 0; i < matrix->height; i++)
        {
            matrix->grid[i][j]=matrix->grid[i][j+1];
        }
    }
}

void applyRow(Matrix *matrix, int row, char operator, int operand){
    for (int j = 0; j < matrix->length; j++)
    {    
        switch (operator)
        {
            case '+':
                matrix->grid[row][j]+=operand;
                break;
            case '-':
                matrix->grid[row][j]-=operand;
                break;
            case '*':
                matrix->grid[row][j]*=operand;
                break;
            case '/':
                matrix->grid[row][j]/=operand;
                break;
            case '%':
                matrix->grid[row][j]%=operand;
                break;
            case '&':
                matrix->grid[row][j]&=operand;
                break;
            case '|':
                matrix->grid[row][j]|=operand;
                break;
            case '^':
                matrix->grid[row][j]^=operand;
                break;
            case '~':
                matrix->grid[row][j]=~matrix->grid[row][j];
                break;
            case '=':
                matrix->grid[row][j]=matrix->grid[row][j]==operand;
                break;
            case '!':
                matrix->grid[row][j]=matrix->grid[row][j]!=operand;
                break;
            case '<':
                matrix->grid[row][j]=matrix->grid[row][j]<operand;
                break;
            case 'S':
                matrix->grid[row][j]=matrix->grid[row][j]<=operand;
                break;
            case '>':
                matrix->grid[row][j]=matrix->grid[row][j]>operand;
                break;
            case 'Z':
                matrix->grid[row][j]=matrix->grid[row][j]>=operand;
                break;
        }
    }
}

void applyColumn(Matrix *matrix, int column, char operator, int operand){
    for (int i = 0;i < matrix->height; i++)
    {    
        switch (operator)
        {
            case '+':
                matrix->grid[i][column]+=operand;
                break;
            case '-':
                matrix->grid[i][column]-=operand;
                break;
            case '*':
                matrix->grid[i][column]*=operand;
                break;
            case '/':
                matrix->grid[i][column]/=operand;
                break;
            case '%':
                matrix->grid[i][column]%=operand;
                break;
            case '&':
                matrix->grid[i][column]&=operand;
                break;
            case '|':
                matrix->grid[i][column]|=operand;
                break;
            case '^':
                matrix->grid[i][column]^=operand;
                break;
            case '~':
                matrix->grid[i][column]=~matrix->grid[i][column];
                break;
            case '=':
                matrix->grid[i][column]=matrix->grid[i][column]==operand;
                break;
            case '!':
                matrix->grid[i][column]=matrix->grid[i][column]!=operand;
                break;
            case '<':
                matrix->grid[i][column]=matrix->grid[i][column]<operand;
                break;
            case 'S':
                matrix->grid[i][column]=matrix->grid[i][column]<=operand;
                break;
            case '>':
                matrix->grid[i][column]=matrix->grid[i][column]>operand;
                break;
            case 'Z':
                matrix->grid[i][column]=matrix->grid[i][column]>=operand;
                break;
        }
    }
}

void map(Matrix *matrix, char operator, int operand){
    for (int i = 0;i < matrix->height; i++)
    {
        for (int j = 0; j < matrix->length; j++)
        {
            switch (operator)
            {
                case '+':
                    matrix->grid[i][j]+=operand;
                    break;
                case '-':
                    matrix->grid[i][j]-=operand;
                    break;
                case '*':
                    matrix->grid[i][j]*=operand;
                    break;
                case '/':
                    matrix->grid[i][j]/=operand;
                    break;
                case '%':
                    matrix->grid[i][j]%=operand;
                    break;
                case '&':
                    matrix->grid[i][j]&=operand;
                    break;
                case '|':
                    matrix->grid[i][j]|=operand;
                    break;
                case '^':
                    matrix->grid[i][j]^=operand;
                    break;
                case '~':
                    matrix->grid[i][j]=~matrix->grid[i][j];
                    break;
                case '=':
                    matrix->grid[i][j]=matrix->grid[i][j]==operand;
                    break;
                case '!':
                    matrix->grid[i][j]=matrix->grid[i][j]!=operand;
                    break;
                case '<':
                    matrix->grid[i][j]=matrix->grid[i][j]<operand;
                    break;
                case 'S':
                    matrix->grid[i][j]=matrix->grid[i][j]<=operand;
                    break;
                case '>':
                    matrix->grid[i][j]=matrix->grid[i][j]>operand;
                    break;
                case 'Z':
                    matrix->grid[i][j]=matrix->grid[i][j]>=operand;
                    break;
            }
        }
    }
}

bool any(Matrix matrix){
    for (int i = 0; i < matrix.height; i++)
    {
        for (int j = 0; j < matrix.length; j++)
        {
            if(matrix.grid[i][j]==1) return true;   
        }
    }
    return false;
}

bool all(Matrix matrix){
    for (int i = 0; i < matrix.height; i++)
    {
        for (int j = 0; j < matrix.length; j++)
        {
            if(matrix.grid[i][j]==0) return false;   
        }
    }
    return true;
}

void rowOnRow(Matrix *matrix, int row1, char operator, int row2){
    for (int j = 0; j < matrix->length; j++)
    {
        switch (operator)
        {
            case '+':
                matrix->grid[row1][j]+=matrix->grid[row2][j];
                break;
            case '-':
                matrix->grid[row1][j]-=matrix->grid[row2][j];
                break;
            case '*':
                matrix->grid[row1][j]*=matrix->grid[row2][j];
                break;
            case '/':
                matrix->grid[row1][j]/=matrix->grid[row2][j];
                break;
            case '%':
                matrix->grid[row1][j]%=matrix->grid[row2][j];
                break;
            case '&':
                matrix->grid[row1][j]&=matrix->grid[row2][j];
                break;
            case '|':
                matrix->grid[row1][j]|=matrix->grid[row2][j];
                break;
            case '^':
                matrix->grid[row1][j]^=matrix->grid[row2][j];
                break;
            case '=':
                matrix->grid[row1][j]=matrix->grid[row1][j]==matrix->grid[row2][j];
                break;
            case '!':
                matrix->grid[row1][j]=matrix->grid[row1][j]!=matrix->grid[row2][j];
                break;
            case '<':
                matrix->grid[row1][j]=matrix->grid[row1][j]<matrix->grid[row2][j];
                break;
            case 'S':
                matrix->grid[row1][j]=matrix->grid[row1][j]<=matrix->grid[row2][j];
                break;
            case '>':
                matrix->grid[row1][j]=matrix->grid[row1][j]>matrix->grid[row2][j];
                break;
            case 'Z':
                matrix->grid[row1][j]=matrix->grid[row1][j]>=matrix->grid[row2][j];
                break;
        }
    }
}

void columnOnColumn(Matrix *matrix, int column1, char operator, int column2){
    for (int i = 0; i < matrix->height; i++)
    {
        switch (operator)
        {
            case '+':
                matrix->grid[i][column1]+=matrix->grid[i][column2];
                break;
            case '-':
                matrix->grid[i][column1]-=matrix->grid[i][column2];
                break;
            case '*':
                matrix->grid[i][column1]*=matrix->grid[i][column2];
                break;
            case '/':
                matrix->grid[i][column1]/=matrix->grid[i][column2];
                break;
            case '%':
                matrix->grid[i][column1]%=matrix->grid[i][column2];
                break;
            case '&':
                matrix->grid[i][column1]&=matrix->grid[i][column2];
                break;
            case '|':
                matrix->grid[i][column1]|=matrix->grid[i][column2];
                break;
            case '^':
                matrix->grid[i][column1]^=matrix->grid[i][column2];
                break;
            case '=':
                matrix->grid[i][column1]=matrix->grid[i][column1]==matrix->grid[i][column2];
                break;
            case '!':
                matrix->grid[i][column1]=matrix->grid[i][column1]!=matrix->grid[i][column2];
                break;
            case '<':
                matrix->grid[i][column1]=matrix->grid[i][column1]<matrix->grid[i][column2];
                break;
            case 'S':
                matrix->grid[i][column1]=matrix->grid[i][column1]<=matrix->grid[i][column2];
                break;
            case '>':
                matrix->grid[i][column1]=matrix->grid[i][column1]>matrix->grid[i][column2];
                break;
            case 'Z':
                matrix->grid[i][column1]=matrix->grid[i][column1]>=matrix->grid[i][column2];
                break;
        }
    }
}

void matrixOnMatrix(Matrix *matrix1, char operator, Matrix matrix2){
    if(operator=='X' && matrix1->length==matrix2.height){
        int result[matrix1->height][matrix2.length];
        for (int i = 0; i < matrix1->height; i++){
            for (int j = 0; j < matrix2.length; j++){
                int sum=0;
                for (int k = 0; k < matrix1->length; k++)
                {
                    sum+=matrix1->grid[i][k]*matrix2.grid[k][j];
                }
                result[i][j]=sum;
            }
        }
        matrix1->length=matrix2.length;
        for (int i = 0; i < matrix1->height; i++){
            for (int j = 0; j < matrix1->length; j++){
                matrix1->grid[i][j]=result[i][j];
            }
        }
    }
    else if(matrix1->height>=matrix2.height && matrix1->length>=matrix2.length){
        for (int i = 0; i < matrix1->height; i++){
            for (int j = 0; j < matrix1->length; j++){
                switch (operator){
                    case '+':
                        matrix1->grid[i][j]+=matrix2.grid[i][j];
                        break;
                    case '-':
                        matrix1->grid[i][j]-=matrix2.grid[i][j];
                        break;
                    case '*':
                        matrix1->grid[i][j]*=matrix2.grid[i][j];
                        break;
                    case '/':
                        matrix1->grid[i][j]/=matrix2.grid[i][j];
                        break;
                    case '%':
                        matrix1->grid[i][j]%=matrix2.grid[i][j];
                        break;
                    case '&':
                        matrix1->grid[i][j]&=matrix2.grid[i][j];
                        break;
                    case '|':
                        matrix1->grid[i][j]|=matrix2.grid[i][j];
                        break;
                    case '^':
                        matrix1->grid[i][j]^=matrix2.grid[i][j];
                        break;
                    case '=':
                        matrix1->grid[i][j]=matrix1->grid[i][j]==matrix2.grid[i][j];
                        break;
                    case '!':
                        matrix1->grid[i][j]=matrix1->grid[i][j]!=matrix2.grid[i][j];
                        break;
                    case '<':
                        matrix1->grid[i][j]=matrix1->grid[i][j]<matrix2.grid[i][j];
                        break;
                    case 'S':
                        matrix1->grid[i][j]=matrix1->grid[i][j]<=matrix2.grid[i][j];
                        break;
                    case '>':
                        matrix1->grid[i][j]=matrix1->grid[i][j]>matrix2.grid[i][j];
                        break;
                    case 'Z':
                        matrix1->grid[i][j]=matrix1->grid[i][j]>=matrix2.grid[i][j];
                        break;
                }
            }
        }
    }
}

int determinant(Matrix matrix){
    if(matrix.height==1 && matrix.length==1) return matrix.grid[0][0];
    else if(isSquare(matrix))
    {
        int det=0;
        for (int j = 0; j < matrix.length; j++)
        {
            Matrix temp=exclude(matrix,0,j);
            det+=(int)pow(-1,j)*matrix.grid[0][j]*determinant(temp);
            delete(&temp);
        }
        return det;
    }
    return -1;
}

void cofactor(Matrix *matrix){
    int result[matrix->height][matrix->length];
    for (int i = 0; i < matrix->height; i++){
        for (int j = 0; j < matrix->length; j++){
            Matrix temp=exclude(*matrix,i,j);
            result[i][j]=(int)pow(-1,i+j)*determinant(temp);
            delete(&temp);
        }
    }
    for (int i = 0; i < matrix->height; i++){
        for (int j = 0; j < matrix->length; j++){
            matrix->grid[i][j]=result[i][j];
        }
    }
}
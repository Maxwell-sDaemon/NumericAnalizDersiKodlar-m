/* deteminant kullanarak kökleri bulma (cramer yöntemi)*/

#include<stdio.h>
#include<stdlib.h>

int getSize()
{
    int size;
    printf("Kare matrisin boyutu nedir?\n");
    scanf("%d",&size);

    return size;
}

double** getMatrix(int size)
{
    double **arr = (double **)malloc(sizeof(double*)*size);
    
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (double*)malloc(size*sizeof(double));   
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            printf("A[%d][%d] : ",i,j);
            scanf("%lf",&arr[i][j]);
        }
    }
    return arr;
}

double *CreateXMatrix(int size)
{
    double *arr= (double*)calloc(size,sizeof(double));   

    for (size_t i = 0; i < size; i++)
    {
        printf("Enter your x %d value : ",i);
        scanf("%lf",&arr[i]);
    }
    return arr;
}

void Display(double **arr,double sizeofArray)
{
    for(size_t i = 0 ; i < sizeofArray ; i++)
    {
        for (size_t j = 0; j < sizeofArray; j++)
        {
            printf("%lf\t",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

double Determinant(double **arr,int size)//recursive determinant bulma 
{
    double sum=0;//determinant değeri
    static int negcount = 1;//determinant toplama işlemi + - + - şeklinde.
    if(size == 2)
    {
        return arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0];
    }
    double **subarr = (double**)malloc(sizeof(double*)*(size-1));
    for (size_t i = 0; i < size-1 ; i++)
    {
        subarr[i] = (double*)malloc(sizeof(double)*(size-1));
    }
    //bunu nasıl kısa yoldan yaparım.
    size_t place = 0;//oluşturulacak matrisde indexleri belirlemede
    for (size_t k = 0; k < size; k++)
    {
        for (size_t i = 0; i < size; i++)
        {
            for (size_t j = 0; j < size; j++)
            {
                if(i != 0 && j != k)//ilk satırdan elemanı alt matrix alamam ve çarpanın bulunduğu elemanı alamam. 
                {
                    subarr[place/(size-1)][place%(size-1)] = arr[i][j];//row major method.
                    place++;
                }
            }
        }
        sum = sum + negcount*arr[0][k] * Determinant(subarr,size-1);
        negcount = -1*negcount;//tailing var stack kullanarak çözülür aman ne gerek var. 

        place = 0;
    }
    free(subarr);
    return -sum;
}
double** deepCopy(double **arr,int size)
{
    double **copy = (double **)malloc(sizeof(double*)*size);
    
    for (size_t i = 0; i < size; i++)
    {
        copy[i] = (double*)malloc(size*sizeof(double));   
    }

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size; j++)
        {
            copy[i][j]=arr[i][j];
        }
    }
    return copy;
}
double *cramerMethod(double **arr,double *yRoot,int size)
{
    double *xRoot = (double*)malloc(sizeof(double)*size);
    double determinant=Determinant(arr,size);
    printf("matris deteminanti : %.2f \n\n",determinant);//matrix deteminantı;

    double **copy;

    for (size_t i = 0; i < size; i++)
    {
        copy = deepCopy(arr,size);
        for (size_t j = 0; j < size; j++)
        {
            copy[j][i] = yRoot[j];
        }
        Display(copy,size);
        xRoot[i]=Determinant(copy,size)/determinant;
    }
    return xRoot;
}

void displayRoot(double *arr,int size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("x%d = %.3f \t",i+1,arr[i]);
    }
}

int main()
{
    int size;
    double **arr,*root ;

    size = getSize();

    arr = getMatrix(size);

    Display(arr,size);

    root=CreateXMatrix(size);

    cramerMethod(arr,root,size);

    displayRoot(root,size);
    
    return 0;
}
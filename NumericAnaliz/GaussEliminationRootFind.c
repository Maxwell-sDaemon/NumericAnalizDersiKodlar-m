/* lineer denklem sistemlerinde kökleri bulacak yöntemlerden ilki gauss yöntemi */

#include<stdio.h>
#include<stdlib.h>

typedef struct Array{
    int rowSize;
    int columnSize;
} size;

double** REF(double **arr,size size);
double* FeedBack(double **arr,double* roots,size size);

void IntroductionOfGaussElimination()
{
    printf("\t\tGAUSS ELIMINASYONU\n1-Gauss eliminasyonu kok bulma yontemlerinden biri olup \nsatirca indirgenmis esolan formlari kullanir. \n\n");
}
size get_size()
{
    size arrsz;
    printf("Hesaplanacak Lineer denklem sisteminin matrix seklinin satir ve sutun(satir+1) sayisini giriniz.\n");
    scanf("%d",&arrsz.rowSize);
    scanf("%d",&arrsz.columnSize);
    
    return arrsz;
}

double** get_matrix(size size)
{
    double **arr = (double **)malloc(sizeof(double*)*size.rowSize);

    for (size_t i = 0; i < size.columnSize; i++)
    {
        arr[i] = (double*)malloc(size.columnSize*sizeof(double));   
    }

    for (size_t i = 0; i < size.rowSize; i++)
    {
        for (size_t j = 0; j < size.columnSize; j++)
        {
            printf("A[%d][%d] : ",i,j);
            if( size.columnSize-1 == j ){
                printf("(sonuc) ");
                scanf("%lf",&arr[i][j]);
            }
            else
            {
                printf("x%d ",j+1);
                scanf("%lf",&arr[i][j]);
            }
        }
    }
    return arr;
}

void Display(double **arr,size size)
{
    for(size_t i = 0 ; i < size.rowSize ; i++)
    {
        for (size_t j = 0; j < size.columnSize ; j++)
        {
            printf("%.3f\t",arr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void displayRoot(double *arr,size size)
{
    for (size_t i = 0; i < size.rowSize; i++)
    {
        printf("x%d = %.3f \t",i+1,arr[i]);
    }
}

double* RootFind(double **arr,size size)
{
    double *roots = (double *)malloc(sizeof(double)*size.rowSize);
    arr=REF(arr,size);
    Display(arr,size);
    roots = FeedBack(arr,roots,size);
    return roots;
}

double* FeedBack(double **arr,double *roots,size size)
{
    double sum=0.0;

    for (int i = size.rowSize-2; i > -1; i--)
    {
        sum = arr[i][size.columnSize-1];//sonuç kısmını bir köşeye aldım sonradan kendinden öncekileri çıkaracağım.
        for (int j = size.columnSize-2; j > i ; j--)//kendinden öncekileri çıkardım sonuç şimdi kökün değerine eşitlendi.
        {
            sum -= arr[i][j]*arr[j][size.columnSize-1];
        }
        arr[i][size.columnSize-1] = sum;//sonucu kök değerini gösteren kısma atadım. 
        Display(arr,size);
        sum = 0.0;
    }
    for(size_t i = 0; i < size.rowSize ; i++)//kökleri verecek matrise asıl matrisimdekileri atadım.
    {
        roots[i] = arr[i][size.columnSize-1];
    }
    return roots;
}

//Reduced row echolon form asıl gauss eliminasyou matrix tersi ya da kök bulma için .
double** REF(double **arr,size size)
{
    double diagonalTemp,temp;
    for (size_t i = 0; i < size.rowSize; i++)//çaprazda dolaşan eleman.
    {
        diagonalTemp = arr[i][i];//izin ilk elemanı 
        for (size_t j = i; j < size.columnSize; j++)//tüm sütun izin elemanlarına bölünür.caprazın solundaki eleman çünkü sağı 0 olacak.
        {//neden i koyunca çalışmıyor?çünkü unitte tüm değerler dolu row echelon method için i konulabilir.
            arr[i][j]/=diagonalTemp;
        }
        for (size_t j = i+1; j < size.rowSize; j++)////diagonalın altında kalan indexler
        {
            temp = arr[j][i];//çapraz altında kalan index i hangi çapraz olduğunu j altında olduğunu belirtir.
            for (size_t k = 0; k < size.columnSize; k++)//çıkarma işlemi için sütün üzerinde yürür.
            {
                arr[j][k]-=arr[i][k]*temp;
            }
        }
    }
    return arr;
}

int main()
{
    size size;
    double **arr,**Unit ;// get_matrix(arr) ; nasıl arr i allocate ederken silinmesi önlenir &arr *** pointer mı?ya da struct adres
    double *x;

    IntroductionOfGaussElimination();

    size = get_size();

    arr = get_matrix(size);
    
    Display(arr,size);

    x = RootFind(arr,size);
    

    displayRoot(x,size);
    
    return 0;
}
/*matrisin tersini alma ya da diğer adıyla gauss jordan yöntemi*/

#include<stdio.h>
#include<stdlib.h>

double** REF(double **arr,double **unit,int lenght);

void IntroductionOfGaussJordanMethod()
{
    printf("\t\tGAUSS-JORDAN ELIMINASYONU\n1-Gauss-Jordan Eliminasyonu matrix tersini alan yontemdir.\n2-Tek hamlede tarayarak isini bitirir.\n\n");
}

int get_size()
{
    int size;
    printf("Kare matrisin boyutu nedir?\n");
    scanf("%d",&size);

    return size;
}

double** get_matrix(int size)
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
double **CreateUnitMatrix(int size)
{
    double **arr = (double **)malloc(sizeof(double*)*size);
    
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = (double*)calloc(size,sizeof(double));   
    }

    for (size_t i = 0; i < size; i++)
    {
        arr[i][i] = 1;
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

//Reduced row echolon form asıl gauss-jordan eliminasyou matrix tersi için .
double** REF(double **arr,double **unit,int lenght)
{
    double diagonalTemp,temp;
    for (size_t i = 0; i < lenght; i++)//çaprazda dolaşan eleman.
    {
        diagonalTemp = arr[i][i];//izin ilk elemanı 
        for (size_t j = 0; j < lenght; j++)//tüm sütun izin elemanlarına bölünür.caprazın solundaki eleman çünkü sağı 0 olacak.
        {//neden i koyunca çalışmıyor?çünkü unitte tüm değerler dolu row echelon method için i konulabilir.
            arr[i][j]/=diagonalTemp;
            unit[i][j]/=diagonalTemp;
        }
        for (size_t j = i+1; j < lenght; j++)////diagonalın altında kalan indexler
        {
            temp = arr[j][i];//çapraz altında kalan index i hangi çapraz olduğunu j altında olduğunu belirtir.
            for (size_t k = 0; k < lenght; k++)//çıkarma işlemi için sütün üzerinde yürür.
            {
                arr[j][k]-=arr[i][k]*temp;
                unit[j][k]-=unit[i][k]*temp;
            }
        }
    }
    return arr;
}

//Reduced Row echolon form diye de varsayılabilir.
double** InverseMatrix(double **arr,double **unit,int lenght)
{
    double diagonalTemp,temp;
    for (size_t i = 0; i < lenght; i++)//çaprazda dolaşan eleman.
    {
        diagonalTemp = arr[i][i];//izin ilk elemanı 
        for (size_t j = 0; j < lenght; j++)//tüm sütun izin elemanlarına bölünür.caprazın solundaki eleman çünkü sağı 0 olacak.
        {//neden i koyunca çalışmıyor?çünkü unitte tüm değerler dolu row echelon method için i konulabilir.
            arr[i][j]/=diagonalTemp;
            unit[i][j]/=diagonalTemp;
        }
        for (size_t j = i+1; j < lenght; j++)////diagonalın altında kalan indexler
        {
            temp = arr[j][i];//çapraz altında kalan index i hangi çapraz olduğunu j altında olduğunu belirtir.
            for (size_t k = 0; k < lenght; k++)//çıkarma işlemi için sütün üzerinde yürür.
            {
                arr[j][k]-=arr[i][k]*temp;
                unit[j][k]-=unit[i][k]*temp;
            }
        }
        for (size_t j = 0; j < i; j++)//çapraz üstünde kalan index
        {
            temp = arr[j][i];
            for (size_t k = 0; k < lenght; k++)//stride
            {   
                arr[j][k]-=arr[i][k]*temp;
                unit[j][k]-=unit[i][k]*temp;
            }
        }
    }
    return arr;
}

int main()
{
    int size;
    double **arr,**Unit ;// get_matrix(arr) ; nasıl arr i allocate ederken silinmesi önlenir &arr *** pointer mı?yada struct adres

    IntroductionOfGaussJordanMethod();

    size = get_size();

    arr = get_matrix(size);

    Display(arr,size);

    Unit=CreateUnitMatrix(size);

    Display(Unit,size);

    InverseMatrix(arr,Unit,size);

    Display(arr,size);

    Display(Unit,size);
    
    return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void RegressionIntro()
{
    printf("\t\t:Regression:\n");
    printf("Iki veri grubu arasindaki iliskiyi saptamak ,\n");
    printf("ve ilerde olusacak verileri tahmin etmek için kullanilir..\n\n");
    printf("\t1-En Kucuk Kareler Lineer Yaklasim Metodu(Linear Least Squares Method)\n");
    printf("\t2-En Kucuk Kareler Polinom Yaklasim Metodu(Quadratic Least Squares Method\n");
    printf("\t3-Coklu Regresyon(Multiple Regression)\n");
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

int getSize()
{
    int numberOfX;
    printf("x,y cifti sayisi : ");
    scanf("%d",&numberOfX);
    return numberOfX;
}

double* Input(int numberOfX)
{
    double temp = 0;
    double* XYDouble = (double*)malloc(sizeof(double)*numberOfX);
    for (size_t i = 0; i < 2*numberOfX; i+=2)
    {
        printf("x(%d)",i/2);
        scanf("%lf",&XYDouble[i]);
        printf("y(%d)",i/2);
        scanf("%lf",&XYDouble[i+1]);
    }
    return XYDouble;
}

double** ConfigurateMatrix(double **configuratable, int size)
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
            arr[i][j]=configuratable[i][j];    
        }
    }
    return arr;
}

double *ConfigurateYPart(double**configuratable, int size)
{
    double *arr= (double*)calloc(size,sizeof(double));   

    for (size_t i = 0; i < size; i++)
    {
        arr[i]=configuratable[i][2];
    }
    return arr;
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
    return sum;
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

double LinearRegression(double *arr,int size,double value)
{
    double sumOfX=0,sumOfY=0,temp=1,sumOfXY=0,sumOfXSquare=0;
    double *root;

    double** RegrMatrix = (double **)malloc(sizeof(double*) * 2);

    for (size_t i = 0; i < 3; i++)
    {
        RegrMatrix[i]=(double *)malloc(sizeof(double) * 3);
    }
    RegrMatrix[0][0] = size;
    for (size_t i = 0; i < 2*size; i++)
    {
        if(i%2==0)
        {
            sumOfX+=arr[i];
            sumOfXSquare += arr[i]*arr[i];
            temp*=arr[i];
        }
        else
        {
            temp*=arr[i];
            sumOfXY+=temp;
            temp=1;
            sumOfY+=arr[i];
        }
    }
    RegrMatrix[0][1]=sumOfX;
    RegrMatrix[1][0]=sumOfX;
    RegrMatrix[1][1]=sumOfXSquare;
    RegrMatrix[0][2]=sumOfY;
    RegrMatrix[1][2]=sumOfXY;
    
    root = cramerMethod(ConfigurateMatrix(RegrMatrix,2),ConfigurateYPart(RegrMatrix,2),2);

    printf("%.2fx + %.2f",root[0],root[1]);

    return root[0]*value + root[1];
}

void EquationFormat(double* root,int degree)
{
    int i = 0;
    while(i<degree)
    {
        printf("%.2fx^%d +",root[i],degree-i);
        i++;
    }
}

double PolynomialRegression(double *arr,int size,int degree,double value)
{
    double* Xies = (double*)calloc(2*degree-2,sizeof(double));
    double* XYies = (double*)calloc(degree,sizeof(double));

    double** RegrMatrix = (double **)malloc(sizeof(double*)*degree );

    for (size_t i = 0; i < degree ; i++)
    {
        RegrMatrix[i]=(double *)malloc(sizeof(double) * degree);
    }

    RegrMatrix[0][0] = size;
    for (size_t i = 0; i < 2*size; i+=2)
    {
        for (size_t j = 0; j < 2*degree-2; j++)
        {
            Xies[j]+=pow(arr[i],j+1);
            XYies[j] += arr[i+1]*pow(arr[i],j+1);
        }
    }
    for (size_t i = 0; i < degree; i++)
    {
        for (size_t j = 0; j < degree; j++)
        {
            RegrMatrix[i][j] = Xies[i+j-1];
        }
    }
    double *root = cramerMethod(RegrMatrix,XYies,degree);

    EquationFormat(root,degree);

    return root[0]*value + root[1];
}

int main()
{   
    int size;
    double value,sum;
    RegressionIntro();
    size=getSize();
    double* input=Input(size);
    printf("\tBulmak istediginiz deger nedir?  ");
    scanf("%lf",&value);
    PolynomialRegression(input,size,3,value);
    
    return 0;
}
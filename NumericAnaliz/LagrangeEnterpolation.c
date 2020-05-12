#include<stdio.h>
#include<stdlib.h>

void InterPolationIntro()
{
    printf("\t\t:Interpolasyon:\n");
    printf("Bir veri grubunda eksik verileri ,\n");
    printf("veri grubundaki diger veriler yardimiyla elde etmeye denir.\n\n");
    printf("\t1-Dogrusal Yaklasim Metodu(Lineer Interpolation Method)\n");
    printf("\t2-Egrisel Yaklasim Metodu(Quadratic Interpolation Method\n");
    printf("\t3-Kubik Yaklasim Metodu(Cubic Interpolation Method)\n");
    printf("\t4-Lagrange Yaklasim Metodu (Lagrange Method)\n\n");
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

double LineerInterPolationFindDot(double x0,double y0,double x1,double y1,double x)
{
    return (y1-y0)/(x1-x0)*(x-x0)+y0; 
}

void LineerInterPolationFindEquation(double x0,double y0,double x1,double y1)
{
    double m = (y1-y0) / (x1 - x0) , n = (x1*y0 - x0*y1) / x1 - x0;
    printf("%.2fx + %.2f \n", m, n);
}

void QuadraticInterPolationFindEquation(double x0,double y0,double x1,double y1,double x2,double y2,double x)
{
    printf("eğrisel interpolasyon eğrisi \n");
    printf("b0 + b1*(x-x0) + b2*(x-x0)*(x-x1) \n");
    double b0 = y0 ,b1 = (y1 - y0)/x1-x0, b2 = ((y2 - y1) / ( x2-x1 ) - (y1 - y0)/ x1- x0) / (x2-x0) ;
    printf("%.2f + %.2f*(x-%2f) + %.2f*(x-%.2f)*(x-%.2f)",b0,b1,x0,b2,x0,x1);
}

double LagrangeInterPolationFindDot(double *arr,int size,double value)
{
    double sum=0;
    double temp=1;

    for (size_t i = 0; i < 2*size; i+=2)
    {
        for (size_t j = 0; j < 2*size; j+=2)
        {
            if(j==i)
            {
                temp *= arr[i+1];
                continue;
            }
            temp *= (value-arr[j]);
            temp /= (arr[i]-arr[j]);
        }
        sum+=temp;
        temp=1;
    }
    return sum;
}

int main()
{
    int size;
    double value,sum;
    InterPolationIntro();
    size=getSize();
    double* input=Input(size);
    printf("\tBulmak istediginiz deger nedir?  ");
    scanf("%lf",&value);
    sum=LagrangeInterPolationFindDot(input,size,value);
    printf("f(%.2f)=%.2f",value,sum);

    return 0;
}
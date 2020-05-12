#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Term
{
    double coeff;
    double power; 
};

struct Poly
{
    int size;
    struct Term *term; 
}*poly;

struct Poly* createPoly()
{
    struct Poly *p = (struct Poly*)malloc(sizeof(struct Poly));
    double val;
    printf("polinomun operand sayisini giriniz.");
    scanf("%d",&p->size);
    
    p->term = (struct Term*)malloc(sizeof(struct Term)*p->size);

    for (size_t i = 0; i < p->size; i++)
    {
        printf("%d . operand katsayisiniz : ",i+1);
        scanf("%lf",&val);
        p->term[i].coeff = val;

        printf("%d . operand ussunuz : ", i+1);

        scanf("%lf",&val);
        p->term[i].power = val;
    }

    return p;
} 

double Eval(double start)
{
    double sum = 0;
    for (size_t i = 0; i < poly->size; i++)
    {
        sum += poly->term[i].coeff*pow(start,poly->term[i].power);
    }
    return sum;
}

double TrapezIntegrate(struct Poly *p, double start, double end, int iter)
{
    double sum= 0,temp;
    double iterCountStep = (end-start) / iter;

    while ( start < end )
    {
        temp = Eval(start);
        start = start + iterCountStep;
        sum += (iterCountStep/2)*(temp + Eval(start));
    }

    return sum;
}

int isEven(int iter)
{
    if(iter % 2 == 0)
        return 1;
    else
        return 0;
}
double SimpsonIntegrate(struct Poly *p, double start, double end, int iter)
{
    double sum = Eval(start)+Eval(end);
    double iterCountStep = (end - start)/iter,i=1; 
    if(isEven(iter))
    {
        while(start < end-iterCountStep )
        {
            start = start+iterCountStep;
            if(isEven(i))
            {
                sum+=2*Eval(start);
                i++;
            }
            else
            {
                sum+=4*Eval(start);
                i++;
            }
        }
        return (sum/3)*iterCountStep;
    }
    printf("\n iterasyon sayisi çift sayi olmalı.(error code -1)");
    return -1;
}

int main(char argv[5],int argc)
{//argc argumant count 

    poly = createPoly();
    
    printf("%.2f \n",TrapezIntegrate(poly,0,5,1000));
    printf("%.2f",SimpsonIntegrate(poly,0,5,1000));
    
    return 0;
}
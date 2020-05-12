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
    struct Poly *poly = (struct Poly*)malloc(sizeof(struct Poly));

    printf("polinomun operand sayisini giriniz.");
    scanf("%d",&poly->size);
    
    poly->term = (struct Term*)malloc(sizeof(struct Term)*poly->size);

    for (size_t i = 0; i < poly->size; i++)
    {
        printf("%d . operand katsayisiniz : ",i+1);
        scanf("%lf",&poly->term[i].coeff);

        printf("%d . operand ussunuz : ", i+1);
        scanf("%lf",&poly->term[i].power);
    }

    return poly;
} 

double Evaluate(double value)
{
    double sum = 0;
    for (size_t i = 0; i < poly->size; i++)
    {
        sum += poly->term[i].coeff*pow(value,poly->term[i].power);
    }
    return sum;
}
//sensitivity = val / ep
double ForwardDerivate(double val,double ep)
{
    double h = val / ep;
    return (Evaluate(val + h) - Evaluate(val))/h;
}

//sensitivity = val / ep <-- ep hassalık belirteci belki ep alıp ep^2 bölünebilir.
double BackwardDerivate(double val,double ep)
{
    double h = val / ep;
    return (Evaluate(val) - Evaluate(val-h))/h;
}

//ep 1-1000 
double CenteredDerivate(double val,double ep)
{
    double h = val / ep;
    return (Evaluate(val+h) - Evaluate(val-h))/(2*h);
}

double TayloredDerivate(double val,double h)
{
    return (1/(2*h))*(-3*Evaluate(val)+4*Evaluate(val+h)-Evaluate(val+2*h));
}
int main(char argv[5],int argc)
{//argc argumant count 

    poly = createPoly();
    
    printf("%.2f",BackwardDerivate(5,100));
    
    return 0;
}
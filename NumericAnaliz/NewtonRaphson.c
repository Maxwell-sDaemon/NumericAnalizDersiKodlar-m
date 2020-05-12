#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Term
{
    int coeff;
    int pow;
};
struct Poly
{
    int size;
    struct Term *term;
};
void IntroductionOfNewtonRaphsonMethod()
{
    printf("\t\tNEWTON-RAPHSON METODU \n1-Acik Yontemdir.\n2-Yanlis nokta yontemine benzer iki noktaya gore egimdense,\ntek nokta uzerinden sonuca varır.\n");
}
//call by adress p1>>poly
void Create(struct Poly *poly)
{
    printf("polinom operand sayisi : ");
    scanf("%d",&poly->size);
    
    poly->term=(struct Term*)malloc(sizeof(struct Term)*poly->size);

    //inserting elements
    for (size_t i = 0; i < poly->size; i++)
    {
        printf("polinomun katsayisi ve ustunu yazin : ");
        scanf("%d %d",&poly->term[i].coeff,&poly->term[i].pow);
    }
}

void Display(struct Poly poly)
{
    for (size_t i = 0; i < poly.size; i++)
    {
        printf("%dx^%d +",poly.term[i].coeff, poly.term[i].pow);
    }
    printf("\n");
}

//f(val) result
double Eval(struct Poly poly,double val)
{
    double sum = 0.f;
    for (size_t i = 0; i < poly.size; i++)
    {
        sum+=poly.term[i].coeff * pow(val,poly.term[i].pow);
    }
    return sum;
}

void GetInput(double *x0,double *e)
{
    printf("Newton-Raphson yonteminde x in baslatici degeri : ");
    scanf("%lf",x0);

    printf("hata payi(e) : ");
    scanf("%lf",e);
    printf("\n");
}
//ileri fark türev alma.
double Deriv(struct Poly p,double x0, double err)
{
    return (Eval(p,x0+err)-Eval(p,x0))/err; 
}

double NewtonRaphson(struct Poly p,double x0, double err)
{
    double cur_x = x0;
    double fcur_x = Eval(p,cur_x);
    double last_x = x0-fcur_x/Deriv(p,cur_x,err);
    while (last_x-cur_x > err)
    {
        cur_x = last_x;
        fcur_x=Eval(p,cur_x);
        last_x = x0-fcur_x/Deriv(p,cur_x,err);
    }
    return cur_x;
}

int main()
{
    struct Poly p1;

    IntroductionOfNewtonRaphsonMethod();
    Create(&p1);
    Display(p1);

    double x0,e,root;

    GetInput(&x0,&e);

    double sum=NewtonRaphson(p1,x0,e);
    printf("%f",sum);

    return 0;
}
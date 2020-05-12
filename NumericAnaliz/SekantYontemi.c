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

void IntroductionSekantMethod()
{
    printf("\t\tSEKANT METHOD\n1-Kapalı yöntemdir.\n2-Yer degistirme yonteminin gelistirilmis versiyonudur.\n3-Benzer ucgenleri(kucuk-buyuk) kullanir.\n");
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
        printf("%dx^%d +",poly.term[i].coeff,poly.term[i].pow);
    }
    printf("\n");
}

//f(val) result
double Eval(struct Poly poly,double val)
{
    double sum = 0.f;
    for (size_t i = 0; i < poly.size; i++)
    {
        sum+=poly.term[i].coeff* pow(val,poly.term[i].pow);
    }
    return sum;
}

void GetInput(double *a,double *b,double *e)
{
    printf("kokun bulunudugu araliginin daraltilacak ilk degeri : ");
    scanf("%lf",a);

    printf("kokun bulundugu araligin daraltilacak son degeri : ");
    scanf("%lf",b);

    printf("hata payi(e) : ");
    scanf("%lf",e);
    printf("\n");
}

double CalculateRoot(struct Poly poly,double a,double b,double err)
{
    double y0=Eval(poly,a),y1=Eval(poly,b),y2,x0=a,x1=b,x2,E=100;
    double c;
    // yanlış aralık verilmesi durumu iraksama
    if(y0*y1 >0)
    {
        printf("verdiginiz aralikta kok bulunmamaktadir.");
    }
    else
    {
        while (E>err)
        {
            x2=x0-((x1-x0)/(y1-y0))*(y0);
            y2=Eval(poly,x2);
            if (y2 * y1 >0 )
            {
                E=abs(x2-x1);
                x1=x2;
                y1=y2;
                c=x1;
            }
            else
            {
                E=abs(x2-x0);
                x0=x2;
                y0=y2;
                c=x0;
            }
        }
        return c;  
    }
}

int main()
{
    struct Poly p1;
    Create(&p1);
    Display(p1);

    double x0,df,e,root;

    GetInput(&x0,&df,&e);
    
    printf("%f",CalculateRoot(p1,x0,df,e));

    return 0;
}
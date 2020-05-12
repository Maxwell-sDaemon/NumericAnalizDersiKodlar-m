/* İkiye Bölme bisection yöntemine alternatif olarak sunulmuş köke yakın olan nokta ile ortalama hesaplanırken 
diğer taraf kısaltılıyor yani boşuna işlem */
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

void IntroductionOfRegulaFalseMethod()
{
    printf("\t\tYER DEGISTIRME YONTEMI\n1-Kapali Yontemdir.\n2-Verilen noktalarin degerlerini kullanma fikrinden cikmistir\n3-Benzer ucgenler prensibi ile egimleri kulllanilir.\n4-Fazla hizlidir.\n");
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
    double fa=Eval(poly,a),fb=Eval(poly,b),fc;
    double c;
    // yanlış aralık verilmesi durumu iraksama
    if(fa*fb >0)
    {
        printf("verdiginiz aralikta kok bulunmamaktadir.");
    }
    else
    {
        do
        {
            c=(b*fa -a*fb)/(fa-fb);
            fc = Eval(poly,c);
            a=c;
            fa=fc;
        }while (fc > err);

        return c;  
    }
}

int main()
{
    struct Poly p1;
    IntroductionOfRegulaFalseMethod();
    Create(&p1);
    Display(p1);

    double x0,df,e,root;

    GetInput(&x0,&df,&e);
    
    printf("%lf",CalculateRoot(p1,x0,df,e));

    return 0;
}
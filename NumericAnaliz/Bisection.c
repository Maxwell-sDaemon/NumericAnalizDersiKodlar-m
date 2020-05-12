/* ortalama değer ile kök bukunur. gerekenler iki başlatıcı değer ve onların ortalaması */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Poly
{
    int i;
    double arr[10][2];
}*poly;


void IntroductionOfBisectionMethod()
{
    printf("\t\tORTA NOKTA METODU\n1-Bu metot kapalı yöntemlerdendir.\n2-Zit degerli iki deger arasinda kok bulunur prensibine dayanir.\n");
}

void InsertPoly(struct Poly *p,double coeff,double pow)
{
    p->arr[poly->i][0] = coeff;
    p->arr[poly->i++][1] = pow; 
}

double Eval(struct Poly *p,double x)
{
    double sum = 0;
    for(int j = 0; j < p->i ; j++)
    {
        sum+=p->arr[j][0]*pow(x,p->arr[j][1]);
    }
    return sum;
}

double FindRoot(double a ,double b,double  err)
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
            // -x +y / 2 = 0 durumu için 
            if (fa*fb==0)
            {
                printf("a ya da b koktur.");
                if(fa==0)return a;
                if(fb==0)return b;
            }
            //daraltma işlemi.
            else
            {
                c=(a+b)/2;
                fc = Eval(poly,c);
                if (fa*fc<0)
                {
                    b=c;
                    fb=Eval(poly,b);
                }
                else
                {
                    a=c;
                    fa=Eval(poly,a);
                }
            }
        }while (fa-fb > err);
        printf("Kokunuz : %lf",c);
        return c;
    }
}
void Display(struct Poly *p)
{
    for (int i = 0; i < p->i; i++)
    {
        printf("%.2f x^%.2f +",p->arr[i][0],p->arr[i][1]);
    }
    printf("\n");
}

int main()
{
    double a,b,epsilon;
    double coeff,pow;
    int size;
    //creating poly
    
    poly=(struct Poly*)malloc(sizeof(struct Poly));
    poly->i = 0;

    printf("gireceginiz polinomun boyutunu giriniz. : ");
    scanf("%d",&size);

    for (int i = 0; i < size; i++)
    {
        printf("%d. katsayi ve %d.kok : ",i+1,i+1);
        scanf("%lf",&coeff);
        scanf("%lf",&pow);
        InsertPoly(poly,coeff,pow);
    }
    Display(poly);
    //İnitial values
    printf("koku icine alan iki nokta yaziniz. : ");
    scanf("%lf",&a);
    scanf("%lf",&b);
    printf("epsilon : ");
    scanf("%lf",&epsilon);
    FindRoot(a,b,epsilon);
    
    return 0;
}
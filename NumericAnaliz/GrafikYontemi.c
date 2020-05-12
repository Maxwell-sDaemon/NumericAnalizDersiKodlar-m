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

void IntroductionOfGraphMethod(){
    printf("\t\tGRAFİK METODU \n1-Kapali yontemlerden ilkidir .\n2-isaret degisene kadar ve kok bulunana kadar \nbelli degisim miktari ile toplama islemine dayanir.\n  ");
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
double Evaluate(struct Poly poly,double val)
{
    double sum = 0.f;
    for (size_t i = 0; i < poly.size; i++)
    {
        sum+=poly.term[i].coeff * pow(val,poly.term[i].pow);
    }
    return sum;
}

void GetInput(double *x0,double *dx,double *e)
{
    printf("grafik yonteminde x in baslatici degeri : ");
    scanf("%lf",x0);

    printf("grafik yonteminde baslatici artis ya da azalis miktari : ");
    scanf("%lf",dx);

    printf("hata payi(e) : ");
    scanf("%lf",e);
    printf("\n");
}

double CalculateRoot(struct Poly poly,double x,double delta,double err)
{
    int flag,flak;//flag x'in işareti +1(flag=1)  x<0(flag=0)
    double temp;//flak temp in işareti
    if(Evaluate(poly,x)<0){flag=0;flak=0;}
    else{flag=1;flak=1;}
    while(delta>err)
    {
        if(flak != flag)
        {
            delta = delta/2;
            flag = flak;
            x=temp;
        }
        temp = x;
        x= x + delta;
        if(Evaluate(poly,x)<0){flag=0;}
        else{flag=1;}
    }
    return x;
}

void RcalculateRoot(struct Poly poly,double x,double delta,double err)
{
    //init ilk değer pozitif ? negatif 
    static int init=0,flag,flak;
    static double temp;
    if(init==0)
    {
        if(Evaluate(poly,x)<0){flag = 0;flak=0;}
        else{flag=1;flak=1;}
        init = 1;
    }
    if(flag != flak)
    {
        if(delta <= err)
        {
            printf("Koklerden biri %lf",x);
            return;
        }
        delta = delta / 2;
        flag = flak;
        RcalculateRoot(poly,temp,delta,err);
    }
    else
    {
        temp=x;
        x=x+delta;
        if (Evaluate(poly,x)<0){flag=0;}else{flag=1;}
        RcalculateRoot(poly,x,delta,err);
    }
}

int main()
{
    struct Poly p1;
    IntroductionOfGraphMethod();

    Create(&p1);
    Display(p1);

    double x0,df,e,root;

    GetInput(&x0,&df,&e);
    
    RcalculateRoot(p1,x0,df,e);
    printf("\nkok : %lf",CalculateRoot(p1,x0,df,e));
    
    return 0;
}
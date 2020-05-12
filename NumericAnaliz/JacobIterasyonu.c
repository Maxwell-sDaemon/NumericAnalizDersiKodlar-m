/* verilen polinomu x li bileşenlere bölüp iki bölünmüş parçanın türevleri karşılaştırılır
eğer -1-1 arasında ise recursive işlem gerçekleştirilir.  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct 
{
    int data;
    struct linkedlist *next;
}llist;

struct Term
{
    double coeff;
    double pow;
};

struct Poly
{
    int size;
    int root;//root state
    struct Term *term;
}*poly;

struct Set
{
    int i;
    struct Poly **poly;
};

void IntroductionOfJacobiIterationMethod()
{
    printf("Gelecekteki ben sana meydan okuyorum.Bunu calistirirsan helal sana nokta\n");
}

void Create(struct Poly *poly)//poly->size
{   
    printf("polinom operand sayisi : ");
    scanf("%d",&poly->size);

    poly->root = 1;
    
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
double Eval(struct Poly *poly,double val)
{
    double sum = 0.f;
    if(poly->root==1)
    {
        for (size_t i = 0; i < poly->size; i++)
        {
            sum+=poly->term[i].coeff * pow(val,poly->term[i].pow);
        }
        return sum;
    }
    else
    {
        for (size_t i = 0; i < poly->size; i++)
        {
            sum+=pow(poly->term[i].coeff * pow(val,poly->term[i].pow),poly->root);
        }
        return sum;
    }   
}


void GetInput(double *x0,double *e)
{
    printf("grafik yonteminde x in baslatici degeri : ");
    scanf("%lf",x0);

    printf("hata payi(e) : ");
    scanf("%lf",e);
    printf("\n");
}

struct Poly *DeepCopy(struct Poly *p)
{
    struct Poly *cp = (struct Poly*)malloc(sizeof(struct Poly)*p->size);
    cp->root=p->root;

    for (size_t i = 0; i < poly->size; i++)
    {
        cp->term[i].pow = p->term[i].pow;
        cp->term[i].coeff=p->term[i].coeff;
    }
    return cp;
}

struct Set *Poly_xies(struct Poly *p)
{
    int divisor,i=0;
    struct Set *polyies = (struct Set*)malloc(sizeof(struct Set)*p->size);

    polyies->i=0;
    //create new poly search pow and find 1 remove it and divide its coeff all coeff. 
    struct Poly *cp = DeepCopy(p); 

    for (i = 0; i < p->size; i++)
    {
        if(p->term[i].pow != 0)
        {
            cp = DeepCopy(p); 
            cp->root = cp->term[i].pow;
            divisor= -cp->term[i].coeff;
            cp->term[i].coeff=cp->term[i].pow=0;
            for (size_t i = 0; i < p->size; i++)
            {
                cp->term[i].coeff/divisor;
            }
        }
        polyies->poly[polyies->i++]= cp;
    }
    return polyies;
}

int IsFit(struct Poly *p,double x0, double err)
{
    return (Eval(p,x0+err)-Eval(p,x0))/err < 1; 
}

llist *JacobiIteration(struct Set *p,double x0,double err)
{
    double itemp =x0 ;
    double hx;
    llist *arr ;
    
    for (size_t i = 0; i < p->i; i++)
    {
        if(IsFit(p->poly[i],x0,err))
        {
            arr = (llist*)malloc(sizeof(llist));
            while (x0-Eval(p->poly[i],x0) > err)
            {
                x0=Eval(p->poly[i],x0);
            }
            arr->data=x0;
            x0=itemp;
        }
    }
    arr->next=NULL;
    return arr;
}

int main()
{
    struct Poly p1;

    IntroductionOfJacobiIterationMethod();
    Create(&p1);
    Display(p1);

    double x0,e,root;

    GetInput(&x0,&e);
    
    struct Set *p = Poly_xies(poly);

    JacobiIteration(p,x0,e);

    return 0;
}
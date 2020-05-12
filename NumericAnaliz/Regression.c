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
double getValue()
{
    double value;
    printf("\tBulmak istediginiz deger nedir?  ");
    scanf("%lf",&value);
    return value;
}
int getSize()
{
    int numberOfX;
    printf("x,y cifti sayisi : ");
    scanf("%d",&numberOfX);
    return numberOfX;
}
int getDegree()
{
    int degree;
    printf("Kacinci dereceden bir fonksiyon uydurmak istersin ? : ");
    scanf("%d",&degree);
    return degree+1;
}
double* Input(int numberOfX)
{
    //heapte yer allocate eder runtime dizi olusturmak için.
    double* XYdouble = (double*)malloc(2*sizeof(double)*numberOfX);
    for (size_t i = 0; i < 2*numberOfX; i+=2)//(x,y) çifti için n*2lik row major matrix olusturur.
    {
        printf("x(%d)",i/2);
        scanf("%lf",&XYdouble[i]);//dizinin her 2n . elemanına x.
        printf("y(%d)",i/2);
        scanf("%lf",&XYdouble[i+1]);//dizinin her 2n+1 . elemanına y.
    }
    return XYdouble;
}

double Determinant(double **arr,int size)//recursive determinant bulma 
{
    double sum=0;//determinant değeri
    static int negcount = 1;//determinant toplama işlemi + - + - şeklinde.
    //temel durum.
    if(size == 2)
    {
        return arr[0][0]*arr[1][1]-arr[0][1]*arr[1][0];
    }
    double **subarr = (double**)malloc(sizeof(double*)*(size-1));
    for (size_t i = 0; i < size-1 ; i++)
    {
        subarr[i] = (double*)malloc(sizeof(double)*(size-1));
    }
    
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
    //İşlem yaparken her iterasyonda kendi içindeki dizi kendi determınantını buldu.
    free(subarr);//ama alt matrixler heapde kalır direk döndürürsek.
    return -sum;//birde burda bir hata vardı + - kısmı ters oldu.
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
    Display(arr,size);
    double determinant=Determinant(arr,size);
    printf("matris deteminanti : %.2f \n\n",determinant);

    double **copy;//her işlemde A.B=C için A = /\ ise /\ dan /\A ve /\B oluştururken /\ kaybetmemek için. 
    //A matrisini her adımda kopyalamalıyız.
    for (size_t i = 0; i < size; i++)
    {
        copy = deepCopy(arr,size);
        for (size_t j = 0; j < size; j++)
        {
            copy[j][i] = yRoot[j];//(A.B = C) olusan kopyanın sütununun yerini C alır.
        }
        Display(copy,size);
        printf("determinant : %lf\n",Determinant(copy,size));// ve /\A,B,C deteminantı hesaplar.
        xRoot[i]=Determinant(copy,size)/determinant;//ve /\ böler kökleri dizide tutar.
    }
    return xRoot;//B cepte artık.
}


void EquationFormat(double* root,int degree)
{
    int i = 0;
    for(int i =0 ; i<degree; i++)
    {
        printf("%.2fx^%d +",root[i],i);
    }
}

double CalculateWithRoots(double *root,double value,int degree)
{
    double sum;
    for (size_t i = 0; i < degree; i++)
    {
        sum += root[i] * pow(value,i);
    }
    return sum;
}

double PolynomialRegression(double *arr,int size,int degree,double value)
{
    //sigma x,x^2,x^3.. lerin ve y, x*y^2.. ların bulunacagı diziler olursur.
    //165.satır neden 2*degree-2
    double* Xies = (double*)calloc(2*degree-2,sizeof(double));//calloc başlatıcı degerleri
    double* XYies = (double*)calloc(degree,sizeof(double));//0 dan başlatır.

    //155-160. satır arası heapde matrix allocate etmedir.
    double** RegrMatrix = (double **)malloc(sizeof(double*)*degree );

    for (size_t i = 0; i < degree ; i++)
    {
        RegrMatrix[i]=(double *)malloc(sizeof(double) * degree);
    }

    for (size_t i = 0; i < 2*size; i+=2)//2 şer artırmak demek arr[i] x imizi verecek demek.
    {
        //3.dereceden bir eğri arıyorsak,3 için sigma x^4 e kadarki sıralı x toplamı gerekli.
        //3.dereceden 2*3-2=4 sigma x^4 , 2.dereceden 2*2-2=2 sigma x^2 
        for (size_t j = 0; j < 2*degree-2; j++)
        {
            Xies[j]+=pow(arr[i],j+1);//A nın X lerini tutanı olusturur.
            if(j < degree){
                XYies[j] += arr[i+1]*pow(arr[i],j);//A.B = C deki C olusturur.
            }
        }
    }
    for (size_t i = 0; i < degree; i++)
    {
        for (size_t j = 0; j < degree; j++)
        {
            RegrMatrix[i][j] = Xies[i+j-1];//A.B = C deki A olusturur..
        }
    }   
    RegrMatrix[0][0] = size;

    double *root = cramerMethod(RegrMatrix,XYies,degree);//kokleri bulup kökler dizisine atar.

    EquationFormat(root,degree);//oluşan eşitliği gösterir.

    return CalculateWithRoots(root,value,degree);//bu kısım yanlıştı düzelttim.
}

int main()
{   
    int size,degree;
    double value,sum;
    RegressionIntro();//giriş babında regresyonun ne oldugunu anlattıgım yer.
    size=getSize();
    double* input=Input(size);//nasıl bir input almalıyım.row-major dizi olusturdum. 
    value = getValue();
    degree = getDegree();

    printf("\n%lf",PolynomialRegression(input,size,degree,value));//3.parametre icin kaçıncı
    //dereceden olduğu tahmini olarak girilir.lineer için 2 , quadratic 2,3,4.. gibi.
    
    return 0;
}

// double** ConfigurateMatrix(double **configuratable, int size)
// {
//     double **arr = (double **)malloc(sizeof(double*)*size);
    
//     for (size_t i = 0; i < size; i++)
//     {
//         arr[i] = (double*)malloc(size*sizeof(double));   
//     }

//     for (size_t i = 0; i < size; i++)
//     {
//         for (size_t j = 0; j < size; j++)
//         {
//             arr[i][j]=configuratable[i][j];    
//         }
//     }
//     return arr;
// }

// double *ConfigurateYPart(double**configuratable, int size)
// {
//     double *arr= (double*)calloc(size,sizeof(double));   

//     for (size_t i = 0; i < size; i++)
//     {
//         arr[i]=configuratable[i][2];
//     }
//     return arr;
// }
// double LinearRegression(double *arr,int size,double value)
// {
//     double sumOfX=0,sumOfY=0,temp=1,sumOfXY=0,sumOfXSquare=0;
//     double *root;

//     double** RegrMatrix = (double **)malloc(sizeof(double*) * 2);

//     for (size_t i = 0; i < 3; i++)
//     {
//         RegrMatrix[i]=(double *)malloc(sizeof(double) * 3);
//     }
//     RegrMatrix[0][0] = size;
//     for (size_t i = 0; i < 2*size; i++)
//     {
//         if(i%2==0)
//         {
//             sumOfX+=arr[i];
//             sumOfXSquare += arr[i]*arr[i];
//             temp*=arr[i];
//         }
//         else
//         {
//             temp*=arr[i];
//             sumOfXY+=temp;
//             temp=1;
//             sumOfY+=arr[i];
//         }
//     }
//     RegrMatrix[0][1]=sumOfX;
//     RegrMatrix[1][0]=sumOfX;
//     RegrMatrix[1][1]=sumOfXSquare;
//     RegrMatrix[0][2]=sumOfY;
//     RegrMatrix[1][2]=sumOfXY;
    
//     root = cramerMethod(ConfigurateMatrix(RegrMatrix,2),ConfigurateYPart(RegrMatrix,2),2);

//     printf("%.2fx + %.2f",root[0],root[1]);

//     return root[0]*value + root[1];
// }
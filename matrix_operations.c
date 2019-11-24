#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define RESULT "result.txt"

typedef struct  {
    int rows,cols;
} matrixSize;

// czytanie rozmiaru macierzy z pliku
matrixSize get_size_of_matrix(char filename[])
{
    matrixSize m;
    int i,j;
    FILE * fp;
    fp = fopen (filename, "r");
    char *record,*line;
    char buffer[1024] ;
    i=0;
    if(fp)
    {
        while((line=fgets(buffer,sizeof(buffer),fp))!=NULL)
   {
     j=0;
     record = strtok(line,";");
     while(record != NULL)
     {
     ++j;
     record = strtok(NULL,";");
     }
     ++i ;
    }
    }
    else{ printf("\nPodano bledna nazwe pliku lub plik nie istnieje !!!\n");}

    m.rows=i;
    m.cols=j;
    return m;
}

// wczytanie wartosci macierzy z pliku
double **get_matrix_values(int rows,int cols,char filename[])
{
   char buffer[1024] ;
   char *record,*line;
   int i=0,j;
   int k;
   double **mat;
   mat = (double**)malloc(rows * sizeof(double*));

    for(k = 0; k < rows; k++)

    {

        *(mat + k) = (double *)malloc(cols * sizeof(double));

    }
   FILE *fstream = fopen(filename,"r");
   if(fstream == NULL)
   {

   }
   while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
   {
     j=0;
     record = strtok(line,";");
     while(record != NULL)
     {
     *(*(mat + i) + j++) = atof(record);
     record = strtok(NULL,";");
     }
     ++i ;
   }

   return mat;

}

// generowanie losowej macierzy o podanym rozmiarze z zadanego przedzialu
double **generate_matrix(int rows,int cols,double min,double max)
{
    double **mat;
    int i,j;
    mat = (double**)malloc(rows * sizeof(double*));

    for(i = 0; i < rows; i++)

    {

        *(mat + i) = (double *)malloc(cols * sizeof(double));

    }

    for(i = 0; i < rows;i++) {
    	for(j = 0; j < cols;j++) {

    		*(*(mat + i) + j)=min + (rand() /(RAND_MAX / (max - min)));
    	}
    }
    return mat;
}

// dodawanie macierzy
void addMatrixes(int rows,int cols, double **mat1, double **mat2)
{
 int i, j,z;
 FILE *file;


    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {

            printf("%.2lf; ", *(*(mat1 + i) + j)+*(*(mat2 + i) + j));
        }

        printf("\n");
    }

      printf("\nCzy chcesz zapisac wynik do pliku?\n");
      printf("1- TAK\n");
      printf("2- NIE\n");
      scanf("%d",&z);
      switch(z){
          case 1: {
              file=fopen(RESULT,"w");
              for (i = 0; i < rows; i++)
              {
                   for (j = 0; j < cols; j++)
                   {

                        fprintf(file,"%.2lf; ", *(*(mat1 + i) + j)+*(*(mat2 + i) + j));
                    }

                  fprintf(file,"\n");
               }

              fclose(file);
              printf("\nWynik zostal zapisany w pliku result.txt.\n");
              break;
          }
          case 2:{break;}
      }
}

// wyswietlanie wartosci macierzy
void printMatrix(double **mat,int rows,int cols)
{
    for(int i = 0; i < rows;i++) {
    	for(int j = 0; j < cols;j++) {

    	 printf("%.2lf; ", *(*(mat + i) + j));
    	}
    	printf("\n");
    }
}

// odejmowanie macierzy
void subMatrixes(int rows,int cols, double **mat1, double **mat2)
{
 int i, j,z;
 FILE *file;


    for (i = 0; i < rows; i++)
    {
        for (j = 0; j < cols; j++)
        {

            printf("%.2lf; ", *(*(mat1 + i) + j)-*(*(mat2 + i) + j));
        }

        printf("\n");
    }
     printf("\nCzy chcesz zapisac wynik do pliku?\n");
      printf("1- TAK\n");
      printf("2- NIE\n");
      scanf("%d",&z);
      switch(z){
          case 1: {
              file=fopen(RESULT,"w");
              for (i = 0; i < rows; i++)
              {
                   for (j = 0; j < cols; j++)
                   {

                        fprintf(file,"%.2lf; ", *(*(mat1 + i) + j)-*(*(mat2 + i) + j));
                    }

                  fprintf(file,"\n");
               }

              fclose(file);
              printf("\nWynik zostal zapisany w pliku result.txt.\n");
              break;
          }
          case 2:{break;}
      }
}

// mnozenie macierzy
void multiplyMatrixes(int rows1,int rows2,int cols1,int cols2, double **mat1, double **mat2)
{

 FILE *file;
 int i, j,k,l,z;
 double **resMat;

 resMat = (double**)malloc(rows1 * sizeof(double*));

    for(l = 0; l < rows1; l++)

    {

        *(resMat + l) = (double *)malloc(cols2 * sizeof(double));

    }


    for (i = 0; i < rows1; i++)
    {
        for (j = 0; j < cols2; j++)
        {
            *(*(resMat + i) + j) = 0;

            for (k = 0; k < cols2; k++)

            {

            *(*(resMat + i) + j) += *(*(mat1 + i) + k) * *(*(mat2 + k) + j);
            }
        }
    }

    printMatrix(resMat,rows1,cols2);

    printf("\nCzy chcesz zapisac wynik do pliku?\n");
      printf("1- TAK\n");
      printf("2- NIE\n");
      scanf("%d",&z);
      switch(z){
          case 1: {
              file=fopen(RESULT,"w");
              for (i = 0; i < rows1; i++)
              {
                   for (j = 0; j < cols2; j++)
                   {

                        fprintf(file,"%.2lf; ", *(*(resMat + i) + j));
                    }

                  fprintf(file,"\n");
               }

              fclose(file);
              printf("\nWynik zostal zapisany w pliku result.txt.\n");
              break;
          }
          case 2:{break;}
      }
}

// wyznacznik macierzy
double matDet(double **mat,int rows,int cols)
{

       double s = 1, det = 0;
       double **arr;
       int l;
       arr= (double**)malloc(rows * sizeof(double*));

    for(l = 0; l < rows; l++)

    {

        *(arr + l) = (double *)malloc(cols * sizeof(double));

    }

       int i, j, m, n, c;
       if(rows==1)
       {
           return (*(*(mat + 0) + 0));
       }

       else
       {
           det = 0;

		for (c = 0; c < rows; c++)

		{

			m = 0;

			n = 0;

			for (i = 0;i < rows; i++)

			{

				for (j = 0 ;j < rows; j++)

				{
				    *(*(arr + i) + j) = 0;
				    if (i != 0 && j != c)

					{

						*(*(arr + m) + n) = *(*(mat + i) + j);

						if (n < (rows - 2))

						{

							n++;

						}

						else

						{

							n = 0;

							m++;

						}
					}
									}
			}

				det = det + s * (*(*(mat + 0) + c) * matDet(arr, rows - 1,cols-1));

				s = -1 * s;

		}
       }
       return (det);

}

// odwracanie macierzy
void matInversion(double **mat,int rows,int cols)
{
  if(rows==cols)
  {
     int l,z;
     FILE *file;
    double **arr, **cofac, **inverse;
    arr= (double**)malloc(rows * sizeof(double*));

    for(l = 0; l < rows; l++)

    {

        *(arr + l) = (double *)malloc(cols * sizeof(double));

    }


    cofac= (double**)malloc(rows * sizeof(double*));

    for(l = 0; l < rows; l++)

    {

        *(cofac + l) = (double *)malloc(cols * sizeof(double));

    }

    inverse= (double**)malloc(rows * sizeof(double*));

    for(l = 0; l < rows; l++)

    {

        *(inverse + l) = (double *)malloc(cols * sizeof(double));

    }

    double det=matDet(mat,rows,cols);
    if(det==0)
    {
        printf("Wyznacznik macierzy jest rowny 0, macierz odwrotna nie istnieje.\n\n");
    }
    else{
    int p, q, m, n, i, j;

    for (q = 0;q < rows; q++)

	{

		for (p = 0;p < rows; p++)

		{

			m = 0;

			n = 0;

			for (i = 0;i < rows; i++)

			{

				for (j = 0;j < rows; j++)

				{

					if (i != q && j != p)

					{

						*(*(arr + m) + n) = *(*(mat + i) + j);

						if (n < (rows - 2))

						{

						n++;

						}

						else

						{

							n = 0;

							m++;

						}

					}

				}

			}

			*(*(cofac + q) + p) = pow(-1, q + p) * matDet(arr, rows-1,cols-1);

		}

	}

	for (i = 0;i < rows; i++)

	{

		for (j = 0;j < rows; j++)

		{

			*(*(arr + i) + j) = *(*(cofac + j) + i);

        }

    }

    for (i = 0;i < rows; i++)

    {

		for (j = 0;j < rows; j++)

		{

			*(*(inverse + i) + j) = *(*(arr + i) + j) / det;

        }

    }

    printMatrix(inverse,rows,cols);

      printf("\nCzy chcesz zapisac wynik do pliku?\n");
      printf("1- TAK\n");
      printf("2- NIE\n");
      scanf("%d",&z);
      switch(z){
          case 1: {
              file=fopen(RESULT,"w");
              for (i = 0; i < rows; i++)
              {
                   for (j = 0; j < cols; j++)
                   {

                        fprintf(file,"%.2lf; ", *(*(inverse + i) + j));
                    }

                  fprintf(file,"\n");
               }

              fclose(file);
              printf("\nWynik zostal zapisany w pliku result.txt.\n");
              break;
          }
          case 2:{break;}
      }
  }
  }
  else{printf("\nMacierz nie jest kwadratowa. Nie mozna policzyc wyznacznika, ani odwrocic.\n\n");}

}



int main()
{

int x,y,w;
char filename1[100];
char filename2[100];
matrixSize ms1,ms2;
int rows1, rows2, cols1, cols2;
double min,max;
double **mat1,**mat2;

printf("\n***Kalkulator macierzowy***\n");
printf("\nWybierz jedna z opcji.\n");
printf("1-Bede wczytywac macierze z pliku csv, w ktorym warosci oddzielone sa srednikiem.\n");
printf("2-Chce wygenerowac macierze losowo.\n");
scanf("%d",&x);
if(x==1){

printf("Menu:\n");
printf("1- Dodawanie macierzy\n");
printf("2- Odejmowanie macierzy\n");
printf("3- Mnozenie macierzy\n");
printf("4- Odwracanie macierzy\n");
scanf("%d",&y);
switch(y)
{
  case 1:{
      printf("Podaj nazwe pliku z pierwsza macierza:\n");
      scanf("%s",&filename1);
      printf("Podaj nazwe pliku z druga macierza:\n");
      scanf("%s",&filename2);

      ms1=get_size_of_matrix(filename1);
      ms2=get_size_of_matrix(filename2);
      if(ms1.cols==ms2.cols && ms1.rows==ms2.rows)
      {
      printf("\nWynik dodawania macierzy to:\n\n");
      addMatrixes(ms1.rows,ms1.cols,get_matrix_values(ms1.rows,ms1.cols,filename1),get_matrix_values(ms2.rows,ms2.cols,filename2));

      }
      else{printf("Nie mozna dodac macierzy ze wzgledu na rozne wymiary.\n");}

      break;
  }

  case 2:{
      printf("Podaj nazwe pliku z pierwsza macierza:\n");
      scanf("%s",&filename1);
      printf("Podaj nazwe pliku z druga macierza:\n");
      scanf("%s",&filename2);

      ms1=get_size_of_matrix(filename1);
      ms2=get_size_of_matrix(filename2);
      if(ms1.cols==ms2.cols && ms1.rows==ms2.rows)
      {
      printf("\nWynik odejmowania macierzy to:\n\n");
      subMatrixes(ms1.rows,ms1.cols,get_matrix_values(ms1.rows,ms1.cols,filename1),get_matrix_values(ms2.rows,ms2.cols,filename2));
      }
      else{printf("Nie mozna odjac macierzy ze wzgledu na rozne wymiary.\n");}
      break;
  }

  case 3:{
      printf("Podaj nazwe pliku z pierwsza macierza:\n");
      scanf("%s",&filename1);
      printf("Podaj nazwe pliku z druga macierza:\n");
      scanf("%s",&filename2);

      ms1=get_size_of_matrix(filename1);
      ms2=get_size_of_matrix(filename2);
      if(ms1.cols==ms2.rows)
      {
      printf("\nWynik mnozenia macierzy to:\n\n");
      multiplyMatrixes(ms1.rows,ms2.rows,ms1.cols,ms2.cols,get_matrix_values(ms1.rows,ms1.cols,filename1),get_matrix_values(ms2.rows,ms2.cols,filename2));
      }
      else{printf("Nie mozna pomnozyc macierzy ze wzgledu na bledne wymiary.\n");}
      break;

  }

  case 4: {
      printf("Podaj nazwe pliku z macierza:\n");
      scanf("%s",&filename1);

      ms1=get_size_of_matrix(filename1);
      printf("\n");
      printf("\nMacierz odwrotna to:\n\n");
      matInversion(get_matrix_values(ms1.rows,ms1.cols,filename1),ms1.rows,ms1.cols);
      break;
  }

}

}

if(x==2){
printf("Menu:\n");
printf("1- Dodawanie macierzy\n");
printf("2- Odejmowanie macierzy\n");
printf("3- Mnozenie macierzy\n");
printf("4- Odwracanie macierzy\n");
scanf("%d",&y);
switch(y)
{
    case 1:{
        printf("Podaj wymiary macierzy (np. 3x3)\n");
        scanf("%dx%d",&rows1,&cols1);
        printf("Podaj wartosc minimalna macierzy:\n");
        scanf("%lf",&min);
        printf("Podaj wartosc maksymalna:\n");
        scanf("%lf",&max);
        mat1=generate_matrix(rows1,cols1,min,max);
        mat2=generate_matrix(rows1,cols1,min,max);
        printf("Macierz 1:\n");
        printMatrix(mat1,rows1,cols1);
        printf("Macierz 2:\n");
        printMatrix(mat2,rows1,cols1);
        printf("\nWynik dodawania macierzy to:\n\n");
        addMatrixes(rows1,cols1,mat1,mat2);
        break;
    }
    case 2:{
        printf("Podaj wymiary macierzy (np. 3x3)\n");
        scanf("%dx%d",&rows1,&cols1);
        printf("Podaj wartosc minimalna macierzy:\n");
        scanf("%lf",&min);
        printf("Podaj wartosc maksymalna:\n");
        scanf("%lf",&max);
        mat1=generate_matrix(rows1,cols1,min,max);
        mat2=generate_matrix(rows1,cols1,min,max);
        printf("Macierz 1:\n");
        printMatrix(mat1,rows1,cols1);
        printf("Macierz 2:\n");
        printMatrix(mat2,rows1,cols1);
        printf("\nWynik odejmowania macierzy to:\n\n");
        subMatrixes(rows1,cols1,mat1,mat2);
        break;
    }

    case 3:{
        printf("Podaj wymiary macierzy 1 (np. 3x3)\n");
        scanf("%dx%d",&rows1,&cols1);
        printf("Podaj wymiary macierzy 2 (np. 3x3)\n");
        scanf("%dx%d",&rows2,&cols2);
        printf("Podaj wartosc minimalna macierzy:\n");
        scanf("%lf",&min);
        printf("Podaj wartosc maksymalna:\n");
        scanf("%lf",&max);
        mat1=generate_matrix(rows1,cols1,min,max);
        mat2=generate_matrix(rows2,cols2,min,max);
        printf("\n\nMacierz 1:\n");
        printMatrix(mat1,rows1,cols1);
        printf("\n\nMacierz 2:\n");
        printMatrix(mat2,rows1,cols1);
        printf("\nWynik mnozenia macierzy to:\n\n");
        multiplyMatrixes(rows1,rows2,cols1,cols2,mat1,mat2);
        break;
    }

    case 4:{
        printf("Podaj wymiary macierzy (np. 3x3)\n");
        scanf("%dx%d",&rows1,&cols1);
        printf("Podaj wartosc minimalna macierzy:\n");
        scanf("%lf",&min);
        printf("Podaj wartosc maksymalna:\n");
        scanf("%lf",&max);
        mat1=generate_matrix(rows1,cols1,min,max);
        printf("\n\nMacierz:\n");
        printMatrix(mat1,rows1,cols1);
        printf("\nMacierz odwrotna to:\n\n");
        matInversion(mat1,rows1,cols1);
        break;
    }
}
}

    return 0;

}














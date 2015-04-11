//Por Rodrigo Peralta   L 152 1226    K1026  rodrigo-peralta@hotmail.com.ar 	(lang: C)

#include <stdio.h>

using namespace std;

void init ();
int pascuas (int year);
int pascuas_butcher(int year);
int pascuas_mmdd (int mes, int dia);

//FUNCION in/out -> Confirmada y calcula la fecha correctamente
int pascuas (int year) //uso year por que la codificacion del programa este no debe ser Unicode o compatible, la ñ no la toma en cuenta, y queda mejor que escribir ANO....
{
    int returnint;
    
    int a = year % 19; //resto de la division año / 19
    int b = year % 4; //resto de la division año / 4
    int c = year % 7; //resto de la division año / 7
    
    
    int M, n;
    if(year >= 1583 && year <= 1699)
         M = 22, n = 2;
    else if(year >= 1700 && year <= 1799)
         M = 23, n = 3;
    else if(year >= 1800 && year <= 1899)
         M = 23, n = 4;
    else if(year >= 1900 && year <= 2099)
         M = 24, n = 5;
    else if(year >= 2100 && year <= 2199)
         M = 24, n = 6;
    else if(year >= 2200 && year <= 2299)
         M = 24, n = 0;     
    
    int d = (19 * a + M) % 30; //resto de la division
    int e = (2 * b + 4 * c + 6 * d + n) % 7; //resto de la division
    
    int diadepascuas;
    
    if(d + e < 10)
    {
         diadepascuas = (d + e + 22);
         printf("\nLa pascua en el año %d calculado por gauss sera el %d de marzo (INT: %04d).\n", year, diadepascuas, pascuas_mmdd (3, diadepascuas) );
    }
    else if(d + e > 9)
    {
         if((d + e - 9) == 26)
         {
               diadepascuas = 19;
         }
         else if((d + e - 9) == 25 && d == 28 && e == 6 && a > 10)
         {
              diadepascuas = 18;
         }
         else diadepascuas = (d + e - 9);
         
         printf("\nLa pascua del año %d calculado por gauss sera el %d de abril (INT: %04d).\n", year, diadepascuas, pascuas_mmdd (04, diadepascuas) );
    }
    
    return 1;
}


/*
COMPARACION CON EL ALGORITMO DE BUTCHER según 
http://es.wikipedia.org/wiki/Computus
https://www.drupal.org/node/1180480

Butcher utiliza otra forma mas compleja de calcularlo para que sea valido para cualquier año a partir del 1583

LA FUNCION CON EL ALGORITMO DE BUTCHER SERIA:*/
           
int pascuas_butcher (int year) // -> Sin embargo, la fecha calculada en este metodo es incorrecta, y todavia no entiendo por que.
{
    int a = year % 19;
    int b = year / 100;
    int c = year % 100;
    int d = b / 4;
    int e = b % 4;
    int f = (b + 8) / 25;
    int g = (b - f + 1) / 3;
    int h = (19*a + b - d - g + 15) % 30;
    int i = c / 4;
    int k = c % 4;
    int l = (32 + 2*e + 2*i - h - k) % 7;
    int m = (a + 11*h + 22*l) / 451;
    int p = (h + l - 7 * m + 114) % 31;
    
    
    int mesdepascuas = (h + l - 7 * m + 114) / 31;
    int diadepascuas = p + 1;
    
    printf("\nEl dia de pascuas para el año %d calculado por butcher es el %d/%d \n\n", year, diadepascuas, mesdepascuas);
    
    init();
    return 1;
}

int pascuas_mmdd (int mes, int dia) 
{
    //No hay manera --que yo sepa-- de retornar un entero con un cero a la izquierda, ya que un entero es representado por 405, no 0405
    //El cero a la izquierda se agrega en un string, particularmente se puede hacer con el %04d (ya que el mes siempre sera 1 caracter, y el dia como maximo 2), 
	//o simplemente agregar un 0 y despues hacer %d (0%d)...
    
    int procesado = mes*100+dia;
    return procesado;
}

void init()
{
    int inputyear;
    
    printf ("Escribi el año que queres ver la fecha de pascuas [1583+]:"); //no se me ocurrio como agregar un "sanity check", si el usuario mete un non int se rompe todo.
    if(scanf("%d", &inputyear) != 1)
    {
		init();
		return;
	}
	
    if(inputyear < 1583)
    {
		init();
        return;
    }
    
    if(inputyear <= 2299)
    {
        pascuas(inputyear);
        pascuas_butcher(inputyear);
	}
	else
        pascuas_butcher(inputyear);
    
    return;
}

int main()
{
    printf("PASCUAS (o dia del chocolate para aquellos que no la festejan)\n\n");
    init();
    return 0;
}





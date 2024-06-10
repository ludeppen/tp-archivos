#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "pila.h"

#define archivoDeEnteros "enteros.bin"
typedef struct {
     int legajo;
     char nombreYapellido [30];
     int edad;
     int anio;
}Alumno;
////////////////////////////////PROTOTIPADOS////////////////////////////////
int cargarInt(int archivoInt[], int dim);
void mostrarArchivoInt(int validos, int archivoInt[]);
void CargarArchivoDeAlumnos(char archivo[], int dim);
void agregarAlFinal(char archivo[]);
void pasarLegajoApila(char archivo[], Pila *pila);
int cantDeMayores(char archivo[],int dato);
void mostrarPorRangoDeEdad(char archivo[],int edad1, int edad2);
void mostrarMayorDeEdad(char archivo[]);
void mostrarPorAnio(char archivo[], int anio);
void pasarAlumnoAarchivo(char archivo[], Alumno A[],int validos);
int cantDeRegistros(char archivo[]);
int filtrarPorAnio(char archivo[], int anio, Alumno A[], int dim);
int cargaArregloStruct (Alumno A[], int dimension);
void mostrarPos(char archivo[],int pos);
void modificarArchivo(char archivo[], int posAmodificar);
void invertirArchivo(char archivo[]);
////////////////////////////////PROTOTIPADOS////////////////////////////////

int main()
{
  char archivo[] = {"archivo.dat"};
  Alumno alumno[10];
  int archivoInt[10];
  int validosInt;
  Pila pila;inicpila(&pila);
  char control = 's';
  while(control == 's')
  {
      int ejercicio;
      system("cls");
      printf("1. Agregar elemento al final del archivo, mostrarlo y ver cant de registros.\n");
      printf("2. Cargar alumnos.\n");
      printf("3. Mostrar alumnos.\n");
      printf("4. Agregar alumno.\n");
      printf("5. Pasar a una pila los legajos de mayores de edad.\n");
      printf("6. Ver total de alumnos mayores a una edad.\n");
      printf("7. Mostrar alumnos por rango de edad.\n");
      printf("8. Ver alumno mayor de edad.\n");
      printf("9. ver total de alumnos por anio.\n");
      printf("10. Agregar alumno y filtrar por anio.\n");
      printf("11. Ver cantidad de registros.\n");
      printf("12. Mostrar por pos.\n");
      printf("13. modificar archivo.\n");
      printf("14. Invertir archivo.\n");
      fflush(stdin);
      scanf("%d", &ejercicio);
      switch(ejercicio)
      {
      case 1:
           system("cls");
           cargarInt(archivoInt,10);
           validosInt = cantDeInts(archivoInt);
           printf("La cantidad de numeros ingresados es: %d.\n",validosInt);
           mostrarInt(validosInt,archivoInt);
           break;
      case 2:
           system("cls");
           CargarArchivoDeAlumnos(archivo,5);
           break;
      case 3:
           system("cls");
           mostrarArchivoDeAlumnos(archivo);
           break;
      case 4:
           system("cls");
           agregarAlFinal(archivo);
           break;
      case 5:
           system("cls");
           pasarLegajoApila(archivo,&pila);
           printf("Los legajos de los alumnos mayores de edad son:\n");
           mostrar(&pila);
           break;
      case 6:
           system("cls");
           int dato;
           printf("Ingrese una edad:\n");
           scanf("%d",&dato);
           int total = cantDeMayores(archivo,dato);
           printf("El total de alumnos mayores a esa edad es: %d",total);
           break;
      case 7:
           system("cls");
           int edad1,edad2;
           printf("Ingrese las edades:\n");
           printf("Mayores a:\n");
           scanf("%d",&edad1);
           printf("menores a:\n");
           scanf("%d",&edad2);
           mostrarPorRangoDeEdad(archivo,edad1,edad2);
           break;
      case 8:
           system("cls");
           mostrarMayorDeEdad(archivo);
           break;
      case 9:
           system("cls");
           int anio;
           printf("Ingrese el anio:\n");
           scanf("%d", &anio);
           mostrarPorAnio(archivo,anio);
           break;
      case 10:
           system("cls");
           int validos = 0;
           validos = cargaArregloStruct(alumno,10);
           int filtrarAnio;
           printf("Ingrese el anio:\n");
           scanf("%d",&filtrarAnio);
           filtrarPorAnio(archivo,filtrarAnio,alumno,10);
           break;
      case 11:
           system("cls");
           int totalAlumnos = cantDeRegistros(archivo);
           printf("El total de alumnos en el archivo es: %d.\n",totalAlumnos);
           break;
      case 12:
           system("cls");
           int pos;
           printf("Ingrese la posicion:\n");
           scanf("%d",&pos);
           mostrarPos(archivo,pos);
           break;
      case 13:
           system("cls");
           int posAmodificar;
           printf("ingrese en que posicion se encuentra en alumno que quiere modificar:\n");
           scanf("%d",&posAmodificar);
           modificarArchivo(archivo,posAmodificar);
           break;
      case 14:
           system("cls");
           invertirArchivo(archivo);
           system("cls");
           mostrarArchivoDeAlumnos(archivo);

      }
      printf("\nDesea ver otro ejercicio? s / n.\n");
      fflush(stdin);
      scanf("%c",&control);
  }
return 0;
}
////////////////////////////////FUNCIONES////////////////////////////////
///N1
int cargarInt(int archivoInt[], int dim)
{
    int i = 0;
    FILE *buffer = fopen("archivoInt", "ab");
    char control = 's';
    if(buffer)
    {
        while(control == 's' && i < dim)
       {
        printf("Ingrese un numero:\n");
        scanf("%d",&archivoInt[i]);
        fwrite(&archivoInt[i],sizeof(int),1,buffer);

        printf("Desea cargar otro numero? s / n.\n");
        fflush(stdin);
        scanf("%c", &control);
        i++;
       }
      fclose(buffer);
    }
    else
    {
      printf("No se pudo abrir el archivo.\n");
    }
return i;
}
void mostrarInt(int validos, int archivoInt[])
{
    int A, i = 1;
    FILE *buffer = fopen("archivoInt","rb");
    if(buffer)
    {
      printf("El contenido del archivo es:\n");
      while(fread(&A,sizeof(int),1,buffer) != 0)
      {
        printf("Elemento %d: %d\n",i,A);
        i++;
      }
     fclose(buffer);
    }
    else
    {
      printf("No se pudo abrir el archivo.\n");
    }
}
int cantDeInts(int archivoInt[])
{
    int cont = 0;
    FILE *buffer = fopen("archivoInt","rb");
    if(buffer != NULL)
    {
      while(fread(&archivoInt,sizeof(int),1,buffer) != 0)
      {
          cont++;
      }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abri.\n");
    }
return cont;
}
///N2
Alumno agregarUnAlumno()
{
    Alumno alumno;
    printf("Ingrese el nombre y apellido del alumno:\n");
    fflush(stdin);
    gets(alumno.nombreYapellido);

    printf("Ingrese la edad del alumno:\n");
    scanf("%d",&alumno.edad);

    printf("Ingrese el anio que cursa el alumno (1 o 2):\n");
    scanf("%d",&alumno.anio);

    printf("Ingrese el legajo del alumno:\n");
    scanf("%d",&alumno.legajo);
return alumno;
}
void CargarArchivoDeAlumnos(char archivo[], int dim)
{
    Alumno A;
    int i = 0;
    FILE *buffer = fopen(archivo,"ab");
    if(buffer != NULL)
    {
      char control = 's';
      while(control == 's' && i < dim)
      {
         A = agregarUnAlumno();
         fwrite(&A,sizeof(Alumno),1,buffer);

         printf("Desea agregar otro alumno? s / n.\n");
         fflush(stdin);
         scanf("%c",&control);
         i++;
      }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }
}
///N3
void mostrarUnAlumno(Alumno alumno)
{
    puts("--------------------------------");
    printf("Legajo: %d\n",alumno.legajo);
    printf("Nombre: %s\n",alumno.nombreYapellido);
    printf("Edad: %d\n",alumno.edad);
    printf("Anio: %d\n", alumno.anio);
    puts("--------------------------------");

}
void mostrarArchivoDeAlumnos(char archivo[])
{
    Alumno alumno;
    FILE *buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
      while(fread(&alumno,sizeof(alumno),1,buffer) > 0)
      {
          mostrarUnAlumno(alumno);
      }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }
}
///N4
void agregarAlFinal(char archivo[])
{
  Alumno A;
  A = agregarUnAlumno();
  FILE *buffer = fopen(archivo,"ab");
  if(buffer != NULL)
  {
      fwrite(&A,sizeof(Alumno),1,buffer);
      fclose(buffer);
      printf("Alumno agregado exitosamente.\n");
  }
  else
  {
      printf("No se pudo abrir.\n");
  }
}
///N5
void pasarLegajoApila(char archivo[], Pila *pila)
{
   Alumno A;
   FILE *buffer = fopen(archivo,"rb");
   if(buffer != NULL)
   {
       while(fread(&A,sizeof(Alumno),1,buffer) != 0)
       {
           if(A.edad >= 18)
           {
               apilar(pila,A.legajo);
           }
       }
       fclose(buffer);
   }
   else
   {
       printf("No se pudo abrir.\n");
   }
}
///N6
int cantDeMayores(char archivo[],int dato)
{
    Alumno A;
    int cont = 0;
    FILE *buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        while(fread(&A,sizeof(Alumno),1,buffer) != 0)
        {
          if(A.edad >= dato)
          {
            cont++;
          }
        }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }
return cont;
}
///N7
void mostrarPorRangoDeEdad(char archivo[],int edad1, int edad2)
{
    Alumno A;
    FILE *buffer= fopen(archivo, "rb");
    if(buffer != NULL)
    {
        while(fread(&A,sizeof(Alumno),1,buffer) != 0)
        {
            if(A.edad > edad1 && A.edad < edad2)
            {
                mostrarUnAlumno(A);
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }
}
///N8
void mostrarMayorDeEdad(char archivo[])
{
    Alumno A;
    Alumno mayor;
    FILE *buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        while(fread(&A,sizeof(Alumno),1,buffer) != 0)
        {
            if(mayor.edad < A.edad)
            {
                mayor = A;
            }
        }
        mostrarUnAlumno(mayor);
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }
}
///N9
void mostrarPorAnio(char archivo[], int anio)
{
    Alumno A;
    FILE *buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        while(fread(&A,sizeof(Alumno),1,buffer) != 0)
        {
            if(A.anio == anio)
            {
                mostrarUnAlumno(A);
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }

}
///N10
int cargaArregloStruct (Alumno A[], int dimension)
{
    int i=0;
    char control = 's';
    while(i<dimension && control=='s')
    {
        printf("\nIngrese legajo: ");
        fflush(stdin);
        scanf("%d", &A[i].legajo);
        printf("\nIngrese nombre apellido: ");
        fflush(stdin);
        gets(A[i].nombreYapellido);
        printf("\nIngrese edad: ");
        fflush(stdin);
        scanf("%d",&A[i].edad);
        i++;
        printf("\nDesea agregar otro registro\n? ");
        fflush(stdin);
        scanf("%c", &control);
    }
    return i;
}
void pasarAlumnoAarchivo(char archivo[], Alumno A[],int validos)
{
    FILE *buffer = fopen(archivo,"ab");
    if(buffer != NULL)
    {
        A = fwrite(A,sizeof(Alumno),validos,buffer);
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }
}
int filtrarPorAnio(char archivo[], int anio, Alumno A[], int dim)
{
    Alumno temp;
    int i;
    FILE *buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        while((fread(&temp,sizeof(Alumno),1,buffer) > 0) && (i < dim))
        {
            if(temp.anio == anio)
            {
                A[i] = temp;
                i++;
            }
        }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abri.\n");
    }
return i;
}
///N11
int cantDeRegistros(char archivo[])
{
    int cantDatos, cant;
    FILE *buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        fseek(buffer,0,SEEK_END);
        cant =ftell(buffer);
        cantDatos= cant / sizeof(Alumno);
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }
return cantDatos;
}
///N12
void mostrarPos(char archivo[],int pos)
{
    Alumno A;
    int cant = 0;
    FILE *buffer = fopen(archivo,"rb");
    if(buffer != NULL)
    {
        cant = cantDeRegistros(archivo);
        if(pos <= cant)
        {
          fseek(buffer,sizeof(Alumno) * (pos - 1), SEEK_SET);
          fread(&A,sizeof(Alumno),1,buffer);
          mostrarUnAlumno(A);
        }
        else
        {
            printf("No es una posicion valida.\n");
        }
        fclose(buffer);
    }
    else
    {
        printf("No se pudo abrir.\n");
    }
}
///N13
void modificarArchivo(char archivo[], int posAmodificar)
{
  Alumno A;
  char control = 's';
  FILE *buffer = fopen(archivo,"r + b");
  if(buffer != NULL)
  {
    fseek(buffer,sizeof(Alumno)*(posAmodificar -1),SEEK_SET);
    fread(&A,sizeof(Alumno),1,buffer);
    while(control == 's')
    {
      int opcion;
      printf("Que desea modificar?:\n");
      printf("1. Nombre y apellido.\n");
      printf("2. Edad.\n");
      printf("3. anio de cursada.\n");
      printf("4. legajo.\n");
      scanf("%d",&opcion);
      switch(opcion)
      {
          case 1:
          printf("Ingrese el nuevo nombre | apellido:\n");
          fflush(stdin);
          gets(A.nombreYapellido);
          break;
          case 2:
          printf("Ingrese la nueva edad:\n");
          scanf("%d",&A.edad);
          break;
          case 3:
          printf("Ingrese el nuevo anio de cursada:\n");
          scanf("%d",&A.anio);
          break;
          case 4:
          printf("Ingrese el nuevo legajo:\n");
          scanf("%d",&A.legajo);
          break;
      }
      printf("\n Desea modificar otro dato?\n");
      fflush(stdin);
      scanf("%c",&control);
    }
      fseek(buffer,sizeof(Alumno)* (posAmodificar - 1),SEEK_SET);
      fwrite(&A,sizeof(Alumno),1,buffer);
      fclose(buffer);
  }
}

///N14
void invertirArchivo(char archivo[])
{
   Alumno A,B;
   int cant = 0;
   FILE *buffer = fopen(archivo, "r+b");
   if(buffer != NULL)
   {
       fseek(buffer,0,SEEK_SET);
       cant = cantDeRegistros(archivo);
       for(int i = 0; i < cant / 2;i++)
       {
          fseek(buffer,sizeof(Alumno) * i,SEEK_SET);
          fread(&A,sizeof(Alumno),1,buffer);

          fseek(buffer,sizeof(Alumno) * (cant - i - 1),SEEK_SET);
          fread(&B,sizeof(Alumno),1,buffer);

          fseek(buffer,sizeof(Alumno) * i,SEEK_SET);
          fwrite(&B,sizeof(Alumno),1,buffer);

          fseek(buffer,sizeof(Alumno) * (cant - i - 1),SEEK_SET);
          fwrite(&A,sizeof(Alumno),1,buffer);
       }
       fclose(buffer);
   }
   else
   {
       printf("No se pudo abrir.\n");
   }
}

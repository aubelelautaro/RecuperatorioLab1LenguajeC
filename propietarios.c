#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "propietarios.h"
#define OCUPADO 0
#define LIBRE 1
#define BORRADO -4
#define EGRESADO -5
#define ALPHA_ROMEO 1
#define FERRARI 2
#define AUDI 3
#define OTRO 4

void hardcodeProp(ePropietario listadoPropietarios[])
{
    int id[]= {1,2,3,4};
    char nombre[][20]= {"Juan","Luis","Maria","Jose"};
    char tarjeta[][20]= {"111-111","222-222","333-333","444-444"};
    char direccion[][20]= {"mitre","urquiza","belgrano","alsina"};

    int i;

    for(i=0; i<4; i++)
    {
        listadoPropietarios[i].idPropietario=id[i];
        listadoPropietarios[i].estado = OCUPADO;
        strcpy(listadoPropietarios[i].tarjetaCredito, tarjeta[i]);
        strcpy(listadoPropietarios[i].nombreApellido, nombre[i]);
        strcpy(listadoPropietarios[i].direccion, direccion[i]);
    }
}

//Valida que se ingresen solo numeros
int validarNumero(char numero[])
{
    int retorno=1;

    int i;
    for(i=0; i<strlen(numero); i++)
    {
        if(!(isdigit(numero[i])))
        {
            retorno=0;
            printf("Error, Ingrese solo numeros\n");
            break;
        }
    }
    return retorno;
}

//se valida que se inserte una tarjeta o patente en este caso
int validarTarjeta(char str[])
{
   int i=0;
   int contadorGuiones=0;
   while(str[i] != '\0')
   {
       if((str[i] != ' ') && (str[i] != '-') && (str[i] < '0' || str[i] > '9'))
           return 0;
       if(str[i] == '-')
            contadorGuiones++;
       i++;
   }
   if(contadorGuiones==1)// debe tener un guion
        return 1;

    return 0;
}

//Inicializa los propietarios en 0
void ePropietario_init(ePropietario listadoPropietarios[],int limite)
{
    int i;

    for(i=0; i<limite; i++)
    {
        listadoPropietarios[i].estado= LIBRE;
        listadoPropietarios[i].idPropietario= 0;
        listadoPropietarios[i].edad = 0;
        strcpy(listadoPropietarios[i].tarjetaCredito,"");
        strcpy(listadoPropietarios[i].nombreApellido,"");
        strcpy(listadoPropietarios[i].direccion,"");
    }
}

//busca si queda algun lugar libre en el array
int ePropietario_buscarLugarLibre(ePropietario listadoPropietarios[],int limite)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listadoPropietarios != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listadoPropietarios[i].estado == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

//busca el siguiente id del ultimo lugar con estado ocupado en el array
int ePropietario_siguienteId(ePropietario listadoPropietarios[],int limite)
{
    int retorno = 0;
    int i;

    for(i=0; i<limite; i++)
    {
        if(listadoPropietarios[i].estado == OCUPADO)
        {
            if(listadoPropietarios[i].idPropietario>retorno)
            {
                 retorno = listadoPropietarios[i].idPropietario;
            }
        }
    }
    return retorno+1;
}

//Se da de alta al propietario y se valida en cada campo necesario
int ePropietario_alta(ePropietario  listadoPropietarios[],int limite)
{
    int retorno = -1;
    int id;
    int edad;
    int indice;
    int validarN;
    int validarE;
    char nombre[100];

    if(limite > 0 && listadoPropietarios != NULL)
    {
        retorno = -2;
        indice = ePropietario_buscarLugarLibre(listadoPropietarios,limite);

        if(indice >= 0)
        {
            retorno = -3;
            id = ePropietario_siguienteId(listadoPropietarios,limite);

            do
            {
                printf("Ingrese nombre y apellido: ");
                fflush(stdin);
                gets(listadoPropietarios[indice].nombreApellido);
                strcpy(nombre,listadoPropietarios[indice].nombreApellido);
                validarN = validarNombre(nombre);
                if(validarN==0)
                {
                    printf("Ingrese solo letras\n");
                }
            }while(validarN==0);

            printf("Ingrese edad: ");
            fflush(stdin);
            scanf("%d",&edad);

            printf("Ingrese direccion: ");
            fflush(stdin);
            gets(listadoPropietarios[indice].direccion);

            do
            {
                printf("Ingrese tarjeta de credito(con un solo guion): ");
                fflush(stdin);
                gets(listadoPropietarios[indice].tarjetaCredito);
            }while(!validarTarjeta(listadoPropietarios[indice].tarjetaCredito));

            retorno = 0;
            listadoPropietarios[indice].edad = edad;
            listadoPropietarios[indice].idPropietario = id;
            listadoPropietarios[indice].estado = OCUPADO;
        }
    }
    if(retorno!=0)
    {
        printf("Error, no se pudo hacer el alta del propietario");
    }
    if(retorno<0)
    {
        printf("No hay lugar disponible\n");
    }
    return retorno;
}

//Se valida que se ingresen letras y espacios solamente
int validarNombre(char nombre[])
{
    int retorno=1;
    int i;

    for(i=0; i<strlen(nombre); i++)
    {
        if(!(isalpha(nombre[i])) && nombre[i]!=' ')
        {
            retorno=0;
            break;
        }
    }

    return retorno;
}

//Se busca el id solicitado por el usuario
int ePropietario_buscarPorId(ePropietario listadoPropietarios[] ,int limite, int id)
{
    int retorno = -1;
    int i;
    if(limite > 0 && listadoPropietarios != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listadoPropietarios[i].estado == OCUPADO && listadoPropietarios[i].idPropietario == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

//Se modifica la tarjeta del propietario validandola
void ePropietario_modificacion(ePropietario listadoPropietarios[] ,int limite)
{
    int id;
    int indexProp=-1;
    int opcion;

    ePropietario_mostrarListado(listadoPropietarios,limite);

    printf("Ingrese id de propietario a modificar su tarjeta: ");
    scanf("%d",&id);

    indexProp = ePropietario_buscarPorId(listadoPropietarios,limite,id);

    if(indexProp>=0)
    {
        printf("Esta seguro que desea modificar la tarjeta? (1.Si - 2.No) \n");
        scanf("%d",&opcion);
        if(opcion == 1)
        {
            do
            {
                printf("\nIngrese nuevo numero de tarjeta (con un solo guion): ");
                fflush(stdin);
                gets(listadoPropietarios[indexProp].tarjetaCredito);
            }while(!validarTarjeta(listadoPropietarios[indexProp].tarjetaCredito));
        }
        else
        {
            printf("Modificacion cancelada\n");
        }
    }
    else
    {
        printf("El id no coincide con ningun propietario\n");
    }
}

void mostrarUsuariosCiertaEdad(ePropietario listadoPropietarios[],int limite)
{
    int edad;
    int i;

    printf("Ingrese edad a mostrar usuarios: ");
    scanf("%d",&edad);
    for(i=0;i<limite;i++)
    {
        if (listadoPropietarios[i].edad >= edad)
        {
            ePropietario_mostrarUno(listadoPropietarios[i]);
        }
    }
}

//Muestra los propietarios pidiendo el id del propietario a dar de baja
void ePropietario_baja(ePropietario listadoPropietarios[] ,int limite)
{
    int id;
    int indexProp = -1;
    int opcion;

    ePropietario_mostrarListado(listadoPropietarios,limite);

    printf("\nIngrese ID de propietario a dar de baja: ");
    fflush(stdin);
    scanf("%d",&id);

    indexProp = ePropietario_buscarPorId(listadoPropietarios,limite,id);

    if(indexProp >= 0)
    {
        printf("Desea confirmar la baja? (1.Si - 2.No)");
        scanf("%d",&opcion);
    }
    else
    {
        printf("No hay ningun propietario con ese id\n");
    }

    if(opcion == 1)
    {
        if(indexProp >= 0)
        {
            ePropietario_mostrarUno(listadoPropietarios[indexProp]);

            listadoPropietarios[indexProp].estado = BORRADO;
            listadoPropietarios[indexProp].idPropietario = 0;
            listadoPropietarios[indexProp].edad = 0;
            strcpy(listadoPropietarios[indexProp].tarjetaCredito,"");
            strcpy(listadoPropietarios[indexProp].nombreApellido, "");
            strcpy(listadoPropietarios[indexProp].direccion, "");

        }
        else
        {
            printf("El id no coincide con ningun propietario\n");
        }
    }
    else
    {
        printf("Baja cancelada\n");
    }
}

//Muestra un propietario
void ePropietario_mostrarUno(ePropietario parametro)
{
     printf("\nID: %d - Nombre : %s - Edad: %d - Direccion: %s - Tarjeta: %s \n",parametro.idPropietario,parametro.nombreApellido,parametro.edad,parametro.direccion,parametro.tarjetaCredito);
}

//Muestra el listado de los usuarios
void ePropietario_mostrarListado(ePropietario listadoPropietarios[],int limite)
{
    int i;
    for(i=0; i<limite; i++)
    {
        if(listadoPropietarios[i].estado == OCUPADO)
        {
            ePropietario_mostrarUno(listadoPropietarios[i]);
        }
    }
}

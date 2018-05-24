#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "autos.h"
#define OCUPADO 0
#define LIBRE 1
#define BORRADO -4
#define EGRESADO -5
#define ALPHA_ROMEO 1
#define FERRARI 2
#define AUDI 3
#define OTRO 4
#include <time.h>

void hardcodeIngresos(eAuto listadoAutos[])
{
    int id[]= {1,2,3,4,5,6,7,8,9,10};
    char patente[][20]= {"AAA","CCC","DDD","BBB","ZZZ","III","HHH","EEE","FFF","GGG"};
    int marca[]= {1,3,3,2,2,3,3,4,3,1};
    int propietario[]= {2,1,2,1,3,3,4,1,4,3};
    int i;

    for(i=0; i<10; i++)
    {
        listadoAutos[i].idAuto = id[i];
        strcpy(listadoAutos[i].patente, patente[i]);
        listadoAutos[i].marca = marca[i];
        listadoAutos[i].idPropietario = propietario[i];
        listadoAutos[i].estado = OCUPADO;
    }
}

void hardcodeEgresos(eAuto listadoAutos[])
{
    int marca[]= {1,1,2,3,2,2,3,4,1,1};
    float importe[]= {100,200,100,300,100,100,200,200,100,100};
    int i;

    for(i=0; i<10; i++)
    {
        listadoAutos[i].marca = marca[i];
        listadoAutos[i].importe = importe[i];
        listadoAutos[i].estado = EGRESADO;
    }
}

void eAuto_init(eAuto listadoAutos[],int limite)
{
    int i;

    for(i=0; i<limite; i++)
    {
        strcpy(listadoAutos[i].patente,"");
        listadoAutos[i].marca = 0;
        listadoAutos[i].idPropietario = 0;
        listadoAutos[i].idAuto = 0;
        listadoAutos[i].estado = LIBRE;
        listadoAutos[i].importe = 0;
    }
}

void eAuto_ingreso(eAuto listadoAutos[],ePropietario listadoPropietarios[],int limiteAutos,int limitePropietarios)
{
    int auxIdPropietario;
    int index;
    int auxIdAuto;
    int flag = 0;
    int i;

    ePropietario_mostrarListado(listadoPropietarios,limitePropietarios);
    printf("\nIngrese id del propietario (del auto a ingresar): ");
    scanf("%d",&auxIdPropietario);

    for(i=0;i<limitePropietarios;i++)
    {
        if(auxIdPropietario == listadoPropietarios[i].idPropietario && auxIdPropietario != 0)
        {
            flag = 1;
            break;
        }
    }

    index = eAuto_buscarLugarLibre(listadoAutos,limiteAutos);

    if(index >= 0 && flag == 1)
    {
        auxIdAuto = eAuto_siguienteId(listadoAutos,limiteAutos);

        do
        {
            printf("\nIngrese marca del auto:");
            scanf("%d",&listadoAutos[index].marca);
        }while(listadoAutos[index].marca < 1 && listadoAutos[index].marca > 5);

        do
        {
            printf("\nIngrese patente:");
            fflush(stdin);
            gets(listadoAutos[index].patente);
        }while (!validarTarjeta(listadoAutos[index].patente));


            listadoAutos[index].idPropietario = auxIdPropietario;
            listadoAutos[index].estado = OCUPADO;
            listadoAutos[index].idAuto = auxIdAuto;
    }

    if(flag == 0)
    {
        printf("No existe el propietario buscado\n");
    }
    if(index < 0)
    {
        printf("No hay mas espacio\n");
    }
}

void eAuto_mostrarUno(eAuto parametro)
{
    char marca[20];

    if(parametro.marca==1)
    {
        strcpy(marca,"ALPHA_ROMEO");
    }
    if(parametro.marca==2)
    {
        strcpy(marca,"FERRARI");
    }
    if(parametro.marca==3)
    {
        strcpy(marca,"AUDI");
    }
    if(parametro.marca==4)
    {
        strcpy(marca,"OTRO");
    }
    printf("\n %d  -  %d  -  %s  -  %s\n",parametro.idAuto,parametro.idPropietario,marca,parametro.patente);
}

//Muestra todos los campos de todos los elementos de un array
void eAuto_mostrarListado(eAuto listadoAutos[],int limite)
{
    int i;
    printf("ID Auto  -  ID Propietario  -  Marca  -  Patente\n");

    for(i=0;i<limite;i++)
    {
        if(listadoAutos[i].estado==OCUPADO)
        {
            eAuto_mostrarUno(listadoAutos[i]);
        }
    }
}

void eAuto_egreso(eAuto listaAutos[],ePropietario listaPropietarios[],int limiteAutos,int limitePropietarios)
{
    int id;
    int indexAuto;
    int indexProp;
    int horas;
    int i;
    int flag=0;
    int auxFlag;
    int opcion;
    float importe;

    char marca[20];

    for(i=0;i<limiteAutos;i++)
    {
        if(listaAutos[i].estado==OCUPADO)
        {
            eAuto_mostrarListado(listaAutos,limiteAutos);

            printf("Ingrese id del auto que egresa: ");
            scanf("%d", &id);
            auxFlag = 1;
            break;
        }
    }

    if(auxFlag==0)
    {
        printf("No hay autos estacionados\n");
        flag=1;
    }
    if(flag!=1)
    {
        indexAuto = eAuto_buscarPorId(listaAutos,limiteAutos,id);
        indexProp = ePropietario_buscarPorId(listaPropietarios,limitePropietarios,listaAutos[indexAuto].idPropietario);

        printf("Confirmar egreso?: 1.Si - 2.No\n");
        scanf("%d", &opcion);

        if(indexAuto >= 0 && opcion == 1)
        {
            horas = devolverHorasEstadia();
            if(listaAutos[indexAuto].marca==1)
            {
                strcpy(marca,"ALPHA_ROMEO");
                importe=horas*150;
                listaAutos[indexAuto].importe=importe;
            }

            if(listaAutos[indexAuto].marca==2)
            {
                strcpy(marca,"FERRARI");
                importe=horas*175;
                listaAutos[indexAuto].importe=importe;
            }

            if(listaAutos[indexAuto].marca==3)
            {
                strcpy(marca,"AUDI");
                importe=horas*200;
                listaAutos[indexAuto].importe=importe;
            }

            if(listaAutos[indexAuto].marca==4)
            {
                strcpy(marca,"OTROS");
                importe=horas*250;
                listaAutos[indexAuto].importe=importe;
            }

            listaAutos[indexAuto].estado = EGRESADO;

            printf("Propietario: %s - Patente: %s - Marca: %s - Valor de estadia: %.2f\n", listaPropietarios[indexProp].nombreApellido, listaAutos[indexAuto].patente, marca, importe);
        }
        else
        {
            if(opcion==1)
            {
                printf("El id no coincide con ningun auto estacionado\n");
            }
        }
    }
}

//Muestra todos los campos de todos los egresos de los elementos de un array
void eAuto_mostrarEgresos(eAuto listadoAutos[],int limiteAutos, ePropietario listadoPropietarios[],int limitePropietarios)
{
    int i;
    int j;
    char marca[20];

    for(i=0;i<limiteAutos;i++)
    {
        if(listadoAutos[i].estado==EGRESADO)
        {
            for(j=0;j<limitePropietarios;j++)
            {
                if(listadoAutos[i].idPropietario == listadoPropietarios[j].idPropietario)
                {
                   break;
                }
            }
            if(listadoAutos[i].marca==1)
            {
                strcpy(marca,"ALPHA_ROMEO");
            }
            if(listadoAutos[i].marca==2)
            {
                strcpy(marca,"FERRARI");
            }
            if(listadoAutos[i].marca==3)
            {
                strcpy(marca,"AUDI");
            }
            if(listadoAutos[i].marca==4)
            {
                strcpy(marca,"OTROS");
            }
            printf("Propietario: %s - Patente: %s Marca: %s Importe a pagar: %.2f\n", listadoPropietarios[j].nombreApellido, listadoAutos[i].patente, marca, listadoAutos[i].importe);
        }
    }
}

void eAuto_recaudacionTotal(eAuto listadoAutos[],int limiteAutos)
{
    int i;
    float acumuladorImportes = 0;

    for(i=0;i<limiteAutos;i++)
    {
        acumuladorImportes+=listadoAutos[i].importe;
    }

    printf("Recaudacion total: %.2f\n", acumuladorImportes);
}

void eAuto_recaudacionPorMarca(eAuto listadoAutos[],int limiteAutos)
{
    int i;
    float acumuladorAlpha = 0;
    float acumuladorFerrari = 0;
    float acumuladorAudi =0;
    float acumuladorOtros = 0;

    for(i=0;i<limiteAutos;i++)
    {
        if(listadoAutos[i].marca==1)
        {
             acumuladorAlpha+=listadoAutos[i].importe;
        }
        if(listadoAutos[i].marca==2)
        {
            acumuladorFerrari+=listadoAutos[i].importe;
        }
        if(listadoAutos[i].marca==3)
        {
            acumuladorAudi+=listadoAutos[i].importe;
        }
        if(listadoAutos[i].marca==4)
        {
            acumuladorOtros+=listadoAutos[i].importe;
        }
    }
    printf("\nRecaudacion\nAlpha Romeo: %.2f\nFerrari: %.2f\nAudi: %.2f\nOtros: %.2f\n\n",acumuladorAlpha,acumuladorFerrari,acumuladorAudi,acumuladorOtros);
}

void eAuto_buscarPorIdPropietario(eAuto listadoAutos[],int limiteAutos, ePropietario listadoPropietarios[],int limitePropietarios)
{
    int id;
    int indexProp;
    int i;
    char marca[20];

    ePropietario_mostrarListado(listadoPropietarios,limitePropietarios);

    printf("Ingrese ID del propietario: ");
    scanf("%d", &id);

    indexProp = ePropietario_buscarPorId(listadoPropietarios,limitePropietarios, id);

    if(indexProp>=0)
    {
        for(i=0;i<limiteAutos;i++)
        {
            if(listadoPropietarios[indexProp].idPropietario == listadoAutos[i].idPropietario && listadoAutos[i].estado==OCUPADO)
            {
                if(listadoAutos[i].marca==1)
                    {
                        strcpy(marca,"ALPHA_ROMEO");
                    }
                if(listadoAutos[i].marca==2)
                    {
                        strcpy(marca,"FERRARI");
                    }
                if(listadoAutos[i].marca==3)
                    {
                        strcpy(marca,"AUDI");
                    }
                if(listadoAutos[i].marca==4)
                    {
                        strcpy(marca,"OTROS");
                    }
                printf("Propietario: %s - Patente: %s - Marca: %s\n", listadoPropietarios[indexProp].nombreApellido, listadoAutos[i].patente, marca);
            }
        }
    }
    else
    {
        printf("El propietario ingresado no existe\n");
    }
}

void eAuto_datosAudi(eAuto listadoAutos[],int limiteAutos, ePropietario listadoPropietarios[],int limitePropietarios)
{
    int i;
    int j;

    for(i=0;i<limiteAutos;i++)
    {
        if(listadoAutos[i].marca == 3 && listadoAutos[i].estado == OCUPADO)
        {
            for(j=0;j<limitePropietarios;j++)
            {
                if(listadoAutos[i].idPropietario == listadoPropietarios[j].idPropietario)
                {
                   printf("\nId propietario: %d - id auto: %d - Propietario: %s - Direccion: %s - Tarjeta: %s \n",listadoPropietarios[j].idPropietario,listadoAutos[i].idAuto,listadoPropietarios[j].nombreApellido,listadoPropietarios[j].direccion,listadoPropietarios[j].tarjetaCredito);
                }
            }
        }
    }
}

void eAuto_estacionadosPorPatente(eAuto listadoAutos[],int limiteAutos, ePropietario listadoPropietarios[],int limitePropietarios)
{
    int i;
    int j;
    int ultimoOcupado;
    int auxI;
    int indexProp;
    int idProp;

    char auxPatente[50];
    char marca[20];
    char auxNombre[20][100];
    char direccion[20][100];

    ultimoOcupado = eAuto_buscarLugarLibre(listadoAutos,limiteAutos);

    if(ultimoOcupado==-2)
    {
        ultimoOcupado=20;
    }

    for(i=0;i<ultimoOcupado-1;i++)
    {
        for(j=i+1;j<ultimoOcupado;j++)
        {
            if(strcmp(listadoAutos[j].patente,listadoAutos[i].patente)==-1)
            {
                strcpy(auxPatente, listadoAutos[j].patente);
                strcpy(listadoAutos[j].patente, listadoAutos[i].patente);
                strcpy(listadoAutos[i].patente, auxPatente);

                auxI=listadoAutos[j].marca;
                listadoAutos[j].marca=listadoAutos[i].marca;
                listadoAutos[i].marca=auxI;

                auxI=listadoAutos[j].idAuto;
                listadoAutos[j].idAuto=listadoAutos[i].idAuto;
                listadoAutos[i].idAuto=auxI;

                auxI=listadoAutos[j].idPropietario;
                listadoAutos[j].idPropietario=listadoAutos[i].idPropietario;
                listadoAutos[i].idPropietario=auxI;
            }
        }
    }

    for(i=0;i<ultimoOcupado;i++)
    {
        indexProp = ePropietario_buscarPorId(listadoPropietarios,limitePropietarios,listadoAutos[i].idPropietario);
        strcpy(auxNombre[i],listadoPropietarios[indexProp].nombreApellido);
        strcpy(direccion[i], listadoPropietarios[indexProp].direccion);
        idProp=listadoPropietarios[indexProp].idPropietario;

    if(listadoAutos[i].estado==OCUPADO)
        {
            if(listadoAutos[i].marca==1)
                    {
                        strcpy(marca,"ALPHA_ROMEO");
                    }

                if(listadoAutos[i].marca==2)
                    {
                        strcpy(marca,"FERRARI");
                    }

                if(listadoAutos[i].marca==3)
                    {
                        strcpy(marca,"AUDI");
                    }

                if(listadoAutos[i].marca==4)
                    {
                        strcpy(marca,"OTROS");
                    }

            printf("Auto: Patente: %s - id: %d - %s\nPropietario: %s - id: %d - %s\n\n",listadoAutos[i].patente, listadoAutos[i].idAuto, marca,auxNombre[i], idProp, direccion[i]);
        }
    }
}

// Me devuelve el indice de un espacio vacio
int eAuto_buscarLugarLibre(eAuto listadoAutos[],int limite)
{
    int retorno = -1;
    int i;

    if(limite > 0 && listadoAutos != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listadoAutos[i].estado == LIBRE)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

// Me devuelve la siguiente id
int eAuto_siguienteId(eAuto listadoAutos[],int limite)
{
    int retorno = 0;
    int i;

    for(i=0;i<limite;i++)
    {
        if(listadoAutos[i].estado == OCUPADO)
        {
            if(listadoAutos[i].idAuto > retorno)
            {
                 retorno = listadoAutos[i].idAuto;
            }
        }
    }
    return retorno+1;
}

// Me devuelve el indice del elemento con la id ingresada
int eAuto_buscarPorId(eAuto listadoAutos[],int limite,int id)
{
    int retorno = -1;
    int i;

    if(limite > 0 && listadoAutos != NULL)
    {
        retorno = -2;
        for(i=0;i<limite;i++)
        {
            if(listadoAutos[i].estado == OCUPADO && listadoAutos[i].idAuto == id)
            {
                retorno = i;
                break;
            }
        }
    }
    return retorno;
}

int devolverHorasEstadia()
{
    int horas;

    srand(time(NULL));

    horas = (rand()%24)+1;

    return horas ;

}

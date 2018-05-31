#include <stdio.h>
#include <stdlib.h>
#include "autos.h"
#define CANTCOCHES 20
#define CANTPROP 20

int main()
{
    char seguir='s';
    int opcion;
    int retorno;

    ePropietario listaProp[CANTPROP];
    ePropietario_init(listaProp,CANTPROP);
    hardcodeProp(listaProp);

    eAuto listaAutos[CANTCOCHES];
    eAuto_init(listaAutos,CANTCOCHES);
    hardcodeIngresos(listaAutos);


    while(seguir=='s')
    {
        printf("1.Alta de propietario\n");
        printf("2.Modificacion de propietario\n");
        printf("3.Baja de propietario\n");
        printf("4.Ingreso de automovil\n");
        printf("5.Egreso de automovil\n");
        printf("6.Recaudacion total del estacionamiento\n");
        printf("7.Recaudacion total por marca\n");
        printf("8.Buscar autos estacionados por id de propietario\n");
        printf("9.Datos de propietarios con autos AUDI estacionados\n");
        printf("10.Listado de autos estacionados con sus propietario, ordenados por patente\n");
        printf("11.Egresar autos (hardcode)\n");
        printf("12.Mostrar autos egresados(hardcode)\n");
        printf("13.Listado de propietarios ordenados por nombre ascendente (no funciona todavia)\n");
        printf("14.Mostrar quienes superan cierta edad\n");
        printf("15.Salir\n");

        fflush(stdin);
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                ePropietario_alta(listaProp,CANTPROP);
                break;
            case 2:
                ePropietario_modificacion(listaProp,CANTPROP);
                break;
            case 3:
                ePropietario_baja(listaProp,CANTPROP);
                break;
            case 4:
                eAuto_ingreso(listaAutos, listaProp,CANTCOCHES,CANTPROP);
                break;
            case 5:
                eAuto_egreso(listaAutos, listaProp,CANTCOCHES,CANTPROP);
                break;
            case 6:
                eAuto_recaudacionTotal(listaAutos,CANTCOCHES);
                break;
            case 7:
                eAuto_recaudacionPorMarca(listaAutos,CANTCOCHES);
                break;
            case 8:
                eAuto_buscarPorIdPropietario(listaAutos,CANTCOCHES,listaProp,CANTPROP);
                break;
            case 9:
                eAuto_datosAudi(listaAutos,CANTCOCHES, listaProp,CANTPROP);
                break;
            case 10:
                eAuto_estacionadosPorPatente(listaAutos,CANTCOCHES,listaProp,CANTPROP);
                break;
            case 11:
                hardcodeEgresos(listaAutos);
                break;
            case 12:
                eAuto_mostrarEgresos(listaAutos,CANTCOCHES,listaProp,CANTPROP);
                break;
            case 13:
                listarPropietariosNombreDescendente(listaAutos,CANTCOCHES,listaProp,CANTPROP);
                break;
            case 14:
                mostrarUsuariosCiertaEdad(listaProp,CANTPROP);
                break;
            case 15:
                seguir = 'n';
                break;
            default:
                printf("Error, opcion incorrecta\n");
        }
    }
    return 0;
}

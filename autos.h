#ifndef AUTOS_H_INCLUDED
#define AUTOS_H_INCLUDED
#include "propietarios.h"

typedef struct
{
    char patente[20];
    int marca;
    int idPropietario;

    int idAuto;
    int estado;
    float importe;

}eAuto;

#endif // AUTOS_H_INCLUDED
void hardcodeIngresos(eAuto[]);
void hardcodeEgresos(eAuto listadoAutos[]);

void eAuto_init(eAuto[],int);
void eAuto_ingreso(eAuto listadoAutos[],ePropietario listadoPropietarios[],int limiteAutos,int limitePropietarios);

void eAuto_mostrarUno(eAuto parametro);
void eAuto_mostrarListado(eAuto listadoAutos[],int limite);

void eAuto_egreso(eAuto listadoAutos[],ePropietario listadoPropietarios[],int limiteAutos,int limitePropietarios);
void eAuto_mostrarEgresos(eAuto listadoAutos[],int limiteAutos,ePropietario listadoPropietarios[],int limitePropietarios);

void eAuto_recaudacionTotal(eAuto listadoAutos[],int limiteAutos);
void eAuto_recaudacionPorMarca(eAuto listadoAutos[],int limiteAutos);

void eAuto_buscarPorIdPropietario(eAuto listadoAutos[],int limiteAutos,ePropietario listadoPropietarios[],int limitePropietarios);
void eAuto_datosAudi(eAuto listadoAutos[],int limiteAutos,ePropietario listadoPropietarios[],int limitePropietarios);
void eAuto_estacionadosPorPatente(eAuto listadoAutos[],int limiteAutos,ePropietario listadoPropietarios[],int limitePropietarios);

int eAuto_buscarLugarLibre(eAuto listadoAutos[],int limite);
int eAuto_siguienteId(eAuto listadoAutos[],int limite);
int eAuto_buscarPorId(eAuto listadoAutos[],int limite,int id);

void listarPropietariosNombreDescendente(eAuto listadoAutos[], int limiteAutos, ePropietario listadoPropietarios[], int limitePropietarios);
void eAuto_estacionadosPorPatente(eAuto listadoAutos[], int limiteAutos, ePropietario listadoPropietarios[], int limitePropietarios);

int devolverHorasEstadia();

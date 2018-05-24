#ifndef PROPIETARIOS_H_INCLUDED
#define PROPIETARIOS_H_INCLUDED

typedef struct
{
    int idPropietario;
    char nombreApellido[100];
    char direccion[100];
    char tarjetaCredito[20];
    int estado;

}ePropietario;

#endif // PROPIETARIOS_H_INCLUDED


void hardcodeProp(ePropietario[]);

int validarNumero(char numero[]);
int validarNombre(char nombre[]);
int validarTarjeta(char str[]);

void ePropietario_init(ePropietario[],int);

int ePropietario_alta(ePropietario[],int);
void ePropietario_baja(ePropietario[],int);
void ePropietario_modificacion(ePropietario[],int);

void ePropietario_mostrarUno(ePropietario parametro);
void ePropietario_mostrarListado(ePropietario[],int limite);

int ePropietario_buscarLugarLibre(ePropietario[],int);
int ePropietario_siguienteId(ePropietario[],int);
int ePropietario_buscarPorId(ePropietario[],int,int);

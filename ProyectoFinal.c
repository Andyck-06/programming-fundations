#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define mensajeContinuar "Informaci%cn guardada correctamente, presione ENTER para continuar. ", 162
#define MAX_CLIENTES 10
#define DATOS_SI_COINCIDEN 1
#define DATOS_NO_COINCIDEN -1
#define NAME_INDEX 0
#define PHONE_INDEX 1
#define CARD_INDEX 2
#define NIP_INDEX 3

char nombre[100] = "\0", nom[50] = "\0", ap[50] = "\0", celular[20] = "\0", numTarjeta[20] = "\0", nip[8] = "\0";
char cnfCelular[20], cnfNip[8], cnfNombre[100], cnfTarjeta[25];
int numClientes = 0, cliente;

char clientes[MAX_CLIENTES][5][100];
float saldos[MAX_CLIENTES];

char msjRgsNombre[50] = "Ingrese el nombre del cliente (Solo nombre(s) ): ";
char msjRgsApellido[36] = "Ingrese los apellidos del cliente: ";
char msjRgsCelular[63] = "Ingrese el n%cmero celular del cliente (10 n%cmeros exactos): ";
char msjRgsNumTarjeta[66] = "Ingrese el n%cmero de tarjeta del cliente (16 n%cmeros exactos): ";
char msjRgsNip[50] = "Ingrese el NIP del cliente (4 n%cmeros exactos): ";

char msjErrRegistro[83] = "%cLa informaci%cn ingresada no es la solicitada!, presione ENTER para reintentar. ";
char msjErrClnInexistente[96] = "\n\n%cNo hay suficientes clientes registrados!, presione ENTER para regresar al men%c principal. ";

char msjDpsCelular[33] = "Ingresa el celular de tu cuenta: ";
char msjDpsNip[29] = "Ingresa el NIP de tu cuenta: ";
char msjTrnNombre[47] = "Ingresa el titular de la cuenta a transferir: ";
char msjTrnTarjeta[34] = "Ingresa la tarjeta de la cuenta: ";

char msjOpcUno[65] = "Usted seleccion%c la opci%cn 1: Registrar a un nuevo cliente.\n\n";
char msjOpcDos[68] = "Usted seleccion%c la opci%cn 2: Depositar dinero a cuenta propia.\n\n";
char msjOpcTres[68] = "Usted seleccion%c la opci%cn 3: Verificar saldo en tarjeta.\n\n";
char msjOpcCuatro[69] = "Usted seleccion%c la opci%cn 4: Transferir dinero a otras cuentas.\n\n";
char msjOpcCinco[56] = "Usted seleccion%c la opci%cn 5: Recargar tiempo aire.\n\n";
char msjOpcSeis[47] = "Usted seleccion%c la opci%cn 6: Cambiar NIP.\n\n";

// función para verificar si la información dada son EXCLUSIVAMENTE letras
int vrfSloLetras(char string[], char msjError[])
{
    int i;

    if (string[0] == '\0')
    {
        printf(msjError, 173, 162, 160);
        getchar();

        system("cls");
        return -1;
    }

    for (i = 0; string[i] != '\0'; i++)
    {
        if (isdigit(string[i]) || ispunct(string[i]))
        {
            printf(msjError, 173, 162, 160);
            getchar();

            system("cls");
            return -1;
            break;
        }
    }
    return 1;
}

// función para verificar si la información dada son EXCLUSIVAMENTE números y de una longitud EXACTA
int vrfSloNumeros(char string[], char msjError[], int delimitador)
{
    int i;

    if (strlen(string) != delimitador)
    {

        printf(msjError, 173, 162);
        getchar();

        system("cls");
        return -1;
    }

    for (i = 0; string[i] != '\0'; i++)
    {
        if (isalpha(string[i]))
        {
            printf(msjError, 173, 162);
            getchar();

            system("cls");
            return -1;
            break;
        }
    }

    return 1;
}

// función para limpiar el salto de linea del fgets
void rmvLinea(char string[])
{
    size_t lon = strlen(string);
    if (lon > 0 && string[lon - 1] == '\n')
    {
        string[lon - 1] = '\0';
    }
}

// función para que si a la hora de ingresar los datos (nombre y apellidos) se genera un error poder reintentar rellenar ese mismo campo
char *msjTxt(char res[], int resSize, char msjDato[], char msjError[], char msjOpcion[], int mstOpc)
{
    int t = 1;
    while (t == 1)
    {
        if (mstOpc == 1)
        {
            printf(msjOpcion, 162, 162);
        }
        printf(msjDato);
        fgets(res, resSize, stdin);

        rmvLinea(res);

        system("cls");

        if (vrfSloLetras(res, msjError) == 1)
        {
            t = 0;
        }
    }
    return (res);
}

// función para que si a la hora de ingresar los datos (celular, tarjeta y nip) se genera un error poder reintentar rellenar ese mismo campo
char *msjNum(char res[], int resSize, char msjDato[], char msjError[], char msjOpcion[], int delimitador, int mstOpc)
{
    int t = 1;
    while (t == 1)
    {
        if (mstOpc == 1)
        {
            printf(msjOpcion, 162, 162);
        }
        printf(msjDato, 163, 163);
        fgets(res, resSize, stdin);

        rmvLinea(res);

        system("cls");

        if (vrfSloNumeros(res, msjError, delimitador) == 1)
        {
            t = 0;
        }
    }
    return (res);
}

// función para verificar si existe un cliente registrado
int vrfExsCliente()
{
    if (numClientes == 0)
    {
        printf(msjErrClnInexistente, 173, 163);
        getchar();
        system("cls");
        return 0;
    }
    return 1;
}

// función para verificar si el celular y el nip coinciden con el el cleinte registrado
int vrfDtsCoincidan(char dtoUno[], int posDtoUno, char dtoDos[], int posDtoDos, char *nombreCliente, float *saldoCliente, int *cliente)
{
    int i = 0;
    for (i; i < numClientes; i++)
    {
        if (strcmp(clientes[i][posDtoUno], dtoUno) == 0 && strcmp(clientes[i][posDtoDos], dtoDos) == 0)
        {
            strcpy(nombreCliente, clientes[i][0]);
            *saldoCliente = (float)saldos[i];
            *cliente = i;
            return 1;
        }
    }
    return -1;
}

int findClientIndex(char msgOption[])
{
    char inputPhone[20];
    char inputNip[8];

    while (1)
    {
        strcpy(inputPhone, msjNum(inputPhone, sizeof(inputPhone), msjDpsCelular, msjErrRegistro, msgOption, 10, 1));
        strcpy(inputNip, msjNum(inputNip, sizeof(inputNip), msjDpsNip, msjErrRegistro, msgOption, 4, 1));
        int i = 0;
        for (i; i < numClientes; i++)
        {
            if (strcmp(clientes[i][PHONE_INDEX], inputPhone) == 0 && strcmp(clientes[i][NIP_INDEX], inputNip) == 0)
            {
                return i;
            }
        }

        printf("Los datos ingresados no coinciden con ninguna cuenta. Presione ENTER para reintentar.\n");
        getchar();
        system("cls");
    }
}

void showCurrentBalance(int clientIndex)
{
    float balance = saldos[clientIndex];
    char *name = clientes[clientIndex][NAME_INDEX];
    printf(msjOpcTres, 162, 162);
    printf("Bienvenid%c %s\n", 64, name);
    printf("Tu saldo actual es: %c%.2f\n", 36, balance);
    printf("\nPresione ENTER para regresar al men%c principal.", 163);
    getchar();
    system("cls");
}

float requestAmountToSave(void)
{
    char inputAmount[100];
    float deposit;

    while (1)
    {
        printf("Ingrese el monto a depositar: ");
        fgets(inputAmount, sizeof(inputAmount), stdin);
        rmvLinea(inputAmount);
        system("cls");

        char *endptr;
        deposit = strtof(inputAmount, &endptr);

        if (*endptr == '\0' && deposit > 0)
        {
            break;
        }

        printf("El monto ingresado no es v%clido. Por favor, presione ENTER para reintentar.\n", 160);
        getchar();
        system("cls");
        printf(msjOpcDos, 162, 162);
    }

    return deposit;
}

int checkAmountIsCorrect(float deposit)
{
    char check;

    while (1)
    {
        printf(msjOpcDos, 162, 162);
        printf("%cEst%c seguro que desea depositar %c%.2f%c (s/n): ", 168, 160, 36, deposit, 63);
        scanf(" %c", &check);
        getchar();
        system("cls");

        if (check == 's' || check == 'S')
        {
            return 1;
        }
        else if (check == 'n' || check == 'N')
        {
            return -1;
        }
        else
        {
            printf("Opci%cn inv%clida. Presione ENTER para reintentar.\n", 162, 160);
        }
    }
}

void addAmountToBalance(int clientIndex, float newAmount)
{
    saldos[clientIndex] += newAmount;
}

int increaseClientBalance()
{
    int clientIndex = -1;
    float amountToAdd;

    clientIndex = findClientIndex(msjOpcDos);

    printf(msjOpcDos, 162, 162);
    printf("Bienvenid%c %s\n\n", 64, clientes[clientIndex][NAME_INDEX]);

    while (1)
    {
        amountToAdd = requestAmountToSave();
        int confirmation = checkAmountIsCorrect(amountToAdd);

        if (confirmation == -1)
        {
            printf(msjOpcDos, 162, 162);
            printf("%cDep%csito cancelado correctamente!, presione ENTER para reintentar.\n", 33, 162);
            getchar();
            system("cls");
            printf(msjOpcDos, 162, 162);
            continue;
        }

        addAmountToBalance(clientIndex, amountToAdd);

        printf(msjOpcDos, 162, 162);
        printf("Monto depositado: %c%.2f\n", 36, amountToAdd);
        printf("Depositado en la tarjeta: %s\n", clientes[clientIndex][CARD_INDEX]);
        printf("\nDep%csito realizado con %cxito, presiona ENTER para regresar al men%c principal. ", 162, 130, 163);
        getchar();
        system("cls");

        return 0;
    }
}

int checkBalance()
{
    int clientIndex = -1;

    clientIndex = findClientIndex(msjOpcTres);

    showCurrentBalance(clientIndex);

    return 0;
}

int main()
{
    int t;
    int op;
    char check;
    float saldo;

    do
    {

        system("cls");
        printf("Bienvenido al Sitema Bancario, por favor seleccione la opci%cn deseada: \n----------------------------------------------------------------------\n\n", 162);

        printf("1. Registrar a un nuevo cliente\n2. Depositar dinero a cuenta propia\n3. Verificar saldo en tarjeta\n4. Transferir dinero a otras cuentas\n5. Recargar tiempo aire\n6. Cambiar NIP\n7. Salir\n\n");
        scanf("%i", &op);
        getchar();
        system("cls");

        if (op != 1 && op == 4)
        {
            if (numClientes < 2)
            {
                printf(msjErrClnInexistente, 173, 163);
                getchar();
                system("cls");
                continue;
            }
        }
        else if (op != 1 && op != 7)
        {
            if (!vrfExsCliente())
            {
                continue;
            }
        }

        switch (op)
        {
        case 1:

            if (numClientes >= MAX_CLIENTES)
            {
                printf("Se ha alcanzado el n%cmero m%cximo de clientes.\n", 163, 160);
                getchar();
                break;
            }

            strcpy(nom, msjTxt(nom, sizeof(nom), msjRgsNombre, msjErrRegistro, msjOpcUno, 1));
            strcpy(ap, msjTxt(ap, sizeof(ap), msjRgsApellido, msjErrRegistro, msjOpcUno, 1));

            // unir nombres y apellidos en un solo string
            snprintf(nombre, sizeof(nombre), "%s %s", nom, ap);

            strcpy(celular, msjNum(celular, sizeof(celular), msjRgsCelular, msjErrRegistro, msjOpcUno, 10, 1));
            strcpy(numTarjeta, msjNum(numTarjeta, sizeof(numTarjeta), msjRgsNumTarjeta, msjErrRegistro, msjOpcUno, 16, 1));
            strcpy(nip, msjNum(nip, sizeof(nip), msjRgsNip, msjErrRegistro, msjOpcUno, 4, 1));

            // imprime los datos capturados
            printf(msjOpcUno, 162, 162);

            printf("Nombre: %s\n", nombre);
            printf("N%cmero celular: %s\n", 163, celular);
            printf("N%cmero de tarjeta: %s\n", 163, numTarjeta);
            printf("NIP: %s\n", nip);

            printf("\nConfirma tu informaci%cn (s/n): ", 162);
            scanf(" %c", &check);

            if (check != 's')
            {
                system("cls");
                printf("%cEl registro fue cancelado con %cxito!", 173, 130);
                getchar();

                // en dado caso que se quiera cancelar el registro, limpia la info de las strings
                strcpy(nom, "");
                strcpy(ap, "");
                strcpy(nombre, "");
                strcpy(celular, "");
                strcpy(numTarjeta, "");
                strcpy(nip, "");

                break;
            }

            // si el registro es correcto, saldo = 0
            saldo = 0;

            strcpy(clientes[numClientes][NAME_INDEX], nombre);
            strcpy(clientes[numClientes][PHONE_INDEX], celular);
            strcpy(clientes[numClientes][CARD_INDEX], numTarjeta);
            strcpy(clientes[numClientes][NIP_INDEX], nip);
            saldos[numClientes] = saldo;

            numClientes++;

            system("cls");

            printf(mensajeContinuar);
            getchar();
            break;

        case 2:

            increaseClientBalance();

            break;

        case 3:

            checkBalance();

            break;

        case 4:
            float sldUno, sldDos, transferencia;
            char transfe[100];
            int clnUno, clnDos;
            t = 2;

            if (vrfExsCliente() != 1)
            {
                break;
            }

            strcpy(cnfCelular, msjNum(cnfCelular, sizeof(cnfCelular), msjDpsCelular, msjErrRegistro, msjOpcCuatro, 10, 1));
            strcpy(cnfNip, msjNum(cnfNip, sizeof(cnfNip), msjDpsNip, msjErrRegistro, msjOpcCuatro, 4, 1));

            if (vrfDtsCoincidan(cnfCelular, PHONE_INDEX, cnfNip, NIP_INDEX, nombre, &saldo, &cliente) != 1)
            {
                printf("%cLos datos no coinciden con ning%cn cliente!", 173, 163);
                getchar();
                break;
            }
            sldUno = saldo;
            clnUno = cliente;

            system("cls");
            printf(msjOpcCuatro, 162, 162);
            printf("Cuenta de: %s.\nSaldo en la tarjeta de: %c%.2f pesos MXN\n\n", nombre, 36, saldo);

            strcpy(cnfNombre, msjTxt(cnfNombre, sizeof(cnfNombre), msjTrnNombre, msjErrRegistro, msjOpcCuatro, 0));
            strcpy(cnfTarjeta, msjNum(cnfTarjeta, sizeof(cnfTarjeta), msjTrnTarjeta, msjErrRegistro, msjOpcCuatro, 16, 1));

            if (vrfDtsCoincidan(cnfNombre, NAME_INDEX, cnfTarjeta, CARD_INDEX, nombre, &saldo, &cliente) != 1)
            {
                printf("%cLos datos no coinciden con ning%cn cliente!", 173, 163);
                getchar();
                break;
            }
            sldDos = saldo;
            clnDos = cliente;

            while (t == 2)
            {

                system("cls");
                printf(msjOpcCuatro, 162, 162);
                printf("Ingrese la cantidad de dinero a transferir (MXN): ");
                fgets(transfe, sizeof(transfe), stdin);
                rmvLinea(transfe);

                char *endptr;
                transferencia = strtof(transfe, &endptr);

                if (*endptr == '\0' && transferencia > 0)
                {
                    t = 1;
                }

                if (transferencia <= 0)
                {
                    system("cls");
                    printf(msjOpcCuatro, 162, 162);
                    printf("%cLa transferencia no puede ser negativa o 0!\nPresione ENTER para reintentar. ", 173);
                    getchar();
                    continue;
                }

                while (t == 1)
                {

                    system("cls");
                    printf(msjOpcCuatro, 162, 162);
                    printf("Transferir a cuenta de: %s. Con tarjeta: %s\n\n", nombre, cnfTarjeta);
                    printf("Transferencia de: %c%.2f pesos MXN\n\n", 36, transferencia);
                    printf("Confirmar transferencia (s/n): ");
                    scanf(" %c", &check);

                    if (check != 's')
                    {
                        system("cls");
                        printf("%cLa transferencia fue cancelada con %cxito!", 173, 130);
                        transferencia = 0;
                        strcpy(transfe, "\0");
                        t = 2;
                        getchar();
                    }
                    else
                    {
                        t = 0;
                    }
                }
            }

            if (sldUno <= 0 || sldUno < transferencia)
            {
                system("cls");
                printf(msjOpcCuatro, 162, 162);
                printf("%cSaldo insuficiente para realizar la transferencia! presione ENTER para regresar al men%c ", 173, 163);
                getchar();
                break;
            }

            if (clnUno != -1)
            {
                saldos[clnUno] = sldUno - transferencia;
                saldos[clnDos] = sldDos + transferencia;
            }

            system("cls");
            printf(msjOpcCuatro, 162, 162);
            printf("%cLa transferencia fue realizada con %cxito!\n\n", 173, 130);
            printf("Transferencia realizada a cuenta de: %s. Con tarjeta: %s\n\n", nombre, cnfTarjeta);
            printf("Saldo anterior: %c%.2f pesos MXN\nCantidad transferida: %c%.2f pesos MXN\nSaldo actual: %c%.2f pesos MXN\n\n", 36, sldUno, 36, transferencia, 36, sldUno - transferencia);
            printf("Presione ENTER para regresar al men%c principal. ", 163);
            transferencia = 0;
            getchar();
            break;

        case 5:
            int comp;
            t = 3;
            float recarga;
            char compa[10], recarg[100];

            strcpy(cnfCelular, msjNum(cnfCelular, sizeof(cnfCelular), msjDpsCelular, msjErrRegistro, msjOpcCinco, 10, 1));
            strcpy(cnfNip, msjNum(cnfNip, sizeof(cnfNip), msjDpsNip, msjErrRegistro, msjOpcCinco, 4, 1));

            if (vrfDtsCoincidan(cnfCelular, PHONE_INDEX, cnfNip, NIP_INDEX, nombre, &saldo, &cliente) != 1)
            {
                printf("%cLos datos no coinciden con ning%cn cliente!", 173, 163);
                getchar();
                break;
            }

            while (t == 3)
            {
                system("cls");
                printf(msjOpcCinco, 162, 162);
                printf("Cuenta de: %s.\nSaldo en la tarjeta de: %c%.2f pesos MXN\n\n", nombre, 36, saldo);
                printf("Seleccione una compa%cia:\n1. AT&T\n2. Telcel\n3. Movistar\n", 164);
                scanf("%i", &comp);
                getchar();
                if (comp == 1)
                {
                    strcpy(compa, "AT&T");
                    t = 2;
                }
                else if (comp == 2)
                {
                    strcpy(compa, "Telcel");
                    t = 2;
                }
                else if (comp == 3)
                {
                    strcpy(compa, "Movistar");
                    t = 2;
                }
                else
                {
                    system("cls");
                    printf(msjOpcCinco, 162, 162);
                    printf("%cLa compa%cia es inexistente! presione ENTER para reintentar", 173, 164);
                    getchar();
                    continue;
                }
            }

            while (t == 2)
            {

                system("cls");
                printf(msjOpcCinco, 162, 162);
                printf("Ingrese la cantidad de dinero a recargar (MXN): ");
                fgets(recarg, sizeof(recarg), stdin);
                rmvLinea(recarg);

                char *endptr;
                recarga = strtof(recarg, &endptr);

                if (*endptr == '\0' && recarga > 0)
                {
                    t = 1;
                }

                if (recarga <= 0)
                {
                    system("cls");
                    printf(msjOpcCinco, 162, 162);
                    printf("%cLa recarga no puede ser negativa o 0!\nPresione ENTER para reintentar. ", 173);
                    getchar();
                    continue;
                }

                while (t == 1)
                {

                    system("cls");
                    printf(msjOpcCinco, 162, 162);
                    printf("Recargar a celular: %s. Con compa%cia: %s\n\n", cnfCelular, 164, compa);
                    printf("Recarga de: %c%.2f pesos MXN\n\n", 36, recarga);
                    printf("Confirmar recarga (s/n): ");
                    scanf(" %c", &check);

                    if (check != 's')
                    {
                        system("cls");
                        printf(msjOpcCinco, 162, 162);
                        printf("%cLa recarga fue cancelada con %cxito!", 173, 130);
                        recarga = 0;
                        strcpy(recarg, "\0");
                        t = 2;
                        getchar();
                    }
                    else
                    {
                        t = 0;
                    }
                }
            }

            if (saldo <= 0 || saldo < recarga)
            {
                printf("%cSaldo insuficiente para realizar la recarga! presione ENTER para regresar al men%c", 173, 163);
                getchar();
                break;
            }

            if (cliente != -1)
            {
                saldos[cliente] = saldo - recarga;
            }

            system("cls");
            printf(msjOpcCinco, 162, 162);
            printf("%cLa recarga fue realizada con %cxito!\n\n", 173, 130);
            printf("Recargar a celular: %s. Con compa%cia: %s\n\n", cnfCelular, 164, compa);
            printf("Saldo anterior: %c%.2f pesos MXN\nCantidad recargada: %c%.2f pesos MXN\nSaldo actual: %c%.2f pesos MXN\n\n", 36, saldo, 36, recarga, 36, saldo - recarga);
            printf("Presione ENTER para regresar al men%c. ", 163);
            recarga = 0;
            getchar();

            break;

        case 6: 

            int clientIndex = findClientIndex(msjOpcSeis);

            char nuevoNip[8];
            while (1)
            {
                printf(msjOpcSeis, 162, 162);
                printf("Bienvenid%c %s\n", 64, clientes[clientIndex][NAME_INDEX]);

                printf("\nIngrese su nuevo NIP (4 n%cmeros exactos): ", 163);
                fgets(nuevoNip, sizeof(nuevoNip), stdin);
                rmvLinea(nuevoNip);
                system("cls");

                if (vrfSloNumeros(nuevoNip, msjErrRegistro, 4) == 1)
                {
                    char confirmacion;

                    printf(msjOpcSeis, 162, 162);
                    printf("%cEl nuevo NIP es correcto? (s/n): ", 168);
                    scanf(" %c", &confirmacion);
                    getchar();
                    system("cls");

                    if (tolower(confirmacion) == 's')
                    {
                        if (strcmp(clientes[clientIndex][NIP_INDEX], nuevoNip) == 0)
                        {
                            printf(msjOpcSeis, 162, 162);
                            printf("No se puede establecer un NIP igual al anterior, presione ENTER para reintentar.");
                            getchar();
                            system("cls");
                            continue;
                        }
                        else
                        {
                            strcpy(clientes[clientIndex][NIP_INDEX], nuevoNip);
                            printf(msjOpcSeis, 162, 162);
                            printf("NIP modificado exitosamente, presione ENTER para regresar al men%c principal.\n", 163);
                            getchar();
                            system("cls");
                            break;
                        }
                    }
                    else
                    {

                        printf(msjOpcSeis, 162, 162);
                        printf("Cambio cancelado con %cxito, presione ENTER para reintentar.\n", 130);
                        getchar();
                        system("cls");
                    }
                }
            }
            break;
        }

    } while (op < 7);

    system("cls");
    printf("Gracias por usar el Sistema Bancario, tenga un buen d%ca.  \n\n", 161);
    printf("           .--._.--.  \n");
    printf("          ( O     O )  \n");
    printf("          /   . .   %c   \n", 92);
    printf("         .`._______.'.  \n");
    printf("        /(           )%c   \n",92);
    printf("      _/  %c  %C   /  /  %c_  \n",92,92,92);
    printf("   .~   `  %c  %c /  /  '   ~.  \n",92,92);
    printf("  {    -.   %c  V  /   .-    }  \n",92);
    printf("_ _`.    %c  |  |  |  /    .'_ _  \n",92);
    printf(">_       _} |  |  | {_       _<  \n");
    printf(" /. - ~ ,_-'  .^.  `-_, ~ - .%c  \n",92);
    printf("         '-'|/   %c|`-`  \n\n",92);

    getchar();
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define mensajeContinuar "Informaci%cn guardada correctamente, presione ENTER para continuar. ", 162
#define MAX_CLIENTES 10
#define DATOS_SI_COINCIDEN 1
#define DATOS_NO_COINCIDEN -1
#define PHONE_INDEX 1
#define NIP_INDEX 3
#define NAME_INDEX 0

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
char msjErrClnInexistente[72] = "%cNo hay clientes registrados!, presione ENTER para regresar al men%c. ";

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
int vrfSloLetras (char string[], char msjError[]){
    int i;

    if(string[0] == '\0'){
        printf(msjError, 173, 162, 160);
        getchar();

        system("clear");
        return -1;
    }

    for (i = 0; string[i] != '\0'; i++){
        if (isdigit(string[i]) || ispunct(string[i]))
        {
            printf(msjError, 173, 162, 160);
            getchar();

            system("clear");
            return -1;
            break;
        }
    }
    return 1;
}

// función para verificar si la información dada son EXCLUSIVAMENTE números y de una longitud EXACTA
int vrfSloNumeros (char string[], char msjError[], int delimitador){
    int i;

    if (strlen(string) != delimitador){
        printf(msjError, 173, 162);
        getchar();

        system("clear");
        return -1;
    }

    for (i = 0; string[i] != '\0'; i++){
        if (isalpha(string[i]))
        {
            printf(msjError, 173, 162);
            getchar();

            system("clear");
            return -1;
            break;
        }
    }

    return 1;
}

// función para limpiar el salto de linea del fgets
void rmvLinea (char string[]){
    size_t lon = strlen(string);
    if (lon > 0 && string[lon - 1] == '\n') {
        string[lon - 1] = '\0';
    }
}

// función para que si a la hora de ingresar los datos (nombre y apellidos) se genera un error poder reintentar rellenar ese mismo campo
char* msjTxt (char res[], int res_size, char mensaje[], char msjError[], char msjOpcion[], int mstOpc){
    int t = 1;
    while (t == 1){
        if(mstOpc == 1){
            printf(msjOpcion, 162, 162);
        }
        printf(mensaje);
        fgets(res, res_size, stdin);

        rmvLinea(res);

        system("clear");

        if(vrfSloLetras(res, msjError) == 1){
            t = 0;
        }
    }
    return(res);
}

// función para que si a la hora de ingresar los datos (celular, tarjeta y nip) se genera un error poder reintentar rellenar ese mismo campo
char* msjNum (char res[], int res_size, char mensaje[], char msjError[], char msjOpcion[], int delimitador, int mstOpc){
    int t = 1;
    while (t == 1){
        if(mstOpc == 1){
            printf(msjOpcion, 162, 162);
        }
        printf(mensaje, 163, 163);
        fgets(res, res_size, stdin);

        rmvLinea(res);

        system("clear");

        if(vrfSloNumeros(res, msjError, delimitador) == 1){
            t = 0;
        }
    }
    return(res);
}

// función para verificar si existe un cliente registrado
int vrfExsCliente (){
    if(nombre[0] == '\0' && celular[0] == '\0' && numTarjeta[0] == '\0' && nip[0] == '\0'){
        printf(msjErrClnInexistente, 173, 163);
        getchar();

        system("clear");
        return -1;
    } else {
        return 1;
    }
}

// función para verificar si el celular y el nip coinciden con el el cleinte registrado
int vrfDtsCoincidan (char dtoUno[], int posDtoUno, char dtoDos[], int posDtoDos, char *nombreCliente, float *saldoCliente, int *cliente){
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i][posDtoUno], dtoUno) == 0 && strcmp(clientes[i][posDtoDos], dtoDos) == 0) {
            strcpy(nombreCliente, clientes[i][0]);
            *saldoCliente = (float)saldos[i];
            *cliente = i;
            return 1;
        }
    }
    return -1;
}

float requestAmountToSave(void) {
    char inputAmount[100];
    float deposit;
    
    printf("\nIngrese el monto a depositar: ");
    fgets(inputAmount, sizeof(inputAmount), stdin);
    rmvLinea(inputAmount);
    
    int isNum = 1;
    int dot = 0;

    for(int i = 0; inputAmount[i] != '\0';i++){
        if (!isdigit(inputAmount[i])) {  
            if (inputAmount[i] == '.' && !dot) {  
                dot = 1;
            } else {
                isNum = 0; 
                return -1;
            }
        }
    }
    
    if(isNum) {
        deposit = atof(inputAmount);

        if(deposit <= 0) {
            system("clear");
            printf(msjOpcDos);
            printf("El valor tiene que ser mayor a 0");
            getchar();
            system("clear");

            return -1;
        }
    } else {
        printf(msjErrRegistro);
        getchar();
        system("clear");
        
        return -1;
    }
    
    return deposit;
}

int increaceClientBalance()
{
    int clientIndex = findClientIndex();

    if (clientIndex == -1) {
        printf("No se encontro un cliente con los datos ingresados.");
        getchar();

        return -1;
    }
    showCurrentBalance(clientIndex);

    float amountToAdd = requestAmountToSave();
    
    addAmountToBalance(clientIndex, amountToAdd);

}

int findClientIndex() {
    char inputPhone[20];
    char inputNip[8];

    strcpy(inputPhone, msjNum(inputPhone, sizeof(inputPhone), msjRgsCelular, msjErrRegistro, msjOpcDos, 10, 1));
    strcpy(inputNip, msjNum(inputNip, sizeof(inputNip), msjRgsNip, msjErrRegistro, msjOpcDos, 4, 1));

    for (int i = 0; i < sizeof(clientes); i++) {
        if (strcmp(clientes[i][PHONE_INDEX], inputPhone) == 0 && strcmp(clientes[i][NIP_INDEX], inputNip) == 0) {
            return i;
        }
    }

    return -1;
}

void showCurrentBalance(int clientIndex) {
    float balance = saldos[clientIndex];
    char name[] = clientes[clientIndex][NAME_INDEX];
    
    printf(msjOpcDos);
    printf("Bienvenid@ %s\nTu saldo actual es: $%.2f\n", name, balance);
}

void addAmountToBalance(int clientIndex, float newAmount) {
    saldos[clientIndex] += newAmount;
}

int main (){

    int op;
    char check;
    float saldo;

    do{

        system("clear");
        printf("Bienvenido al Sitema Bancario, por favor seleccione la opci%cn deseada: \n----------------------------------------------------------------------\n\n", 162);

        printf("1. Registrar a un nuevo cliente\n2. Depositar dinero a cuenta propia\n3. Verificar saldo en tarjeta\n4. Transferir dinero a otras cuentas\n5. Recargar tiempo aire\n6. Cambiar NIP\n7. Salir\n\n");
        scanf("%i", &op);
        getchar();
        system("clear");

        switch (op)
        {
        case 1:

            if (numClientes >= MAX_CLIENTES){
                printf("Se ha alcanzado el número m%cximo de clientes.\n", 160);
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
            printf("Nombre: %s\n", nombre);
            printf("N%cmero celular: %s\n", 163, celular);
            printf("N%cmero de tarjeta: %s\n", 163, numTarjeta);
            printf("NIP: %s\n", nip);

            printf("Confirma tu informaci%cn (s/n): ",162);
            scanf(" %c", &check);

            if(check != 's'){
                system("clear");
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

            strcpy(clientes[numClientes][0], nombre);
            strcpy(clientes[numClientes][1], celular);
            strcpy(clientes[numClientes][2], numTarjeta);
            strcpy(clientes[numClientes][3], nip);
            saldos[numClientes] = saldo;

            numClientes++;

            system("clear");

            printf(mensajeContinuar);
            getchar();
            break;

        case 2:
        float deposit;
        char input[100];
        int isNum, dot;

        vrfExsCliente();
        int excl = vrfExsCliente();
        if(excl != 1){
            break;
        }

        while(1){
		strcpy(celular, msjNum(celular, sizeof(celular), msjRgsCelular, msjErrRegistro, msjOpcDos, 10, 1));
        strcpy(nip, msjNum(nip, sizeof(nip), msjRgsNip, msjErrRegistro, msjOpcDos, 4, 1));

        int itMatch = vrfDtsCoincidan(celular, 1, nip, 3, nombre, &saldo, &cliente);

        if (itMatch == 1) {
            printf(msjOpcDos);
            printf("Bienvenid@ %s\nTu saldo actual es: $%.2f\n", nombre, saldo);
            
            break;
            }else{
            printf(msjOpcDos);
            printf("\nLos datos ingresados no coinciden con ninguna cuenta");
            getchar();
            system("clear");

            continue;
            }
        }

        while(1){
            printf("\nIngrese el monto a depositar: ");
                fgets(input, sizeof(input), stdin);
                rmvLinea(input);

                isNum = 1;
                dot = 0;

            for(int i = 0; input[i] != '\0';i++){
                if (!isdigit(input[i])) {  
                    if (input[i] == '.' && !dot) {  
                        dot = 1;
                    } else {
                        isNum = 0; 
                        break;
                    }
                }
            }
            if(isNum){
                    deposit = atof(input);

                    if(deposit <= 0){
                        system("clear");
                        printf(msjOpcDos);
                        printf("El valor tiene que ser mayor a 0");
                        getchar();
                        system("clear");

                        continue;
                    }
                }else{
                    printf(msjErrRegistro);
                    getchar();
                    system("clear");
                    continue;
                }
            printf("\nEsta seguro que desea depositar $%.2f?  (s/n): ", deposit);
            scanf(" %c", &check);
            system("clear");

            if(check == 's' || check == 'S'){
                printf(msjOpcDos);
                printf("\nSu deposito fue realizado con exito.\n\nMonto depositado: $%.2f\n\nDepositado en la tarjeta: %s\n\n",deposit,numTarjeta );
                getchar();

                break;
            }else{
                printf(msjOpcDos);
                printf("Deposito cancelado.\n");
                getchar();
                system("clear");

                continue;
            }
        }

        saldo += deposit;
        saldos[cliente] =  saldo;

        printf(mensajeContinuar);
        getchar();
            break;

        case 3:

        vrfExsCliente();
        excl = vrfExsCliente();
        if(excl != 1){
            break;
        }

        while(1){
            strcpy(celular, msjNum(celular, sizeof(celular), msjRgsCelular, msjErrRegistro, msjOpcTres, 10, 1));
            strcpy(nip, msjNum(nip, sizeof(nip), msjRgsNip, msjErrRegistro, msjOpcTres, 4, 1));

            int itMatch = vrfDtsCoincidan(celular, 1, nip, 3, nombre, &saldo, &cliente);

        if (itMatch == 1) {
            printf(msjOpcTres);
            printf("Bienvenid@ %s\n\nTu saldo actual es: $%.2f\n", nombre, saldo);
            getchar();

            break;
        }else{
            printf(msjOpcTres);
            printf("\nLos datos ingresados no coinciden con ninguna cuenta.");
            getchar();
            system("clear");

            continue;
        }
        }

            break;
            
        case 4:
            
            break;

        case 5:
            
            break;

        case 6:

            break;
        }

    } while (op < 7);

    return 0;
}
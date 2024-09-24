#include <iostream>
#include <vector>
#include <bitset>
#include <iomanip>
#include <math.h>

using namespace std;

// Funcion q converte un nomero decimal a binario
void toBinary(int num, int *bin, int bitQnty) {
    for (int i = bitQnty - 1; i >= 0; i--) {
        bin[i] = num % 2;
        num = num / 2;
    }
}

// Funcion q imprime un arreglo binario
void printBinary(int *bin, int bitQnty) {
    for (int i = 0; i < bitQnty; i++) {
        cout << bin[i];
    }
}

// Funcion q calcula el complemento a 2 de un número
void plus1(int *bin, int bitQnty) {
    int carry = 1; // Empieza con 1 para sumar
    for (int i = bitQnty - 1; i >= 0; i--) {
        int sum = bin[i] + carry;
        bin[i] = sum % 2; // Resultado del bit
        carry = sum / 2;   // Carry para la próxima iteración
    }
}

// Funcion q suma dos numeros binarios
void plusAwithM(int *binA, int *binM, int bitQnty) {
    int carry = 0;
    for (int i = bitQnty - 1; i >= 0; i--) {
        int sum = binA[i] + binM[i] + carry;
        binA[i] = sum % 2;
        carry = sum / 2;
    }
}

// Funcion q realiza el corrimiento aritmético
void arithmeticShift(int *binA, int *binQ, int &Q1, int bitQnt) {
    Q1 = binQ[bitQnt - 1]; // Guardamos el último bit de Q
    for (int i = bitQnt - 1; i > 0; i--) {
        binQ[i] = binQ[i - 1]; // Desplazamos Q a la derecha
        binA[i] = binA[i - 1]; // Desplazamos A a la derecha
    }
    binQ[0] = binA[bitQnt - 1]; // El bit más significativo de A se coloca en Q0
}

// Funcion principal del algoritmo-Booth
void boothAlgorithm(int *binA, int *binQ, int *binM, int *binMinusM, int bitQnt) {
    int Q1 = 0; // Inicializa Q-1
    int count = bitQnt;

    cout << "\n" << setw(bitQnt + 2) << "A" << setw(bitQnt + 2) << "Q" << setw(5) << "Q-1" << setw(bitQnt + 2) << "M\n";
    cout << "-------------------------------------------------------\n";

    while (count != 0) {
        // Muestra el estado actual
        printBinary(binA, bitQnt);
        cout << "  ";
        printBinary(binQ, bitQnt);
        cout << setw(5) << Q1 << "  ";
        printBinary(binM, bitQnt);
        cout << "\n";

        // Verifica los bits Q-0 y Q-1
        if (Q1 == 0 && binQ[bitQnt - 1] == 1) {
            cout << "   A = A - M\n";
            plusAwithM(binA, binMinusM, bitQnt); // A = A - M
        } else if (Q1 == 1 && binQ[bitQnt - 1] == 0) {
            cout << "   A = A + M\n";
            plusAwithM(binA, binM, bitQnt); // A = A + M
        } else {
            cout << "   No se realiza suma\n";
        }

        cout << "   Corrimiento Aritmetico\n";
        arithmeticShift(binA, binQ, Q1, bitQnt); // Corrimiento aritmetico
        count--;
    }

    // Resultado final
    cout << "\nResultado: ";
    printBinary(binA, bitQnt);
    cout << " ";
    printBinary(binQ, bitQnt);
    cout << "\n";
}

int main() {
    int m, q, bitQnt;

    cout << "Ingresa una cantidad de bits a usar: ";
    cin >> bitQnt;

    int binaryM[bitQnt];
    int binaryMinusM[bitQnt];
    int binaryQ[bitQnt];
    int binaryA[bitQnt];

    // Inicializa A a 0
    fill(binaryA, binaryA + bitQnt, 0);

    cout << "Ingresa un multiplicando (M): ";
    cin >> m;
    cout << "Ingresa un multiplicador (Q): ";
    cin >> q;

    // Convertir a binario
    toBinary(m, binaryM, bitQnt);
    toBinary(q, binaryQ, bitQnt);

    // Calcular complemento a 2 de M
    copy(binaryM, binaryM + bitQnt, binaryMinusM);
    plus1(binaryMinusM, bitQnt);

    // Ejecutar el algoritmo de Booth
    boothAlgorithm(binaryA, binaryQ, binaryM, binaryMinusM, bitQnt);

    return 0;
}
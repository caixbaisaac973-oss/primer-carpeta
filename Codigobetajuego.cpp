#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <algorithm>
#include <limits>

using namespace std;

void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarAhorcado(int intentosFallidos) {
    cout << "\n";
    cout << "  +---+\n";
    cout << "  |   |\n";
    cout << "  " << (intentosFallidos >= 1 ? "O" : " ") << "   |\n";
    cout << " " << (intentosFallidos >= 3 ? "/" : " ") 
         << (intentosFallidos >= 2 ? "|" : " ") 
         << (intentosFallidos >= 4 ? "\\" : " ") << "  |\n";
    cout << " " << (intentosFallidos >= 5 ? "/" : " ") 
         << " " << (intentosFallidos >= 6 ? "\\" : " ") << "  |\n";
    cout << "      |\n";
    cout << "=========\n\n";
}

string aMayusculas(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

vector<string> obtenerCartasClashRoyale() {
    return {
        "CABALLERO", "ARQUERAS", "GOLEM", "PEKKA", "MINI PEKKA", 
        "GIGANTE", "MAGO", "BRUJA", "ESQUELETOS", "ESBIRROS", 
        "DUENDES", "MONTAPUERCOS", "VALQUIRIA", "GLOBO BOMBASTICO", "DRAGON INFERNAL", 
        "BEBE DRAGON", "PRINCIPE", "PRINCIPE OSCURO", "CHISPITAS", "LEÑADOR", 
        "TRONCO", "SABUESO DE LAVA", "MINERO", "MAGO DE HIELO", "MAGO ELECTRICO", 
        "ARQUERA MAGICA", "FENIX", "MEGACABALLERO", "BANDIDA", "FANTASMA REAL", 
        "PESCADOR", "BRUJA NOCTURNA", "BRUJA MADRE", "MONJE", "REY DUENDE", 
        "CAZADOR", "ESPIRITU DE HIELO", "ESPIRITU DE FUEGO", "ESPIRITU ELECTRICO", "ESPIRITU SANADOR", 
        "LANZAROCAS", "VERDUGO", "LANZAFUEGOS", "DUENDE LANZADARDOS", "CURANDERA GUERRERA", 
        "GUARDIA REAL", "PILLO", "BARBAROS", "BARBAROS DE ELITE", "CANONERO", 
        "MEGA ESBIRRO", "TORRE INFERNAL", "TORRE DE BOMBAS", "BALLESTA", "MORTERO", 
        "TESLA", "LAPIDA", "HORNO", "JAULA DEL DUENDE", "CHOZA DE DUENDES", 
        "CHOZA DE BARBAROS", "EXCAVADORA DE DUENDES", "BOLA DE FUEGO", "DESCARGA", "RAYO", 
        "COHETE", "VENENO", "HIELO", "CLON", "CURACION", "TORNADO", 
        "BARRIL DE DUENDES", "BARRIL DE BARBAROS", "BARRIL DE ESQUELETOS", "PAQUETE REAL", "BARRIL DE NIEVE"
    };
}

void jugar() {
    vector<string> cartas = obtenerCartasClashRoyale();
    
    int indice = rand() % cartas.size();
    string cartaOculta = aMayusculas(cartas[indice]);
    
    string progreso = "";
    for (char c : cartaOculta) {
        if (c == ' ') {
            progreso += ' ';
        } else {
            progreso += '_';
        }
    }

    int intentosFallidos = 0;
    const int maxIntentos = 6;
    vector<char> letrasUsadas;
    bool ganado = false;

    while (intentosFallidos < maxIntentos && !ganado) {
        limpiarPantalla();
        cout << "========================================" << endl;
        cout << "        AHORCADO - CLASH ROYALE          " << endl;
        cout << "========================================" << endl;
        
        mostrarAhorcado(intentosFallidos);

        cout << "Carta a adivinar: " << progreso << endl << endl;
        
        cout << "Letras probadas: ";
        for (char l : letrasUsadas) {
            cout << l << " ";
        }
        cout << endl;

        cout << "Intentos restantes: " << (maxIntentos - intentosFallidos) << endl;
        cout << "----------------------------------------" << endl;
        cout << "Ingresa una letra: ";

        char letraInput;
        cin >> letraInput;
        letraInput = toupper(letraInput);

        if (find(letrasUsadas.begin(), letrasUsadas.end(), letraInput) != letrasUsadas.end()) {
            cout << "\n¡Ya probaste esa letra! Presiona Enter para continuar...";
            limpiarBuffer();
            cin.get();
            continue;
        }

        letrasUsadas.push_back(letraInput);

        bool acierto = false;
        for (size_t i = 0; i < cartaOculta.length(); i++) {
            if (cartaOculta[i] == letraInput) {
                progreso[i] = letraInput;
                acierto = true;
            }
        }

        if (!acierto) {
            intentosFallidos++;
        }

        if (progreso == cartaOculta) {
            ganado = true;
        }
    }

    limpiarPantalla();
    mostrarAhorcado(intentosFallidos);

    if (ganado) {
        cout << "========================================" << endl;
        cout << "      ¡FELICIDADES! ¡HAS GANADO!        " << endl;
        cout << " La carta era: " << cartaOculta << endl;
        cout << "========================================" << endl;
    } else {
        cout << "========================================" << endl;
        cout << "              ¡HAS PERDIDO!             " << endl;
        cout << " La carta correcta era: " << cartaOculta << endl;
        cout << "========================================" << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    char opcion;

    do {
        jugar();
        cout << "\n¿Quieres jugar de nuevo? (S/N): ";
        cin >> opcion;
        limpiarBuffer(); // Limpia el salto de linea restante para evitar fallos en la siguiente partida
    } while (toupper(opcion) == 'S');

    cout << "\n¡Gracias por jugar!" << endl;
    return 0;
}

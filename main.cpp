#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <limits>
#include <cstdlib>
#include <ctime> 
using namespace std;

// Mapa para la Taxonomía de Bloom
map<int, string> TaxonomiaBloom = {
    {0, "Recordar"}, {1, "Entender"}, {2, "Aplicar"},
    {3, "Analizar"}, {4, "Evaluar"}, {5, "Crear"}
};

// Clase Pregunta
class Pregunta {
private:
    string enunciado;
    string respuesta;
    int nivel;
    int tiempo_estimado;

public:
    Pregunta(string enunciado, string respuesta, int nivel, int tiempo_estimado) {
        this->enunciado = enunciado;
        this->respuesta = respuesta;
        this->nivel = nivel;
        this->tiempo_estimado = tiempo_estimado;
    }
    ~Pregunta() {}

    // Getters
    int getNivel() const { return nivel; }
    int getTiempoEstimado() const { return tiempo_estimado; }
    string getEnunciado() const { return enunciado; }
    string getRespuesta() const { return respuesta; }
    // Setters
    void setEnunciado(string nuevoEnunciado) { enunciado = nuevoEnunciado; }
    void setRespuesta(string nuevaRespuesta) { respuesta = nuevaRespuesta; }
    void setTiempoEstimado(int nuevoTiempo) { tiempo_estimado = nuevoTiempo; }
    void setNivel(int nuevoNivel) { nivel = nuevoNivel; }

    // Método para mostrar la pregunta
    void mostrarPregunta() const {
        cout << "Enunciado: " << enunciado 
             << "\nNivel: " << TaxonomiaBloom[nivel] 
             << "\nTiempo estimado: " << tiempo_estimado << " min\n";
    }
};

// Clase Evaluacion
class Evaluacion {
private:
    vector<Pregunta> preguntas;
    string fecha;
public:
    Evaluacion(string fecha) : fecha(fecha) {}
    ~Evaluacion() {}

    void agregarPregunta(const Pregunta& pregunta) {
        preguntas.push_back(pregunta);
    }

    int calcularTiempoTotal() const {
        int total = 0;
        for (const auto& p : preguntas) {
            total += p.getTiempoEstimado();
        }
        return total;
    }

    void mostrarEvaluacion() const {
        cout << "Evaluación del " << fecha << "\n";
        int i = 1;
        for (const auto& p : preguntas) {
            cout << i << ". " << p.getEnunciado() << "\n";
            i++;
        }
        cout << "\nTiempo total estimado: " << calcularTiempoTotal() << " min\n";
    }
};


class SistemaEvaluacion {
private:
    vector<Pregunta> preguntas;
public:
    void agregarPregunta(const Pregunta& pregunta) {
        preguntas.push_back(pregunta);
    }

    void mostrar_EPreguntas() {
        int i;
        for (i=0; i < preguntas.size(); i++) {
            cout << i + 1 << ". " << preguntas[i].getEnunciado() << "\n";
        }
    }

    void modificarPregunta() {
        if (preguntas.empty()) {
            cout << "No hay preguntas disponibles.\n";
            return;
        }
        mostrar_EPreguntas();
        int indice;
        cout << "Seleccione el número de la pregunta a modificar: ";
        cin >> indice;
        cin.ignore();
        if (indice < 1 || indice > preguntas.size()) {
            cout << "Índice inválido.\n";
            return;
        }
        string nuevoEnunciado, nuevaRespuesta;
        int nuevoTiempo;
        cout << "Ingrese el nuevo enunciado: ";
        getline(cin, nuevoEnunciado);
        cout << "Ingrese la nueva respuesta: ";
        getline(cin, nuevaRespuesta);
        cout << "Ingrese el nuevo tiempo estimado: ";
        cin >> nuevoTiempo;
        cin.ignore();
        preguntas[indice - 1].setEnunciado(nuevoEnunciado);
        preguntas[indice - 1].setRespuesta(nuevaRespuesta);
        preguntas[indice - 1].setTiempoEstimado(nuevoTiempo);
        cout << "Pregunta modificada con éxito.\n";
    }

    void borrarPregunta() {
        if (preguntas.empty()) {
            cout << "No hay preguntas disponibles.\n";
            return;
        }
        mostrar_EPreguntas();
        int indice;
        cout << "Seleccione el número de la pregunta a borrar: ";
        cin >> indice;
        cin.ignore();
        if (indice < 1 || indice > preguntas.size()) {
            cout << "Índice inválido.\n";
            return;
        }

        preguntas.erase(preguntas.begin() + indice - 1);
        cout << "Pregunta eliminada con éxito.\n";
    }

    void mostrarPreguntasPorNivel(int nivel) {
        cout << "Preguntas del nivel " << TaxonomiaBloom[nivel] << " (" << nivel << ")\n";
        for (const auto& p : preguntas) {
            if (p.getNivel() == nivel) {
                p.mostrarPregunta();
            }
        }
    }

    void crearEvaluacion() {
        string fecha;
        cout << "Ingrese la fecha de la evaluación: ";
        getline(cin, fecha);
        Evaluacion nuevaEvaluacion(fecha);

        if (preguntas.empty()) {
            cout << "No hay preguntas en el banco para crear la evaluación.\n";
            return;
        }

        int numPreguntas, nivel;
        cout << "Ingrese la cantidad de preguntas: ";
        cin >> numPreguntas;
        cin.ignore();

        cout << "Ingrese el nivel de preguntas (0-5): ";
        cin >> nivel;
        cin.ignore();

        
        vector<Pregunta> preguntasFiltradas;
        for (const auto& p : preguntas) {
            if (p.getNivel() == nivel) {
                preguntasFiltradas.push_back(p);
            }
        }

        if (preguntasFiltradas.empty()) {
            cout << "No hay preguntas disponibles para el nivel seleccionado.\n";
            return;
        }

        if (numPreguntas <= preguntasFiltradas.size()) {
            for (int i = 0; i < numPreguntas; i++) {
                srand(static_cast<unsigned int>(time(0)));
                int indiceAleatorio = rand() % preguntasFiltradas.size();
                nuevaEvaluacion.agregarPregunta(preguntasFiltradas[indiceAleatorio]);
                preguntasFiltradas.erase(preguntasFiltradas.begin() + indiceAleatorio);
                indiceAleatorio=-1;
            }
            nuevaEvaluacion.mostrarEvaluacion();
        } else {
            cout << "No hay suficientes preguntas disponibles para el nivel seleccionado.\n" << endl;
        }}

       
};
bool validacion(int opcion){
    if (cin.fail() || (opcion < 1 || opcion > 6)) {
        // Si hubo un error en la entrada (es decir, no es un número entero)
        cin.clear(); // Limpiar el error de estado
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer
        return true;
    }
    return false;
}
void limpiar_pantalla(){
    cout << "\033[2J\033[H";
}


int main() {
    SistemaEvaluacion sistema;
    int opcion;
    do {
        cout << "\n=== Menú ===\n";
        cout << "1. Agregar Pregunta\n";
        cout << "2. Modificar Pregunta\n";
        cout << "3. Borrar Pregunta\n";
        cout << "4. Mostrar Preguntas por Nivel\n";
        cout << "5. Crear Evaluación\n";
        cout << "6. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;
        if(validacion(opcion)==true){
            limpiar_pantalla();
            cout<<"Ingrese un valor válido\n\n"<<endl;
            continue;
        }
        cin.ignore();
        switch (opcion) {
            case 1: { 
                string enunciado, respuesta; 
                int nivel, tiempo;
                cout << "Ingrese el enunciado: "; getline(cin, enunciado);
                cout << "Ingrese la respuesta: "; getline(cin, respuesta);
                cout << "Ingrese el nivel (0-5): "; cin >> nivel;
                cout << "Ingrese el tiempo estimado (min): "; cin >> tiempo;
                cin.ignore();
                sistema.agregarPregunta(Pregunta(enunciado, respuesta, nivel, tiempo));
                break; 
               
            }
            case 2: sistema.modificarPregunta(); break;
            case 3: sistema.borrarPregunta(); break;
            case 4: {
                int nivel; cout << "Ingrese el nivel (0-5): "; cin >> nivel;
                sistema.mostrarPreguntasPorNivel(nivel);
                break;
                
            }
            case 5: sistema.crearEvaluacion();break;
        }
    } while (opcion != 6); 
    return 0;
}
#include "server.h"
#include <thread>
#include <iostream>
#include <chrono>

int main() {
    try {
        Server server(8080);  // Crear el servidor en el puerto 8080

        // Crear un hilo para iniciar el servidor
        std::thread server_thread([&server]() {
            server.start();
        });

        // Realizar otras tareas en el hilo principal
        std::cout << "Servidor corriendo en el hilo secundario..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));  // Espera simulando otras tareas

        // Detener el servidor después de un tiempo
        server.stop();

        // Esperar a que el hilo del servidor termine
        if (server_thread.joinable()) server_thread.join();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Aplicación finalizada." << std::endl;
    return 0;
}

#include "server.h"
#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int port) : port(port), running(true) {
    // Crear el socket del servidor
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == 0) {
        throw std::runtime_error("Error al crear el socket.");
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Enlazar el socket a la dirección y puerto
    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Error en el bind.");
    }
}

void Server::handle_client(int client_socket) {
    char buffer[1024] = {0};
    while (true) {
        int bytes_read = read(client_socket, buffer, 1024);
        if (bytes_read <= 0) break; // Cliente cerró la conexión
        std::cout << "Mensaje recibido: " << buffer << std::endl;

        // Enviar respuesta al cliente
        const char* response = "Mensaje recibido";
        send(client_socket, response, strlen(response), 0);
        memset(buffer, 0, sizeof(buffer));
    }
    close(client_socket);
}

void Server::start() {
    if (listen(server_socket, 5) < 0) {
        throw std::runtime_error("Error en el listen.");
    }
    std::cout << "Servidor escuchando en el puerto " << port << std::endl;

    std::vector<std::thread> client_threads;
    while (running) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            std::cerr << "Error al aceptar conexión." << std::endl;
            continue;
        }

        // Crear un hilo para cada cliente
        client_threads.emplace_back(&Server::handle_client, this, client_socket);
    }

    // Esperar a que todos los hilos terminen
    for (auto& th : client_threads) {
        if (th.joinable()) th.join();
    }

    close(server_socket);
}

void Server::stop() {
    running = false; // Cambia la bandera para detener el bucle de aceptación de conexiones
    close(server_socket);
    std::cout << "Servidor detenido." << std::endl;
}

#ifndef SERVER_H
#define SERVER_H

class Server {
public:
    Server(int port);
    void start();  // Inicia el servidor y maneja conexiones
    void stop();   // Detiene el servidor
private:
    int server_socket;
    int port;
    bool running;  // Bandera para controlar el bucle del servidor
    void handle_client(int client_socket);  // Función para manejar cada cliente
};

#endif
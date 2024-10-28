MyServerApp

Este ejemplo lanza un Socket desde el main Thread.
Esta estructura es útil si necesitas que el main thread o hilo principal gestione otras 
tareas mientras el servidor se ejecuta de manera concurrente en su propio hilo.

   ```
   /project
   ├── main.cpp          # Punto de entrada de la aplicación, lanza el hilo del servidor
   ├── server.h          # Declaración del servidor
   ├── server.cpp        # Implementación del servidor y manejo de sockets
   └── CMakeLists.txt    # Archivo para compilar con CMake
   ```

Explicación
Lanzamiento del servidor en un hilo: El servidor se lanza desde main en un hilo separado (server_thread), 
lo cual permite que main pueda ejecutar otras tareas en paralelo. En este caso, simulamos una pausa de 10 segundos 
para representar otras operaciones.

Control de ejecución y parada: La función Server::stop() cambia la bandera running a false, 
lo que hace que el bucle en start() finalice. Esto detiene el servidor de manera segura antes de que se cierre el programa.

Sincronización con join(): Usamos server_thread.join() en el hilo principal para asegurarnos de que 
el hilo del servidor se cierre correctamente antes de que termine main.

Este enfoque es modular y permite realizar otras tareas en el hilo principal mientras el servidor está corriendo. 
También es fácil de extender, por ejemplo, para agregar una interfaz de usuario o una consola de administración en el hilo principal.
#include <arpa/inet.h>
#include <sys/socket.h>

#include <iostream>
#include <string>

using namespace std;
class ConexionCliente
{
public:
    ConexionCliente(string IPServidor, int puerto);
    void mostrarEstadoConexion();

    void enviarMensaje(string mensaje);
    void recibirMensaje();
    void cerrarConexion();

private:
    /*  IPServidor deberia ser char[] pero string facilita algunas cosas
        la otra opcion era crear un char de tamano fijo
        o una estructura que contenga un char de tamano variable
        ya que no es lo mismo por ejemplo 192.168.0.1 que 127.0.0.1
    */
    string IPServidor;
    int puerto;
    int status;
    int valread;
    int client_fd;
    const int TAMANO_BUFFER = 1024;
    struct sockaddr_in serv_addr;

    char *getIPFormateada();
    void verificarClienteFD(int client_fd);
    void configurarServidor();
    void configurarCliente();
    void configurarEstado();
    void validarConexion();
};

ConexionCliente::ConexionCliente(string IPServidor, int puerto)
{
    this->IPServidor = IPServidor;
    this->puerto = puerto;

    cout << IPServidor << endl;
    cout << puerto << endl;
    configurarServidor();
    configurarCliente();
    configurarEstado();
    validarConexion();
}

char *ConexionCliente::getIPFormateada()
{
    return this->IPServidor.data();
}

void ConexionCliente::mostrarEstadoConexion()
{
    cout << "IP: " << this->IPServidor << endl;
    cout << "Puerto: " << this->puerto << endl;
    cout << "Client_fd: " << this->client_fd << endl;
    cout << "Status: " << this->status << endl;
    cout << "Valread: " << this->valread << endl;
}

void ConexionCliente::configurarServidor()
{
    this->serv_addr.sin_family = AF_INET;
    this->serv_addr.sin_port = htons(this->puerto);
}

void ConexionCliente::configurarCliente()
{
    this->client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->client_fd < 0)
    {
        cout << "ERROR: Falla al crear el socket" << endl;
        exit(1);
    }
}

void ConexionCliente::configurarEstado()
{
    this->status = connect(this->client_fd, (struct sockaddr *)&this->serv_addr, sizeof(this->serv_addr));
    if (this->status < 0)
    {
        cout << "Error: Conexion fallida" << endl;
        exit(1);
    }
}

void ConexionCliente::validarConexion()
{
    if (inet_pton(AF_INET, IPServidor.data(), &serv_addr.sin_addr) <= 0)
    {
        cout << "Error: Direccion invalida o no soportada" << endl;
        exit(1);
    }
}

void ConexionCliente::enviarMensaje(string mensaje)
{
    send(this->client_fd, mensaje.data(), mensaje.length(), 0);
    this->recibirMensaje();
}

void ConexionCliente::recibirMensaje()
{
    char buffer[TAMANO_BUFFER] = {0};
    this->valread = read(this->client_fd, buffer, TAMANO_BUFFER);
    cout << buffer << endl;
}

void ConexionCliente::cerrarConexion()
{
    close(this->client_fd);
}
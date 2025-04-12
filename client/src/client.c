#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger(); //Por lo que entiendo aca iniciamos un puntero a un log

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	logger = log_create("logs/cliente.log","Probando un log", true, LOG_LEVEL_INFO); //Y aca a ese puntero creado le estamos asignando un log
	
	if(logger == NULL){
		printf("No se pudo crear el logger");
		abort();
	}
	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config(); //Iniciamos un puntero a un config

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	config = config_create("cliente.config"); //Aca le asignamos un config

	if(config == NULL){
		printf("No se pudo crear el config");
		abort();
	}

	valor = config_get_string_value(config, "CLAVE");
	// Loggeamos el valor de config
	log_info(logger, valor); 

	ip = config_get_string_value(config, "IP");
	log_info(logger, ip); 

	puerto = config_get_string_value(config, "PUERTO");
	log_info(logger, puerto); 

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);
	log_destroy(logger); //Aca destruimos ese log.

	config_destroy(config);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	send(conexion, valor, strlen(valor)+1 ,0);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	while(strcmp(leido, "")){
		log_info(logger, leido);
		leido = readline("> ");
	
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	}

	// ¡No te olvides de liberar las lineas antes de regresar!
	free(leido);

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	t_log* logger;
	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger(); //Por lo que entiendo aca iniciamos un puntero a un log

	logger = log_create("logs/cliente.log","Probando un log", true, LOG_LEVEL_INFO); //Y aca a ese puntero creado le estamos asignando un log
	
	if(logger == NULL){
		printf("No se pudo crear el logger");
		abort();
	}

	paquete = crear_paquete();
	
	//Aca vamos a leer de consola y mandarselo a agregar_a_paquete para que lo vaya cargando
	leido = readline("> ");

	while(strcmp(leido, "")){
		log_info(logger, leido);
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		leido = readline("> ");
	}

	enviar_paquete(paquete, conexion);
	free(leido);
	free(paquete);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	  free(logger);
	  free(config);
	  liberar_conexion(conexion);
}

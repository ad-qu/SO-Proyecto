//#include <my_global.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	
	MYSQL *conn;
	int err;
	
	// Estructura especial para almacenar resultados de consultas 
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	
	//Creamos una conexion al servidor MYSQL 
	conn = mysql_init(NULL);
	if (conn==NULL) {
		printf ("Error al crear la conexion: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	//Inicializar la conexion
	conn = mysql_real_connect (conn, "localhost","root", "mysql", "juego" , 0, NULL, 0);
	if (conn==NULL) {
		printf ("Error al inicializar la conexion: %u %s\n", 
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	char usuario[16], contra[16];
	char consulta[80];
	char *p;
	
	printf ("Buenas, vamos a proceder a registrarnos.\nEscribe el usuario y la contrasena separados por un espacio.\n");
	
	gets(consulta);
	
	p = strtok(consulta, " ");
	
	strcpy(usuario,p);
	
	while (p != NULL)
	{
		strcpy(contra, p);
		p = strtok(NULL," ");
	}
	
	sprintf (consulta, "INSERT INTO jugador(usuario, contrasena) VALUES('%s', '%s')", usuario, contra);

	err = mysql_query (conn, consulta);
	if (err!=0) {
		printf ("Error al registrarse. %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	
	mysql_close (conn);
	exit(0);
}

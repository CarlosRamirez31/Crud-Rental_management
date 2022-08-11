#include <conio.h>
#include <fstream>
#include <string>
using namespace std;

struct Contrato{
	char proNombre[20], proApellido[20], proCedula[20], inNombre[20], inApellido[20], agNombre[20];
	char inCedula[20], inNumero[20];
	int fDia, fMes, fAnios;
}contratos;

struct Alquileres{
	char agNombre[20], inNombre[20], inTelefono[15] , inCedula[20], vProvincia[20], vMunicipio[20];
	char vCalle[20], proCedula[20];
	int piso, iDia, iMes, iAnio;
}alquiler;  

struct Agencia{
	char codigo[10], direccion[30], rnc[10], nombre[20];
}agencia;

struct Inquilino{
	char cedula[20], nombre[20], apellido[20], telefono[20], descripcion[40];
	char firma[10];
	int nDia, nMes, nAnios;
	int mImporte;
}inquilino;

struct Propietario{
	char cedula[20], nombre[20], apellido[20], telefono[20], direccion[20], gmail[20];
	int viviendas;
}propietario;

struct Vivienda{
	char calle[30], numero[10] = "", provincia[30], municipio[30], descripcion[40], cPropietario[20] = "";
	int piso;
}vivienda; 

void controlAcceso();
void menu();
void menuInquilino();
void crearInquilino(ofstream &);
void listaInquilino(ifstream &);
void modificarInquilino(ifstream &);
void eliminarInquilino(ifstream &);

void alquilarVivienda(ofstream &);
void busquedaInquilino(ifstream &);
void busquedaAgencia(ifstream &);
void asignacion(Contrato);
bool firma(int, int, int, int, int, int);

void menuVivienda();
void crearVivienda(ofstream &);
void listaVivienda(ifstream &);
void modificarVivienda(ifstream &);
void eliminarVivienda(ifstream &);

void menuPropietario();
void crearPropietario(ofstream &);
bool verificarCedula(char []);
void formatoCedula(char []);
void formatoTelefono(char tel[]);
void listaPropietario(ifstream &);
void modificarPropietario(ifstream &);
void eliminarPropietario(ifstream &);

void menuAlquileres();
void crearAlquiler(ofstream &);
void listaAlquiler(ifstream &);
void modificarAlquiler(ifstream &);
void eliminarAlquiler(ifstream &);

void menuContrato();
void renovarContrato(ofstream &);
void eliminarContratoV(ifstream &, char[]);
void listaContrato(ifstream &);
void eliminarContrato(ifstream &);
void alquilerContrato(ifstream &, char[]);

void menuAgencia();
void crearAgencia(ofstream &);
void listaAgencia(ifstream &);
void modificarAgencia(ifstream &);
void eliminarAgencia(ifstream &);

ofstream escribir;
ifstream ver;
int opcion;
char rpt;
bool band = false, band2 = false;

void controlAcceso(){
	string nombre, contra;
	char letra;
	
	do{
		cout << "\tControl de Acceso" << endl;
		cout << "Digite su nombre: "; getline(cin, nombre);
		cout << "Digite la contrasena: "; 
		
		letra = getch();
		contra = "";
		while(letra != 13){
			if(letra!=8){
				contra.push_back(letra);
				cout << "*";
			}
			else{
				if(contra.length() > 0){
					cout << "\b \b";
					contra = contra.substr(0,contra.length() -1);
				}
			}
			letra = getch();
		}
		
		if((nombre == "12") && (contra == "12")){
			system("cls");
			menu();
		}
		else{
			cout << "\nEl usuario y la contrasena es incorrecto " << endl;
			system("pause");
		}
		system("cls");
	}
	while((nombre != "12") || (contra != "12"));
}

void menu(){
	do{
		cout << "Gestion de alquileres" << endl;
		cout << "1. Alquilar una vivienda" << endl;
		cout << "2. CRUD Agencias" << endl;
		cout << "3. CRUD Viviendas" << endl;
		cout << "4. CRUD Propietarios" << endl;
		cout << "5. CRUD Alquileres" << endl;
		cout << "6. CRUD Inquilinos" << endl;
		cout << "7. GRUD Contratos" << endl;
		cout << "8. Salir" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				alquilarVivienda(escribir); break;
			case 2:
				menuAgencia(); break;
			case 3:
				menuVivienda(); break;
			case 4:
				menuPropietario(); break;
			case 5:
				menuAlquileres(); break;
			case 6:
				menuInquilino(); break;
			case 7:
				menuContrato(); break;
			case 8:
				cout << "Gracias por utilizar el menu" << endl;
		}
		system("cls");
	}
	while(opcion != 7);
}

void alquilarVivienda(ofstream &escribir){
	ifstream in;
	ofstream creacion, cont;
	char inCedula[20], agCodigo[15];
	int iDia, iMes, iAnios, fDia, fMes, fAnios;
	
	
	escribir.open("Alquileres.dat", ios::out | ios::binary | ios::app);
	cont.open("Contrato.dat", ios::out | ios::binary | ios::app);
	
	if(escribir.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(cont.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	band = false;
	while(band == false){
		
		system("cls");
		fflush(stdin);
		cout << "Exite alguna persona registra que desea alquilar una casa(s/n)? "; cin >> rpt;
		cout << "\n";
		
		if((rpt == 'S') || (rpt == 's')){
			band = true;
			busquedaInquilino(in);
			
			if(band2 == true){
				cout << "Fecha limite de firma:" << endl;
				cout << "Dia: "; cin >> fDia;
				cout << "Mes: "; cin >> fMes;
				cout << "Anio: "; cin >> fAnios;
				system("cls");
				
				cout << "\n\t\tContrato\n\n";
				cout << "-------------------------------------------------------" << endl;
				cout << "\tNombre de la agencia: " << contratos.agNombre << endl;
				cout << "\tNombre del inquilino: " << contratos.inNombre << endl;
				cout << "\tCedula del inquilino: " << contratos.inCedula << endl;
				cout << "\tNumero telefonico del inquilino: " << contratos.inNumero << endl;
				cout << "-------------------------------------------------------" << endl;
				cout << "\tNombre de propietario: " << contratos.proNombre<< endl;
				cout << "\tApellido del propietario: " << contratos.proApellido << endl;
				cout << "\tCedula del propietario: " << contratos.proCedula << endl;
				cout << "-------------------------------------------------------" << endl;
				
				cout << "\n\tQuiere firma el contrato(s/n)? "; cin >> rpt;
				
				if((rpt == 'S') || (rpt == 's')){
				
					cout << "\n\nFecha actual de cuando firmo:" << endl;
					cout << "Dia: "; cin >> iDia;
					cout << "Mes: "; cin >> iMes;
					cout << "Anio: "; cin >> iAnios;
					
					contratos.fDia = fDia;
					contratos.fMes = fMes;
					contratos.fAnios = fAnios;
					
					if(firma(fDia, fMes, fAnios, iDia, iMes, iAnios)){
						escribir.write((char*)&alquiler,sizeof(Alquileres));
						cont.write((char*)&contratos,sizeof(Contrato));
					}
					else{
						cout << "\nLo sentimo, la fecha de firma limite se ha terminado." << endl;
						system("pause");
					}
				}
			}
		}
		else{
			crearInquilino(creacion);
		}
	}
	
	escribir.close();
	cont.close();
}

void busquedaInquilino(ifstream &ver){
	char aux[15];
	
	cout << "\tLista de inquilinos Disponibles\n\n";
	listaInquilino(ver);
	
	ver.open("Inquilinos.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	
	fflush(stdin);
	cout << "Digite la cedula del inquilino: "; cin.getline(aux,15,'\n');
	formatoCedula(aux);
	while(!ver.eof()){
		ver.read((char*)&inquilino,sizeof(Inquilino));
		if(!ver.eof()){
			if(strcmp(aux,inquilino.cedula) == 0){
				strcpy(alquiler.inNombre,inquilino.nombre);
				strcpy(alquiler.inCedula,inquilino.cedula);
				strcpy(alquiler.inTelefono,inquilino.telefono);
				strcpy(contratos.inNombre,inquilino.apellido);
				strcpy(contratos.inApellido,inquilino.apellido);
				strcpy(contratos.inCedula,inquilino.cedula);
				strcpy(contratos.inNumero,inquilino.telefono);
				band2 = true;
			}	
		}
	}
	
	if(band2 == false){
		cout << "No se encontro ningun inquilino con ese numero de cedula" << endl;
		system("pause");
		return;
	}
	band2 = false;
	
	ver.close();
	system("cls");	

	cout << "\tLista de vivienda\n\n";
	listaVivienda(ver);
	
	ver.open("Vivienda.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite el numero de cedula de dueno de la vivienda: "; cin.getline(aux,15,'\n');
	formatoCedula(aux);
	while(!ver.eof()){
		ver.read((char*)&vivienda,sizeof(Vivienda));
		if(!ver.eof()){
			if(strcmp(aux,vivienda.cPropietario) == 0){
				strcpy(alquiler.vProvincia,vivienda.provincia);
				strcpy(alquiler.vMunicipio,vivienda.municipio);
				strcpy(alquiler.vCalle,vivienda.calle);
				alquiler.piso = vivienda.piso;
				band2 = true;	
			}	
		}
	}
	
	if(band2 == false){
		cout << "No se ha encontrado ninguna casa con ese numero de referencia" << endl;
		system("pause");
		return;
	}
	band2 = false;
	
	ver.close();
	system("cls");
	
	ver.open("Propietario.dat", ios::in	| ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se puedo abrir" << endl;
	}

	while(!ver.eof()){
		ver.read((char*)&propietario,sizeof(Propietario));
		if(!ver.eof()){
			if(strcmp(aux,propietario.cedula) == 0){
				strcpy(contratos.proNombre,propietario.nombre);
				strcpy(contratos.proApellido,propietario.apellido);
				strcpy(contratos.proCedula,propietario.cedula);
				strcpy(alquiler.proCedula,propietario.cedula);
				band2 = true;	
			}	
		}
	}
	
	if(band2 == false){
		cout << "No se ha encontrado ningun propietario con ese numero de cedula" << endl;
		system("pause");
		return;
	}
	band2 = false;
	
	ver.close();
		
	cout << "\tLista de agencia Disponibles\n\n";
	listaAgencia(ver);
	
	ver.open("Agencias.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite el codigo de la agencia: "; cin.getline(aux,15,'\n');
	while(!ver.eof()){
		ver.read((char*)&agencia,sizeof(Agencia));
		if(!ver.eof()){
			if(strcmp(aux,agencia.codigo) == 0){
				strcpy(alquiler.agNombre,agencia.nombre);
				band2 = true;
			}	
		}
	}
	
	if(band2 == false){
		cout << "No se encontro ningun inquilino con ese numero de cedula" << endl;
		system("pause");
		return;
	}
	
	ver.close();
	system("cls");
}

bool firma(int fDia, int fMes, int fAnio, int iDia, int iMes, int iAnio){
	if(fAnio > iAnio){
		return true;
	}
	else if(fAnio == iAnio){
		if(fMes > iMes){
			return true;
		}
		else if(fMes == iMes){
			return (fDia >= iDia)? true : false;
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}
}

void busquedaAgencia(ifstream &ver){
	bool band = false;
	char agCodigo[15];
	
	cout << "\tLista de agencia Disponibles\n\n";
	listaAgencia(ver);
	
	ver.open("Agencias.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	cout << "Digite el codigo de la agencia: "; cin.getline(agCodigo,15,'\n');
	while((!ver.eof()) && (band == false)){
		ver.read((char*)&agencia,sizeof(Agencia));
		if(!ver.eof()){
			if(strcmp(agCodigo,agencia.codigo)){
				band = true;	
			}	
		}
	}
	
	ver.close();
}

void menuInquilino(){
	do{
		cout << "\tBienvenido al menu de inquilinos" << endl;
		cout << "1. Crear" << endl;
		cout << "2. Listar" << endl;
		cout << "3. Modificar" << endl;
		cout << "4. Eliminar" << endl;
		cout << "5. Salir" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				crearInquilino(escribir); break;
			case 2:
				listaInquilino(ver); break;
			case 3:
				modificarInquilino(ver); break;
			case 4:
				eliminarInquilino(ver); break;
			case 5:
				cout << "Saliendo del menu de inquilino..." << endl;
		}
		system("pause");
		system("cls");
	}
	while(opcion != 5);
}

void crearInquilino(ofstream &escribir){
	escribir.open("Inquilinos.dat", ios::out | ios::binary | ios::app);
	
	if(escribir.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite el nombre: "; cin.getline(inquilino.nombre,20,'\n');
	cout << "Digite su apellido: "; cin.getline(inquilino.apellido,20,'\n');
	cout << "Digite su numero de telefono: "; cin.getline(inquilino.telefono,20,'\n');
	formatoTelefono(inquilino.telefono);
	do{
		cout << "Digite su cedula: "; cin.getline(inquilino.cedula,20,'\n');
	}
	while(verificarCedula(inquilino.cedula));
	formatoCedula(inquilino.cedula);
	cout << "Digite su fecha de nacimiento: " << endl;
	cout << "Dia: "; cin >> inquilino.nDia;
	cout << "Mes: "; cin >> inquilino.nMes;
	cout << "anio:"; cin >> inquilino.nAnios;
	fflush(stdin);
	cout << "Digite un breve descripcion: "; cin.getline(inquilino.descripcion,40,'\n');
		
	escribir.write((char*)&inquilino,sizeof(Inquilino));
		
	escribir.close();
}

void listaInquilino(ifstream &ver){
	ver.open("Inquilinos.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	while(!ver.eof()){
		ver.read((char*)&inquilino,sizeof(Inquilino));
		if(!ver.eof()){
			cout << "Nombre: " << inquilino.nombre << endl;
			cout << "Apellido: " << inquilino.apellido << endl;
			cout << "Numero de telefono: " << inquilino.telefono << endl;
			cout << "Cedula: " << inquilino.cedula << endl;
			cout << "Fecha de nacimiento: " << inquilino.nDia << "/" << inquilino.nMes <<
			"/" << inquilino.nAnios << endl;
			cout << "Descripcion: " << inquilino.descripcion << endl;
			cout << "\n";
		}
	}
	
	ver.close();
}

void modificarInquilino(ifstream &ver){
	char cAux[10];
	ofstream modificar;
	
	ver.open("Inquilinos.dat", ios::in | ios::binary);
	modificar.open("modificar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(modificar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la cedula del inquilino: "; cin.getline(cAux,10,'\n');
	formatoCedula(cAux);
	
	while(!ver.eof()){
		ver.read((char*)&inquilino,sizeof(Inquilino));
		
		if(!ver.eof()){
			if(strcmp(cAux,inquilino.cedula) == 0){
				fflush(stdin);
				cout << "Digite el nombre: "; cin.getline(inquilino.nombre,20,'\n');
				cout << "Digite su apellido: "; cin.getline(inquilino.apellido,20,'\n');
				cout << "Digite su numero de telefono: "; cin.getline(inquilino.telefono,20,'\n');
				formatoTelefono(inquilino.telefono);
				cout << "Cedula: " << inquilino.cedula << endl;
				cout << "Digite su fecha de nacimiento: " << endl;
				cout << "Dia: "; cin >> inquilino.nDia;
				cout << "Mes: "; cin >> inquilino.nMes;
				cout << "anio:"; cin >> inquilino.nAnios;
				fflush(stdin);
				cout << "Digite un breve descripcion: "; cin.getline(inquilino.descripcion,40,'\n');
				modificar.write((char*)&inquilino,sizeof(Inquilino));
				cout << "\n";	
			}
			else{
				modificar.write((char*)&inquilino,sizeof(Inquilino));
			}	
		}
	}
	
	ver.close();
	modificar.close();
	
	remove("Inquilinos.dat");
	rename("modificar.dat","Inquilinos.dat");
}

void eliminarInquilino(ifstream &ver){
	char cAux[10];
	ofstream eliminar;
	
	ver.open("Inquilinos.dat", ios::in | ios::binary);
	eliminar.open("modificar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(eliminar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la cedula del inquilino: "; cin.getline(cAux,10,'\n');
	formatoCedula(cAux);
	
	while(!ver.eof()){
		ver.read((char*)&inquilino,sizeof(Inquilino));
		
		if(!ver.eof()){
			if(strcmp(cAux,inquilino.cedula) == 0){
				cout << "\tInquilino eliminado." << endl;
			}
			else{
				eliminar.write((char*)&inquilino,sizeof(Inquilino));
			}	
		}
	}
	
	ver.close();
	eliminar.close();
	
	remove("Inquilinos.dat");
	rename("modificar.dat","Inquilinos.dat");
}

void menuVivienda(){
	do{
		cout << "\tBienvenido al menu de viviendas" << endl;
		cout << "1. Crear" << endl;
		cout << "2. Listar" << endl;
		cout << "3. Modificar" << endl;
		cout << "4. Eliminar" << endl;
		cout << "5. Salir" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				crearVivienda(escribir); break;
			case 2:
				listaVivienda(ver); break;
			case 3:
				modificarVivienda(ver); break;
			case 4:
				eliminarVivienda(ver); break;
			case 5:
				cout << "Saliendo del menu de viviendas..." << endl;
		}
		system("pause");
		system("cls");
	}
	while(opcion != 5);
}

void crearVivienda(ofstream &escribir){
	ofstream propietarios;
	escribir.open("Vivienda.dat", ios::out | ios::binary | ios::app);
	
	if(escribir.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la provincia: "; cin.getline(vivienda.provincia,30,'\n');
	cout << "Digite el municipio: "; cin.getline(vivienda.municipio,30,'\n');
	cout << "Digite la calle: "; cin.getline(vivienda.calle,30,'\n');
	cout << "Digite el numero de la casa: "; cin.getline(vivienda.numero,10,'\n');
	cout << "Digite el piso: "; cin >> vivienda.piso;
	fflush(stdin);
	cout << "Descripcion de la vivienda: "; cin.getline(vivienda.descripcion,30,'\n');
		
	if(strcmp(vivienda.cPropietario,"") == 0){
		cout << "\n\tRegistrando propietario" << endl;
		crearPropietario(propietarios);
		escribir.write((char*)&vivienda,sizeof(Vivienda));
	}	
	else{
		escribir.write((char*)&vivienda,sizeof(Vivienda));
	}
	
	escribir.close();
}

void listaVivienda(ifstream &ver){
	ver.open("Vivienda.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	while(!ver.eof()){
		ver.read((char*)&vivienda,sizeof(Vivienda));
		if(!ver.eof()){
			cout << "Provincia: " << vivienda.provincia << endl;
			cout << "Municipio: " << vivienda.municipio << endl;
			cout << "Calle: " << vivienda.calle << endl;
			cout << "Numero de casa: " << vivienda.numero << endl;
			cout << "Piso: " << vivienda.piso << endl;
			cout << "Descripcion: " << vivienda.descripcion << endl;
			cout << "Cedula propietario: " << vivienda.cPropietario << endl;
			cout << "\n";
		}
	}
	
	ver.close();
}

void modificarVivienda(ifstream &ver){
	char cAux[15];
	ofstream modificar;
	
	ver.open("Vivienda.dat", ios::in | ios::binary);
	modificar.open("modificar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(modificar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la cedula del propietario: "; cin.getline(cAux,15,'\n');
	formatoCedula(cAux);
	
	while(!ver.eof()){
		ver.read((char*)&vivienda,sizeof(Vivienda));
		
		if(!ver.eof()){
			if(strcmp(cAux,vivienda.cPropietario) == 0){
				fflush(stdin);
				cout << "Digite la provincia: "; cin.getline(vivienda.provincia,30,'\n');
				cout << "Digite el municipio: "; cin.getline(vivienda.municipio,30,'\n');
				cout << "Digite la calle: "; cin.getline(vivienda.calle,30,'\n');
				cout << "Digite el numero de la casa: "; cin.getline(vivienda.numero,10,'\n');
				fflush(stdin);
				cout << "Digite el piso: "; cin >> vivienda.piso;
				cout << "Descripcion de la vivienda: "; cin.getline(vivienda.descripcion,30,'\n');
				modificar.write((char*)&vivienda,sizeof(Vivienda));
				cout << "\n";	
			}
			else{
				modificar.write((char*)&vivienda,sizeof(Vivienda));
			}	
		}
	}
	
	ver.close();
	modificar.close();
	
	remove("Vivienda.dat");
	rename("modificar.dat","Vivienda.dat");
}

void eliminarVivienda(ifstream &ver){
	char cAux[15];
	ofstream eliminar;
	
	ver.open("Vivienda.dat", ios::in | ios::binary);
	eliminar.open("eliminar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(eliminar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la cedula del propietario: "; cin.getline(cAux,15,'\n');
	formatoCedula(cAux);
	
	while(!ver.eof()){
		ver.read((char*)&vivienda,sizeof(Vivienda));
		
		if(!ver.eof()){
			if(strcmp(cAux,vivienda.cPropietario) == 0){
				cout << "\tLa vivienda ha sido eliminada con exito" << endl;
			}
			else{
				eliminar.write((char*)&vivienda,sizeof(Vivienda));
			}	
		}
	}
	
	ver.close();
	eliminar.close();
	
	remove("Vivienda.dat");
	rename("eliminar.dat","Vivienda.dat");
}

void menuPropietario(){
	do{
		cout << "\tBienvenido al menu de Propietarios" << endl;
		cout << "1. Crear" << endl;
		cout << "2. Listar" << endl;
		cout << "3. Modificar" << endl;
		cout << "4. Eliminar" << endl;
		cout << "5. Salir" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				crearPropietario(escribir); break;
			case 2:
				listaPropietario(ver); break;
			case 3:
				modificarPropietario(ver); break;
			case 4:
				eliminarPropietario(ver); break;
			case 5:
				cout << "Saliendo del menu de Propietarios..." << endl;
		}
		system("pause");
		system("cls");
	}
	while(opcion != 5);
}

void crearPropietario(ofstream &escribir){
	ofstream viviendas;
	escribir.open("Propietario.dat", ios::out | ios::binary | ios::app);
	
	if(escribir.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite su nombre: "; cin.getline(propietario.nombre,20,'\n');
	cout << "Digite su apellido: "; cin.getline(propietario.apellido,20,'\n');
	do{
		cout << "Digite su cedula: "; cin.getline(propietario.cedula,20,'\n');
	}
	while(verificarCedula(propietario.cedula));
	formatoCedula(propietario.cedula);
	cout << "Digite su numero de telefono: "; cin.getline(propietario.telefono,20,'\n');
	formatoTelefono(propietario.telefono);
	cout << "Digite su direccion: "; cin.getline(propietario.direccion,20,'\n');
	cout << "Digite su Gmail: "; cin.getline(propietario.gmail,20,'\n');
	strcpy(vivienda.cPropietario,propietario.cedula);
	escribir.write((char*)&propietario,sizeof(Propietario));
		
	if(strcmp(vivienda.numero,"") == 0){
		cout << "\n\tRegistrando vivienda" << endl;
		crearVivienda(viviendas);
	}
	
	escribir.close();
}

bool verificarCedula(char ced[]){
	if((strlen(ced) < 11) || (strlen(ced) > 11)){
		cerr << "\tError al leer la cedula, compruebe que todo este correcto" << endl;
		return true;
	}
	else{
		return false;
	}
}

void formatoCedula(char ced[]){
	int cont = 0;
	string aux = ced;
	
	for(int i=0;i<strlen(ced);i++){
		if(ced[i] == '-'){
			cont++;
		}
	}
	
	if((strlen(ced) >= 11) && (cont<1)){
		aux = aux.substr(0,3) + "-" + aux.substr(3,7) + "-" + ced[10];
		strcpy(ced,aux.c_str());
	}
}

void formatoTelefono(char tel[]){
	int cont = 0;
	string aux = tel;
	
	for(int i=0;i<strlen(tel);i++){
		if(tel[i] == '-'){
			cont++;
		}
	}

	if((strlen(tel) >= 10) && (cont<1)){
		aux = aux.substr(0,3) + "-" + aux.substr(3,3) + "-" + aux.substr(5,4);
		strcpy(tel,aux.c_str());
	}
}

void listaPropietario(ifstream &ver){
	ver.open("Propietario.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	while(!ver.eof()){
		ver.read((char*)&propietario,sizeof(Propietario));
		if(!ver.eof()){
			cout << "Nombre: " << propietario.nombre << endl;
			cout << "Apellido: " << propietario.apellido << endl;
			cout << "Cedula: " << propietario.cedula << endl;
			cout << "Numero telefonico: " << propietario.telefono << endl;
			cout << "Direccion: " << propietario.direccion << endl;
			cout << "Gmail: " << propietario.gmail << endl;
			cout << "\n";
		}
	}
	
	ver.close();
}

void modificarPropietario(ifstream &ver){
	char cAux[15];
	ofstream modificar;
	
	ver.open("Propietario.dat", ios::in | ios::binary);
	modificar.open("modificar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(modificar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la cedula: "; cin.getline(cAux,15,'\n');
	formatoCedula(cAux);
	
	while(!ver.eof()){
		ver.read((char*)&propietario,sizeof(Propietario));
		
		if(!ver.eof()){
			if(strcmp(cAux,propietario.cedula) == 0){
				fflush(stdin);
				cout << "Digite su nombre: "; cin.getline(propietario.nombre,20,'\n');
				cout << "Digite su apellido: "; cin.getline(propietario.apellido,20,'\n');
				cout << "Cedula: " << propietario.cedula << endl;
				cout << "Digite su numero de telefono: "; cin.getline(propietario.telefono,20,'\n');
				formatoTelefono(propietario.telefono);
				cout << "Digite su direccion: "; cin.getline(propietario.direccion,20,'\n');
				cout << "Digite su Gmail: "; cin.getline(propietario.gmail,20,'\n');
				modificar.write((char*)&propietario,sizeof(Propietario));
				cout << "\n";	
			}
			else{
				modificar.write((char*)&propietario,sizeof(Propietario));
			}	
		}
	}
	
	ver.close();
	modificar.close();
	
	remove("Propietario.dat");
	rename("modificar.dat","Propietario.dat");
}

void eliminarPropietario(ifstream &ver){
	char cAux[15];
	ofstream eliminar;
	
	ver.open("Propietario.dat", ios::in | ios::binary);
	eliminar.open("eliminar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(eliminar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la cedula: "; cin.getline(cAux,15,'\n');
	formatoCedula(cAux);
	
	while(!ver.eof()){
		ver.read((char*)&agencia,sizeof(Agencia));
		
		if(!ver.eof()){
			if(strcmp(cAux,propietario.cedula) == 0){
				cout << "\tEl propietario se ha eliminado de sistema con exito" << endl;
			}
			else{
				eliminar.write((char*)&agencia,sizeof(Agencia));
			}	
		}
	}
	
	ver.close();
	eliminar.close();
	
	remove("Propietario.dat");
	rename("eliminar.dat","Propietario.dat");
}

void menuAlquileres(){
	do{
		cout << "\tBienvenido al menu de alquileres" << endl;
		cout << "1. Lista" << endl;
		cout << "2. Eliminar" << endl;
		cout << "3. Salir" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				listaAlquiler(ver); break;
			case 2:
				eliminarAlquiler(ver); break;
			case 3:
				cout << "Saliendo del menu de alquileres..." << endl; break;
		}
		system("pause");
		system("cls");
	}
	while(opcion != 3);
}

void listaAlquiler(ifstream &ver){
	ver.open("Alquileres.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	while(!ver.eof()){
		ver.read((char*)&alquiler,sizeof(Alquileres));
		if(!ver.eof()){
			cout << "Nombre del inquilino: " << alquiler.inNombre << endl;
			cout << "Cedula del inquilino: " << alquiler.inCedula << endl;
			cout << "Cedula del propietario: " << alquiler.proCedula << endl;
			cout << "Numero telefonico del inquilino: " << alquiler.inTelefono << endl;
			cout << "Provincia vivienda: " << alquiler.vProvincia << endl;
			cout << "Municipio vivienda: " << alquiler.vMunicipio << endl;
			cout << "Calle vivienda: " << alquiler.vCalle << endl;
			cout << "Piso: " << alquiler.piso << endl;
			cout << "\n";
		}
	}
	
	ver.close();
}

void eliminarAlquiler(ifstream &ver){
	char rncAux[10];
	ofstream eliminar;
	
	ver.open("Alquileres.dat", ios::in | ios::binary);
	eliminar.open("eliminar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(eliminar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite el rnc: "; cin.getline(rncAux,10,'\n');
	while(!ver.eof()){
		ver.read((char*)&alquiler,sizeof(Alquileres));
		
		if(!ver.eof()){
			if(strcmp(rncAux,agencia.rnc) == 0){
				cout << "\tLa agencia se ha eliminado de sistema con exito" << endl;
			}
			else{
				ver.read((char*)&alquiler,sizeof(Alquileres));
			}	
		}
	}
	
	ver.close();
	eliminar.close();
	
	remove("Alquileres.dat");
	rename("eliminar.dat","Alquileres.dat");
}

void menuContrato(){
	do{
		cout << "\tBienvenido al menu de contratos" << endl;
		cout << "1. Renova contrato" << endl;
		cout << "2. Lista" << endl;
		cout << "3. Eliminar" << endl;
		cout << "4. Salir" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				renovarContrato(escribir); break;
			case 2:
				listaContrato(ver); break;
			case 3:
				eliminarContrato(ver); break;
			case 4:
				cout << "Saliendo del menu de contrato..." << endl; break;
		}
		system("pause");
		system("cls");
	}
	while(opcion != 4);
}

void renovarContrato(ofstream &escribir){
	char cAux[15];
	ifstream ver1;
	
	ver.open("Contrato.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	
	fflush(stdin);
	cout << "Digite la cedula del propietario para verifiacar el contrato: "; cin.getline(cAux,15,'\n');
	formatoCedula(cAux);
	while(!ver.eof()){
		ver.read((char*)&contratos,sizeof(Contrato));
		if(!ver.eof()){
			if(strcmp(cAux,contratos.proCedula) == 0){
				cout << "Quiere renovar el propietario(s/n)? "; cin >> rpt;
				if((rpt == 'S') || (rpt == 's')){
					contratos.fAnios += 10;
				}
				else{
					ver.close();
					eliminarContratoV(ver1, cAux);
				}
			}	
		}
	}
	
	ver.close();
}

void listaContrato(ifstream &ver){
	ver.open("Contrato.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	while(!ver.eof()){
		ver.read((char*)&contratos,sizeof(Contrato));
		if(!ver.eof()){
			cout << "\tContrato" << endl;
			cout << "Nombre de la agencia: " << contratos.agNombre << endl;
			cout << "Nombre del inquilino: " << contratos.inNombre << endl;
			cout << "Cedula del inquilino: " << contratos.inCedula << endl;
			cout << "Numero telefonico del inquilino: " << contratos.inNumero << endl;
			cout << "Nombre de propietario: " << contratos.proNombre<< endl;
			cout << "Apellido del propietario: " << contratos.proApellido << endl;
			cout << "Cedula del propietario: " << contratos.proCedula << endl;
			cout << "Fecha del contrato: " << endl;
			cout << "Dia: " << contratos.fDia << "/" << contratos.fMes << "/" << contratos.fDia << endl;
			cout << "\n";
		}
	}
	
	ver.close();
}

void eliminarContratoV(ifstream &ver, char cAux[]){
	ofstream eliminar;
	ifstream ver1;
	
	ver.open("Contrato.dat", ios::in | ios::binary);
	eliminar.open("eliminar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(eliminar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	while(!ver.eof()){
		ver.read((char*)&contratos,sizeof(Contrato));
		
		if(!ver.eof()){
			if(strcmp(cAux,contratos.proCedula) == 0){
				cout << "\tEl contrato ha sido eliminado de sistema con exito" << endl;
				alquilerContrato(ver1,cAux);
			}
			else{
				eliminar.write((char*)&contratos,sizeof(Contrato));
			}	
		}
	}
	
	ver.close();
	eliminar.close();
	
	remove("Contrato.dat");
	rename("eliminar.dat","Contrato.dat");
}

void eliminarContrato(ifstream &ver){
	char cAux[20];
	ofstream eliminar;
	ifstream ver1;
	
	ver.open("Contrato.dat", ios::in | ios::binary);
	eliminar.open("eliminar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(eliminar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite la cedula del propietario: "; cin.getline(cAux,20,'\n');
	formatoCedula(cAux);
	while(!ver.eof()){
		ver.read((char*)&contratos,sizeof(Contrato));
		
		if(!ver.eof()){
			if(strcmp(cAux,contratos.proCedula) == 0){
				cout << "\tEl contrato ha sido eliminado de sistema con exito" << endl;
				alquilerContrato(ver1,cAux);
			}
			else{
				eliminar.write((char*)&contratos,sizeof(Contrato));
			}	
		}
	}
	
	ver.close();
	eliminar.close();
	
	remove("Contrato.dat");
	rename("eliminar.dat","Contrato.dat");
}                 

void alquilerContrato(ifstream &ver, char cAux[]){
	ofstream eliminar2;
	
	ver.open("Alquileres.dat", ios::in | ios::binary);
	eliminar2.open("eliminar2.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(eliminar2.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	while(!ver.eof()){
		ver.read((char*)&alquiler,sizeof(Alquileres));
		
		if(!ver.eof()){
			if(strcmp(cAux,alquiler.proCedula) == 0){
				cout << "\tEl alquiler se ha eliminado de sistema con exito" << endl;
			}
			else{
				eliminar2.write((char*)&alquiler,sizeof(Alquileres));
			}	
		}
	}
	
	ver.close();
	eliminar2.close();
	
	remove("Alquileres.dat");
	rename("eliminar2.dat","Alquileres.dat");
}

void menuAgencia(){
	do{
		cout << "\tBienvenido al menu de agencia" << endl;
		cout << "1. Crear" << endl;
		cout << "2. Listar" << endl;
		cout << "3. Modificar" << endl;
		cout << "4. Eliminar" << endl;
		cout << "5. Salir" << endl;
		cout << "Opcion: "; cin >> opcion;
		
		system("cls");
		switch(opcion){
			case 1:
				crearAgencia(escribir); break;
			case 2:
				listaAgencia(ver); break;
			case 3:
				modificarAgencia(ver); break;
			case 4:
				eliminarAgencia(ver); break;
			case 5:
				cout << "Saliendo del menu de agencia..." << endl;
		}
		system("pause");
		system("cls");
	}
	while(opcion != 5);
}

void crearAgencia(ofstream &escribir){
	escribir.open("Agencias.dat", ios::out | ios::binary | ios::app);
	
	if(escribir.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	do{
		fflush(stdin);
		cout << "Digite el nombre de la agencia: "; cin.getline(agencia.nombre,20,'\n');
		cout << "Digite el codigo: "; cin.getline(agencia.codigo,10,'\n');
		cout << "Digite la direccion: "; cin.getline(agencia.direccion,30,'\n');
		cout << "Digite el rnc: "; cin.getline(agencia.rnc,10,'\n');
		escribir.write((char*)&agencia,sizeof(Agencia));
		cout << "\tQuiere agregar otra agencia(s/n)?"; cin >> rpt;
	}
	while((rpt == 'S') || (rpt == 's'));
	
	escribir.close();
}

void listaAgencia(ifstream &ver){
	ver.open("Agencias.dat", ios::in | ios::binary);
	
	if(ver.fail()){
		cerr << "El archivo no se pudo abrir" << endl;
		exit(1);
	}
	
	while(!ver.eof()){
		ver.read((char*)&agencia,sizeof(Agencia));
		if(!ver.eof()){
			cout << "Nombre: " << agencia.nombre << endl;
			cout << "Codigo: " << agencia.codigo << endl;
			cout << "Direccion: " << agencia.direccion << endl;
			cout << "rnc: " << agencia.rnc << endl;
			cout << "\n";
		}
	}
	
	ver.close();
}

void modificarAgencia(ifstream &ver){
	char rncAux[10];
	ofstream modificar;
	
	ver.open("Agencias.dat", ios::in | ios::binary);
	modificar.open("modificar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(modificar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite el rnc: "; cin.getline(rncAux,10,'\n');
	while(!ver.eof()){
		ver.read((char*)&agencia,sizeof(Agencia));
		
		if(!ver.eof()){
			if(strcmp(rncAux,agencia.rnc) == 0){
				fflush(stdin);
				cout << "Digite el nombre de la agencia: "; cin.getline(agencia.nombre,20,'\n');
				cout << "Digite el codigo: "; cin.getline(agencia.codigo,10,'\n');
				cout << "Digite la direccion: "; cin.getline(agencia.direccion,30,'\n');
				cout << "Digite el rnc: "; cin.getline(agencia.rnc,10,'\n');
				modificar.write((char*)&agencia,sizeof(Agencia));
				cout << "\n";	
			}
			else{
				modificar.write((char*)&agencia,sizeof(Agencia));
			}	
		}
	}
	
	ver.close();
	modificar.close();
	
	remove("Agencias.dat");
	rename("modificar.dat","Agencias.dat");
	
}

void eliminarAgencia(ifstream &ver){
	char rncAux[10];
	ofstream eliminar;
	
	ver.open("Agencias.dat", ios::in | ios::binary);
	eliminar.open("eliminar.dat", ios::out | ios::binary);
	
	if(ver.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	if(eliminar.fail()){
		cerr << "No se pudo abrir el archivo" << endl;
		exit(1);
	}
	
	fflush(stdin);
	cout << "Digite el rnc: "; cin.getline(rncAux,10,'\n');
	while(!ver.eof()){
		ver.read((char*)&agencia,sizeof(Agencia));
		
		if(!ver.eof()){
			if(strcmp(rncAux,agencia.rnc) == 0){
				cout << "\tLa agencia se ha eliminado de sistema con exito" << endl;
			}
			else{
				eliminar.write((char*)&agencia,sizeof(Agencia));
			}	
		}
	}
	
	ver.close();
	eliminar.close();
	
	remove("Agencias.dat");
	rename("eliminar.dat","Agencias.dat");
}
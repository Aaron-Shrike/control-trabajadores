/*
Desarrollar un programa que permita registrar los trabajadores de una empresa;
los cuales pueden ser contratados a tiempo completo o a tiempo parcial.
Los trabajadores da tiempo completo deben tener los siguientes datos:
Nombres, apellido paterno y materno, DNI, cargo, sueldo bruto, bono y descuento.
Los trabajadores a tiempo parcial deben tener los siguientes datos: Nombres, apellido
paterno y materno, DNI, cargo, pago por hora y la cantidad de horas laboradas.
Se debe reportar:

1. Listado de todos los trabajadores: Nombre completo, cargo y sueldo neto.
2. Dado un DNI mostrar nombre completo, cargo y los datos de pago según su
contrato.
3. Dado un tipo de trabajador listar los trabajadores registrados: Nombre completo,
cargo y DNI
*/

#include "basicas.cpp"

#define MAX_DNI 9

class Persona{
  private:
	char nombres[MAX];
	char apellidoPaterno[MAX];
	char apellidoMaterno[MAX];
   	int edad;

  public:
	Persona()
	{
   		this->nombres[0] = NULL;
   		this->apellidoPaterno[0] = NULL;
   		this->apellidoMaterno[0] = NULL;
		this->edad = 0;
	}

   	void getNombreCompleto(char *nombre)
   	{
   		strcpy( nombre, this->apellidoPaterno);
      	strcat( nombre, " ");
      	strcat( nombre, this->apellidoMaterno);
      	strcat( nombre , " ");
      	strcat( nombre, this->nombres);
   	}

   	int getEdad()
	{
   		return this->edad;
   	}

   	virtual void leer()
	{
   		cout << "Nombres : "; cin >> this->nombres;
   		cout << "Ap. Paterno : "; cin >> this->apellidoPaterno;
   		cout << "Ap. Materno : "; cin >> this->apellidoMaterno;
      	this->edad=leeEntero("Edad[0-120] : ",0,120,"\t* Edad no valida");
   	}
};

class Trabajador : public Persona{
  private:
	char DNI[MAX_DNI];
   	char cargo[MAX];
   	
  public:
   	Trabajador()
	{
   		this->DNI[0]=NULL;
      	this->cargo[0]=NULL;
   	}

	virtual void leer()
	{
      	Persona::leer();
   		cout << "DNI : "; cin >> this->DNI;
      	cout << "Cargo : "; cin >> this->cargo;
   	}

	virtual float getSueldoNeto()=0;

   	void getDNI(char *auxDNI)
	{
   		strcpy(auxDNI,this->DNI);
   	}

   	void getCargo(char *auxCargo)
	{
   		strcpy(auxCargo,this->cargo);
   	}

  	virtual int getTipo()=0;
};

class TrabajadorTC:public Trabajador{
  private:
	float sueldoBruto;
   	float descuento;
   	float bono;

  public:
   	virtual void leer()
	{
   		Trabajador::leer();
   		cout << "Sueldo Bruto : "; cin >> this->sueldoBruto;
      	cout << "Descuento : "; cin >> this->descuento;
      	cout << "Bono : "; cin >> this->bono;
   	}

	virtual float getSueldoNeto()
	{
   		return this->sueldoBruto - this->descuento + this->bono;
   	}

   	float getSueldoBruto()
	{
   		return this->sueldoBruto;
   	}

   	float getDescuento()
	{
   		return this->descuento;
   	}

   	float getBono()
	{
   		return this->bono;
   	}

   	virtual int getTipo()
	{
   		return 1;
   	} 
};

class TrabajadorTP:public Trabajador{
  private:
	float pagoHora;
   	int cantidadHoras;

  public:
   	virtual void leer()
	{
   		Trabajador::leer();
   		cout << "Pago por hora : "; cin >> this->pagoHora;
      	cout << "Cantidad de horas laboradas : "; cin >> this->cantidadHoras;
   	}

	virtual float getSueldoNeto()
	{
   		return this->pagoHora * this->cantidadHoras;
   	}

   	int getPagoHora()
	{
   		return this->pagoHora;
   	}

   	int getCantidadHoras()
	{
   		return this->cantidadHoras;
   	}

   	virtual int getTipo()
	{
   		return 0;
   	}
};

class NodoTrabajador{
  friend class ListaTrabajadores;
	
  private:
   	Trabajador *trabajador;
	NodoTrabajador *sgte;
	
  public:
	NodoTrabajador()
	{
   		this->trabajador = NULL;
      	this->sgte = NULL;
   	}

   	~NodoTrabajador()
	{
   		if(this->trabajador != NULL)
		{
      		delete this->trabajador;
      	}
   }
};

class ListaTrabajadores{
  private:
	int n;
   	NodoTrabajador *cab;

  public:
	ListaTrabajadores()
	{
   		this->n = 0;
      	this->cab = NULL;
   	}

   	~ListaTrabajadores()
	{
   		NodoTrabajador *temp;

      	while(this->cab != NULL)
		{
			temp = this->cab;

         	this->cab = temp->sgte;
         	delete temp;
      	}
      	this->cab = NULL;
      	this->n=0;
   	}

   	int getN()
	{
   		return this->n;
   	}

   	void agregar(Trabajador *nuevo)
	{
   		NodoTrabajador *temp;
      	NodoTrabajador *ultimo;

      	temp = new NodoTrabajador();
      	temp->trabajador = nuevo;

      	if(this->cab == NULL)
		{
      		this->cab = temp;
      	}
		else
		{
      		ultimo = this->cab;
         	while(ultimo->sgte != NULL)
			{
         		ultimo = ultimo->sgte;
         	}
         	ultimo->sgte = temp;
      	}

      	this->n++;
   	}

   	Trabajador *buscarTrabajador(char *DNIBuscar)
	{
   		NodoTrabajador *temp = this->cab;
      	char DNI[MAX_DNI];

      	while(temp != NULL)
		{
         	temp->trabajador->getDNI(DNI);

         	if(strcmpi(DNI,DNIBuscar)==0)
			{
         		return temp->trabajador;
         	}

         	temp = temp->sgte;
      	}

      	return NULL;
   	}

   	Trabajador *get(int pos)
	{
   		NodoTrabajador *temp = this->cab;

      	if(pos>=0 && pos<this->n)
		{
			for(int i=0;i<pos;i++)
			{
      			temp = temp->sgte;
      		}
         	return temp->trabajador;
      	}
		else
		{
      		return NULL;
      	}
   	}
};

ListaTrabajadores trabajadores;

int leerOpcion()
{
	char *opciones[5]={"Registrar trabajador","Listar trabajador","Buscar trabajador","Listrar por tipo","Salir"};
   	int op;

   	for(int i=0;i<5;i++)
	{
   		cout << (i+1) << ".- " << opciones[i] << endl;
   	}

   	op=leeEntero(" Opcion : ",1,5,"\t* Opcion no valida");

   	return op;
}

int leerTipo()
{
	char *tipos[2]={"Trabajo tiempo completo","Trabajo tiempo parcial"};
   	int tipo;

   	for(int i=0;i<2;i++)
	{
   		cout << (i+1) << ". "<< tipos[i] << endl;
   	}

   	tipo=leeEntero(" Tipo : ",1,2,"\t* Tipo no valida");

   	return tipo;
}

Trabajador *crearTrabajador(int tipo)
{
	Trabajador *t=NULL;

   	switch(tipo)
	{
   		case 1: t=new TrabajadorTC(); break;
      	case 2: t=new TrabajadorTP(); break;
   	}

   	return t;
}

void registrarTrabajador()
{
	Trabajador *trab;
   	int tipo;

   	cout << "\n" << endl;
	tipo=leerTipo();
   	trab=crearTrabajador(tipo);
   	trab->leer();
   	trabajadores.agregar(trab);

   	cout << "\t* Trabajador registrado exitosamente" << endl;
	getch();
}

//REPORTE01
void listarTrabajador()
{
	char nombreCompleto[MAX*3];
   	char DNI[MAX_DNI];

   	cout << "\n" << endl;
	cout << " - LISTADO DE  TRABAJADORES -" << endl;
   	cout << "--------------------------------------" << endl;

   	for(int i=0;i<trabajadores.getN();i++)
	{
   		trabajadores.get(i)->getNombreCompleto(nombreCompleto);
      	trabajadores.get(i)->getDNI(DNI);

      	cout << (i+1) << ".- " << nombreCompleto << " - " << DNI << "("
      		<< trabajadores.get(i)->getSueldoNeto() << ")"<< endl;
   	}
   	cout << "======================================" << endl;
   	getch();
}

//REPORTE02
void presentarPorDNI()
{
	Trabajador *trab;
	char nombreCompleto[MAX+3];
   	char cargo[MAX];
   	char DNI[MAX_DNI];

   	cout << "\nDNI a buscar : "; cin >> DNI;
   	trab = trabajadores.buscarTrabajador(DNI);
   	cout << "\n";
   	
   	if(trab != NULL)
	{
   		trab->getNombreCompleto(nombreCompleto);
      	trab->getCargo(cargo);

      	cout << " Nombre : " << nombreCompleto << endl;
      	cout << " Cargo : " << cargo << endl;

   		if(trab->getTipo() == 1)
		{
      		cout << " Sueldo Base : " << ((TrabajadorTC *)trab)->getSueldoBruto() << endl;
         	cout << " Descuento : " << ((TrabajadorTC *)trab)->getDescuento() << endl;
         	cout << " Bono : " << ((TrabajadorTC *)trab)->getBono() << endl;
      	}
      	else
		{
      		cout << " Pago por Hora : " << ((TrabajadorTP *)trab)->getPagoHora() << endl;
         	cout << " Cantidad de Horas : " << ((TrabajadorTP *)trab)->getCantidadHoras() << endl;
      	}
      	cout << " Sueldo Neto : " << trab->getSueldoNeto() << endl;
   	}
	else
	{
   		cout << "\t* No se encontro persona con el DNI indicado" << endl;
   	}
   	getch(); 
}

//REPORTE03
void presentarPorTipo()
{
	Trabajador *trab;
	char nombreCompleto[MAX+3];
   	char cargo[MAX];
   	char DNI[MAX_DNI];
   	int n=0,auxTipo,cantidad = trabajadores.getN();

	cout << "\n" << endl;
   	auxTipo = leerTipo();
	cout << "--------------------------------------" << endl;   
	for(int i=0;i<cantidad;i++)
	{
   		trab = trabajadores.get(i);

      	if(trab->getTipo() == auxTipo)
		{
      		trab->getNombreCompleto(nombreCompleto);
         	trab->getCargo(cargo);
         	trab->getDNI(DNI);

         	cout << (n+1) << ".- " << nombreCompleto <<  " - " << cargo <<  "("
         		<< DNI << ")" << endl;
         	n++;
      	}
   	}
   	if(n == 0)
	{
   		cout << "\t* No hay trabajadores con el tipo indicado" << endl;
	}
   	cout << "======================================" << endl;
   	getch();
}

int main()
{
   	int op;

   	do
	{
   		system("cls");
  		cout<<"------------ MENU ------------"<<endl;
   		op=leerOpcion();
      	switch(op)
		{
      		case 1: registrarTrabajador();	break;
         	case 2: listarTrabajador(); break;
         	case 3: presentarPorDNI(); break;
         	case 4: presentarPorTipo(); break;
         	case 5: break;
      	}
   	}while(op<5);
}

#include <iostream>
#include <fstream>

using namespace std;

int Menu(int,int);
int mostrar_horario();
int sugiere_horario(int);
int disponibilidad_horaria();
char disponibilidad_materia(char*);

int main()
{   int horario_estudio_asignado=0;// horas que han sido asignadas
    //menu 1
    int menu=1;
    while(menu==1){
        int opcion=3;
        opcion= Menu(opcion,menu);//llamado funcion menu
        if(opcion==1){
            //tecla para salir
            int salir=0;
            while(salir==0){
                mostrar_horario();
                cout<<"1. Atras: ";
                cin>>salir;
            }
        }
        else if(opcion==2){
            sugiere_horario(horario_estudio_asignado);//llamado funcion para sugerir horario
            disponibilidad_horaria();//llamado funcion para mostrar disponibilidad horaria
            //tecla para continuar
            int continuar=0;
            while(continuar==0){
                cout<<endl;
                cout<<"1. Continuar: ";
                cin>>continuar;
            }
            //menu 2
            int menu=2;
            while(menu==2){
                int opcion=3;
                Menu(opcion,menu);//llamado funcion menu
                system("cls");
                cout<<endl;
                char materia_escrita[25];
                cout<<"Codigo o Nombre de la materia: ";
                cin>>materia_escrita;
                disponibilidad_materia(materia_escrita);
                cout<<endl;
                char dia[10];
                cout<<"Dia: ";
                cin>>dia;
                char hora[10];
                cout<<"Formato de Hora: 05:00 a 22:00 : ";
                cin>>hora;
            }



        }
    }

    return 0;
}

int Menu(int opcion,int menu){
    switch(menu){
    case 1:
        while(opcion>2){
            system("cls");//limpiar la terminal
            cout<<endl;
            cout<<"Menu principal:"<<endl;
            cout<<endl;
            cout<<"1. Ver Horario"<<endl;
            cout<<"2. Agendar Horario"<<endl;
            cout<<"3. Salir"<<endl;
            cout<<endl;
            cout<<"Seleccione una opcion: ";
            cin>>opcion;
            if (opcion==3){cout<<endl;exit(0);}
        }
        break;
    case 2:
        while(opcion>1){
            system("cls");
            cout<<endl;
            cout<<"Menu Para Agendar:"<<endl;
            cout<<endl;
            cout<<"1. Agendar Horario"<<endl;
            cout<<"2. Salir"<<endl;
            cout<<endl;
            cout<<"Seleccione una opcion: ";
            cin>>opcion;
            if (opcion==2){cout<<endl;exit(0);}
        }
        break;
    }

    return opcion;
}
int mostrar_horario(){
    system("cls");
    // Abrir el archivo para lectura
    ifstream archivo("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/horario.txt");
    // Verifica si el archivo se abrio correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de lectura." << endl;
        return 1;
    }
    char contenido_linea[150];
    int longitud_linea;
    while (archivo.getline(contenido_linea, 150)){//lee todas las lineas de archivo
        longitud_linea = 0;
        //cuenta caracteres hasta llegar al final de la línea \n o al final de la cadena \0
        while (contenido_linea[longitud_linea] != '\0' && contenido_linea[longitud_linea] != '\n'){
            longitud_linea++;
        }
        //imprime las lineas que tienen contenido
        if(longitud_linea>6 || longitud_linea==0)cout <<contenido_linea<<endl;
    }

  // Cierra el archivo
  archivo.close();
  cout<<endl;
}
int sugiere_horario(int horario_estudio_asignado){
    system("cls");
    // Abrir el archivo para lectura
    ifstream archivo("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/materias.txt");
    // Verifica si el archivo se abrio correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de lectura." << endl;
        return 1;
    }
    char contenido_linea[150];
    int linea=0;
    int longitud_linea;

    int horario_estudio;

    while (archivo.getline(contenido_linea, 150)){//lee todas las lineas de archivo
        linea++;
        longitud_linea = 0;
        //cuenta caracteres hasta llegar al final de la línea \n o al final de la cadena \0
        while (contenido_linea[longitud_linea] != '\0' && contenido_linea[longitud_linea] != '\n'){
            longitud_linea++;
        }

        if(longitud_linea>55 || longitud_linea==0)cout <<contenido_linea<<endl;//imprime las lineas descriptivas

        if(linea>3){//toma las lineas mayores de 3
            if(longitud_linea>7){
                int tamaño_materia=longitud_linea-13;//13 son los caracteres fijos
                char materia[tamaño_materia];//13 son los caracteres fijos
                //ciclo para agregar las materias
                for (int i = 8; i<longitud_linea; i++) {
                    if(contenido_linea[i]==':')break;
                    materia[i-8]=contenido_linea[i];
                }
                int creditos=0;
                //ciclo para añadir creditos de la materia
                for (int i = 10+tamaño_materia; i<11+tamaño_materia; i++) {
                    creditos=contenido_linea[i]-'0';
                }
                int Hclase=0;
                //ciclo para agregar las horas de clase por materia
                for (int i = 12+tamaño_materia; i<longitud_linea; i++) {
                    Hclase=contenido_linea[i]-'0';
                }
                horario_estudio=((48*creditos)/16)-Hclase;
                //Imprime las horas de estudio requeridas
                cout<<"Se sugiere "<<horario_estudio<<" horas de estudio para ";
                for (int i = 0; i<tamaño_materia; i++) {
                    cout<<materia[i];
                }
                cout<<": "<<horario_estudio-horario_estudio_asignado<<"/"<<horario_estudio<<" horas disponibles."<<endl;
            }
        }


    }

  // Cierra el archivo
  archivo.close();
}
int disponibilidad_horaria(){
    // Abrir el archivo para lectura
    ifstream archivo("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/horario.txt");
    // Verifica si el archivo se abrio correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de lectura." << endl;
        return 1;
    }

    cout<<endl;
    cout<<"Horario disponible para agendar:"<<endl;
    char contenido_linea[150];
    int longitud_linea;
    while (archivo.getline(contenido_linea, 150)){//lee todas las lineas de archivo
        longitud_linea = 0;
        //cuenta caracteres hasta llegar al final de la línea \n o al final de la cadena \0
        while (contenido_linea[longitud_linea] != '\0' && contenido_linea[longitud_linea] != '\n'){
            longitud_linea++;
        }
        //imprime las lineas que tienen contenido
        if(longitud_linea<11){
            int contador=0;//cuenta que no hayan espacios en la linea, si hay no la imprime
            for (int i = 0; i<longitud_linea; i++) {
                if(contenido_linea[i]==' ')break;
                contador++;
            }
            if(contador==longitud_linea)cout <<contenido_linea<<endl;
            else{
                contador=0;//cuenta que hayan 1,2 o 3 '0' en la linea, si no hay no la imprime
                for (int i = 0; i<longitud_linea; i++) {
                    if(contenido_linea[i]=='0')contador++;
                }
                if(contador>0)cout <<contenido_linea<<"  ";
            }
        }
    }

  // Cierra el archivo
  archivo.close();
  cout<<endl;
}
char disponibilidad_materia(char *materia_escrita){
    system("cls");
    // Abrir el archivo para lectura
    ifstream archivo("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/materias.txt");
    // Verifica si el archivo se abrio correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de lectura." << endl;
        return 1;
    }
    char contenido_linea[150];
    int linea=0;
    int longitud_linea;
    int contador_validar=0;//se usa para validar si se encuentra la materia
    int contador_validar2=0;//se usa para validar si se encuentra la materia

    while (archivo.getline(contenido_linea, 150)){//lee todas las lineas de archivo
        linea++;
        longitud_linea = 0;
        //cuenta caracteres hasta llegar al final de la línea \n o al final de la cadena \0
        while (contenido_linea[longitud_linea] != '\0' && contenido_linea[longitud_linea] != '\n'){
            longitud_linea++;
        }

        if(linea>3){//toma las lineas mayores de 3
            if(longitud_linea>7){
                int tamaño_materia=longitud_linea-13;//13 son los caracteres fijos
                char materia[tamaño_materia];//13 son los caracteres fijos
                //ciclo para agregar las materias
                for (int i = 8; i<longitud_linea; i++) {
                    if(contenido_linea[i]==':')break;
                    materia[i-8]=contenido_linea[i];
                }
                char codigo[7];//7 es numero fijo del codigo
                //ciclo para agregar el codigo de materias
                for (int i = 0; i<7; i++) {
                    codigo[i]=contenido_linea[i];
                }
                contador_validar=0;//se usa para validar si se encuentra la materia
                //Ciclo de comparacion para saber si esta la materia
                for (int j = 0; j<tamaño_materia; j++) {
                    if(*(materia_escrita+j)==materia[j])contador_validar++;
                }
                contador_validar2=0;//se usa para validar si se encuentra la materia
                //Ciclo de comparacion para saber si esta la materia
                for (int j = 0; j<tamaño_materia; j++) {
                    if(*(materia_escrita+j)==codigo[j])contador_validar2++;
                }
                if(contador_validar>5 || contador_validar2>5)break;
            }
        }


    }
    if(contador_validar<6 && contador_validar2<6){cout<<endl;cout<<"Materia no registrada"<<endl;}

  // Cierra el archivo
  archivo.close();
}

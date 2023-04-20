#include <iostream>
#include <fstream>

using namespace std;

int Menu(int,int);
int mostrar_horario();
int sugiere_horario();
int disponibilidad_horaria();
int disponibilidad_materia(char*,bool*,char*);
int disponibilidad_Agendar_DH(char*,char*,char*);
int restar_horas(char*);

int main()
{
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
            sugiere_horario();//llamado funcion para sugerir horario
            disponibilidad_horaria();//llamado funcion para mostrar disponibilidad horaria
            //tecla para continuar
            int continuar=0;
            while(continuar==0){
                cout<<endl;
                cout<<"1. Continuar: ";
                cin>>continuar;
            }
            system("cls");
            //menu 2
            int menu=2;
            while(menu==2){
                int opcion=3;
                Menu(opcion,menu);//llamado funcion menu
                system("cls");
                cout<<endl;
                //para saber si la materia esta registrada
                bool esta=false;
                char materia_escrita[25];
                char materia_registrada;
                while(esta==false){
                    cout<<"Codigo o Nombre de la materia: ";
                    //cin>>materia_escrita;
                    cin.getline(materia_escrita, sizeof(materia_escrita));
                    disponibilidad_materia(materia_escrita,&esta,&materia_registrada);//funcion para saber si la materia esta, y para obtener el nombre de esa materia
                    cout<<endl;
                }
                char dia[10];
                char hora[6];
                //Menu para poner el dia y la hora a registrar
                cout<<"Formato del dia: nombre"<<endl;
                cout<<endl<<"Dia: ";
                cin>>dia;
                system("cls");
                cout<<endl<<"Formato de la Hora: 24:00"<<endl;
                cout<<endl<<"Hora: ";
                cin>>hora;
                //tecla para continuar
                int continuar=0;
                while(continuar==0){
                    cout<<endl;
                    cout<<"1. Continuar: ";
                    cin>>continuar;
                }
                system("cls");
                int H_encontrada=disponibilidad_Agendar_DH(dia,hora,&materia_registrada);//funcion para agendar hora, si no esta disponible da la opcion de cambiar el contenido o no
                if(H_encontrada>0)restar_horas(&materia_registrada);//funcion para restar horas de estudio, abre el documento y cambia H estudio
            }



        }
    }

    return 0;
}
//Funcion para los menus principales
int Menu(int opcion,int menu){
    switch(menu){
    case 1:
        while(opcion>2){
            system("cls");//limpiar la terminal
            cout<<endl;
            cout<<"Menu principal:"<<endl;
            cout<<endl;
            cout<<"1. Ver Horario Agendado"<<endl;
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
//funcion para mostrar horario agendado
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
//funcion para sugerir horas para estudiar dependiendo de la materia
int sugiere_horario(){
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

        if((longitud_linea>55 && longitud_linea<60) || longitud_linea==0)cout <<contenido_linea<<endl;//imprime las lineas descriptivas

        if(linea>4){//toma las lineas mayores de 3
            if(longitud_linea>7){
                int tamaño_materia=longitud_linea-15;//13 son los caracteres fijos
                char materia[tamaño_materia];//13 son los caracteres fijos
                //ciclo para agregar las materias
                for (int i = 8; i<longitud_linea; i++) {
                    if(contenido_linea[i]==':')break;
                    materia[i-8]=contenido_linea[i];
                }
                int creditos=0;
                //añadir creditos de la materia
                creditos=contenido_linea[10+tamaño_materia]-'0';

                int Hclase=0;
                //agregar las horas de clase por materia
                Hclase=contenido_linea[12+tamaño_materia]-'0';

                int horario_estudio_asignado=0;// horas que han sido asignadas
                //ciclo para agregar las horas de estudio asignado por el usuario
                horario_estudio_asignado=contenido_linea[14+tamaño_materia]-'0';

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
//funcion para dar horas disponibles, horas sin contenido
int disponibilidad_horaria(){
    // Abrir el archivo para lectura
    ifstream archivo("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/horario.txt");
    // Verifica si el archivo se abrio correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de lectura." << endl;
        return 1;
    }

    cout<<endl;
    cout<<"Horas disponible para agendar:"<<endl;
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
//funcion para saber si la materia esta registrada en codigo o en nombre
int disponibilidad_materia(char *materia_escrita,bool *esta, char *materia_registrada){
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
        int tamaño_materia=longitud_linea-15;//15 son los caracteres fijos

        if(linea>4){//toma las lineas mayores de 3
            if(longitud_linea>7){
                char materia;
                char *materiapr=&materia;
                char codigo[7];

                //ciclo para agregar el codigo de materias
                for (int i = 0; i<7; i++) {
                    codigo[i]=contenido_linea[i];
                }
                //ciclo para agregar las materias
                for (int i = 8; i<longitud_linea; i++) {
                    if(contenido_linea[i]==':')break;
                    *(materiapr+(i-8))=contenido_linea[i];
                }
                contador_validar=0;//se usa para validar si se encuentra la materia
                //Ciclo de comparacion para saber si esta la materia
                for (int j = 0; j<tamaño_materia; j++) {
                    if(*(materia_escrita+j)==*(materiapr+j))contador_validar++;
                }
                contador_validar2=0;//se usa para validar si se encuentra la materia
                //Ciclo de comparacion para saber si esta la materia
                for (int k = 0; k<7; k++) {
                    if(*(materia_escrita+k)==codigo[k])contador_validar2++;
                }
                if(contador_validar>4){
                    //para añadir la materia a materia registrada
                    //llena la cadena de espacios
                    for (int i = 0; i<longitud_linea+10; i++) {
                        *(materia_registrada+i)=' ';
                    }
                    //llena la cadena con la materia
                    for (int i = 0; i<tamaño_materia; i++) {
                        *(materia_registrada+i)=*(materiapr+i);
                    }
                    *esta=true;
                    break;
                }
                if(contador_validar2>6){
                    //para añadir la materia a materia registrada
                    //llena la cadena de espacios
                    for (int i = 0; i<longitud_linea+10; i++) {
                        *(materia_registrada+i)=' ';
                    }
                    //llena la cadena con la materia
                    for (int i = 0; i<tamaño_materia; i++) {
                        *(materia_registrada+i)=*(materiapr+i);
                    }
                    *esta=true;
                    break;
                }
            }
        }


    }
    if(contador_validar<5 && contador_validar2<5)cout<<endl<<"<<< Materia no registrada >>>"<<endl;

  // Cierra el archivo
  archivo.close();
}
//funcion para saber si hay disponibilidad de hora, si no la hay, da la posibilidad de cabiar el contenido
int disponibilidad_Agendar_DH(char* dia,char* hora,char* materia_registrada){
    system("cls");
    // Abrir el archivo para lectura y escritura
    ifstream archivo("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/horario.txt");
    ofstream archivo_temporal("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/horario_temporal.txt");
    // Verifica si el archivo se abrio correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de lectura." << endl;
        return 1;
    }
    char contenido_linea[150];
    int longitud_linea;
    int linea=0;
    bool dia_encontrado=false;
    bool hora_encontrada=false;
    int linea_escrita=0;
    int H_encontrada=0;

    while (archivo.getline(contenido_linea, 150)){//lee todas las lineas de archivo
        linea_escrita=0;
        linea++;
        longitud_linea = 0;
        //cuenta caracteres hasta llegar al final de la línea \n o al final de la cadena \0
        while (contenido_linea[longitud_linea] != '\0' && contenido_linea[longitud_linea] != '\n'){
            longitud_linea++;
        }

        //para buscar el dia
        char valido;
        if(dia_encontrado==false){
            int contador_validar=0;//para validar que encontro el dia
            for (int i=0; i<longitud_linea; i++) {
                if(contenido_linea[i]==':'){valido=':';break;}
                if(*(dia+i)==contenido_linea[i]) contador_validar++;

            }
            if(contador_validar>3 && valido==':')dia_encontrado=true;
        }
        if(dia_encontrado==true){
            if(hora_encontrada==false){
                //para buscar hora
                int contador_validar2=0;//para validar que encontro la hora
                for (int i=0; i<6; i++) {
                    if(*(hora+i)==contenido_linea[i])contador_validar2++;
                }
                if(contador_validar2==5){//se encontro la hora
                    if(longitud_linea<7){
                        archivo_temporal<<hora<<" Estudiar "<<materia_registrada<<endl;
                        linea_escrita++;
                    }
                    else{
                        int si_no;
                        cout<<endl<<"<<< Hora no disponible >>>"<<endl;
                        cout<<endl<<"Quieres remplazar la actividad?"<<endl;
                        cout<<endl<<"1. Si      2. No "<<endl;
                        cin>>si_no;
                        if(si_no==1){
                            archivo_temporal<<hora<<" Estudiar "<<materia_registrada<<endl;
                            linea_escrita++;
                        }
                        system("cls");
                    }
                    hora_encontrada=true;
                    H_encontrada++;
                }
            }
        }
        if(linea_escrita==0)archivo_temporal<<contenido_linea<<endl;
    }
    if(dia_encontrado==false)cout<<endl<<"<<< Dia Erroneo >>>"<<endl;
    if(hora_encontrada==false) cout<<endl<<"<<< Hora no disponible >>>"<<endl;
    archivo.close();
    archivo_temporal.close();
    const char* archivo1 = "C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/horario.txt";
    const char* archivo_actual = "C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/horario_temporal.txt";
    const char* archivo_nuevo = "C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/horario.txt";
    remove(archivo1);
    rename(archivo_actual,archivo_nuevo);
    return H_encontrada;
}
//funcion para restar horas disponibles para estudiar por materia, para cambiar este el el archivo
int restar_horas(char* materia_registrada){
    system("cls");
    // Abrir el archivo para lectura y escritura
    ifstream archivo("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/materias.txt");
    ofstream archivo_temporal("C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/materias_temporal.txt");
    // Verifica si el archivo se abrio correctamente
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de lectura." << endl;
        return 1;
    }
    char contenido_linea[150];
    int longitud_linea;
    int linea=0;
    bool materia_encontrada=false;
    bool hora_registrada=false;
    int linea_escrita=0;

    while (archivo.getline(contenido_linea, 150)){//lee todas las lineas de archivo
        linea_escrita=0;
        linea++;
        longitud_linea = 0;
        //cuenta caracteres hasta llegar al final de la línea \n o al final de la cadena \0
        while (contenido_linea[longitud_linea] != '\0' && contenido_linea[longitud_linea] != '\n'){
            longitud_linea++;
        }
        int tamaño_materia=longitud_linea-15;//13 son los caracteres fijos
        if(linea>4){
            //para buscar el dia
            char valido;
            if(materia_encontrada==false){
                int contador_validar=0;//para validar que encontro el dia
                for (int i=0; i<longitud_linea; i++) {
                    if(contenido_linea[i]==':'){valido=':';break;}
                    if(*(materia_registrada+i)==contenido_linea[i+8]) contador_validar++;
                }
                if(contador_validar>5 && valido==':')materia_encontrada=true;
            }
            int horario_estudio_asignado=0;// horas que han sido asignadas
            //para agregar las horas de estudio asignado por el usuario
            horario_estudio_asignado=contenido_linea[14+tamaño_materia]-'0';

            if(materia_encontrada==true){
                if(hora_registrada==false){
                    int suma=horario_estudio_asignado+1;
                    for (int i=0; i<15+tamaño_materia; i++) {
                        if(i==14+tamaño_materia){archivo_temporal<<suma<<endl;break;}
                        archivo_temporal<<contenido_linea[i];
                    }
                    linea_escrita++;
                    hora_registrada=true;
                }
            }
        }
        if(linea_escrita==0)archivo_temporal<<contenido_linea<<endl;
    }
    archivo.close();
    archivo_temporal.close();
    const char* archivo1 = "C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/materias.txt";
    const char* archivo_actual = "C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/materias_temporal.txt";
    const char* archivo_nuevo = "C:/Users/duvan/Documents/proyectos c++/sistema_de_programacion_de_tiempo/materias.txt";
    remove(archivo1);
    rename(archivo_actual,archivo_nuevo);
}

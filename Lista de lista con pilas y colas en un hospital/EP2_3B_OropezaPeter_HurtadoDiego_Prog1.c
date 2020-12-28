
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct paciente
{

	char *nombre;
	char *padecimiento;
	int gravedad;
	struct paciente *siguiente;
	struct paciente *anterior;
};

struct doctor
{
	int n_pacientes;
	char *nombre_doctor;
	struct paciente *ini;
	struct paciente *fin;
	struct doctor *siguiente;
	struct doctor *anterior;
};



void menu(struct doctor **inicio, struct doctor **fin,struct paciente **ini, struct paciente **fini);
void push_paciente(struct paciente ***inicio, struct paciente ***finall,int valor/*tipo de urgencia*/,struct paciente *q,struct paciente *p,char *nombre,char *problema);
void imprimir_lista_espera(struct paciente **inicio); //el nodo final estará apuntando a NULL
void push_doctor(struct doctor ***inicio, struct doctor ***finall,int valor/*recibe 0 cantidad de pacientes atendidos*/,char *nombre_doc);
void asignar_paciente_a_doctor(struct doctor ***inicio,struct paciente ***ini,int *in,int *rap);
void imprimir(struct doctor **inicio);
void vaciar_todo(struct doctor ***inicio,struct doctor ***fin,struct paciente ***ini); //el nodo final estará apuntando a NULL


void main(void)
{
    struct doctor *inicio=0,*fin=0;
    struct paciente *ini=0, *fini=0;


  	 menu(&inicio,&fin,&ini,&fini);


     system("pause");

}



void menu(struct doctor **inicio, struct doctor **fin,struct paciente **ini, struct paciente **fini)
{
    int opc,cant_doc=2,tipo_urg,opc_urg,cant_pac=0,cant_in=0,cant_rap=0;
    struct paciente *q=0,*p=0;
    char nombre_paciente[30],padecimiento[50],nombre_doc[30];

	printf("\nIngrese el nombre del primer doctor: ");
	scanf("%[^\n]%*c",nombre_doc);
	push_doctor(&inicio,&fin,0,nombre_doc);
	printf("\nIngrese el nombre del segundo doctor: ");
	scanf("%[^\n]%*c",nombre_doc);
	push_doctor(&inicio,&fin,0,nombre_doc);

	system("cls");

    do
    {
        do
        {
	printf("                           +-------------------+\n");
	printf("                           |      HOSPITAL     | \n");
	printf("                           |     PARACETAMOL   | \n");
	printf("                           |                   |   \n");
	printf("                           |                   |  \n");
	printf("______....+-------------------+....______\n");
	printf("....------******** ______....LLLLLLLLLLLLLLLLLLL....______ ```````------....\n");
	printf(" ....------******                                       ```````------....  |\n");
	printf("|   +--------------+         _______________             +------------+    |\n");
	printf("|   |EMERGENCIAS   |        /               \\            |DOCTORES    |   |\n");
	printf("|   |              |       /_________________\\           |PARACETAMOL |   |\n");
	printf("|   +--------------+       | |      |      | |           +------------+    |\n");
	printf("|                          | |______|______| |                             |\n");
	printf("|__________________________|/|_____[|]_____|\\|____________________________|\n");
	printf("|__________________________|/|      |      |\\|____________________________|\n");
	printf("|                          | |______|______| |                             |\n");
	printf("|__________________________|/               \\|____________________________|\n");
            printf("\n1.Capturar nombres de medicos");
            printf("\n2. Capturar Paciente");
            printf("\n3. Mostrar Pacientes en espera");
            printf("\n4.Asignar paciente para atencion");
            printf("\n5.Listado de pacientes atendidos");
            printf("\n6.Salir\n");
            scanf("%d%*c",&opc);

            if(opc<1 || opc>6)
            	system("cls");

        }while(opc<1 || opc>6);


        switch(opc)
        {
            case 1:

					if(cant_doc<4 )
					{
						if(cant_doc==2 && (cant_pac==15 || cant_in==5))
						{
							printf("\nIngrese el nombre del doctor auxiliar 1: ");
							scanf("%[^\n]%*c",nombre_doc);
							push_doctor(&inicio,&fin,0,nombre_doc);

						}
						else if(cant_pac==20 || (cant_in>5 && cant_rap==5))
						{
							printf("\nIngrese el nombre del doctor auxiliar 2: ");
							scanf("%[^\n]%*c",nombre_doc);
							push_doctor(&inicio,&fin,0,nombre_doc);
						}


					}
					else
					{
						printf("\nYa se encuentra la totalidad de doctores en la sala\n\n");
					}

                break;

            case 2:

            	printf("\nPor favor ingrese el nombre del paciente: ");
            	scanf("%[^\n]%*c",nombre_paciente);
            	printf("\nPor favor ingrese el padecimiento: ");
            	scanf("%[^\n]%*c",padecimiento);

            	do
				{
					printf("\nIngrese el tipo de Urgencia\n\n");
					printf("\n3. Atencion inmediata");
					printf("\n2. Atencion rapido");
					printf("\n1. Atencion pronta\n");
					scanf("%d%*c",&opc_urg);

				}while(opc_urg<1 || opc_urg>3);

            	if(opc_urg==3)
            		cant_in++;
            	else if(opc_urg==2)
            		cant_rap++;

            	push_paciente(&ini,&fini,opc_urg,q,p,nombre_paciente,padecimiento);
				cant_pac++;

                break;

             case 3:
                if(cant_pac==0)
                {
                    printf("\nNo hay pacientes en la lista de espera\n\n");
                }
                else
             	  imprimir_lista_espera(ini);

                break;

            case 4:

                if((*ini!=0))
                {
                    asignar_paciente_a_doctor(&inicio,&ini,&cant_in,&cant_rap);
                    cant_pac--;

                }
                else
                    printf("\nNo hay pacientes en la lista de espera\n\n");



                break;

             case 5:

             	imprimir(inicio);

                break;


            case 6:

					vaciar_todo(&inicio,&fin,&ini);
					printf("\nYA SE ELIMINO LA MEMORIA...BYE...\n");


                break;

        }

	system("pause");
	system("cls");
    }while(opc!=6);




}


void push_paciente(struct paciente ***inicio, struct paciente ***finall,int valor,struct paciente *q,struct paciente *p,char *nombre,char *problema)
{

	struct paciente *nuevo=0;


	nuevo= (struct paciente*)malloc(sizeof(struct paciente));

	if(nuevo!=0)
	{

		nuevo->gravedad=valor; //se le asigna al nodo el tipo de gravedad (3,2,1)
		nuevo->nombre= (char*)malloc(sizeof(char)*strlen(nombre));
		strcpy(nuevo->nombre,nombre);
		nuevo->padecimiento= (char*)malloc(sizeof(char)*strlen(problema));
		strcpy(nuevo->padecimiento,problema);

		// ya se le asignaron todos los valores ue debe tener el nodo en los pasos anteriores

		if((**inicio)==0) //verifica ue ambos sean nulos(la lista esta vacía)
		{


			(**inicio)=nuevo;
			(**inicio)->anterior=0;
			(**inicio)->siguiente=0;
			(**finall)=nuevo;
			(**finall)->siguiente=0;
			(**finall)->anterior=0;




		}
		else
		{

                if(nuevo->gravedad> (**inicio)->gravedad)
                {
                    //insertar al inicio

                    nuevo->siguiente=(**inicio);
                    (**inicio)->anterior=nuevo;
                    nuevo->anterior=0;
                    (**inicio)=nuevo;

                }
                else
                {
                        if(nuevo->gravedad == (**finall)->gravedad || nuevo->gravedad < (**finall)->gravedad)
                        {
                            //insertar al final

                            (**finall)->siguiente=nuevo;
                            nuevo->anterior=(**finall);
                            nuevo->siguiente=0;
                            (**finall)=nuevo;

                        }
                        else
                        {
                            q=(**inicio);
                            p=(**inicio)->siguiente;

                            while(p!=0)
                            {
                                if(p->gravedad == nuevo->gravedad)
                                {
                                    p=p->siguiente;
                                    q=q->siguiente;
                                }
                                else
                                {
                                    if(p->gravedad > nuevo->gravedad)
                                    {
                                        p=p->siguiente;
                                        q=q->siguiente;
                                    }
                                    else
                                        break;
                                }
                            }
                            //insertar entre dos nodos
                            nuevo->siguiente=p;
                            nuevo->anterior=q;
                            q->siguiente = nuevo;
                            p->anterior =nuevo;


                        }


                }




		}




	}
//	return algo;
}

void imprimir_lista_espera(struct paciente **inicio) //el nodo final estará apuntando a NULL
{
	struct paciente *aux=(*inicio);


	if(aux!=0)
	{
	    while(aux != 0)
		{
	            printf("   _._ \n");
				printf("  /\\\\\\\\ \n");
				printf("  |. .| \n");
				printf("  \\_-_/ \n");
				printf(" /`   `\\ \n");
				printf("/_|   |_\\ \n");
				printf("\\_\\___/_/ \n");
				printf("  |   | \n");
				printf("  |   |\n");
				printf("  |_|_| \n");
				printf(" (__/__) \n");
	            printf("\nNombre Paciente: %s ",aux->nombre);
	            printf("\nPadecimiento: %s ",aux->padecimiento);
	            printf("\nTipo de Urgencia: %d \n\n\n",aux->gravedad);




			aux=aux->siguiente;


		}

	}

}

void push_doctor(struct doctor ***inicio, struct doctor ***finall,int valor/*recibe 0 cantidad de pacientes atendidos*/,char *nombre_doc)
{
	struct doctor *nuevo=0;

	nuevo= (struct doctor*)malloc(sizeof(struct doctor));


	nuevo->n_pacientes=valor;

	nuevo->nombre_doctor= (char*)malloc(sizeof(char)*strlen(nombre_doc));
	strcpy(nuevo->nombre_doctor,nombre_doc);

	if(nuevo!=0)
	{

		nuevo->n_pacientes=valor;

		nuevo->ini=0;
		nuevo->fin=0;

		if((**inicio)==0 && (**finall)==0) //verifica ue ambos sean nulos(la cola esta vacía)
		{


			(**inicio)=nuevo;
			(**inicio)->anterior=0;
			(**inicio)->siguiente=0;
			(**finall)=nuevo;
			(**finall)->siguiente=0;
			(**finall)->anterior=0;




		}
		else
		{


                    //insertar al final

                    (**finall)->siguiente=nuevo;
                    nuevo->anterior=(**finall);
                    nuevo->siguiente=0;
                    (**finall)=nuevo;





		}




	}

}


void asignar_paciente_a_doctor(struct doctor ***inicio,struct paciente ***ini,int *in,int *rap)
{
	int i=1,opc_doc;


	struct doctor *aux=(**inicio);
	struct paciente *a,*nuevo=0;

	printf("\nCual doctor desea asignarle el paciente?");

	if(aux!=0)
	{
	    while(aux != 0)
		{
					printf("   _____ \n");
					printf(" , \\_+_/,\n");
					printf(" ,((|||)),\n");
					printf(" .(|*_*|).\n");
					printf("  ·; = ;· \n");
					printf("  __) (__\n");
					printf(" /  \\_/  \\\n");
					printf("/_(_ : _)_\\\n");
					printf("| |)___( \\ \\\n");
					printf("| /     \\/ /\n");
	            printf("\n%d. %s ",i,aux->nombre_doctor);
	            i++;


			aux=aux->siguiente;


		}

	}

	printf("\n");

	do
	{
		scanf("%d%*c",&opc_doc);

		if(opc_doc<1 || opc_doc>i)
			printf("\nEl valor introducido no se asocia con un doctor\n\n");

	}while(opc_doc<1 || opc_doc>i);


	aux=(**inicio);
	i=1;

	if(aux!=0)
	{
	    while(aux != 0)
		{
				if(i==opc_doc)
				{
					if((**ini)->gravedad==3)
						in--;
					else if((**ini)->gravedad==2)
						rap--;

				    nuevo= (struct paciente*)malloc(sizeof(struct paciente));
				    a=(**ini);

				   	nuevo->gravedad=(**ini)->gravedad; //se le asigna al nodo el tipo de gravedad (3,2,1)
					nuevo->nombre= (char*)malloc(sizeof(char)*strlen((**ini)->nombre));
					strcpy(nuevo->nombre,(**ini)->nombre);
					nuevo->padecimiento= (char*)malloc(sizeof(char)*strlen((**ini)->padecimiento));
					strcpy(nuevo->padecimiento,(**ini)->padecimiento);

				    aux->n_pacientes=aux->n_pacientes+1; //se le suma 1 a la cantidad de pacientes atendidos

				    if(aux->ini==0)
					{

						aux->ini=nuevo;
						aux->fin=nuevo;
						aux->ini->anterior=0;
						aux->fin->anterior=0;
						aux->ini->siguiente=0;
						aux->fin->siguiente=0;
					}
					else
					{
						//prueba
						aux->fin->siguiente=nuevo;
	                    nuevo->anterior=aux->fin;
	                    nuevo->siguiente=0;
	                    aux->fin=nuevo;

					}
					free(a);

					(**ini)=(**ini)->siguiente;


					break;
				}

	            i++;


			aux=aux->siguiente;



		}

	}


}


void imprimir(struct doctor **inicio)
{

	struct doctor *aux=0;
	struct paciente *a=0;

	aux=(*inicio);
	char m=186;

	printf("\n\nLa Fila de Filas esta asi:\n");

	while(aux != 0)
	{
		a=aux->ini;
				printf("   _._ \n");
				printf("  /\\\\\\\\ \n");
				printf("  |. .| \n");
				printf("  \\_-_/ \n");
				printf(" /`   `\\ \n");
				printf("/_|   |_\\ \n");
				printf("\\_\\___/_/ \n");
				printf("  |   | \n");
				printf("  |   |\n");
				printf("  |_|_| \n");
				printf(" (__/__) \n");
		printf("\nNombre del Doctor %s  (Numero de pacientes: %d) \n\n",aux->nombre_doctor,aux->n_pacientes);

			while(a != 0)
			{

				printf("\nNombre: %s \nPadecimiento: %s \nGravedad: %d \n\n",a->nombre,a->padecimiento,a->gravedad);


				a=a->siguiente;
			}
			printf("\n%c",m);
			printf("\n--------------------------------------------\n");


		aux=aux->siguiente;
	}
	printf("\n\n\n");


}

void vaciar_todo(struct doctor ***inicio,struct doctor ***fin,struct paciente ***ini) //el nodo final estará apuntando a NULL
{

	struct doctor *aux=0,*p;
	struct paciente *a=0,*h,*pp=0;

	pp=(**ini);

	while(pp!=0)
	{
		h=pp->siguiente;
		free(pp);
		pp=h;
	}



	aux=(**inicio);


	while(aux != 0)
	{
		a=aux->ini;


			while(a != 0)
			{

				h=a->siguiente;
				free(a);
				a=h;

			}

		p=aux->siguiente;
		free(aux);
		aux=p;
	}

	(**fin)=0;
	(**inicio)=0;

}


#include <stdio.h>
#include <string.h>
#include <windows.h>

struct Data{
	char category[20];
	char type[20];
	int defense;
	int attack;
	int enchant;
	int id;
	int price;
	int durability;
	int cuantity;
	};

class ItemData{
	private:
		ItemData *sig;
		struct Data data;
		
	public:
		ItemData();
		~ItemData();
		void setSig(ItemData *);
		ItemData* getSig(void);
		void setData(struct Data);
		struct Data getData(void);
	};

class ItemDatabase{
	private:
		ItemData *begin;
		
	public:
		ItemDatabase();
		~ItemDatabase();
		void addItem(ItemData *);
		void printData(void);
		bool loadData(ItemData *);
		void saveData(FILE *);
		void deleteData(void);
		void searchData(char *, char *);
		void searchData(int);
		void deleteItem(ItemData *);
	};

class Inventory{
	private:
		ItemData *begin;
		
	public:
		Inventory();
	};
	
ItemData::ItemData(){
	sig = NULL;
	}
	
ItemDatabase::ItemDatabase(){
	begin = NULL;
	}

ItemData::~ItemData(){
	printf("\nItem de Categoria %s / Tipo %s eliminado",data.category,data.type);
	}
	
ItemDatabase::~ItemDatabase(){
	printf("\nBase de datos en memoria eliminada");
	}
	
Inventory::Inventory(){
	begin = NULL;
	}

void ItemDatabase::addItem(ItemData *data){
	ItemData *aux;
	if(!begin){
		begin = data;
		begin->setSig(NULL);
		return;
		}
	aux = begin;
	while(aux->getSig()){
		aux = aux->getSig();
		}
	aux->setSig(data);
	data->setSig(NULL);
	return;
	}

bool ItemDatabase::loadData(ItemData *data){
	char in[20];
	struct Data aux;
	fflush(stdin);
	printf("\nCategoria: ");
	gets(in);
	if(!strcmp(in, "fin"))
		return false;
	strcpy(aux.category, in);
	printf("Tipo: ");
	gets(in);
	strcpy(aux.type, in);
	printf("Ataque: ");
	scanf("%d", &aux.attack);
	printf("Defensa: ");
	scanf("%d", &aux.defense);
	printf("Precio: ");
	scanf("%d", &aux.price);
	printf("Durabilidad: ");
	scanf("%d", &aux.durability);
	printf("ID: ");
	scanf("%d", &aux.id);
	aux.enchant = 0;
	aux.cuantity = 0;
	data->setData(aux);
	return true;
	}

void ItemDatabase::printData(){
	ItemData *aux;
	struct Data data;
	aux = begin;
	while(aux){
		printf("\n\n\nCategoria: %s\nTipo: %s\nAtaque: %d\nDefensa: %d\nPrecio: %d\nDurabilidad: %d\nID: %d\nEncantamiento: %d\nCantidad: %d",aux->getData().category, aux->getData().type, aux->getData().attack, aux->getData().defense, aux->getData().price, aux->getData().durability, aux->getData().id, aux->getData().enchant, aux->getData().cuantity);
		aux = aux->getSig();
		}
	return;
	}
	
void ItemDatabase::saveData(FILE* file){
	ItemData *aux;
	struct Data data;
	aux = begin;
	while(aux){
		data = aux->getData();
		fwrite(&data, sizeof(data), 1, file);
		aux = aux->getSig();
		}
	return;
	}

void ItemDatabase::deleteData(){
	ItemData *auxDel,*auxSig;
	auxDel = begin;
	auxSig = begin->getSig();
	while(auxSig){
		delete auxDel;
		auxDel = auxSig;
		auxSig = auxSig->getSig();
		}
	delete auxDel;
	return;
	}
	
void ItemDatabase::searchData(char *cat, char *typ){
	ItemData *aux;
	if(!begin){
		printf("Base de datos vacia");
		getchar();
		return;
		}
	aux = begin;
	while(aux){
		if(!strcmp(aux->getData().category,cat)&&!strcmp(aux->getData().type,typ)){
			deleteItem(aux);
			return;
			}
		aux = aux->getSig();
		}
	printf("Item no encontrado en base de datos");
	getchar();
	return;
	}

void ItemDatabase::searchData(int id){
	ItemData *aux;
	if(!begin){
		printf("Base de datos vacia");
		getchar();
		return;
		}
	aux = begin;
	while(aux){
		if(id == aux->getData().id){
			deleteItem(aux);
			return;
			}
		aux = aux->getSig();
		}
	printf("Item no encontrado en base de datos");
	getchar();
	return;
	}
	
void ItemDatabase::deleteItem(ItemData *auxDel){
	ItemData *aux;
	aux = begin;
	if(auxDel == aux){
		begin = begin->getSig();
		delete auxDel;
		return;
		}
	while(aux->getSig() != auxDel){
		aux = aux->getSig();
		}
	if(!auxDel->getSig()){
		aux->setSig(NULL);
		delete auxDel;
		return;
		}
	aux->setSig(auxDel->getSig());
	delete auxDel;
	return;
	}

void ItemData::setSig(ItemData *data){
	sig = data;
	return;
	}

ItemData* ItemData::getSig(){
	return sig;
	}

void ItemData::setData(struct Data aux){
	data = aux;
	return;
	}

struct Data ItemData::getData(){
	return data;
	}

char* changeName(char *nom){
	int i = 0;
	char lof[5] = {".lof"};
	while(nom[i] != '\0'){
		i++;
		}
	for(int j = i; j <= i+4; j++){
		nom[j] = lof[j-i];
		}
	return nom;
	}

int main(void){
	ItemDatabase *iDb = new ItemDatabase;
	ItemData *iD;
	FILE *savedData;
	struct Data aux;
	int election;
	char str[2][20];
	bool quitFlag = 0;
	while(!quitFlag){
		printf("1. Crear base de datos en memoria\n2. Cargar base de datos .lof en memoria\n3. Guardar base de datos como .lof\n4. Guardar base de datos en un .lof existente\n5. Imprimir base de datos desde memoria\n6. Eliminar base de datos en memoria\n7. Eliminar especificamente segun ...\n8. Salir\n\n-> ");
		scanf("%d", &election);
		switch(election){
			case 1:
				iD = new ItemData;
				while(iDb->loadData(iD)){
					iDb->addItem(iD);
					iD = new ItemData;
					}
				delete iD;
				break;
			
			case 2:
				savedData = fopen("database.lof", "a+b");
				fseek(savedData, 0, SEEK_SET);
				fread(&aux, sizeof(aux), 1, savedData);
				while(!feof(savedData)){
					iD = new ItemData;
					iD->setData(aux);
					iDb->addItem(iD);
					fread(&aux, sizeof(aux), 1, savedData);
					}
				fclose(savedData);
				break;
			
			case 3:
				fflush(stdin);
				printf("\n\nNombre de la base de datos: ");
				gets(str[0]);
				savedData = fopen(changeName(str[0]), "wb");
				fseek(savedData, 0, SEEK_END);
				iDb->saveData(savedData);
				fclose(savedData);
				break;
			
			case 4:
				savedData = fopen("database.lof", "a+b");
				fseek(savedData, 0, SEEK_END);
				iDb->saveData(savedData);
				fclose(savedData);
				break;
			
			case 5:
				iDb->printData();
				getchar();
				getchar();
				break;
			
			case 6:
				iDb->deleteData();
				delete iDb;
				iDb = new ItemDatabase;
				getchar();
				getchar();
				break;
			
			case 7:
				system("cls");
				printf("1. Categoria / Tipo\n2. ID\n3. Volver\n\n--> ");
				scanf("%d",&election);
				switch(election){
					case 1:
						fflush(stdin);
						printf("\nCategoria: ");
						gets(str[0]);
						printf("Tipo: ");
						gets(str[1]);
						iDb->searchData(str[0],str[1]);
						getchar();
						break;
						
					case 2:
						fflush(stdin);
						printf("\nID: ");
						scanf("%d",&election);
						iDb->searchData(election);
						getchar();
						getchar();
						break;
					
					default:
						break;
					}
				break;
			
			case 8:
				quitFlag = 1;
				break;
				
			default:
				break;
			}
		system("cls");
		}
	return 0;
	}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include<stdbool.h>
//D���m Olu�turma (Etiket, A��rl�k, Next)
struct node
{
    int label;
    int weight;
    struct node* next;
};

//D���m� yeniden adland�rma
typedef struct node Node;

//Graf Yap�s� Olu�turma
struct graph
{
    int num_vertices; //K��e Say�s�
    Node** adj_list; //Kom�uluk Listesi
};

//Graf� yeniden adland�rma
typedef struct graph Graph;

//Yeni d���m olu�turma
Node* createNode(int v,int weight)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->label = v;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

//Bo� graf olu�turma
Graph* CreateNullGraph(int vertices)
{

    Graph* G = malloc(sizeof(Graph)); //dinamik bellekten Graf yap�s� kadar yer ay�rma
    G->num_vertices = vertices;

    G->adj_list = malloc(vertices * sizeof(Node*)); //Graf�n kom�uluk matrisi = D���m�n boyutu * k��eler (Tepe) kadar bellekten yer ay�rma

    int i;
    for (i = 0; i < vertices; i++) { //t�m tepeleri gezecek for d�ng�s�
        G->adj_list[i] = NULL; //bo� graf oldu�u i�in kom�uluk matrisi Bo�
    }
    return G;
}

//D���mlerin aras�ndaki kenarlar�n olu�turulmas�
void add_edge(Graph* G, int src, int dest,int directed, int weight) //kaynaktan hedefe, y�nl�-y�ns�z ve a��rl�kl� d���mlere kenar ekleme
{
    if(directed==0)
        weight=1;
    Node* newNode = createNode(dest,weight);
    newNode->next = G->adj_list[src];
    G->adj_list[src] = newNode;

    if(!directed)
    {
        Node* srcNode = createNode(src,weight);
        srcNode->next = G->adj_list[dest];
        G->adj_list[dest] = srcNode;
    }
}

//Graf� ekrana yazd�rma
void printGraph(Graph* G)
{
    int v;
    for (v = 0; v < G->num_vertices; v++)
    {
        Node* temp = G->adj_list[v];
        printf("%d = ", v);
        while (temp)
        {
            printf("%d -> ", temp->label);
            temp = temp->next;
        }
        printf("\n");
    }
}

//Dereceleri yazd�rma
void printDegrees(Graph* G)
{
    int v;
    for (v = 0; v < G->num_vertices; v++)
    {
        int d =0;
        Node* temp = G->adj_list[v];
        printf("Dugumun derecesi %d = ", v);
        while (temp)
        {
            d++;
            temp = temp->next;
        }
        printf("%d\n",d);
    }
}
//Kom�u olup olmad���n� kontrol eden fonksiyon
int isNeighbor(Graph* G, int src, int dest) //Graf, kaynak, hedef
{
    Node* tempList= G->adj_list[src];
    while(tempList != NULL)
    {
        if(tempList->label == dest)
            return tempList->weight;
        tempList=tempList->next;

    }
    return 0;
}

//Kom�uluk matrisini yazd�rma
void AdjMatris(Graph* G)
{
    int i,j;
    FILE *fp = fopen("output.txt","w"); //output.txt dosyas� "yazma" modunda a��l�r
    for(i=0;i<G->num_vertices;i++) //t�m k��eler bitene kadar gezilecek
    {
        for(j=0;j<G->num_vertices;j++)
        {
            fprintf(fp,"%d ",isNeighbor(G,i,j)); //dosyaya kom�ular�n� yazd�rma
        }
        fprintf(fp,"\n");
    }
    fclose(fp); //dosyay� kapatma
}

//Yol g�venilir mi
bool isSafe(int v, Graph* G, int path[], int pos)
{
    int i;
    if (!isNeighbor(G,path[pos - 1],v)) //yolun bir �nceki d���m� eklemek istenen d���m ile komsu mu
        return false;

    for ( i= 0; i < pos; i++) 
        if (path[i] == v)//daha �nce yola eklendi mi
            return false; //yola eklenemez

    return true; //yola eklenebilir
}

//Bulunan ��z�m� yazd�rma
void printSolution(int path[],Graph* G)
{
    int i;
    for(i= 0; i <G->num_vertices ; i++)
        printf("%d -> ", path[i]);
    //printf("%d -> ", path[0]);
}


void eulerYoluYazd�r(Graph* G){
	int tek=0;
	for(int i= 0; i <G->num_vertices ; i++){
	//tek derece
		if((sizeof(G->num_vertices[i]) %2 != 0){
			tek=i;
		}
	}
	baslangicTuruYazdir(tek);
}

void sonrakiTepeGecerliMi(int u,int v){
	//tek tepe noktas� mevcut ise;
	if(sizeof(G->num_vertices[u]) == 1)
	{
		return true;
	}
	//birden fazla tepe noktas� mevcut ise;
	else
	{
		//u-v k�pr� de�il ise
		//u'dan ulas�labilen kose say�s�
		visited=[false]*(G->num_vertices[v]);
			
		//kenar gezildikten sonra gezilen kenar�n silinmesi
		kenarSil(u,visited);
		visited=[false]*(G->num_vertices[v]);
			
		//kenar�n grafi�e yeniden eklenmesi
		add_edge(G,u,v,0,0);
		return false;
	}
}
void baslangicTuruYazdir(Graph* G, int u){
	int v;
	for(v=0;v < G->num_vertices; v++){
		if(sonrakiTepeGecerliMi(u,v))
		{
			printf("Gecerli tepeler: %d \t %d \n",u,v);
			//kenar gezildikten sonra gezilen kenar�n silinmesi
			kenarSil(u,visited);
			baslangicTuruYazdir(G,v);
		}			
	}
}


//ziyaret edilen kenar listeden kald�r�lacak
void kenarSil(Graph* G, int k1, int k2){
	for (int i = 0; i < G->num_vertices; i++) {
		if (i == k2){
			G->num_vertices[i].pop(k2);
		}
	}
}

int main()
{
	int noV=6;
	Graph* G=CreateNullGraph(noV);
	add_edge(G,0,1,0,0);
    add_edge(G,0,2,0,0);
    add_edge(G,1,2,0,0);
    add_edge(G,2,3,0,0);
    add_edge(G,3,4,0,0);
    add_edge(G,3,5,0,0);
    add_edge(G,4,5,0,0);
    AdjMatris(G); //komsuluk matrisi dosyaya yazd�r�l�yor
	
	//printDegrees(G);
	//eulerYoluYazd�r(G);

    return 0;
}

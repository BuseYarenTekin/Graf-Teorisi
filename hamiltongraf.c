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

//Hamilton Recursive Fonksiyon
bool HamiltonRec(Graph* G,int path[], int pos) //Rek�rsif olarak her bir kombinasyon kontrol edilir
{
    //T�m d�g�mler eklendiyse
    if (pos == G->num_vertices)
    {
        return true;
        if (isNeighbor(G,path[pos - 1],path[0])) //en bastaki d�g�m en sondaki d�g�me ba�l� ise
            return true; //Hamilton turu
        else
            return false;
    }
    int v;
    for ( v= 1; v < G->num_vertices; v++)
    {
        if (isSafe(v, G, path, pos))
        {
            path[pos] = v;
            if (HamiltonRec (G, path, pos + 1) == true) //grafa bu tepe eklenebilir mi- eger oyleyse bir sonraki elemana gec
                return true;
            path[pos] = -1;
        }
    }
    return false;
}

//Bulunan ��z�m� yazd�rma
void printSolution(int path[],Graph* G)
{
    int i;
    for(i= 0; i <G->num_vertices ; i++)
        printf("%d -> ", path[i]);
    //printf("%d -> ", path[0]);
}

//Hamilton Graf� olup olmad��� kontrol eden fonksiyon
bool HamiltonCycle(Graph* G)
{
    int i;
    int path[G->num_vertices];

    for (i= 0; i < G->num_vertices; i++)
        path[i] = -1;

    path[0] = 0; //yolun ba�lang�c� 0 olarak se�ilir

    if (HamiltonRec(G, path, 1) == false ) //Rek�rsif olarak 
    {
        printf("\nCozum bulunamadi");
        return false;
    }
    else
    {
        printSolution(path,G); //��z�m vard�r, ekrana yazd�rma
    }
    return true; //Hamilton graf�
}

int main()
{
	int noV=6;
	//ilk graf de�eri i�in Number of Vertices (6-1)
	//int noV=5;
	Graph* G=CreateNullGraph(noV);
	add_edge(G,0,1,0,0);
    add_edge(G,0,2,0,0);
    add_edge(G,1,2,0,0);
    add_edge(G,2,3,0,0);
    add_edge(G,3,4,0,0);
    add_edge(G,3,5,0,0);
    add_edge(G,4,5,0,0);
	//farkl� bir graf de�erleri i�in kenar ekleme
//	add_edge(G,0,4,0,0);
//	add_edge(G,0,2,0,0);
//	add_edge(G,4,2,0,0);
//	add_edge(G,2,1,0,0);
//	add_edge(G,2,3,0,0);
//	add_edge(G,1,3,0,0);

    AdjMatris(G); //komsuluk matrisi dosyaya yazd�r�l�yor
    HamiltonCycle(G);

    return 0;
}

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

//DFS dola��m�n� hesaplayan fonksiyon
void DFS(Graph* G, int vertex, int visited[]) //Graf, tepe, ziyaret_edilen[] 
{
    if(visited[vertex] == 0) //ziyaret_edilen dizisi bo�sa -- ziyaret edilen tepe yok ise
    {
        //printf("%d -> ",vertex);
        visited[vertex] = 1; //ziyaret edilen tepe var
        Node* tmp = G->adj_list[vertex]; //ziyaret edilen tepeyi kom�uluk matrisine ekleme
        while(tmp != NULL)
        {
            DFS(G,tmp->label,visited); //temp'e atanan tepenin etiketi ve a��rl��� ile DFS fonksiyonuna g�nder - RECURSIVE
            tmp = tmp->next; //bir sonraki tepeye ge�
        }
    }
}

//Ba�l� bile�en say�s�
int ConnectedComponent(Graph* G)
{
    int visited[G->num_vertices];
    int i;
    int noc = 1;
    int visitCounter=0;
    for(i=0;i<G->num_vertices;i++)
        visited[i] = 0;
    DFS(G,0,visited);
    for(i=0;i<G->num_vertices;i++)
        if(visited[i] == 1)
            visitCounter++;
    while(visitCounter != G->num_vertices)
    {
        for(i=0;i<G->num_vertices;i++)
            if(visited[i] == 0)
            {
                DFS(G,i,visited);
                break;
            }


        visitCounter=0;
        for(i=0;i<G->num_vertices;i++)
        if(visited[i] == 1)
            visitCounter++;
        noc++;
    }
    printf("%d \n",noc);
    return noc;
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
    if (!isNeighbor(G,path[pos - 1],v))
        return false;

    for ( i= 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

//Bulunan ��z�m� yazd�rma
void printSolution(int path[],Graph* G)
{
    int i;
    for(i= 0; i <G->num_vertices ; i++)
        printf("%d -> ", path[i]);
    //printf("%d -> ", path[0]);
}

//Ana men�
int main()
{
    int noV=5; //Tepe Say�s�
    Graph* G=CreateNullGraph(noV); //Tepe say�s� kadar d���m olan bo� graf olu�turma
    //Kenar ekleme
    add_edge(G,0,4,0,0);
    add_edge(G,0,2,0,0);
    add_edge(G,4,2,0,0);
    add_edge(G,2,1,0,0);
    add_edge(G,2,3,0,0);
    add_edge(G,1,3,0,0);
    add_edge(G,0,3,0,0);

    //AdjMatris(G);
    return 0;
}


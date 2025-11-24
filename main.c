#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define INFINITO INT_MAX
#define MAX_NOME 30
#define MAX_NOS 256
#define TOTAL_ARESTAS_FIXAS 136
#define COR_ROXO "\033[35m"
#define COR_VERMELHO "\033[31m"
#define COR_VERDE "\033[32m"
#define COR_AZUL "\033[34m"
#define COR_AMARELO "\033[33m"
#define COR_RESET "\033[0m"

typedef struct {
    const char* a;
    const char* b;
    int peso;
} ArestaFixa;

static const ArestaFixa ARESTAS_FIXAS[] = {
    {"Ayr'ka", "Hadur", 1},
    {"Ayr'ka", "Indra", 1},
    {"Bacchus", "Geddon", 1},
    {"Baker", "Hadur", 1},
    {"Baker", "Kiel", 1},
    {"Baker", "Osiris", 1},
    {"Baker", "Pallas", 1},
    {"Baker", "Tayac", 3},
    {"Banshee", "Fora", 1},
    {"Banshee", "Garron", 1},
    {"Banshee", "Leir", 1},
    {"Banshee", "Tamsa", 1},
    {"Banshee", "Yulin", 6},
    {"Branaugh", "Chronos", 3},
    {"Bremen", "Kallis", 1},
    {"Bremen", "Nyx", 1},
    {"Bremen", "Tanga", 3},
    {"Bremen", "Vega", 1},
    {"Caliban", "Nul", 6},
    {"Caliban", "Oberon", 3},
    {"Caliban", "Orion", 3},
    {"Caliban", "Viking", 3},
    {"Cano", "Davien", 3},
    {"Cano", "Pyro", 6},
    {"Castra", "Nyx", 1},
    {"Castra", "Oso", 6},
    {"Castra", "Oya", 1},
    {"Castra", "Pyro", 1},
    {"Cathcart", "Davien", 3},
    {"Cathcart", "Hades", 3},
    {"Cathcart", "Kilian", 6},
    {"Cathcart", "Nexus", 1},
    {"Centauri", "Elysium", 1},
    {"Centauri", "Nul", 1},
    {"Charon", "Genesis", 1},
    {"Charon", "Helios", 3},
    {"Charon", "Kins", 6},
    {"Charon", "Tyrol", 1},
    {"Chronos", "Kellog", 1},
    {"Corel", "Geddon", 1},
    {"Corel", "Genesis", 1},
    {"Corel", "Nemo", 1},
    {"Croshaw", "Ferron", 1},
    {"Croshaw", "Nul", 6},
    {"Croshaw", "Rhetor", 1},
    {"Croshaw", "Sol", 1},
    {"Davien", "Ferron", 1},
    {"Davien", "Kilian", 1},
    {"Davien", "Sol", 1},
    {"Eealus", "Oya", 6},
    {"Eealus", "Rihlah", 1},
    {"Eealus", "Trise", 3},
    {"Eealus", "Virtus", 1},
    {"Ellis", "Kilian", 1},
    {"Ellis", "Magnus", 1},
    {"Ellis", "Min", 6},
    {"Ellis", "Nexus", 1},
    {"Ellis", "Taranis", 3},
    {"Elysium", "Idris", 1},
    {"Elysium", "Leir", 6},
    {"Elysium", "Vanguard", 1},
    {"Ferron", "Idris", 3},
    {"Fora", "Nemo", 1},
    {"Fora", "Rhetor", 3},
    {"Garron", "Idris", 1},
    {"Garron", "Leir", 6},
    {"Geddon", "Gliese", 1},
    {"Genesis", "Taranis", 3},
    {"Goss", "Helios", 3},
    {"Goss", "Osiris", 1},
    {"Goss", "Tayac", 1},
    {"Goss", "Terra", 3},
    {"Goss", "Tyrol", 3},
    {"Gurzil", "Hadrian", 1},
    {"Gurzil", "Oya", 6},
    {"Gurzil", "Rihlah", 3},
    {"Hades", "Nemo", 1},
    {"Hades", "Nexus", 1},
    {"Hadrian", "Kiel", 1},
    {"Hadrian", "Oya", 1},
    {"Hadrian", "Pyro", 6},
    {"Hadrian", "Terra", 1},
    {"Hadur", "Pallas", 3},
    {"Helios", "Taranis", 3},
    {"Helios", "Tyrol", 6},
    {"Horus", "Kayfa", 3},
    {"Horus", "Kiel", 1},
    {"Horus", "Rihlah", 6},
    {"Idris", "Rhetor", 1},
    {"Indra", "Kins", 1},
    {"Indra", "Osiris", 1},
    {"Kabal", "Leir", 3},
    {"Kallis", "Oso", 1},
    {"Kayfa", "Rihlah", 1},
    {"Kellog", "Odin", 1},
    {"Kellog", "Vector", 3},
    {"Kellog", "Virgil", 3},
    {"Leir", "Vanguard", 6},
    {"Leir", "Yulin", 3},
    {"Magnus", "Stanton", 1},
    {"Magnus", "Terra", 3},
    {"Min", "Nexus", 1},
    {"Nul", "Vega", 3},
    {"Nyx", "Odin", 1},
    {"Nyx", "Pyro", 3},
    {"Nyx", "Tohil", 1},
    {"Nyx", "Virgil", 3},
    {"Oberon", "Tiber", 3},
    {"Oberon", "Vega", 1},
    {"Oberon", "Virgil", 1},
    {"Odin", "Tanga", 3},
    {"Orion", "Tiber", 1},
    {"Orion", "Viking", 1},
    {"Oslo", "Pyro", 6},
    {"Oso", "Pyro", 6},
    {"Oya", "Tohil", 3},
    {"Pallas", "Tal", 1},
    {"Pyro", "Stanton", 3},
    {"Pyro", "Terra", 6},
    {"Stanton", "Terra", 1},
    {"Taranis", "Terra", 6},
    {"Tayac", "Terra", 1},
    {"Tiber", "Vector", 1},
    {"Tiber", "Virgil", 1},
    {"Tohil", "Virtus", 1},
    {"Trise", "Virtus", 1},
    {"Vagabond", "Vanguard", 1},
    {"Vagabond", "Vulture", 1},
    {"Vanguard", "Voodoo", 1},
    {"Vega", "Virgil", 3},
    {"Vendetta", "Vesper", 1},
    {"Vendetta", "Voodoo", 1},
    {"Veritas", "Vermilion", 1},
    {"Veritas", "Volt", 1},
    {"Vermilion", "Virgo", 1},
    {"Virgo", "Vulture", 1},
};

typedef struct Aresta
{
    int destino;
    int peso;
    struct Aresta* proxima;
} Aresta;


typedef struct
{
    char nome[MAX_NOME];
    Aresta* listaArestas;
} No;

typedef struct
{
    int totalNos;
    No* listaNos;
} Grafo;

int encontrarIndice(Grafo* g, const char* nome)
{
    for (int i = 0; i < g->totalNos; i++)
    {
        if (strcmp(g->listaNos[i].nome, nome) == 0)
        {
            return i;
        }
    }

    return -1;
}

int adicionarNo(Grafo* g, const char* nome)
{
    int idx = encontrarIndice(g, nome);
    
    if (idx != -1)
    {                                                                               
        return idx;
    }

    if (g->totalNos >= MAX_NOS) {
        fprintf(stderr, "Erro: número máximo de nós (%d) atingido.\n", MAX_NOS);
        exit(1);
    }

    g->listaNos[g->totalNos].listaArestas = NULL;
    strncpy(g->listaNos[g->totalNos].nome, nome, MAX_NOME - 1);
    g->listaNos[g->totalNos].nome[MAX_NOME - 1] = '\0';

    return g->totalNos++;
}


void adicionarArestaDireta(Grafo* g, int origem, int destino, int peso)
{
    Aresta* a = malloc(sizeof(Aresta));
    a->destino = destino;
    a->peso = peso;
    a->proxima = g->listaNos[origem].listaArestas;
    g->listaNos[origem].listaArestas = a;
}

void adicionarAresta(Grafo* g, const char* origem, const char* destino, int peso)
{
    int o = adicionarNo(g, origem);
    int d = adicionarNo(g, destino);
    adicionarArestaDireta(g, o, d, peso);
    adicionarArestaDireta(g, d, o, peso);
}

void removerArestaDireta(Grafo* g, int origem, int destino)
{
    Aresta* atual = g->listaNos[origem].listaArestas;
    Aresta* anterior = NULL;

    while (atual) {
        if (atual->destino == destino) {
            if (anterior) anterior->proxima = atual->proxima;
            else g->listaNos[origem].listaArestas = atual->proxima;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->proxima;
    }
}

void removerAresta(Grafo* g, const char* origem, const char* destino)
{
    int o = encontrarIndice(g, origem);
    int d = encontrarIndice(g, destino);
    if (o == -1 || d == -1) return;
    removerArestaDireta(g, o, d);
    removerArestaDireta(g, d, o);
}

int obterPesoAresta(Grafo* g, int origem, int destino) {
    Aresta* atual = g->listaNos[origem].listaArestas;
    while (atual) {
        if (atual->destino == destino) return atual->peso;
        atual = atual->proxima;
    }
    return -1;
}

const char* corPorPeso(int peso) {
    if (peso <= 1) return COR_VERDE;
    if (peso <= 3) return COR_AMARELO;
    return COR_VERMELHO;
}

void carregarDadosEmCodigo(Grafo* g) {
    for (int i = 0; i < TOTAL_ARESTAS_FIXAS; i++) {
        adicionarAresta(g, ARESTAS_FIXAS[i].a, ARESTAS_FIXAS[i].b, ARESTAS_FIXAS[i].peso);
    }
}

void exibirGrafo(Grafo* g) {
    printf(COR_AZUL "Grafo com %d nos:" COR_RESET "\n", g->totalNos);
    for (int i = 0; i < g->totalNos; i++) {
        printf(COR_ROXO "[%d]" COR_RESET " %s\n", i, g->listaNos[i].nome);
        Aresta* a = g->listaNos[i].listaArestas;
        if (!a) {
            printf(COR_AMARELO "  (sem arestas)" COR_RESET "\n");
        }
        while (a) {
            const char* corPeso = corPorPeso(a->peso);
            printf("  " COR_VERDE "->" COR_RESET " %s %s(peso %d)" COR_RESET "\n",
                   g->listaNos[a->destino].nome, corPeso, a->peso);
            a = a->proxima;
        }
    }
}

int menorDistancia(int dist[], int visitado[], int n) {
    int min = INFINITO, indice = -1;
    for (int i = 0; i < n; i++)
        if (!visitado[i] && dist[i] <= min)
            min = dist[i], indice = i;
    return indice;
}

void dijkstra(Grafo* g, int origem, int destino, int* distFinal, int anterior[]) {
    int n = g->totalNos;
    int dist[MAX_NOS], visitado[MAX_NOS];

    for (int i = 0; i < n; i++) {
        dist[i] = INFINITO;
        visitado[i] = 0;
        anterior[i] = -1;
    }

    dist[origem] = 0;

    for (int c = 0; c < n; c++) {
        int u = menorDistancia(dist, visitado, n);
        if (u == -1) break;

        visitado[u] = 1;

        Aresta* a = g->listaNos[u].listaArestas;
        while (a) {
            int v = a->destino;
            if (!visitado[v] && dist[u] + a->peso < dist[v]) {
                dist[v] = dist[u] + a->peso;
                anterior[v] = u;
            }
            a = a->proxima;
        }
    }

    *distFinal = dist[destino];
}

void imprimirCaminho(Grafo* g, int anterior[], int v) {
    if (v == -1) return;
    if (anterior[v] != -1) {
        imprimirCaminho(g, anterior, anterior[v]);
        printf(" " COR_AZUL "->" COR_RESET " ");
    }
    printf(COR_ROXO "%s" COR_RESET, g->listaNos[v].nome);
}

void dfs(Grafo* g, int v, int visitado[]) {
    visitado[v] = 1;
    Aresta* a = g->listaNos[v].listaArestas;
    while (a) {
        if (!visitado[a->destino]) dfs(g, a->destino, visitado);
        a = a->proxima;
    }
}

int estaConectado(Grafo* g) {
    int visitado[MAX_NOS] = {0};
    dfs(g, 0, visitado);

    for (int i = 0; i < g->totalNos; i++)
        if (!visitado[i]) return 0;
    return 1;
}

void habilitarModoRaw(struct termios* antigo) {
    tcgetattr(STDIN_FILENO, antigo);
    struct termios raw = *antigo;
    raw.c_lflag &= ~(ICANON | ECHO);
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void restaurarModoRaw(struct termios* antigo) {
    tcsetattr(STDIN_FILENO, TCSANOW, antigo);
}

int menuInterativo(const char* titulo, const char* opcoes[], int total) {
    struct termios antigo;
    habilitarModoRaw(&antigo);

    int selecionado = 0;
    while (1) {
        system("clear");
        printf(COR_VERMELHO "%s\n\n" COR_RESET, titulo);
        for (int i = 0; i < total; i++) {
            if (i == selecionado) printf(COR_ROXO "> %s" COR_RESET "\n", opcoes[i]);
            else printf("  %s\n", opcoes[i]);
        }
        printf("\nUse as setas Up/Down e Enter. Q para sair.\n");

        int ch = getchar();
        if (ch == '\n' || ch == '\r') {
            restaurarModoRaw(&antigo);
            return selecionado;
        } else if (ch == 'q' || ch == 'Q') {
            restaurarModoRaw(&antigo);
            return total - 1;
        } else if (ch == 27) {
            int seq1 = getchar();
            int seq2 = getchar();
            if (seq1 == '[') {
                if (seq2 == 'A') {
                    selecionado = (selecionado - 1 + total) % total;
                } else if (seq2 == 'B') {
                    selecionado = (selecionado + 1) % total;
                }
            }
        }
    }
}

void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void aguardarEnter(void) {
    printf("\nPressione Enter para voltar ao menu...");
    limparBufferEntrada();
}

double tempoDecorrido(clock_t inicio, clock_t fim) {
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}

// Encontra rota alternativa removendo temporariamente cada aresta do caminho principal
void rotaAlternativa(Grafo* g, int origem, int destino) {
    int anterior[MAX_NOS];
    int dist;

    dijkstra(g, origem, destino, &dist, anterior);

    if (dist == INFINITO) {
        printf("Nao existe caminho principal entre as estacoes.\n");
        return;
    }

    int caminho[MAX_NOS];
    int tam = 0;
    int atual = destino;

    while (atual != -1) {
        caminho[tam++] = atual;
        atual = anterior[atual];
    }

    printf(COR_AZUL "Caminho principal:" COR_RESET " ");
    for (int i = tam - 1; i >= 0; i--) {
        printf(COR_ROXO "%s" COR_RESET, g->listaNos[caminho[i]].nome);
        if (i > 0) printf(" " COR_AZUL "->" COR_RESET " ");
    }
    printf(" " COR_AMARELO "(custo %d)" COR_RESET "\n", dist);

    int melhorAlternativa = INFINITO;
    int melhorAnterior[MAX_NOS];

    for (int i = tam - 1; i > 0; i--) {
        int u = caminho[i];
        int v = caminho[i - 1];

        const char* noU = g->listaNos[u].nome;
        const char* noV = g->listaNos[v].nome;

        int pesoOriginal = obterPesoAresta(g, u, v);

        printf("\n" COR_VERMELHO "Testando falha na rota:" COR_RESET " %s " COR_AZUL "<->" COR_RESET " %s\n", noU, noV);

        removerAresta(g, noU, noV);

        int antTemp[MAX_NOS], distTemp;
        dijkstra(g, origem, destino, &distTemp, antTemp);

        if (distTemp != INFINITO) {
            printf("  " COR_VERDE "Caminho alternativo encontrado" COR_RESET " " COR_AMARELO "(custo %d)" COR_RESET ": ", distTemp);
            imprimirCaminho(g, antTemp, destino);
            printf("\n");

            if (distTemp < melhorAlternativa) {
                melhorAlternativa = distTemp;
                memcpy(melhorAnterior, antTemp, sizeof(int) * MAX_NOS);
            }
        } else {
            printf("  " COR_VERMELHO "Nenhum caminho alternativo disponivel." COR_RESET "\n");
        }

        if (pesoOriginal == -1) pesoOriginal = 1;
        adicionarAresta(g, noU, noV, pesoOriginal);
    }

    printf("\n" COR_AZUL "========== Resultado Final =========" COR_RESET "\n");
    if (melhorAlternativa == INFINITO) {
        printf(COR_VERMELHO "Nao existem rotas alternativas disponiveis." COR_RESET "\n");
    } else {
        printf(COR_VERDE "Melhor rota alternativa" COR_RESET " " COR_AMARELO "(custo %d)" COR_RESET ": ", melhorAlternativa);
        imprimirCaminho(g, melhorAnterior, destino);
        printf("\n");
    }
}

int main() {
    Grafo g;
    g.totalNos = 0;
    g.listaNos = malloc(sizeof(No) * MAX_NOS);

    carregarDadosEmCodigo(&g);

    removerAresta(&g, "Elysium", "Idris");
    removerAresta(&g, "Idris", "Rhetor");
    removerAresta(&g, "Rhetor", "Croshaw");
    removerAresta(&g, "Croshaw", "Nul");

    const char* opcoes[] = {
        "Exibir grafo",
        "Verificar conectividade",
        "Calcular menor caminho",
        "Sair"
    };

    while (1) {
        int escolha = menuInterativo("Menu principal", opcoes, 4);
        system("clear");

        if (escolha == 0) {
            clock_t t0 = clock();
            exibirGrafo(&g);
            clock_t t1 = clock();
            printf("\nTempo de execucao: %.6f s\n", tempoDecorrido(t0, t1));
            aguardarEnter();
        } else if (escolha == 1) {
            clock_t t0 = clock();
            if (estaConectado(&g))
                printf("Rede conectada.\n");
            else
                printf("Rede NAO conectada.\n");
            clock_t t1 = clock();
            printf("Tempo de execucao: %.6f s\n", tempoDecorrido(t0, t1));
            aguardarEnter();
        } else if (escolha == 2) {
            char origem[MAX_NOME], destino[MAX_NOME];
            printf("Origem: ");
            scanf("%29s", origem);
            printf("Destino: ");
            scanf("%29s", destino);
            limparBufferEntrada();

            int o = encontrarIndice(&g, origem);
            int d = encontrarIndice(&g, destino);

            if (o == -1 || d == -1) {
                printf("Estacao invalida.\n");
            } else {
                int anterior[MAX_NOS], dist;
                clock_t t0 = clock();
                dijkstra(&g, o, d, &dist, anterior);
                clock_t t1 = clock();

                if (dist == INFINITO)
                    printf("Nao existe caminho disponivel.\n");
                else {
                    printf("Custo minimo: %d\n", dist);
                    printf("Caminho: ");
                    imprimirCaminho(&g, anterior, d);
                    printf("\n");
                }
                printf("Tempo de execucao: %.6f s\n", tempoDecorrido(t0, t1));

                if (dist != INFINITO) {
                    char resposta;
                    printf("\nDeseja buscar uma rota alternativa? (s/n): ");
                    scanf(" %c", &resposta);
                    limparBufferEntrada();
                    if (resposta == 's' || resposta == 'S') {
                        rotaAlternativa(&g, o, d);
                    }
                }
            }
            aguardarEnter();
        } else if (escolha == 3) {
            break;
        }
    }

    return 0;
}

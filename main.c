#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_CAIXAS  5
#define NUM_NOMES   7

// declarando telas e funcoes //
void tela_perguntas();
void tela_cobra();
void tela_gousmas();
void tela_sair();
void limpar_tela(void);
int ler_inteiro(int min, int max);

// conteudo da caixa //
typedef enum { VAZIA, BOTAO, COBRA } Conteudo;

// estrutura da caixa //
typedef struct {
    Conteudo conteudo;
    int aberta;
} Caixa;

void embaralhar_caixas(Caixa caixas[]);
void exibir_caixas(const Caixa caixas[]);
int escolher_nome(int jogador, int outro_idx);
int pedir_caixa(const Caixa caixas[]);

// nomes para o jogo cobra na caixa //
const char *NOMES[NUM_NOMES] = {
    "Amira", "Ramses", "Nefertari", "Tutmes",
    "Bastet", "Anubis", "Khamul"
};

// funcao para o programa ler apenas numeros permitidos //
int ler_inteiro(int min, int max) {
    int valor;
    while (1) {
        if (scanf("%d", &valor) != 1) {
            while (getchar() != '\n'); // limpa o que o usuario entrou
            printf("Opcao invalida. Digite um numero: ");
            continue;
        }
        while (getchar() != '\n'); // limpa...
        if (valor < min || valor > max) {
            printf("Opcao invalida. Digite entre %d e %d: ", min, max);
            continue;
        }
        return valor;
    }
}

// tela do menu principal //
int main(){
    srand((unsigned int)time(NULL)); 
    int opcao = 0;

    while (opcao != 4) {
        limpar_tela();
        printf("GAME HUB\n\n"
               "1: Perguntas e respostas \n"
               "2: Cobra na caixa! \n"
               "3: Gousmas war \n"
               "4: Sair \n\n"
               "Escolha uma opcao: ");

        opcao = ler_inteiro(1, 4);

        switch (opcao) {
            case 1: tela_perguntas(); break;
            case 2: tela_cobra(); break;
            case 3: tela_gousmas(); break;
            case 4: tela_sair(); break;
        }
    }
    return 0; 
}

// jogo perguntas e respostas //
void tela_perguntas(){
    limpar_tela();
    
    printf("PERGUNTAS E RESPOSTAS\n\nNesse primeiro jogo, voce ira responder cinco perguntas.\nSerao apresentadas quatro alternativas, porem so uma sera a certa.\n\n");

    printf("1. Qual filme venceu o premio de Melhor Filme no Oscar de 2020?\n");
    printf("1) 1917\n2) Coringa\n3) Parasita\n4) Era Uma Vez em... Hollywood\n\n");
    int resposta1 = ler_inteiro(1, 4);
    if(resposta1 == 3) printf("Correto!\n\n");
    else printf("Incorreto. 'Parasita' era a resposta correta\n\n");

    printf("2. Qual destes diretores dirigiu o filme Titanic?\n");
    printf("1) Steven Spielberg\n2) Christopher Nolan\n3) James Cameron\n4) Quentin Tarantino\n\n");
    int resposta2 = ler_inteiro(1, 4);
    if(resposta2 == 3) printf("Correto!\n\n");
    else printf("Incorreto. 'James Cameron' era a resposta correta!\n\n");

    printf("3. Qual e um dos filmes de maior bilheteria da historia, dirigido por James Cameron?\n");
    printf("1) Avatar\n2) O Senhor dos Aneis\n3) Jurassic Park\n4) Vingadores\n\n");
    int resposta3 = ler_inteiro(1, 4);
    if(resposta3 == 1) printf("Correto!\n\n");
    else printf("Incorreto. 'Avatar' era a resposta correta!\n\n");

    printf("4. Qual desses diretores e conhecido pelo filme Pulp Fiction?\n");
    printf("1) Martin Scorsese\n2) Quentin Tarantino\n3) Ridley Scott\n4) Tim Burton\n\n");
    int resposta4 = ler_inteiro(1, 4);
    if(resposta4 == 2) printf("Correto!\n\n");
    else printf("Incorreto. 'Quentin Tarantino' era a resposta correta!\n\n");

    printf("5. Qual destes filmes faz parte da franquia Star Wars?\n");
    printf("1) Interestelar\n2) Matrix\n3) Blade Runner 2049\n4) Rogue One\n\n");
    int resposta5 = ler_inteiro(1, 4);
    if(resposta5 == 4) printf("Correto!\n");
    else printf("Incorreto. 'Rogue One' era a resposta correta!\n");
    
 
    printf(" FIM DE JOGO\n\n");
    printf("Deseja jogar novamente? (S/N): ");
    
    char resposta;
    scanf(" %c", &resposta); 
    
    // limpa... //
    while (getchar() != '\n'); 

    if (resposta == 'S' || resposta == 's') {
        tela_perguntas(); 
    } 

}

// jogo cobra na caixa //
int escolher_nome(int jogador, int outro_idx) {
    while (1) {
        printf("\nJogador %d, escolha seu nome:\n\n", jogador);
        for (int i = 0; i < NUM_NOMES; i++) {
            if (i == outro_idx)
                printf("%d. %-12s (ja escolhido)\n", i + 1, NOMES[i]);
            else
                printf("%d. %s\n", i + 1, NOMES[i]);
        }
        printf("\nOpcao: ");
        int escolha = ler_inteiro(1, NUM_NOMES);
        
        if (escolha - 1 == outro_idx) {
            printf("Este nome ja foi escolhido. Escolha outro.\n");
            continue;
        }
        return escolha - 1;
    }
}

void embaralhar_caixas(Caixa caixas[]) {
    for (int i = 0; i < NUM_CAIXAS; i++) {
        caixas[i].conteudo = VAZIA;
        caixas[i].aberta   = 0;
    }
    int pos_botao = rand() % NUM_CAIXAS;
    caixas[pos_botao].conteudo = BOTAO;

    int pos_cobra;
    do {
        pos_cobra = rand() % NUM_CAIXAS;
    } while (pos_cobra == pos_botao);
    caixas[pos_cobra].conteudo = COBRA;
}

void exibir_caixas(const Caixa caixas[]) {
    printf("\nCaixas:\n\n");
    for (int i = 0; i < NUM_CAIXAS; i++) printf("+--------+ ");
    putchar('\n');
    for (int i = 0; i < NUM_CAIXAS; i++) printf("|  [%d]   | ", i + 1);
    putchar('\n');
    for (int i = 0; i < NUM_CAIXAS; i++) {
        if (!caixas[i].aberta) printf("|   ???  | ");
        else if (caixas[i].conteudo == VAZIA) printf("|  VAZIA | ");
        else if (caixas[i].conteudo == BOTAO) printf("| [BOTAO]| ");
        else printf("| ~COBRA~| ");
    }
    putchar('\n');
    for (int i = 0; i < NUM_CAIXAS; i++) printf("+--------+ ");
    putchar('\n');
}

int pedir_caixa(const Caixa caixas[]) {
    while (1) {
        printf("\nEscolha uma caixa (1 a %d): ", NUM_CAIXAS);
        int escolha = ler_inteiro(1, NUM_CAIXAS);
        if (caixas[escolha - 1].aberta) {
            printf("A caixa %d ja foi aberta! Escolha outra.\n", escolha);
            continue;
        }
        return escolha - 1;
    }
}

void tela_cobra() {
    limpar_tela();
    printf("COBRA NA CAIXA\n\nNesse segundo jogo, dois exploradores ficam presos em uma tumba egipcia e precisam escolher entre cinco caixas enquanto Uma delas contem o botao para abrir a porta a outra esconde uma cobra mortal. Procure o botao e evite a cobra.\n");
    
    int idx1 = escolher_nome(1, -1);
    int idx2 = escolher_nome(2, idx1);

    int atual = rand() % 2;
    const char *nomes[2] = { NOMES[idx1], NOMES[idx2] };

    limpar_tela();
    printf("COBRA NA CAIXA\n\n%s comeca!\n", nomes[atual]);
    printf("Pressione ENTER para continuar...");
    getchar();

    Caixa caixas[NUM_CAIXAS];
    embaralhar_caixas(caixas);

    int fim = 0;
    int vencedor = -1;
    Conteudo resultado_final = VAZIA;

    while (!fim) {
        limpar_tela();
        printf("COBRA NA CAIXA\n\nVez de: %s\n", nomes[atual]);
        exibir_caixas(caixas);

        int idx_caixa = pedir_caixa(caixas);
        caixas[idx_caixa].aberta = 1;

        limpar_tela();
        printf("COBRA NA CAIXA\n\nVez de: %s\n", nomes[atual]);
        exibir_caixas(caixas);

        if (caixas[idx_caixa].conteudo == BOTAO) {
            printf("\n*** BOTAO ENCONTRADO! ***\nA porta se abre - %s venceu!\n", nomes[atual]);
            vencedor = atual;
            resultado_final = BOTAO;
            fim = 1; 
        } else if (caixas[idx_caixa].conteudo == COBRA) {
            printf("\n~~~ COBRA! ~~~\n%s foi picado(a)! A tumba guarda seus segredos...\n", nomes[atual]);
            vencedor = atual;
            resultado_final = COBRA;
            fim = 1; 
        } else {
            printf("\nCaixa %d esta vazia. Nada acontece.\n", idx_caixa + 1);
            atual ^= 1; 
            printf("A vez passa para %s.\n", nomes[atual]);
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
    }

    printf("\n");
    if (resultado_final == BOTAO) printf("VITORIA de %s!\n", nomes[vencedor]);
    else printf("DERROTA de %s!\n", nomes[vencedor]);

    printf("\nDeseja jogar novamente? (S/N): ");
    char resposta;
    scanf(" %c", &resposta);
    while (getchar() != '\n'); // limpa... //

    if (resposta == 'S' || resposta == 's') {
        tela_cobra(); // volta para tela inicial do proprio jogo //
    }
} // fim da tela cobra //

// jogo gousmas war //
void tela_gousmas() {
    int jogar_novamente = 1;

    while (jogar_novamente) {
        limpar_tela();
        printf("GOUSMAS WAR\n\nNesse terceiro jogo, cada jogador possui duas Gousmas que começam com nível de furia 1 e, ao atacar outra, transferem toda sua fúria para o alvo. Se uma Gousma ultrapassar fúria 5, ela e destruida. Os jogadores podem dividir suas Gousmas para distribuir a fúria, respeitando o limite de duas por jogador. Vence quem eliminar todas as Gousmas do adversario.");

        int idx1 = escolher_nome(1, -1);
        int idx2 = escolher_nome(2, idx1);

        const char *nomes[2] = { NOMES[idx1], NOMES[idx2] };
        
       // furia comeca em 1 e perde quando 0 //
        int furia[2][2] = {{1, 1}, {1, 1}};
        int atual = rand() % 2;
        int fim = 0;
        int vencedor = -1;

        while (!fim) {
            limpar_tela();
            printf("GOUSMAS WAR\n\n");
            
            // Desenha a mesa limpa
            for (int i = 0; i < 2; i++) {
                printf("Jogador: %s\n", nomes[i]);
                for (int j = 0; j < 2; j++) {
                    if (furia[i][j] == 0)
                        printf("%d. Gousma %d: *DESTRUIDA*\n", j+1, j+1);
                    else
                        printf("%d. Gousma %d: Furia %d\n", j+1, j+1, furia[i][j]);
                }
                printf("\n");
            }

            printf("Vez de %s. Escolha sua acao:\n", nomes[atual]);
            printf("1. Atacar\n");
            printf("2. Dividir\n");
            printf("Opcao: ");
            
            int acao;
            while (1) {
                acao = ler_inteiro(1, 2);
                if (acao == 2 && furia[atual][0] <= 1 && furia[atual][1] <= 1) {
                    printf("Voce nao tem Gousmas com furia suficiente para dividir (precisa de pelo menos 2).\nEscolha outra acao: ");
                    continue;
                }
                break;
            }

            int opp = atual ^ 1; // inimigo //

            if (acao == 1) { // atacar //
                printf("\nQual Gousma sua vai atacar? (1 ou 2): ");
                int atacante;
                while (1) {
                    atacante = ler_inteiro(1, 2) - 1;
                    if (furia[atual][atacante] == 0) printf("Gousma destruida! Escolha outra: ");
                    else break;
                }

                printf("Qual Gousma inimiga sera o alvo? (1 ou 2): ");
                int alvo;
                while (1) {
                    alvo = ler_inteiro(1, 2) - 1;
                    if (furia[opp][alvo] == 0) printf("Essa Gousma ja esta destruida! Escolha outra: ");
                    else break;
                }

                furia[opp][alvo] += furia[atual][atacante];
                printf("\n-> Gousma %d atacou a Gousma %d inimiga!\n", atacante+1, alvo+1);

                if (furia[opp][alvo] > 5) {
                    printf("-> A furia da Gousma %d inimiga passou de 5! Ela explodiu e foi DESTRUIDA!\n", alvo+1);
                    furia[opp][alvo] = 0;
                }
            } 
            else { // dividir //
                printf("\nQual Gousma sua vai DOAR furia? (1 ou 2): ");
                int doadora;
                while (1) {
                    doadora = ler_inteiro(1, 2) - 1;
                    if (furia[atual][doadora] <= 1) printf("Essa Gousma nao tem furia suficiente para doar. Escolha outra: ");
                    else break;
                }
                
                int receptora = doadora ^ 1; // pega a outra gousma // 
                int max_transfer = furia[atual][doadora] - 1; // nao pode zerar //
                
                if (furia[atual][receptora] == 0)
                    printf("Sua Gousma %d esta DESTRUIDA e revivera.\n", receptora+1);
                
                printf("Quanto de furia deseja transferir para a Gousma %d? (1 a %d): ", receptora+1, max_transfer);
                int qtd = ler_inteiro(1, max_transfer);

                furia[atual][doadora] -= qtd;
                furia[atual][receptora] += qtd;

                printf("\n-> Transferiu %d de furia da Gousma %d para a Gousma %d!\n", qtd, doadora+1, receptora+1);

                if (furia[atual][receptora] > 5) {
                    printf("-> OOPS! A furia da sua Gousma %d passou de 5! Ela foi DESTRUIDA!\n", receptora+1);
                    furia[atual][receptora] = 0;
                }
            }

            printf("\nPressione ENTER para continuar...");
            getchar();

            // vendo a condicao de fim de jogo //
            if (furia[opp][0] == 0 && furia[opp][1] == 0) {
                vencedor = atual;
                fim = 1;
            } else if (furia[atual][0] == 0 && furia[atual][1] == 0) {
                // jogador dividindo a furia que nao permite //
                vencedor = opp;
                fim = 1;
            }

            if (!fim) atual ^= 1; // muda o turno //
        }

        limpar_tela();
        printf("GOUSMAS WAR\n\n--- FIM DE JOGO ---\n");
        printf("VITORIA DE %s!\n\n", nomes[vencedor]);

        printf("--- FIM DE JOGO ---\\n\\n");
		printf("Deseja jogar novamente? (S/N): ");

		char resposta;
		scanf(" %c", &resposta);
		while (getchar() != '\\n');
		if (resposta == 'S' || resposta == 's') {
    tela_gousmas();
}
    }

    printf("\nDeseja jogar novamente? (S/N): ");
    char resposta;
    scanf(" %c", &resposta);
    while (getchar() != '\n');

    if (resposta == 'S' || resposta == 's') {
        tela_gousmas(); // 
    }
} // fim tela gousmas //

// tela sair //
void tela_sair(){
    limpar_tela();
    printf("Saindo do Game Hub...\n\n");  
    printf("Pressione ENTER para fechar...");
    getchar();
}
```

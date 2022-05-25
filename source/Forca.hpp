//#ifndef Forca_hpp
//#define Forca_hpp

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
 
class Forca {
    public:
        enum Dificuldade{
            FACIL=1, MEDIO=2, DIFICIL=3
        };
    private:
        //TODO: armazenar os scores?
       
        std::vector< std::pair<int, std::string> > m_palavras; //<! palavras e sua ocorrência no Corpus
 
        std::string m_arquivo_scores; //<! nome do arquivo contendo os scores
 
        std::string m_arquivo_palavras; //<! nome do arquivo contendo as palavras
 
        Dificuldade d = Dificuldade::FACIL; //<! dificuldade do jogo
 
        std::string m_palavra_atual; //<! palavra sendo testada atualmente

        std::vector<std::string> array_palavras; //<! palavra já utilizada
 
        int m_tentativas_restantes = 6; //<! tentativas restantes

        std::vector< std::string > letras; //<! letras testadas
   
    public:
        /**
         * Cria a classe Forca
         * O construtor pode ou não validar os arquivos de entrada, no entanto, mesmo com 
         * os arquivos inválidos o objeto deve ser construído. Para o caso de arquivos de palavras
         * ou scores inválidos, use o método eh_valido.
         * @param palavras o arquivo que contém as palavras
         * @param scores o nome do arquivo que contém os scores
         * @see eh_valido
         */
        Forca( std::string palavras, std::string scores );
       
 
        /**
         * Valida os arquivos de entrada de acordo com as especificações.
         * Ao validar os arquivos, no caso de arquivos inválidos, este método deve retornar a 
         * razão correspondente de acordo com as especificações.
         * @return {T,""} se os arquivos estiverem válidos, {F,"razão"} caso contrário.
         */
        std::pair<bool, std::string> eh_valido();
 
        /**
         * Carrega os arquivos de scores e palavras preenchendo **ao menos** a estrutura m_palavras
         */
        void carrega_arquivos();
 
        /**
         * Modifica a dificuldade do jogo.
         * De acordo com a dificuldade configurada, o método proxima_palavra retornará palavras
         * diferentes.
         * @param d a dificuldade desejada
         * @see proxima_palavra
         */
        void set_dificuldade(Dificuldade d);
 
        /**
         * Retorna a próxima palavra de acordo com a dificuldade atual.
         * Este método deve atualizar o atributo m_palavra_atual e retornar a palavra um texto no formato
         * "_ _ _ _ ... _" dependendo do tamanho de m_palavra_atual. O método também deve sortear as 
         * letras que devem aparecer dependendo do nível de dificuldade.
         * @return a próxima palavra do conjunto de palavras disponível de acordo com a dificuldade atual.
         */
        std::string proxima_palavra();
 
        /**
         * Retorna a palavra atual que está sendo jogada.
         * @return o valor do atributo m_palavra_atual.
         */
        std::string get_palavra_atual();
 
        /**
         * Testa se uma letra pertence á palavra atual, retorna T se a letra pertence.
         * Este método testa se uma letra pertence à palavra atual e retorna True caso pertença. 
         * Caso contrário, o método deve atualizar o atributo m_tentativas_restantes, decrementando 
         * em 1, e retornar False.
         * @param palpite uma letra, que deve ser testada se pertence à palavra.
         * @return T se a palpite pertence à palavra, F caso contrário.
         */
        bool palpite(std::string palpite);
 
        /**
         * Em caso de Game Over este método deve retornar T.
         * @return T caso o m_tentativas_restantes do jogo esteja igual a 0, F caso contrário.
         */
        bool game_over();

        /**
         * Em caso de o jogador acertar todas as letrinhas, uma mensagem comemorativa aparecerá na tela.
         */
        void win();
 
        /**
         * Atualiza o número de tentativas restantes.
         * Este método é útil no caso do jogador escolher continuar o jogo.
         * @param tentativas atualiza o valor da variável m_tentativas_restantes.
         */
        void set_tentativas_restantes(int tentativas);
 
        /**
         * Retorna a quantidade de tentativas restantes.
         * @return a quantidade de tentativas restantes.
         */
        int get_tentativas_restantes();
 
        /**
         * Realiza a leitura e impressão do arquivo scores, apresentando seus valores e por fim retorna o valor das opções apresentadas
         */
        int leitura_scores();

        /**
         * Faz a leitura das palavras e seus respectivos valores de ocorrência
         * alocando-os no vector, para que assim seja facilitado o futuro 
         * tratamentos dos dados.
         */
         void carregar_palavras(std::string end_palavras);

        /**
         * Inicia o jogo da forca, mostrando a quantidade de letras, chances,* e uma tela amigavel ao jogador para que possa selecionar as letras
         */
         void jogar(bool reset);

        /**
         * Realiza a verificacao da letra escolhida pelo jogador, retornando verdadeiro ou * falso para se a letra já foi selecionada ou não
         */
         bool teste_letra(std::string palpite);

        /**
         * Realiza a alteração do arquivo scores, atribuido a ele 
         * novos valores, nomes e palavras de jogos recentes.
         */
         void alterar_scores(std::string nome_jogador);
         
};

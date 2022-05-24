#ifndef INTERFACE_HPP
#define INTERFACE_HPP
#include <iostream>

/**
 * Carrega os arquivos de palavras e de end_scores
 */
void loading_arquivos(std::string end_palavras, std::string end_scores);

/**
 * Mostra o menu e inicial e suas opções de palavra_escolhida
 */
int menu();

/**
 * Ao selecionar iniciar jogo, então as opções de dificuldade são apresentadas por meio dessa função
 */
int menu_dificuldade();

/**
 * Realiza a impressão do bonequinho da forca, adicionando um membro a cada erro
 */
void layout_boneco(int fichas);

/**
 * Atualiza o jogador das letras que estão faltando, como também mostra as letras testadas e contidas nas palavras
 */
int barrinha_de_letras(std::string palavra_escolhida, std::string palpite, int reset);

/**
 * Realiza a obtenção dos pontos nas quais o jogador obtem durante o acerto e erros dos palpites
 */
int set_pontos(int pontos);

#endif
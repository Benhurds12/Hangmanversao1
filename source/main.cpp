#include "Interface.hpp"
#include "Forca.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <list>
#include <stdlib.h> 
#include <time.h>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(int argc, char *argv[]){
  
  int layout_escolha=0, nv=0;
  pair<bool, string> teste;
  string nome_jogador;
  string palavra_escolhida;

  Forca jogo_da_forca( argv[1], argv[2] );

  system("clear");

  jogo_da_forca.carrega_arquivos();

  jogo_da_forca.carregar_palavras(argv[1]);

  teste = jogo_da_forca.eh_valido();
  if(teste.first == 1){
    cout << ">>> {True} Arquivos Válidos!." << endl; 
  } else {
    cout << ">>> {False} " << teste.second << endl;
    layout_escolha ++;
  }
  cout << "--------------------------------------------------------------------" << endl;
  cout << "Insira seu nome:\n";
  cin >> nome_jogador;
  while(layout_escolha == 0){
    layout_escolha = menu();

    if(layout_escolha == 1){ //JOGO INICIAL
      nv = menu_dificuldade();
      
      if(nv == 1){ //ESCOLHA DE DIFICULDADE
        jogo_da_forca.set_dificuldade(jogo_da_forca.Dificuldade::FACIL);
      } else if (nv == 2){
        jogo_da_forca.set_dificuldade(jogo_da_forca.Dificuldade::MEDIO);
      } else {
        jogo_da_forca.set_dificuldade(jogo_da_forca.Dificuldade::DIFICIL);
      }

      jogo_da_forca.jogar(0);
      
      layout_escolha = 1;
      
      while(layout_escolha == 1){

        cout << "\n--------------------------------------------------------------------" << endl;
        cout << "Deseja jogar novamente?" << endl;
        cout << "1 - Sim" << endl;
        cout << "2 - Não" << endl;
        cout << "Escolha: ";
        cin >> layout_escolha;

        if(layout_escolha == 1){
          system("clear");
          jogo_da_forca.jogar(1);
        } else {
          cout << "Salvando o resultado!\n";
          jogo_da_forca.alterar_scores(nome_jogador);
          cout << "=-------[ Até Logo ]-------=\n\n" << "Obrigado por jogar. Até a próxima!";
          return (0);
          
        }

      }

    } else if (layout_escolha == 3){
      layout_escolha = jogo_da_forca.leitura_scores();
    }
      else if (layout_escolha == 2){
  string voltar;
  cout << "=-------[ Gameplay ]-------=\n\n Ola, ";
  cout << nome_jogador<< "! aqui estão as regras do jogo:\n" <<
  "[1] É preciso adivinhar a palavra ou frase secreta que o jogo escolheu sugerindo cartas.\n"
  "[2] Exibiremos uma fila de travessões, representando cada letra do a palavra/frase secreta que estás a tentar adivinhar.\n"
  "[3] Cada adivinhação correta dá-lhe 1 ponto.\n[4] Cada palpite errado perde 1 ponto e mostraremos mais um parte do hangman\n"
  "[5] Ao errar 6 vezes é GAMEOVER!\n"
  "[6] Se conseguir acertar a palavra você ganha pontos extras!\n"
  "[7] Após uma ronda de adivinhação (desafio) estar completa, pode tentar outra"
     " palavra secreta ou desistir do jogo.\n\n";
     cout << "Quando estiver pronto para voltar ao menu, pressione qualquer letra ou numero e pressione enter:";
     cin >> voltar;
     layout_escolha=0;
      }
      else if(layout_escolha == 4){
        cout << "=-------[   AVISO   ]-------=" << '\n' << "\nDeseja realmente sair do jogo?[y/N] >";
          string saida;
          cin >> saida;
          saida = toupper(saida[0]);
          if(saida[0]=='Y'){
          system("clear");
          cout << "=-------[ Até Logo ]-------=\n\n" << "Obrigado por jogar. Até a próxima! ";
          exit (3);
          }
      }
      else if(layout_escolha==14){break;}
  }
  
  return 0;
}
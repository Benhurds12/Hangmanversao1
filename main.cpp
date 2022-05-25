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
          //cout << "Digite seu nome para atualizar a tabela de Scores: ";
          cout << "Salvando no arquivo de Scores!";
          //cin >> nome_jogador;
          jogo_da_forca.alterar_scores(nome_jogador);
        }

      }

    } else if (layout_escolha == 3){
      layout_escolha = jogo_da_forca.leitura_scores();
    }
      else if (layout_escolha == 2){
  cout << "=-------[ Gameplay ]-------=\n\n Hi, ";
  cout << nome_jogador<< "! here are the game rules:\n" <<
  "[1] You need to guess the secret word or phrase the game has chosen\n"
  "    by suggesting letters.\n"
  "[2] We will display a row of dashes, representing each letter of the\n"
  "    the secret word/phrase you're trying to guess.\n"
  "[3] Each correct guess earns you 1 point.\n"
  "[4] Each wrong guess you loose 1 point and I draw on component of a\n"
  "    hanged stick figure (the hangman!)\n"
  "[5] If you wrong guess 6 times you loose the challenge\n"
  "[6] If you can guess the secret word/phrase before the hangman is\n"
  "    complete you add 2 extra points to your overall score.\n"
  "[7] After a guessing round (challenge) is complete you may try another\n"
  "    secret word/phrase or quit the game.\n\n" << " Press Any letter to continue >";
      }
  }
  
  return 0;
}
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
          cout << "Digite seu nome para atualizar a tabela de Scores: ";
          cin >> nome_jogador;
          jogo_da_forca.alterar_scores(nome_jogador);
        }

      }

    } else if (layout_escolha == 2){
      layout_escolha = jogo_da_forca.leitura_scores();
    }
  }
  
  return 0;
}
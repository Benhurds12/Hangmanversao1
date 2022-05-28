#include "Interface.hpp"
#include "Forca.hpp"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

int set_pontos(int pont){
  static int pontos_salvos = 0;
  if(pont != 0){
    pontos_salvos = pont;
  }
  return pontos_salvos;
}

void loading_arquivos(string end_palavras, string end_scores){

  cout << ">>> Lendo arquivos de palavras [" << end_palavras << "] e scores [" << end_scores << "], por favor aguarde..." << endl;
  
  cout << "--------------------------------------------------------------------" << endl;
}

int menu(){
  int escolha=0;
  cout << "Bem vindo ao Jogo Forca! Por favor escolha uma das opções" << endl;
  cout << "1 - Iniciar Jogo" << endl;
  cout << "2 - Ver as regras do jogo" << endl;
  cout << "3 - Ver scores anteriores" << endl;
  cout << "4 - Fechar o jogo" << endl;
  cout << "Sua escolha: ";

  cin  >> escolha;
  //caso digite errado
  while(escolha != 2 && escolha != 3 && escolha != 4 && escolha != 1){
    cout << "WARNING!!!\n Os valores devem ser 1, 2, 3 ou 4! Tente novamente:";
    cin >> escolha;
  }

  system("clear");

  return escolha;
}

int menu_dificuldade(){
  int escolha_dificuldade=0;
  cout << "O nível fácil tem nomes de animais. O médio nomes de frutas. O nível difícil possui palavras diversas da lingua portuguesa" << endl;
  cout << "Vamos iniciar o jogo! Por favor escolha o nível de dificuldade:" << endl;
  cout << "1 - Fácil" << endl;
  cout << "2 - Médio" << endl;
  cout << "3 - Difícil" << endl;
  cout << "Sua escolha: ";
  
  cin >> escolha_dificuldade;
  while(escolha_dificuldade != 1 && escolha_dificuldade != 2 && escolha_dificuldade != 3){
    cout << "WARNING!!!\n Os valores devem ser 1, 2 ou 3! Tente novamente:";
    cin >> escolha_dificuldade;
  }

  return escolha_dificuldade;
}

void layout_boneco(int fichas){
  switch (fichas){
    case 6:
      cout << "\n =-------[ Hangman Challenge ]-------=  \n    ┌──────┐\n    │      │  \n";
      cout << "    │\n";
      cout << "    │\n";
      cout << "    │\n";
      cout << "    │\n";
      cout << "    │\n \n";
      break;
    case 5:
      cout << "\n =-------[ Hangman Challenge ]-------=  \n    ┌──────┐\n    │      │  \n";
      cout << "    │      0\n";
      cout << "    │\n";
      cout << "    │\n";
      cout << "    │\n";
      cout << "    │\n \n";
      break;
    case 4:
      cout << "\n =-------[ Hangman Challenge ]-------=  \n    ┌──────┐\n    │      │  \n";
      cout << "    │      0\n";
      cout << "    │      |\n";
      cout << "    │\n";
      cout << "    │\n";
      cout << "    │\n \n";
      break;
    case 3:
      cout << "\n =-------[ Hangman Challenge ]-------=  \n    ┌──────┐\n    │      │  \n";
      cout << "    │      0\n";
      cout << "    │      |\\ \n";
      cout << "    │\n";
      cout << "    │\n";
      cout << "    │\n \n";
      break;
    case 2:
      cout << "\n =-------[ Hangman Challenge ]-------=  \n    ┌──────┐\n    │      │  \n";
      cout << "    │      0\n";
      cout << "    │     /|\\ \n";
      cout << "    │\n";
      cout << "    │\n";
      cout << "    │\n \n";      
      break;
    case 1:
      cout << "\n =-------[ Hangman Challenge ]-------=  \n    ┌──────┐\n    │      │  \n";
      cout << "    │      0\n";
      cout << "    │     /|\\ \n";
      cout << "    │       \\ \n";
      cout << "    │\n";
      cout << "    │\n \n";
      break;
    case 0:
      cout << "\n =-------[ Hangman Challenge ]-------=  \n    ┌──────┐\n    │      │  \n";
      cout << "    │      0\n";
      cout << "    │     /|\\ \n";
      cout << "    │     / \\ \n";
      cout << "    │\n";
      cout << "    │\n \n";
  }
}

int barrinha_de_letras(string palavra_escolhida, string palpite, int reset){
  int tamanho_palavra = palavra_escolhida.length();
  int consoantes = max(1, int(tamanho_palavra/5));
  int indice1, indice2;
  int aux;
  string maiuscula;
  static string palavra_barrinha;
  static int letrinhas = 0;
  static int turno = 0;
  static int pontos = 0;
  static int pontos_perdidos = 0;
  static int erros = 0;

  if(reset == 1){
    palavra_barrinha = " ";
    turno = 0;
    letrinhas = 0;
    pontos_perdidos = 0;
    erros = 0;
  }

  unsigned seed = time(0);
  srand(seed);
  if(turno == 0){
    for(int i=0; i<tamanho_palavra; i++){
      palavra_barrinha[i] = '_';
    }
    do{
      indice1 = rand() % tamanho_palavra;
      indice2 = rand() % tamanho_palavra;
    } while(indice2 == indice1);
    while(consoantes > 0){
  
      for(int i=0; i<tamanho_palavra; i++){
        if(i == indice1 && consoantes > 0){
          maiuscula = toupper(palavra_escolhida[i]);
          
          palavra_barrinha[i] = maiuscula[0];
          consoantes -= 1;
          letrinhas ++;
        } else if (i == indice2 && consoantes > 0){
          maiuscula = toupper(palavra_escolhida[i]);
          
          palavra_barrinha[i] = maiuscula[0];
          consoantes -= 1;
          letrinhas ++;
        } else {
          
          palavra_barrinha[i] = '_';
        }
      }
    }

  } else {
    for(int i=0; i<tamanho_palavra; i++){
      maiuscula = toupper(palavra_escolhida[i]);

      //SE O PALPITE ESTIVER CORRETO
      if(maiuscula[0] == palpite[0] && palavra_barrinha[i] == '_'){
        palavra_barrinha[i] = maiuscula[0];
        letrinhas ++;
        pontos ++;
      } else {
        erros ++;
      }
    }
    
    if(erros == tamanho_palavra && pontos > pontos_perdidos){
      pontos_perdidos++;
      erros = 0;
    } else {
      erros = 0;
    }

    if(letrinhas == tamanho_palavra){
      pontos += 2;
      if(pontos_perdidos == 0){
        pontos ++;
      }
    }
  }
  

  for(int k=0; k<tamanho_palavra; k++){
    cout << palavra_barrinha[k] << " ";
  }
  cout << "\nPontos: " << (pontos-pontos_perdidos) << endl;
  

  turno ++;
  aux = set_pontos(pontos-pontos_perdidos);
  return letrinhas;
  
}
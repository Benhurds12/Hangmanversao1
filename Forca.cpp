#include "Forca.hpp"
#include "Interface.hpp"
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <list>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;


Forca::Forca(string palavras, string scores){
  this->m_arquivo_palavras = palavras;
  this->m_arquivo_scores = scores;
}

void Forca::carrega_arquivos(){
  fstream arquivo_palavra;
  fstream arquivo_scores;

  arquivo_palavra.open(m_arquivo_palavras, ios::in);
  arquivo_scores.open(m_arquivo_scores, ios::out | ios::app);

  loading_arquivos(m_arquivo_palavras, m_arquivo_scores);

  if(arquivo_palavra.is_open()){
    cout << ">>> ARQUIVOS DE PALAVRAS CARREGADO COM SUCESSO!" << endl;
  } else {
    cout << ">>> ERRO AO CARREGAR OS ARQUIVOS DE PALAVRAS!" << endl;
  }
  if(arquivo_scores.is_open()){
    cout << ">>> ARQUIVOS DE SCORES CARREGADO COM SUCESSO!" << endl;
  } else {
    cout << ">>> ERRO AO CARREGAR OS ARQUIVOS DE SCORES!" << endl;
  }

  cout << "--------------------------------------------------------------------" << endl;

  arquivo_palavra.close();
  arquivo_scores.close();
}

int Forca::leitura_scores(){
  string linha;
  char escolha_layout;
  fstream arquivo;
  arquivo.open(m_arquivo_scores, ios::in);
  while(getline(arquivo, linha)){
    cout << linha << endl;
  } 

  cout << "--------------------------------------------------------------------" << endl;
  
  cout << "Deseja voltar ao menu inicial?[Y/N]: ";
  cin >> escolha_layout;

  if(toupper(escolha_layout) == 'Y'){
    system("clear");
    return 0;
  } else {
    system("clear");
    cout << "(👍≖‿‿≖)👍 Jogo Finalizado ☜(ˆ▿ˆ☜)" << endl;
    return 3;
  }

  arquivo.close();
}

void Forca::set_dificuldade(Dificuldade d){
  system("clear");

  this->d = d;
}

void Forca::carregar_palavras(string end_palavras){
  ifstream arquivo_p;
  arquivo_p.open(end_palavras, ios::in);

  string linha, palavra;
  int frequencia, space;
  
  while(!arquivo_p.eof()){
    getline(arquivo_p, linha);
    frequencia = stoi(linha);
      
    space = linha.find(' ');
    palavra = linha.erase(0,space+1);

    m_palavras.push_back(make_pair(frequencia, linha));
      
  }

  arquivo_p.close();
}

pair<bool, string> Forca::eh_valido(){
  string palavra, scores;

  //REALIZANDO TESTES DE VALIDACAO DOS ARQUIVOS DE PALAVRAS
  for(int i=0; i<m_palavras.size(); i++){
    palavra = m_palavras[i].second;

    for(int k=0; k<palavra.length(); k++){ //TESTE DE LETRAS
      if(!isalpha(palavra[k]) || palavra[k] == '-'){

        return pair<bool, string>(false, "Caracteres que não estão entre [a/A - z/Z] ou contém hífen[-].");
      }
    }

    if(palavra.length() <= 4){ //TESTE DE QUANTIDADE
      
      return pair<bool, string>(false, "Palavra com tamanho menor ou igual a 4 letras.");
    }

    if(typeid(m_palavras[i].first).name() == NULL || m_palavras[i].first <= 0){

      return pair<bool, string>(false, "Palavra sem valor de frequencia valida.");
    }

  }

  //REALIZANDO TESTES DE VALIDACAO DOS ARQUIVOS DE SCORES
  fstream arquivo_scores;
  arquivo_scores.open(m_arquivo_scores, ios::in);

  string texto;
  while(getline(arquivo_scores, texto)){
    int contador=0;
    
    for(int i=0; i<texto.length(); i++){
      if(texto[i] == ';'){
        contador ++;
        if(contador > 3){
          return pair<bool, string>(false, "Presença de mais de 3 ;.");
        }

        if(contador == 1 && !isalpha(texto[i-1])){
          cout << texto[i-1] << endl;
          return pair<bool, string>(false, "Campo de dificuldade VAZIO.");
        }
        if(contador == 1 && !isalpha(texto[i+2])){
          cout << texto[i+2] << endl;
          return pair<bool, string>(false, "Campo de nome VAZIO.");
        }
        if(contador == 3 && (!isdigit(texto[i+2]))){
          if(texto[i+2] != '-'){
            return pair<bool, string>(false, "Campo de pontuação VAZIO");
          }
        }
      }
    }
  }

  return pair<bool, string>(true, "Arquivos validos!.");
}

string Forca::get_palavra_atual(){

  int palavra=0;
  int contador = 0;
  int finalizador = 0;
  unsigned seed = time(0);
  srand(seed);

  if(this->d == FACIL){ //NIVEL FACIL
    
    if(array_palavras.size() < 11){
      while(contador == 0){
        contador = 1;
        palavra = rand()%11;
        m_palavra_atual = m_palavras[palavra].second;

        for(auto it=array_palavras.begin(); it!=array_palavras.end(); it++){
          if(m_palavra_atual == *it){
            contador = 0;
          }
        }
      }
      array_palavras.push_back(m_palavras[palavra].second);
    
      return m_palavra_atual;
    } else {
      cout << "Não há mais palavras" << endl;
      return "invalid";
    }

  } else if (this->d == MEDIO){ //NIVEL MEDIO

    if(array_palavras.size() < 11){
      while(contador == 0){
        contador = 1;
        palavra = rand()%11;
        m_palavra_atual = m_palavras[palavra+11].second;

        for(auto it=array_palavras.begin(); it!=array_palavras.end(); it++){
          if(m_palavra_atual == *it){
            contador = 0;
          }
        }
      }
      array_palavras.push_back(m_palavras[palavra+11].second);
    
      return m_palavra_atual;
      
    } else {
      cout << "Não há mais palavras" << endl;
      return "invalid";
    }
    
  } else { //NIVEL DIFICIL

    if(array_palavras.size() < 11){
      while(contador == 0){
        contador = 1;
        palavra = rand()%11;
        m_palavra_atual = m_palavras[palavra+22].second;

        for(auto it=array_palavras.begin(); it!=array_palavras.end(); it++){
          if(m_palavra_atual == *it){
            contador = 0;
          }
        }
      }
      array_palavras.push_back(m_palavras[palavra+22].second);
    
      return m_palavra_atual;
      
    } else {
      cout << "Não há mais palavras" << endl;
      return "invalid";
    }
  }
}

int Forca::get_tentativas_restantes(){
  return this->m_tentativas_restantes;
}

bool Forca::palpite(string palpite){
  for(int i=0; i<m_palavra_atual.length(); i++){
    if(toupper(m_palavra_atual[i]) == toupper(palpite[0])){
      return true;
    }
  }
  return false;
}

bool Forca::teste_letra(string palpite){
  auto it2 = palpite;
  for(auto it=letras.begin(); it!=letras.end(); it++){
    if(*it == it2){
      return false;
    }
  }
  letras.push_back(palpite);
  return true;
}

void Forca::set_tentativas_restantes(int tentativas){
  this->m_tentativas_restantes += tentativas;
}

bool Forca::game_over(){
  if(get_tentativas_restantes() == 0){
    return true;
  } else {
    return false;
  }
}

void Forca::win(){
  cout << "Parabéns você acertou a palavra" << endl;
  cout << "(^o^)~≪☆*CONGRATULATIONS*☆≫~(^o^)／" << endl;
}

void Forca::alterar_scores(string nome_jogador){
  ofstream arquivo_edit;
  arquivo_edit.open(m_arquivo_scores, ios::app);
  string dificuldade;
  string ultimo_nome;

  if(this->d == FACIL){
    dificuldade = "Fácil";
  } else if (this->d == MEDIO){
    dificuldade = "Médio";
  } else {
    dificuldade = "Difícil";
  }
  arquivo_edit << "\n";
  arquivo_edit << dificuldade << "; " << nome_jogador << "; ";
  for(auto it=array_palavras.begin(); it !=array_palavras.end()-1; it++){
    arquivo_edit << *it << ", ";
  }
  arquivo_edit << array_palavras.back() << "; " << set_pontos(0);

  arquivo_edit.close();
}

void Forca::jogar(bool reset){
  string palavra_escolhida = get_palavra_atual();
  if(palavra_escolhida != "invalid"){
    string palpite_p, palavra_m;
    int letrinhas = 0;
    int resetando = 0;
    bool contem = false;

    if(reset == 1){
      m_tentativas_restantes = 6;
      letras.clear();
      resetando = 1;
    }

    cout << "Iniciando o Jogo no nível ";
    if(d == 1){
      cout << "Fácil";
    } else if(d == 2){
      cout << "Médio";
    } else {
      cout << "Difícil";
    }
    cout << ", será que você conhece essa palavra?" << endl;

    layout_boneco(m_tentativas_restantes);
    letrinhas = barrinha_de_letras(palavra_escolhida, palpite_p, resetando);

    while(get_tentativas_restantes() > 0){
      palpite_p = toupper(palpite_p[0]);
      
      do{
        cout << "Palpite: ";
        cin >> palpite_p;
        if(palpite_p[0]=='*'){  //                       AQUI ESTOU EU
          cout << "=-------[ Attention ]-------=" << '\n' << "\nDo you really want to quit the challenge? [y/N] >";
          cin >> palpite_p;
        if(palpite_p[0]=='y'){
          system("clear");
          cout << "=-------[ Farewell ]-------=\n\n" << "Thanks for playing. See you next time!";
          return 3;
        }
        else{
          cin >> palpite_p;
        }
        }
        palpite_p = toupper(palpite_p[0]);
      }while(teste_letra(palpite_p) == 0);


      if(palpite(palpite_p) == 1){
        system("clear");
        cout << "Muito bem! A palavra contém a letra " << palpite_p[0] << "!" << endl;
        layout_boneco(get_tentativas_restantes());
        letrinhas = barrinha_de_letras(palavra_escolhida, palpite_p, 0);
        resetando = 0;
        if(letrinhas >= palavra_escolhida.length()){
          win();
          break;
        }
        
      } else if (palpite(palpite_p) == 0){
        system("clear");
        cout << "Meh, não achei a letra " << palpite_p[0] << "! (ㆆ_ㆆ)" << endl;
        set_tentativas_restantes(-1);
        layout_boneco(get_tentativas_restantes());

        letrinhas = barrinha_de_letras(palavra_escolhida, palpite_p, 0);
        resetando = 0;
        
      }

    }

    if(game_over() == 1){
      cout << "O jogo acabou, a palavra era :" << palavra_escolhida << endl;
      /* cout << 
      " ________  ________  _____ ______   _______           ________  ___      ___ _______   _______     " << "\n" <<
      "|\\   ____\\|\\   __  \\|\\   _ \\  _   \\|\\  ___ \\         |\\   __  \\|\\  \\    /  /|\\  ___ \\ |\\   __ \\    " << "\n" <<
      "\\ \\  \\___|\\ \\  \\|\\  \\ \\  \\\\\\__\\ \\  \\ \\  __/|        \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\\ \\  \\|\\  ||   " << "\n" <<
      " \\ \\  \\  __\\ \\   __  \\ \\  \\|__| \\  \\ \\  \\_|/__       \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/_\\ \\   _  _\\  " << "\n" <<
      "  \\ \\  \\|\\  \\ \\  \\ \\  \\ \\  \\    \\ \\  \\ \\  \\_|\\ \\       \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\ \\  \\\\  \\| " << "\n" <<
      "   \\ \\_______\\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\_______\\       \\ \\_______\\ \\__/ /     \\ \\_______\\ \\__\\\\ _\\ " << "\n" <<
      "    \\|_______|\\|__|\\|__|\\|__|     \\|__|\\|_______|        \\|_______|\\|__|/       \\|_______|\\|__|\\|__|" << endl;
    */
      cout << "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡀⠀\n"<<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣤⣤⠀⠀⠀⢀⣴⣿⡶⠀⣾⣿⣿⡿⠟⠛⠁\n" << 
"⠀⠀⠀⠀⠀⠀⣀⣀⣄⣀⠀⠀⠀⠀⣶⣶⣦⠀⠀⠀⠀⣼⣿⣿⡇⠀⣠⣿⣿⣿⠇⣸⣿⣿⣧⣤⠀⠀⠀\n" << 
"⠀⠀⢀⣴⣾⣿⡿⠿⠿⠿⠇⠀⠀⣸⣿⣿⣿⡆⠀⠀⢰⣿⣿⣿⣷⣼⣿⣿⣿⡿⢀⣿⣿⡿⠟⠛⠁⠀⠀\n" <<
"⠀⣴⣿⡿⠋⠁⠀⠀⠀⠀⠀⠀⢠⣿⣿⣹⣿⣿⣿⣿⣿⣿⡏⢻⣿⣿⢿⣿⣿⠃⣼⣿⣯⣤⣴⣶⣿⡤⠀\n" <<
"⣼⣿⠏⠀⣀⣠⣤⣶⣾⣷⠄⣰⣿⣿⡿⠿⠻⣿⣯⣸⣿⡿⠀⠀⠀⠁⣾⣿⡏⢠⣿⣿⠿⠛⠋⠉⠀⠀⠀\n" <<
"⣿⣿⠲⢿⣿⣿⣿⣿⡿⠋⢰⣿⣿⠋⠀⠀⠀⢻⣿⣿⣿⠇⠀⠀⠀⠀⠙⠛⠀⠀⠉⠁⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠹⢿⣷⣶⣿⣿⠿⠋⠀⠀⠈⠙⠃⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠈⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣤⣤⣴⣶⣦⣤⡀⠀\n" <<
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⣠⡇⢰⣶⣶⣾⡿⠷⣿⣿⣿⡟⠛⣉⣿⣿⣿⠆\n" <<
"⠀⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⡎⣿⣿⣦⠀⠀⠀⢀⣤⣾⠟⢀⣿⣿⡟⣁⠀⠀⣸⣿⣿⣤⣾⣿⡿⠛⠁⠀\n" <<
"⠀⠀⠀⠀⣠⣾⣿⡿⠛⠉⢿⣦⠘⣿⣿⡆⠀⢠⣾⣿⠋⠀⣼⣿⣿⣿⠿⠷⢠⣿⣿⣿⠿⢻⣿⣧⠀⠀⠀\n" <<
"⠀⠀⠀⣴⣿⣿⠋⠀⠀⠀⢸⣿⣇⢹⣿⣷⣰⣿⣿⠃⠀⢠⣿⣿⢃⣀⣤⣤⣾⣿⡟⠀⠀⠀⢻⣿⣆⠀⠀\n" <<
"⠀⠀⠀⣿⣿⡇⠀⠀⢀⣴⣿⣿⡟⠀⣿⣿⣿⣿⠃⠀⠀⣾⣿⣿⡿⠿⠛⢛⣿⡟⠀⠀⠀⠀⠀⠻⠿⠀⠀\n" <<
"⠀⠀⠀⠹⣿⣿⣶⣾⣿⣿⣿⠟⠁⠀⠸⢿⣿⠇⠀⠀⠀⠛⠛⠁⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀\n" <<
"⠀⠀⠀⠀⠈⠙⠛⠛⠛⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n";

   }
  
  }

}

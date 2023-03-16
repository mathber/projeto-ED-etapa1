/*
  Aplicação para alterações diretamente no arquivo binário da base de dados
  Alunos:
  José Airton Rios Junior
  Lara Ramos Linhares
  Matheus Bertoldo
*/

#include "Atleta.hpp"
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

// Função para limpar a tela em todos os SOs
void clearTerminal() {
#if defined _WIN32
  system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
  system("clear");
#elif defined(__APPLE__)
  system("clear");
#endif
}
// insere atleta em uma posição específica
void insereAtleta(fstream &arquivo, int posicao, int tamanhoDoArq) {

  // inserção dos dados do atleta

  int id, ano;
  string nome, time, jogos, temporada;
  id = posicao;

  cout << "Insira as informações do novo atleta a seguir." << endl;
  cout << "Nome: ";
  cin.ignore();
  getline(cin, nome);
  cout << "Time: ";
  getline(cin, time);
  cout << "Jogos: ";
  getline(cin, jogos);
  cout << "Ano: ";
  cin >> ano;
  cout << "Temporada: ";
  cin.ignore();
  getline(cin, temporada);

  Atleta atletaNovo(id, nome, time, jogos, ano, temporada);

  // posicionando os atletas
  
  Atleta aux;
  int posFinal = tamanhoDoArq, cont=1;
  
  // a leitura e escrita ocorre no sentido do final até a posição que será trocada
  while((posFinal - cont) >= posicao){

    // é posicionado e lido o atleta 
    arquivo.seekg((posFinal - cont)*sizeof(Atleta));
    arquivo.read((char *) (&aux), sizeof(Atleta));
    
    // trocando o valor do id do atleta a ser alterado
    aux.setId(posFinal-cont+1);

    // é reescrito uma posição à frente
    arquivo.seekp((posFinal - cont + 1)*sizeof(Atleta));
    arquivo.write((const char *) (&aux), sizeof(Atleta));
    
    cont++;
  }

  // depois de posicionar todos os atletas uma posição à frente, o novo atleta é escrito na posição requisitada
  arquivo.seekp(posicao*sizeof(Atleta));
  arquivo.write((const char *) (&atletaNovo), sizeof(Atleta));

  cout << "\nAtleta inserido com sucesso!" << endl << endl;
  system("pause");

};
// visualiza registro em um dado intervalo
void visualizarRegistros(fstream &arquivo, int inicio, int fim) {
  Atleta atletaAux;

  int intervalo = fim - inicio;

  arquivo.seekg(inicio * sizeof(Atleta));
  for (int i = 0; i <= intervalo; i++) {
    arquivo.read((char *)(&atletaAux), sizeof(Atleta));
    atletaAux.imprimeAtleta();
  }

  // retornando para o início do vetor
  arquivo.seekg(0, arquivo.beg);
  system("pause");
};
// alterar os dados de registro em uma posição específica
void alteraDadosAtleta(fstream &arquivo, int posicao){
  // inserção dos dados do atleta

  int id, ano;
  string nome, time, jogos, temporada;
  id = posicao;

  Atleta aux;
  cout << "O atleta escolhido para alteração foi..." << endl << endl;

  arquivo.seekg(posicao*sizeof(Atleta));
  arquivo.read((char *) (&aux), sizeof(Atleta));
  aux.imprimeAtleta();

  cout << "\nDeseja mesmo continuar? (y/n) ";
  char escolha;
  cin >> escolha;
  
  if(escolha == 'y'){
  
    cout << "\nInsira as novas alterações do atleta." << endl << endl;
    
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Time: ";
    getline(cin, time);
    cout << "Jogos: ";
    getline(cin, jogos);
    cout << "Ano: ";
    cin >> ano;
    cout << "Temporada: ";
    cin.ignore();
    getline(cin, temporada);
  
    Atleta atletaNovo(id, nome, time, jogos, ano, temporada);
  
    arquivo.seekp(posicao*sizeof(Atleta));
    arquivo.write((const char *) (&atletaNovo), sizeof(Atleta));

    cout << "\nAtleta atualizado com sucesso!" << endl << endl;
    system("pause");
    
  } else {
    cout << "retornando ao menu..." << endl << endl;
  }
  
};
// trocar dois registro de posição
void trocaAtletas(fstream &arquivo, int posAtleta1, int posAtleta2){
  Atleta aux1, aux2;
  int auxId = posAtleta1;
  
  // pega os dois registros do binário para a troca
  arquivo.seekg(posAtleta1*sizeof(Atleta));
  arquivo.read((char *)(&aux1), sizeof(Atleta));

  arquivo.seekg(posAtleta2*sizeof(Atleta));
  arquivo.read((char *)(&aux2), sizeof(Atleta));

  cout << "\nOs atletas escolhidos para alteração são..." << endl << endl;
  aux1.imprimeAtleta();
  cout << endl;
  aux2.imprimeAtleta();

  cout << "\nDeseja mesmo continuar? (y/n) ";
  char escolha;
  cin >> escolha;

  if(escolha=='y'){
    // inverte os IDs dos registros
    aux1.setId(posAtleta2);
    aux2.setId(auxId);
  
    // insere os registros realizando a troca
    arquivo.seekp(posAtleta1*sizeof(Atleta));
    arquivo.write((const char *) (&aux2), sizeof(Atleta));
  
    arquivo.seekp(posAtleta2*sizeof(Atleta));
    arquivo.write((const char *) (&aux1), sizeof(Atleta));
  
    cout << "Atletas trocados com sucesso!\n\n";
    aux2.imprimeAtleta();
    aux1.imprimeAtleta();
  
    system("pause");
    
  } else {
    cout << "retornando ao menu..." << endl << endl;
  }
  
};

int main() {

  int opcao = 0, posicao, tamanhoDoArq;

  fstream arquivo("data_athlete_game_binary_test", ios::in | ios::out);

  if (arquivo) {

    cout << "\nLendo da base de dados 'data_athlete_game_binary'." << endl << endl;
    
    while (opcao != 6) {

      //clearTerminal();

      // MENU PRINCIPAL
      cout << "========= Atletas Database =========" << endl << endl;
      cout << "1 - Inserir atleta" << endl;
      cout << "2 - Visualizar atletas em um intervalo" << endl;
      cout << "3 - Alterar dados de um atleta" << endl;
      cout << "4 - Trocar atletas de posição" << endl;
      cout << "5 - Imprimir todos os atletas" << endl;
      cout << "6 - Sair" << endl << endl;

      cout << "Digite sua opção: ";
      cin >> opcao;

      switch (opcao) {
      // INSERIR ATLETA
      case 1:
        cout << "Informe a posição de inserção:" << endl;
        cin >> posicao;

        arquivo.seekg(0, arquivo.end);
        tamanhoDoArq = arquivo.tellg()/sizeof(Atleta);
        arquivo.seekg(0, arquivo.beg);
   
        insereAtleta(arquivo, posicao, tamanhoDoArq);

        break;
      // VIZUALIZAR ATLETA EM UM DADO INTERVALO
      case 2:

        int inicio, fim;

        arquivo.seekg(0, arquivo.end);
        tamanhoDoArq = arquivo.tellg()/ sizeof(Atleta);
        arquivo.seekg(0, arquivo.beg);

        cout << "Determine o intervalo de leitura dos atletas (de acordo com o ID)" << endl << endl;
        cout << "OBS: escolha os valores entre 0 e " << tamanhoDoArq-1 << endl;
        cout << "Digite um valor para o início: ";
        cin >> inicio;
        cout << "Digite um valor para o fim: ";
        cin >> fim;

        cout << endl << endl;
        visualizarRegistros(arquivo, inicio, fim);

        break;

      // ALTERAR DADOS DE UM ATLETA
      case 3:
        int id;
        cout << "Informe o ID do atleta para ser alterado.\nID: ";
        cin >> id;

        alteraDadosAtleta(arquivo, id);
        
        break;

      // TROCAR POSIÇÃO DE ATLETAS
      case 4:
        int id1, id2;

        arquivo.seekg(0, arquivo.end);
        tamanhoDoArq = arquivo.tellg()/sizeof(Atleta);
        arquivo.seekg(0, arquivo.beg);
        
        cout << "Informe os ID's para serem trocados." << endl;
        cout << "OBS: escolha os valores entre 0 e " << tamanhoDoArq-1 << endl;
        cout << "ID do primeiro atleta: ";
        cin >> id1;
        cout << "ID do segundo atleta: ";
        cin >> id2;

        trocaAtletas(arquivo, id1, id2);

        break;

      // IMPRIMIR ATLETA
      case 5:
        
        arquivo.seekg(0, arquivo.end);
        tamanhoDoArq = arquivo.tellg()/sizeof(Atleta);
        arquivo.seekg(0, arquivo.beg);

        cout << "Registros de Atletas salvos:\n\n";
        cout << "===========================================\n";
        
        visualizarRegistros(arquivo, 0, tamanhoDoArq-1);
        
        cout << "\n===========================================";

        break;

      // ENCERRAMENTO DO SISTEMA
      case 6:
        cout << "Encerrando sistema...\n\n\n";
        cout << "Feito por:\n\nJosé Airton\nLara Ramos\nMatheus Bertoldo\n\n";
        break;

      default:
        cout << "Valor Inválido!" << endl;
        cout << "Por favor, insira um valor válido.";
        break;
      }
    }
  } else {
    cout << "Infelizmente o arquivo 'data_athlete_game_binary' não foi "
            "encontrado e o programa não pode ser executado. Por favor, "
            "verifique a condição do arquivo.";
  }

  return 0;
}
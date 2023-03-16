/*
  Aplicação para converter o arquivo CSV em binário
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

int main() {

  Atleta *atletaAux = new Atleta;
  string linha;
  int opcao = 0;

  ifstream leitura("teste.csv");
  ofstream escrita("teste_binario", ios::binary);

  if (leitura) {
    // retirando a primeira linha
    getline(leitura, linha);
    while (getline(leitura, linha)) {

      *atletaAux = atletaAux->separaCampos(linha);
      atletaAux->imprimeAtleta();

      linha = "";

      escrita.write((const char *)(atletaAux), sizeof(Atleta));
    }

    escrita.close();

  } else {
    cout << "A leitura do arquivo não foi possível." << endl;
  }

  // delete[] vetorAtletas;
  leitura.close();

  cout << "A conversão do arquivo 'data_athlete_game' foi concluída com "
          "sucesso !"
       << endl
       << endl;
  system("pause");

  return 0;
}

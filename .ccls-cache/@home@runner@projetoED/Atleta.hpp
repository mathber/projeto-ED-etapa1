/*
  Aplicação da classe Atleta usada no main.cpp e menu.cpp
  Alunos:
  José Airton Rios Junior
  Lara Ramos Linhares
  Matheus Bertoldo
*/

#include <iostream>
#include <cstring>

class Atleta{
  private:
    int id;
    char nome[65];
    char time[25];
    char jogos[15];
    int ano;
    char temporada[10];
  public:
    Atleta();
    Atleta(int id, std::string nome, std::string time, std::string jogos, int ano, std::string temporada);
    void setId(int id);
    Atleta separaCampos(std::string linha);
    void imprimeAtleta();
};

Atleta::Atleta(){};
//obs.: o fim com \0 em cada string serve para garantir que não será armazenado lixo no arquivo binário
Atleta::Atleta(int id, std::string nome, std::string time, std::string jogos, int ano, std::string temporada){
  this->id = id;
  int tam = nome.length();
  for(int i=0; i<nome.length(); i++){
    this->nome[i] = nome[i];
  }
  this->nome[tam]='\0';
  tam = time.length();
  for(int i=0; i<time.length(); i++){
    this->time[i] = time[i];
  }
  this->time[tam]='\0';
  tam = jogos.length();
  for(int i=0; i<jogos.length(); i++){
    this->jogos[i] = jogos[i];
  }
  this->jogos[tam]='\0';
  this->ano = ano;
  tam = temporada.length();
  for(int i=0; i<temporada.length(); i++){
    this->temporada[i] = temporada[i];
  }
  this->temporada[tam]='\0';
};

void Atleta::setId(int id){
  this->id = id;
}

void Atleta::imprimeAtleta(){
  std::cout << "Id: " << id << std::endl;
  std::cout << "Nome: " << nome << std::endl;
  std::cout << "Time: " << time << std::endl;
  std::cout << "Jogos: " << jogos << std::endl;
  std::cout << "Ano: " << ano << std::endl;
  std::cout << "Temporada: " << temporada << std::endl << std::endl;
}

/* função que separa cada informação(string) antes da vírgula em atributo específico do objeto Atleta */
Atleta Atleta::separaCampos(std::string linha) {
  Atleta atleta;
  char letra;
  std::string campo;
  int cont = 0, contAspas = 0, tamCampo, tamLinha=linha.length();

  for(int i=0; i<=tamLinha; i++){
    // lê caracter por caracter
    letra = linha[i];
    
    if(letra=='"'){
      contAspas++;
    }
    // quando as aspas estiverem fechadas e o caracter atual for uma vírgula, ele preenche um campo
    if((letra==',' or i==tamLinha) and (contAspas%2==0)){

      tamCampo=campo.length();
      
      switch (cont) {
        case 0:
          atleta.id = stoi(campo);
          break;
        
        case 1:
          /* determina o fim do campo para que outras strings futuras não interfiram */
          atleta.nome[tamCampo]='\0';
          for(int i=0; i<tamCampo; i++){
            atleta.nome[i] = campo[i];
          }
          break;
        
        case 2:
          atleta.time[tamCampo]='\0';
          for(int i=0; i<tamCampo; i++){
            atleta.time[i] = campo[i];
          }
          break;
        
        case 3:
          atleta.jogos[tamCampo]='\0';
          for(int i=0; i<tamCampo; i++){
            atleta.jogos[i] = campo[i];
          }
          break;
        
        case 4:
          atleta.ano = stoi(campo);
          break;
        
        case 5:
          atleta.temporada[tamCampo]='\0';
          for(int i=0; i<tamCampo; i++){
            atleta.temporada[i] = campo[i];
          }
          break;
      }
      campo="";
      cont++;
    } else {
      // adiciona ao campo letra por letra
      campo += letra;
    }
  }      
  return atleta;
}

#include "hashTable.h"
static Sensor REMOVED_SENSOR(-1, "", ""); // Placeholder para dizer que o sensor foi deletado (como utilizamos nullptr pra indicar vazio, para removidos usa-se objeto de valor "vazio")
#define REMOVED (&REMOVED_SENSOR)
int M = BUFFER_SIZE;
/*
    Construtor da tabela hash
    Inicializa o array como nullptr (vazias)
*/
HashTable::HashTable(){
    for(int i = 0; i < BUFFER_SIZE; i++)data[i] = nullptr;
}

/*
    Função de inserção, recebe um sensor como parâmetro
    Calcula o índice com sondagem dupla
    Se a posição estiver vazia ou marcada como removida, insere o sensor
    Evita duplicatas de ID  
    Se houver colisão, incrementa i e tenta próxima posição
*/
void HashTable::insert(Sensor& sensor){
    
    int key = sensor.getId();

    // K%M & 1 + (K % (M-1)) = double hash
    int hash1 = key % M; int hash2 = 1 + (key % (M-1));

    for(int i =0; i< BUFFER_SIZE;i++){
        int index = (hash1 + i * hash2) % M;
        std::cout<<std::endl;
        std::cout<<"Trying to insert "<< key<<" at index ["<<index<<"]"<<std::endl;
        if(data[index] == nullptr || data[index] == REMOVED){
            data[index] = new Sensor(sensor);
            std::cout<<"Successfully inserted key "<<key<<" at index ["<<index<<"]"<<std::endl;
            return;
        }
        if (data[index]->getId() == key){
            std::cout<<"There is a sensor with same ID"<<std::endl;
            return;
        }
        number_of_colisions++;
    }
    std::cout<<"Hash Table is full!"<<std::endl;
    std::cout<<std::endl;
}

/*
    Função de busca, recebe uma chave (no caso, id) como parâmetro
    Calcula o índice usando sondagem dupla
    Percorre a tabela até encontrar o sensor ou uma posição vazia
    Retorna ponteiro para o sensor se encontrar, ou nullptr se não existir
*/
Sensor* HashTable::search(int key){
    // K%M & 1 + (K % (M-1)) = double hash
    // K%M & 1 + (K % (M-1)) = double hash
    int hash1 = key % M; int hash2 = 1 + (key % (M-1));
    std::cout<<std::endl;
    for(int i =0; i< BUFFER_SIZE;i++){
        int index = (hash1 + i * hash2) % M;
        std::cout<<"Searching "<< key<<" at index ["<<index<<"]"<<std::endl;
        if(data[index] == nullptr){
            std::cout<<"Element with key "<<key<<" doesn't exist at the calculated index ["<<index<<"]"<<std::endl;
            return nullptr;
        }
        if (data[index] != REMOVED && data[index]->getId() == key ){
            std::cout<<"Element with key "<<key<<" found at the calculated index ["<<index<<"]"<<std::endl;
            return data[index];
        }
    }
    std::cout<<"Hash table is full"<<std::endl;
    std::cout<<std::endl;
    return nullptr; //tabela com tamanho máximo
}

/* 
    Função de remoção, passa chave como parâmetro
    Percorre a tabela até encontrar o sensor
    Quando encontra, deleta o objeto e atribui o placeholder REMOVED
    Se não encontrar, informa que o sensor não existe
*/
void HashTable::_delete(int key){
    int hash1 = key % M; int hash2 = 1 + (key % (M-1));
    std::cout<<std::endl;
    for(int i =0; i< BUFFER_SIZE;i++){
        int index = (hash1 + i * hash2) % M;
        std::cout<<"Deleting "<< key<<" at index ["<<index<<"]"<<std::endl;
        if(data[index] == nullptr){
            std::cout<<"Element with key "<<key<<" not found ["<<index<<"]"<<std::endl;
            std::cout<<std::endl;
            return;
        }
        if (data[index] != REMOVED && data[index]->getId() == key){
            delete data[index];
            data[index] = REMOVED;
            std::cout<<"Element with key "<<key<<" deleted ["<<index<<"] successfully"<<std::endl;
            std::cout<<std::endl;
            return;
        }
    }
    std::cout << "Element with key " << key << " not found in table" << std::endl;
    std::cout << std::endl;
}

/*
    Retorna número total de colisões
*/
int HashTable::getNumberOfColisions(){
    return number_of_colisions;
}

/*
    Exibe todos os sensores guardados na tabela hash
    Mostra apenas ocupados
    Diz quantos índices estão disponíveis
*/
void HashTable::printHashTable(){
    int freeIndexes = 0;
    std::cout<<std::endl;
    std::cout<<"Printing Hash Table:"<<std::endl;
    for(int i=0;i<BUFFER_SIZE;i++){
        if(data[i] != nullptr && data[i] != REMOVED){
            data[i]->show();
        } else if (data[i] == nullptr) {
            freeIndexes++;
        }
    }
    std::cout<<std::endl;
    std::cout<<"There are "<<freeIndexes<<" free indexes"<<std::endl;
    
}

/*
    Retorna o número de posições disponíveis para inserção
    Posições disponíveis: nullptr OU REMOVED
*/
int HashTable::getFreeSpaces(){
    int availableSpaces = 0;
    for(int i = 0; i < BUFFER_SIZE; i++){
        if(data[i] == nullptr || data[i] == REMOVED){
            availableSpaces++;
        }
    }
    return availableSpaces;
}
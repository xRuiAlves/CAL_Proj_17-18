Neste projeto foi usada a sintaxe de c++11, bem como multithreading, pelo que são necessárias as flags -std=c++11 e -pthread

O projeto foi realizado no IDE Clion, pelo que a compilação é aconselhada através do mesmo (lembrando que tem de se fazer "Reload CMake Project" - File > Reload CMake Project)

Caso não seja possível correr CLion, é aconselhado usar o programa cmake com o ficheiro fornecido CMakeLists.txt, que funcionará como um makefile.

Os mapas processados (.txt que foram obtidos a partir do processamento de ficheiros .osm do OpenStreetMaps) estão numa pasta maps/ ao mesmo nivel de src/, um nivel acima da pasta do executável (../maps/). Uma vez que estes caminhos estão escritos no código, a alteração da localização destes ficheiros inviabiliza a leitura dos mesmos e, consequentemente a execução dos algoritmos do programa.

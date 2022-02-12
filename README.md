# Clonar o repositório
* git clone https://github.com/jvitormichels/arvores.git

# Fluxo para mandar as alterações
* git add .
* git commit -m "[descreve oq tu fez]"
* git push origin master

# Descrição do trabalho, por Leandro, O Brabo

  O objetivo deste trabalho consiste em analisar a complexidade algorítmica das
operações de adição de nós e balanceamento em árvores AVL, rubro-negra e B. A análise
deve ser realizada considerando a geração de um conjunto de dados (chaves) com tamanho
variando entre 1 e 1000. As chaves devem ser geradas prevendo o pior caso (chaves
ordenadas crescente ou decrescente) e caso médio (chaves aleatórias). Para geração das
chaves aleatórias, sugere-se o uso da função rand e srand em C considerando um tamanho
de amostra de 10 conjuntos para validade estatística.

  O resultado final do experimento deve ser exibido em dois gráficos de linha (um para o pior
caso e outro para o caso médio), onde o eixo X representa o tamanho dos conjuntos de
dados (1 a 1000) e o eixo Y representa o esforço computacional das operações (adição de
chaves e balanceamento). Cada gráfico deve apresentar 3 linhas, as quais representam as
respectivas operações para cada estrutura de dados avaliada.

# Checklist
[x] Implementação básica das três árvores disponibilizada pelo professor

[ ] Implementação do método que vai gerar o csv

[ ] Monitoramento do esforço computacional de cada árvore

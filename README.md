Descrição e Genero:
O jogo se passa em um futuro ciberpunk, com um personagem seguindo um objetivo descrito
na abertura do game. Ele trabalha para a empresa Dingen-i e a operação dele se passa
dentro da empresa rival Biozeera no qual está acontecendo anomalias que devem ser investigadas
pelo agente.

O jogo é estilo plataforma com elemento de mira e personalização de skills. Apenas um
jogador e com hordas e objetos para serem achados no mapa. Com mudança de ambientação e 
criaturas de acordo com o progresso do jogo.

História do jogo:
Duas empresas rivais, brigam a muito tempo pelas inovações científicas e
em um mundo com a ética totalmente diferente onde vale tudo pela
ciência, as empresas estão dispostas a jogarem sujo para manter a imagem
e sua aparência diante do mundo. Em um cenário assim fica difícil saber
quem é o vilão e quem é o mocinho.

Objetivo:

Controles:
Para andar com o personagem você usa as letras 'w','a','s','d'. Para atirar você mira com o mouse
e clica no botão esquerdo. Para abrir a porta você deve apertar 'f'.

Membros do time e seus papéis:
O único personagem é o principal, o agente da empresa e seu papel e passar pelas fases coletando as chaves
para abrir as portas.

Dependencias e versões:
  - SDL2 32 bits
  - gcc11
  - mingw32 32bits

Como instalar e como compilar:
Para instalar basta você clonar o projeto. Ele por padrão é um projeto do Visual Studio, mas ele possui um
makefile dentro dele caso esteja-se usando o Ubuntu, Mac ou Windows sem o VS. 

Caso esteja usando o VS você precisa informar que arquitetura é de 32 bits e informar o local da pasta de Recursos.

Caso esteja usando o makefile, basta usar o comando make (Linux ou Mac) ou mingw32-make (Windows). Certifique-se 
que as pastas dep e bin estão criadas antes de rodas o comando.

Licensa open source:
The MIT License (MIT)

Copyright (c) [2017] [Blackcraft]

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Screenshots do jogo:
Vídeo:







# GameEngine
Engine de um jogo desenvolvida na disciplina de IDJ

Programação:

● 30%:
  - Movimentação básica e colisão com o mapa.
  - Interação com elementos de movimentação (escadas etc).
  - Pulo Duplo.
  - Background Parallax.
  
● 70%:
  - Troca de Fases.
  - Interação com objetos especiais, como caixas, chaves, abertura de portas
  - Ataques Básicos (tiro forte e tiro normal)
  - Inimigos:
    - Inteligência Artificial dos inimigos
    - 2 Espécies diferentes
    - Pathfinding
    - Mecânica de Spawn
    
● 100%:
  - Horda
    - Chega um momento em que o player tenta abrir uma porta X
    - Ao tentar abrir essa porta X chaves irão ser spawnadas em regiões do mapa
    - O player deve encontrar essas chaves e pegá-las
    - Na posição das chaves serão spawnados inimigos, que só irão
    parar de spawnar após o player chegar na porta
  - Implementação das habilidades especiais(mínimo 1).
  - Boss!
  - Refinamento do jogo. Correção de Bugs.

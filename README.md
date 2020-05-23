# sumo-robot-pi2
Código de um robo lutador de sumô da categoria mega-sumo que fiz para a disciplina de projeto integrador 2 da faculdade. 
O robô tem funcionamento bastante simples, utilizando dois sensores infravermelhos de preto e branco (usados para indicar se o robô está no interior da arena ou em sua borda) e um sensor ultrassônico HC-SR04 para "ver" se há algo em sua frente (potencialmente seu adversário), uma ponte H simples para controle de dois motores ligados às rodas. O código utiliza a [biblioteca Ultrassonic da FilipeFlop](https://github.com/filipeflop/Ultrasonic) para uso do sensor ultrassônico.

## Funcionamento
O funcionamento do robô é simples. Ele se desloca para frente até que seus sensores infravermelhos percebam que ele chegou à borda da arena. Então ele freia, retorna por algumas centenas de microssegundos e faz um movimento de giro ao mesmo tempo que varre sua frente com o sensor ultrassônico a procura de seu adversário. Caso encontre algo, ele para o giro e se move para direção do que 
encontrou, caso não, ele continua o movimento por um tempo determinado que deverá corresponder ao tempo necessário para que ele faça aproximadamente meia volta, encerra-o e volta a deslocar-se para frente.
Por desconhecimento meu na época que fiz este robô, ele não utiliza um giroscópio nem faz a leitura da tensão de alimentação, fazendo com que seu movimento não seja confiável e mude muito com a descarga da bateria usada em sua alimentação e criando a necessidade de reajustes das constantes de tempo.

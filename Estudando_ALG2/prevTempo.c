/*15.Imagine que você é responsável por analisar a previsão do tempo de um mês inteiro,
armazenada em um vetor de números reais, onde cada elemento representa a temperatura
média de um dia. Seu objetivo é implementar um programa que permita ao usuário
observar estatísticas de qualquer período de 7 dias dentro do mês.
O programa deve exibir para o período selecionado:
• Dia de início e dia de fim do período
• Temperatura máxima nesse período
• Temperatura mínima nesse período
• Temperatura média nesse período
O programa inicia mostrando os dados dos dias 1 a 7. O usuário pode então “navegar”
pelo mês com as seguintes opções:
• a k: avançar a janela de 7 dias em k dias à frente (se houver dias suficientes)
• r k: retroceder a janela de 7 dias em k dias (se possível)
• s: encerrar o programa
Dica: Para tornar a simulação eficiente, utilize um deque para armazenar os elementos da
semana e atualizar rapidamente as estatísticas à medida que a janela desliza para frente
ou para trás.*/
- Construtor por omiss�o das classes: colocar ou n�o colocar (visto que ser�o useless)?
- void pressToContinue() - useful ou useless?
- Formatar a funcao padrao para imprimir o supermercado (para ficar bonitinho)? E adicionar mais merdas (de momento s� me lembro de por o total gasto por todos os clientes)?

Cenas:

Naquela funcao padrao para imprimir cada tipo de dados, n�o se coloca endl no fim da funcao (conven��o que me parece mais pratica), se for preciso adiciona.se ao cham�.la
Falta fazer -> int ProductIndex(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos <- na classe Product
Substituir fun��o DeleteWhitespace pela que saiu no teste (quando dispon�vel)
Falta fazer -> multimap<int, int> transactionIdx //multimap que traduz o ID do cliente nos indices das suas transacoes no vetor de transacoes <- na classe Vende++
- Construtor por omissão das classes: colocar ou não colocar (visto que serão useless)?
- void pressToContinue() - useful ou useless?
- Formatar a funcao padrao para imprimir o supermercado (para ficar bonitinho)? E adicionar mais merdas (de momento só me lembro de por o total gasto por todos os clientes)?

Cenas:

Naquela funcao padrao para imprimir cada tipo de dados, não se coloca endl no fim da funcao (convenção que me parece mais pratica), se for preciso adiciona.se ao chamá.la
Falta fazer -> int ProductIndex(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos <- na classe Product
Substituir função DeleteWhitespace pela que saiu no teste (quando disponível)
Falta fazer -> multimap<int, int> transactionIdx //multimap que traduz o ID do cliente nos indices das suas transacoes no vetor de transacoes <- na classe Vende++
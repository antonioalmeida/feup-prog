Cenas:

- Ajeitar a função void pressToContinue();
- Formatar a funcao padrao para imprimir o supermercado (para ficar bonitinho)? E adicionar mais merdas (de momento só me lembro de por o total gasto por todos os clientes)?
- Implementar um segundo construtor para a classe Client (para quando forem adicionados novos objetos em tempo de execução)
	Recomendação: Definir estes como os construtores padrão de cada classe (ou seja, os protótipos seriam:
			Client(); //ID = maxClientID (atributo da classe Vende++), perguntar nome e data de adesão, shopVolume = 0
- Naquela funcao padrao para imprimir cada tipo de dados, não se coloca endl no fim da funcao (convenção que me parece mais pratica), se for preciso adiciona.se ao chamá.la
- Substituir função DeleteWhitespace pela que saiu no teste (quando disponível)


FEITO:

- Implementar um segundo construtor para a classe Transaction, protótipo:
			Transaction(const vector<Product> &productList, const vector<Client> &clientList);
			//Dentro, perguntar o ID do cliente (verificar que existe), data da compra (usando a respetiva classe) e os produtos (verificar que cada produto adicionado existe), push_back no fim
			NÃO FOI PRECISO -> //Após criar a transação, chamar um outro método (talvez um método friend na classe Vende++) que calcula o valor de uma transação e soma ao valor do respetivo cliente no vetor
			NÃO FOI PRECISO ->//Sugestão de protótipo (ideia apenas porque não sei se métodos friend podem modificar atributos): friend void updateClientShopVol(Transaction tran);

- -> multimap<int, int> transactionIdx //multimap que traduz o ID do cliente nos indices das suas transacoes no vetor de transacoes <- na classe Vende++
- -> int ProductIndex(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos <- na classe Product

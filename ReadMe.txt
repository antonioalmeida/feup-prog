Cenas:

- Ajeitar a fun��o void pressToContinue();
- Formatar a funcao padrao para imprimir o supermercado (para ficar bonitinho)? E adicionar mais merdas (de momento s� me lembro de por o total gasto por todos os clientes)?
- Implementar um segundo construtor para a classe Client (para quando forem adicionados novos objetos em tempo de execu��o)
	Recomenda��o: Definir estes como os construtores padr�o de cada classe (ou seja, os prot�tipos seriam:
			Client(); //ID = maxClientID (atributo da classe Vende++), perguntar nome e data de ades�o, shopVolume = 0
- Naquela funcao padrao para imprimir cada tipo de dados, n�o se coloca endl no fim da funcao (conven��o que me parece mais pratica), se for preciso adiciona.se ao cham�.la
- Substituir fun��o DeleteWhitespace pela que saiu no teste (quando dispon�vel)


FEITO:

- Implementar um segundo construtor para a classe Transaction, prot�tipo:
			Transaction(const vector<Product> &productList, const vector<Client> &clientList);
			//Dentro, perguntar o ID do cliente (verificar que existe), data da compra (usando a respetiva classe) e os produtos (verificar que cada produto adicionado existe), push_back no fim
			N�O FOI PRECISO -> //Ap�s criar a transa��o, chamar um outro m�todo (talvez um m�todo friend na classe Vende++) que calcula o valor de uma transa��o e soma ao valor do respetivo cliente no vetor
			N�O FOI PRECISO ->//Sugest�o de prot�tipo (ideia apenas porque n�o sei se m�todos friend podem modificar atributos): friend void updateClientShopVol(Transaction tran);

- -> multimap<int, int> transactionIdx //multimap que traduz o ID do cliente nos indices das suas transacoes no vetor de transacoes <- na classe Vende++
- -> int ProductIndex(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos <- na classe Product
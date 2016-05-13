# Sell++ 

C++ based clients & transactions management tool that uses .txt files as input and output.
A project in collaboration with @cyrilico regarding a subject for college. 

## Features

#####Client's Management
1. Show clients alphabetically
2. Show a client's properties
3. Edit a client's properties
4. Add a new client
5. Remove a client
6. Show 'Bottom10' (clients with the least shopVolume)

#####Transactions Management
1. Show transactions between two dates
2. Show client's transactions (by chronological order)
3. Add a transaction (make a purchase)
4. Show transactions made on a specific date
5. Show all transactions made

#####Recommendation System
1. Show recommended product for a specific client
2. Show recommended product for 'Bottom10' clients

#####Others
	1. Show available products
	
##Usage
1. Run program
2. Follow instructions on screen to add 'clients', 'products' and 'transactions' input files.
3. Navigate menus to select features

Example files are available in the repository as 'clients.txt', 'products.txt' and 'transactions.txt', and must follow the respective patterns in order to work

##Improvements:

- Ajeitar a função void pressToContinue();
- Formatar a funcao padrao para imprimir o supermercado (para ficar bonitinho)? E adicionar mais merdas (de momento só me lembro de por o total gasto por todos os clientes)?
 - Implementar um segundo construtor para a classe Client (para quando forem adicionados novos objetos em tempo de execução)
	Recomendação: Definir estes como os construtores padrão de cada classe (ou seja, os protótipos seriam:
			Client(); //ID = maxClientID (atributo da classe Vende++), perguntar nome e data de adesão, shopVolume = 0
- Naquela funcao padrao para imprimir cada tipo de dados, não se coloca endl no fim da funcao (convenção que me parece mais pratica), se for preciso adiciona.se ao chamá.la
- Substituir função DeleteWhitespace pela que saiu no teste (quando disponível)


##Improvements made:

- Implementar um segundo construtor para a classe Transaction, protótipo:
			Transaction(const vector<Product> &productList, const vector<Client> &clientList);
			//Dentro, perguntar o ID do cliente (verificar que existe), data da compra (usando a respetiva classe) e os produtos (verificar que cada produto adicionado existe), push_back no fim
			NÃO FOI PRECISO -> //Após criar a transação, chamar um outro método (talvez um método friend na classe Vende++) que calcula o valor de uma transação e soma ao valor do respetivo cliente no vetor
			NÃO FOI PRECISO ->//Sugestão de protótipo (ideia apenas porque não sei se métodos friend podem modificar atributos): friend void updateClientShopVol(Transaction tran);

- -> multimap<int, int> transactionIdx //multimap que traduz o ID do cliente nos indices das suas transacoes no vetor de transacoes <- na classe Vende++
- -> int ProductIndex(string nome); // uso do map para "traduzir" o nome em indice no vetor de produtos <- na classe Product

--Trabalho de Laboratório de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--MarceDB - Sistema de gestão para marcenaria.

--Autor:
--Matheus Henrique dos Santos Gomes

--Arquivo com exemplos de consultas SQL:

-- 1 - Projetos de valor acima de 15mil com clientes e vendedores 
SELECT p.id_projeto, c.nomeCliente, v.cidadeAtua, p.valorVenda
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
JOIN vendedor as v ON p.id_funcVendedor=v.id_funcVendedor
WHERE p.valorVenda>15000;

-- 2 - Cortes realizados em março de 2024
SELECT c.id_corte, p.ambientes, c.diaCortado, c.inicio_corte, c.fim_corte
FROM corte as c
JOIN projeto as p ON c.id_projOrigem=p.id_projeto
WHERE c.diaCortado BETWEEN '2024-03-01' AND '2024-03-31'
AND c.cortado=TRUE;

-- 3 - Projetos por status
SELECT p.id_projeto, 'Finalizado' as situação
FROM projeto as p
WHERE p.finalizado=TRUE
UNION
SELECT p.id_projeto, 'Não Finalizado' as situação
FROM projeto as p
WHERE p.finalizado=FALSE;

-- 4 - Vendas totais por vendedor
SELECT v.id_funcVendedor, f.salario, SUM(p.valorVenda) as total_vendas
FROM projeto as p
JOIN vendedor as v ON p.id_funcVendedor=v.id_funcVendedor
JOIN funcionario as f ON v.id_funcVendedor=f.id_func
GROUP BY v.id_funcVendedor, f.salario
ORDER BY total_vendas DESC;

-- 5 - Projetos por cliente
SELECT c.nomeCliente, COUNT(p.id_projeto) as qtd_projetos
FROM cliente as c
LEFT JOIN projeto as p ON c.id_cliente=p.id_cli
GROUP BY c.id_cliente, c.nomeCliente
ORDER BY qtd_projetos DESC;

-- 6 - Projetos acima da média
SELECT p.id_projeto, c.nomeCliente, p.valorVenda
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
WHERE p.valorVenda>(SELECT AVG(valorVenda) FROM projeto)
ORDER BY p.valorVenda DESC;

-- 7 - projetos de clientes específicos
SELECT p.id_projeto, c.nomeCliente, p.ambientes
FROM projeto as p
JOIN cliente as c ON p.id_cli = c.id_cliente
WHERE c.id_cliente IN (1, 2, 4, 8)
ORDER BY c.nomeCliente;

-- 8 - Projetos ainda não finalizados
SELECT p.id_projeto, c.nomeCliente, p.ambientes, p.valorVenda
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
WHERE p.finalizado=FALSE
ORDER BY p.diaVendido;

-- 9 - Clientes com projetos alto padrão
SELECT DISTINCT c.id_cliente, c.nomeCliente
FROM cliente as c
JOIN projeto as p ON c.id_cliente=p.id_cli
WHERE p.valorVenda>30000;

-- 10 - Cidades de atuação disponíveis
SELECT DISTINCT cidadeAtua
FROM vendedor
ORDER BY cidadeAtua;

-- 11 - todos os detalhes de um projeto
SELECT p.id_projeto, c.nomeCliente as cliente, v.cidadeAtua as cidade, p.ambientes, p.valorVenda as preço, p.garantiaMesVenda as tempo_garantia
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
JOIN vendedor as v ON p.id_funcVendedor=v.id_funcVendedor;

-- 12 - Maior projeto de cada cliente
SELECT p.id_projeto, c.nomeCliente, p.ambientes, p.valorVenda
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
WHERE p.valorVenda=(
    SELECT MAX(p2.valorVenda)
    FROM projeto as p2
    WHERE p2.id_cli=p.id_cli
);

-- 13 - Projetos a partir de uma data
SELECT p.id_projeto, p.ambientes, c.nomeCliente, p.diaVendido, p.valorVenda
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
WHERE p.diaVendido>='2024-06-14'
ORDER BY p.diaVendido DESC;

-- 14 - Vendedores top performance
SELECT v.id_funcVendedor, SUM(p.valorVenda) as total_vendas
FROM projeto as p
JOIN vendedor as v ON p.id_funcVendedor=v.id_funcVendedor
GROUP BY v.id_funcVendedor
HAVING SUM(p.valorVenda)>50000
ORDER BY total_vendas DESC;

-- 15 - Todos clientes (mesmo sem projetos)
SELECT c.nomeCliente, COUNT(p.id_projeto) as qtd_projetos,
       COALESCE(SUM(p.valorVenda), 0) as total_gasto
FROM cliente c
LEFT JOIN projeto p ON c.id_cliente = p.id_cli
GROUP BY c.id_cliente, c.nomeCliente
ORDER BY total_gasto DESC;

-- 16 - Status de cortes
SELECT id_corte, diaCortado,
       COALESCE(CAST(inicio_corte AS TEXT), 'Não iniciado') as inicio,
       COALESCE(CAST(fim_corte AS TEXT), 'Não finalizado') as fim
FROM corte
WHERE id_projOrigem=3;
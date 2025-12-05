--Trabalho de Laboratório de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--MarceDB - Sistema de gestão para marcenaria.

--Autor:
--Matheus Henrique dos Santos Gomes

--Arquivo com exemplos de consultas SQL:

-- 1 - Projetos de clientes de valor acima de 15mil e local 
SELECT p.id_projeto, c.nomeCliente, v.cidadeAtua, p.valorVenda
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
JOIN vendedor as v ON p.id_funcVendedor=v.id_funcVendedor
WHERE p.valorVenda>15000;

-- 2 - Cortes realizados no período de março de 2024
SELECT c.id_corte, p.ambientes, c.diaCortado, c.inicio_corte, c.fim_corte
FROM corte as c
JOIN projeto as p ON c.id_projOrigem=p.id_projeto
WHERE c.diaCortado BETWEEN '2024-03-01' AND '2024-03-31'
AND c.cortado=TRUE;

-- 3 - status dos projetos
SELECT p.id_projeto, 'Finalizado' as situação
FROM projeto as p
WHERE p.finalizado=TRUE
UNION
SELECT p.id_projeto, 'Não Finalizado' as situação
FROM projeto as p
WHERE p.finalizado=FALSE;

-- 4 - desempenho do vendedor comparando salário com o total de vendas
SELECT v.id_funcVendedor, f.salario, SUM(p.valorVenda) as total_vendas
FROM projeto as p
JOIN vendedor as v ON p.id_funcVendedor=v.id_funcVendedor
JOIN funcionario as f ON v.id_funcVendedor=f.id_func
GROUP BY v.id_funcVendedor, f.salario
ORDER BY total_vendas DESC;

-- 5 - qtd de projetos por cliente
SELECT c.nomeCliente, COUNT(p.id_projeto) as qtd_projetos
FROM cliente as c
LEFT JOIN projeto as p ON c.id_cliente=p.id_cli
GROUP BY c.id_cliente, c.nomeCliente
ORDER BY qtd_projetos DESC;

-- 6 - Projetos que estão acima da média de valor
SELECT p.id_projeto, c.nomeCliente, p.valorVenda
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
WHERE p.valorVenda>(SELECT AVG(valorVenda) FROM projeto)
ORDER BY p.valorVenda DESC;

-- 7 - projetos dos clientes 1,2,4 e 8
SELECT p.id_projeto, c.nomeCliente, p.ambientes
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
WHERE c.id_cliente IN (1, 2, 4, 8)
ORDER BY c.nomeCliente;

-- 8 - Projetos ainda não finalizados
SELECT p.id_projeto, c.nomeCliente, p.ambientes, p.valorVenda
FROM projeto as p
JOIN cliente as c ON p.id_cli=c.id_cliente
WHERE p.finalizado=FALSE
ORDER BY p.diaVendido;

-- 9 - Clientes com projetos alto padrão >30000
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

-- 12 - projeto mais caro de cada cliente
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

-- 14 - Vendedores com mais de 50000 em vendas
SELECT v.id_funcVendedor, SUM(p.valorVenda) as total_vendas
FROM projeto as p
JOIN vendedor as v ON p.id_funcVendedor=v.id_funcVendedor
GROUP BY v.id_funcVendedor
HAVING SUM(p.valorVenda)>50000
ORDER BY total_vendas DESC;

-- 15 - total gasto e número de projetos de todos os clientes
SELECT c.nomeCliente, COUNT(p.id_projeto) as qtd_projetos,
       COALESCE(SUM(p.valorVenda), 0) as total_gasto
FROM cliente as c
LEFT JOIN projeto as p ON c.id_cliente=p.id_cli
GROUP BY c.id_cliente, c.nomeCliente
ORDER BY total_gasto DESC;
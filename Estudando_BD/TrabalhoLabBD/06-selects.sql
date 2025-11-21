--Trabalho de Laboratório de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--MarceDB - Sistema de gestão para marcenaria.

--Autor:
--Matheus Henrique dos Santos Gomes

--Arquivo com exemplos de consultas SQL:

-- 1. JUNÇÃO INTERNA - Projetos com clientes e vendedores (valor > 15.000)
SELECT p.id_projeto, c.nomeCliente, v.cidadeAtua, p.valorVenda
FROM projeto p
INNER JOIN cliente c ON p.id_cli = c.id_cliente
INNER JOIN vendedor v ON p.id_funcVendedor = v.id_funcVendedor
WHERE p.valorVenda > 15000;

-- 2. RESTRIÇÃO DE TEMPO - Cortes realizados em março de 2024
SELECT c.id_corte, p.ambientes, c.diaCortado, c.inicio_corte, c.fim_corte
FROM corte c
INNER JOIN projeto p ON c.id_projOrigem = p.id_projeto
WHERE c.diaCortado BETWEEN '2024-03-01' AND '2024-03-31'
AND c.cortado = TRUE;

-- 4. OPERAÇÃO ENTRE CONJUNTOS - Projetos por status
SELECT p.id_projeto, 'Finalizado' as status
FROM projeto p
WHERE p.finalizado = TRUE
UNION ALL
SELECT p.id_projeto, 'Não Finalizado' as status
FROM projeto p
WHERE p.finalizado = FALSE;

-- 5. FUNÇÕES AGREGADAS - Vendas totais por vendedor
SELECT v.id_funcVendedor, f.salario, SUM(p.valorVenda) as total_vendas
FROM projeto p
INNER JOIN vendedor v ON p.id_funcVendedor = v.id_funcVendedor
INNER JOIN funcionario f ON v.id_funcVendedor = f.id_func
GROUP BY v.id_funcVendedor, f.salario
ORDER BY total_vendas DESC;

-- 6. AGRUPAMENTO - Projetos por cliente
SELECT c.nomeCliente, COUNT(p.id_projeto) as qtd_projetos
FROM cliente c
LEFT JOIN projeto p ON c.id_cliente = p.id_cli
GROUP BY c.id_cliente, c.nomeCliente
ORDER BY qtd_projetos DESC;

-- 7. RESTRIÇÃO DE AGRUPAMENTO - Clientes com 3+ projetos
SELECT c.nomeCliente, COUNT(p.id_projeto) as qtd_projetos
FROM cliente c
INNER JOIN projeto p ON c.id_cliente = p.id_cli
GROUP BY c.id_cliente, c.nomeCliente
HAVING COUNT(p.id_projeto) >= 3;

-- 8. SUBCONSULTA - Projetos acima da média
SELECT p.id_projeto, c.nomeCliente, p.valorVenda
FROM projeto p
INNER JOIN cliente c ON p.id_cli = c.id_cliente
WHERE p.valorVenda > (SELECT AVG(valorVenda) FROM projeto)
ORDER BY p.valorVenda DESC;

-- 9. OPERADOR IN - Projetos de clientes específicos
SELECT p.id_projeto, c.nomeCliente, p.ambientes
FROM projeto p
INNER JOIN cliente c ON p.id_cli = c.id_cliente
WHERE c.id_cliente IN (1, 2, 4, 8)
ORDER BY c.nomeCliente;

-- 10. OPERADOR NOT - Projetos não finalizados
SELECT p.id_projeto, c.nomeCliente, p.ambientes, p.valorVenda
FROM projeto p
INNER JOIN cliente c ON p.id_cli = c.id_cliente
WHERE NOT p.finalizado
ORDER BY p.diaVendido;

-- 11. OPERADOR EXISTS - Clientes com projetos premium
SELECT c.id_cliente, c.nomeCliente
FROM cliente c
WHERE EXISTS (
    SELECT 1 FROM projeto p 
    WHERE p.id_cli = c.id_cliente AND p.valorVenda > 30000
);

-- 12. DISTINCT - Cidades de atuação
SELECT DISTINCT cidadeAtua
FROM vendedor
ORDER BY cidadeAtua;

-- 13. JUNÇÃO MÚLTIPLA - Detalhes completos do projeto
SELECT p.id_projeto, c.nomeCliente as cliente, 
       v.cidadeAtua, p.ambientes, p.valorVenda, p.garantiaMesVenda
FROM projeto p
INNER JOIN cliente c ON p.id_cli = c.id_cliente
INNER JOIN vendedor v ON p.id_funcVendedor = v.id_funcVendedor;

-- 14. SUBCONSULTA CORRELACIONADA - Maior projeto por cliente
SELECT p.id_projeto, c.nomeCliente, p.ambientes, p.valorVenda
FROM projeto p
INNER JOIN cliente c ON p.id_cli = c.id_cliente
WHERE p.valorVenda = (
    SELECT MAX(p2.valorVenda)
    FROM projeto p2
    WHERE p2.id_cli = p.id_cli
);

-- 15. FUNÇÃO DE DATA - Projetos dos últimos 18 meses
SELECT p.id_projeto, c.nomeCliente, p.diaVendido, p.valorVenda
FROM projeto p
INNER JOIN cliente c ON p.id_cli = c.id_cliente
WHERE p.diaVendido >= CURRENT_DATE - INTERVAL '18 months'
ORDER BY p.diaVendido DESC;

-- 16. CASE - Classificação por valor
SELECT p.id_projeto, p.ambientes, p.valorVenda,
    CASE 
        WHEN p.valorVenda < 10000 THEN 'Econômico'
        WHEN p.valorVenda BETWEEN 10000 AND 25000 THEN 'Standard'
        ELSE 'Premium'
    END as classificacao
FROM projeto p
ORDER BY p.valorVenda DESC;

-- 17. HAVING - Vendedores top performance
SELECT v.id_funcVendedor, SUM(p.valorVenda) as total_vendas
FROM projeto p
INNER JOIN vendedor v ON p.id_funcVendedor = v.id_funcVendedor
GROUP BY v.id_funcVendedor
HAVING SUM(p.valorVenda) > 50000
ORDER BY total_vendas DESC;

-- 18. LEFT JOIN - Todos clientes (mesmo sem projetos)
SELECT c.nomeCliente, COUNT(p.id_projeto) as qtd_projetos,
       COALESCE(SUM(p.valorVenda), 0) as total_gasto
FROM cliente c
LEFT JOIN projeto p ON c.id_cliente = p.id_cli
GROUP BY c.id_cliente, c.nomeCliente
ORDER BY total_gasto DESC;

-- 19. COALESCE - Status de cortes
SELECT id_corte, diaCortado,
       COALESCE(CAST(inicio_corte AS TEXT), 'Não iniciado') as inicio,
       COALESCE(CAST(fim_corte AS TEXT), 'Não finalizado') as fim
FROM corte
WHERE id_projOrigem = 3;
--Trabalho de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--SIGVID - Sistema Integrado de Gestão de Violações e Denúncias.

--Autores:
--Matheus Henrique dos Santos Gomes
--Paulo Antonio Blasque Fernandes

--Arquivo com exemplos de consultas SQL:

--Listar todas as pessoas denunciantes
SELECT *
FROM Pessoa_denunciante;

--Listar todas as denúncias com relatos, status e órgão responsável
SELECT d.num_ident, d.relato, d.status, o.nome AS orgao
FROM Denuncia AS d
JOIN Orgao_responsavel AS o ON d.cod_ident_org = o.cod_ident
ORDER BY d.num_ident;

--Listar denúncias identificadas com nome e idade do denunciante
SELECT d.num_ident, p.nome, p.idade
FROM Denuncia_identificada di
JOIN Pessoa AS p ON di.cpf_denunciante = p.cpf
JOIN Denuncia AS d ON di.num_ident = d.num_ident
ORDER BY d.num_ident;

--Mostrar denúncias com seus relatos e respectivas violações separadas por uma vírgula
SELECT d.num_ident, d.relato, STRING_AGG(v.descricao, ', ') AS violacoes
FROM Denuncia AS d
JOIN Denuncia_contem_violacao AS dv ON d.num_ident = dv.num_ident
JOIN Violacao AS v ON dv.cod_vio = v.cod_vio
GROUP BY d.num_ident, d.relato
ORDER BY d.num_ident;

--Listar denuncias e seus respectivos tipos provas com descrição, ordenado de maneira crescente pelo numero identificador
SELECT d.num_ident, p.tipo_prova, p.descricao
FROM Denuncia_contem_provas AS dp
JOIN Prova AS p ON dp.cod_prova = p.cod_prova
JOIN Denuncia AS d ON dp.num_ident = d.num_ident
ORDER BY num_ident, tipo_prova;

--Listar denúncias feitas por pessoas com mais de 60 anos
SELECT d.num_ident, p.nome, p.idade
FROM Denuncia_identificada di
JOIN Pessoa AS p ON di.cpf_denunciante = p.cpf
JOIN Denuncia AS d ON di.num_ident = d.num_ident
WHERE p.idade>60;

--Listar denúncias com mais de uma violação e sua respectiva quantidade de violações
SELECT num_ident, COUNT(*) AS total_violacoes
FROM Denuncia_contem_violacao
GROUP BY num_ident
HAVING COUNT(*)>1;

--Listar denúncias com mais de uma prova e sua respectiva quantidade de provas
SELECT num_ident, COUNT(*) AS total_provas
FROM Denuncia_contem_provas
GROUP BY num_ident
HAVING COUNT(*)>1;

--Listar pessoas denunciadas e o nome do órgão para onde a denúncia foi
SELECT p.nome AS pessoa_denunciada, o.nome AS orgao
FROM Pessoa_denunciada AS pd
JOIN Pessoa AS p ON pd.cpf = p.cpf
JOIN Orgao_responsavel AS o ON pd.cod_ident_org = o.cod_ident;

--Listar as denuncias com provas do tipo 'Audio' associadas a denúncias de assédio e a descrição da prova.
SELECT d.num_ident, p.descricao
FROM Denuncia AS d
JOIN Denuncia_contem_provas AS dp ON d.num_ident=dp.num_ident
JOIN Prova AS p ON dp.cod_prova=p.cod_prova
JOIN Denuncia_contem_violacao AS dv ON d.num_ident=dv.num_ident
WHERE dv.cod_vio='VIO00005' AND p.tipo_prova='Áudio';

--Contar quantas denúncias cada órgão recebeu
SELECT o.nome AS orgao, COUNT(d.num_ident)
FROM Orgao_responsavel AS o
JOIN Denuncia AS d ON o.cod_ident=d.cod_ident_org
GROUP BY o.nome;

--Listar o numero de identificação de denúncias já encerradas
SELECT num_ident, status
FROM Denuncia
WHERE status='Encerrada';

--Listar denúncias com mais de uma pessoa envolvida
SELECT DISTINCT d.num_ident
FROM Denuncia AS d
JOIN Pessoa_denunciante AS pd ON d.num_ident = pd.num_ident
JOIN Pessoa_denunciada AS pda ON d.cod_ident_org = pda.cod_ident_org;

--Listar denúncias que estão em análise por perícia técnica
SELECT num_ident, metodo_analise, relato
FROM Denuncia
WHERE metodo_analise='Perícia técnica';

--Listar todas as violações com suas descrições
SELECT cod_vio, descricao
FROM Violacao;

--Listar as provas do tipo 'Documento' associadas a denúncias com mais de uma violação
SELECT DISTINCT p.cod_prova, p.descricao
FROM Prova AS p
JOIN Denuncia_contem_provas AS dp ON p.cod_prova=dp.cod_prova
JOIN (
  SELECT num_ident
  FROM Denuncia_contem_violacao
  GROUP BY num_ident
  HAVING COUNT(*) > 1
) AS dv ON dp.num_ident = dv.num_ident
WHERE p.tipo_prova = 'Documento';

--Contar quantas vezes cada tipo de prova aparece
SELECT tipo_prova, COUNT(*) AS total
FROM Prova
GROUP BY tipo_prova;

--Ver denúncias em que a pessoa denunciante também é a pessoa denunciada
SELECT di.num_ident, p.nome
FROM Denuncia_identificada AS di
JOIN Pessoa_denunciada AS pd ON di.cpf_denunciante = pd.cpf
JOIN Pessoa AS p ON p.cpf = pd.cpf;

--Listar denuncias acompanhadas por advogados
SELECT aad.num_ident, a.nome AS nome_advogado
FROM Advogado_acompanha_denuncia AS aad
JOIN Advogado AS a ON aad.num_oab = a.num_oab;
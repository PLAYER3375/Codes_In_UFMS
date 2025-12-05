--Trabalho de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--SIGVID - Sistema Integrado de Gestão de Violações e Denúncias.

--Autores:
--Matheus Henrique dos Santos Gomes
--Paulo Antonio Blasque Fernandes

--Arquivo para a povoação do banco de dados:

--insert de pessoas
INSERT INTO Pessoa (cpf, nome, idade) VALUES
	('690.243.518-98', 'Sr. Luiz Fernando Cunha', 72),
	('421.986.730-96', 'Srta. Nina Melo', 42),
	('781.236.945-55', 'Manuela Ferreira', 66),
	('089.753.621-59', 'Sr. Thomas Martins', 74),
	('138.964.702-13', 'Dr. Calebe Jesus', 44),
	('841.926.753-82', 'Ana Laura Nogueira', 20),
	('534.169.027-34', 'Ana Clara Carvalho', 34),
	('290.674.381-03', 'Eduarda da Rosa', 79),
	('615.907.432-61', 'Srta. Luana da Rocha', 76);

INSERT INTO telefonePessoa (cpf, telefone) VALUES
	('690.243.518-98', '(18) 99776-4433'),
	('421.986.730-96', '(18) 98176-4433'),
	('781.236.945-55', '(18) 99176-4433'),
	('089.753.621-59', '(67) 99776-4433'),
	('138.964.702-13', '(11) 99776-4433'),
	('841.926.753-82', '(11) 99717-4433'),
	('534.169.027-34', '(67) 99793-4433'),
	('290.674.381-03', '(11) 99723-4433'),
	('615.907.432-61', '(18) 99775-4433'),
	('089.753.621-59', '(67) 99776-4443'),
	('138.964.702-13', '(11) 99776-4333');

--insert dos advogados
INSERT INTO Advogado (num_oab, nome, area_atua) VALUES
	('SP862477', 'Renan Aragão', 'Trabalhista'),
	('MS670672', 'Mariane Castro', 'Ambiental'),
	('AM976507', 'Bernardo das Neves', 'Trabalhista'),
	('RN589822', 'Noah Castro', 'Trabalhista'),
	('MT475972', 'Maria Fernanda da Cunha', 'Criminal');

--insert dos adv usando o Default
INSERT INTO Advogado (num_oab, nome) VALUES
	('TO833293', 'Catarina Ferreira'),
	('SP175467', 'Fernanda Monteiro'),
	('SP557251', 'Benício Santos');

--insert dos contratos
INSERT INTO Contrato (cpf_pes, num_oab, valor_contrato, data_contrato) VALUES
	('690.243.518-98', 'SP862477', 14866.8, '2020-02-11'),
	('089.753.621-59', 'SP175467', 9970.71, '2024-11-03'),
	('138.964.702-13', 'SP557251', 2913.32, '2024-04-29'),
	('841.926.753-82', 'RN589822', 9249.26, '2022-08-25'),
	('534.169.027-34', 'TO833293', 12606.85, '2023-01-14'),
	('290.674.381-03', 'MT475972', 18347.21, '2023-04-22'),
	('841.926.753-82', 'TO833293', 17440.89, '2024-10-07');

--insert dos orgãos
INSERT INTO Orgao_responsavel VALUES
  ('ORG8923', NULL, FALSE, 'Defensoria', 'Almeida', '5329', 'Residencial Martins', 'Rezende do Norte');

INSERT INTO Orgao_responsavel VALUES
  ('ORG33333', 'ORG8923', FALSE, 'Delegacia', 'Aragão', '5244', 'Área da Rocha', 'Lopes da Praia'),
  ('ORG78912', 'ORG8923', TRUE, 'Ministério do Trabalho e Emprego', 'Duarte das Neves e Filhos', '8087', 'Parque Marina Peixoto', 'Nunes'),
  ('ORG91234', 'ORG8923', TRUE, 'Delegacia', 'Peixoto', '9299', 'Aeroporto Kevin Alves', 'Souza'),
  ('ORG22222', 'ORG8923', TRUE, 'Ministério do Trabalho e Emprego', 'Cunha', '1495', 'Rua de Monteiro', 'da Costa');

INSERT INTO Orgao_responsavel VALUES
  ('ORG5689', 'ORG33333', FALSE, 'Delegacia', 'da Mota S/A', '3910', 'Via de da Paz', 'Freitas da Serra'),
  ('ORG45678', 'ORG33333', TRUE, 'Ministério do Trabalho e Emprego', 'da Mota', '1032', 'Vereda de Cardoso', 'Alves'),
  ('ORG6791', 'ORG33333', TRUE, 'Ambiental Estadual', 'Moraes', '6535', 'Lago de Moraes', 'Lima');

INSERT INTO Orgao_responsavel VALUES
  ('ORG12345', 'ORG5689', FALSE, 'Delegacia', 'Cardoso', '1529', 'Área Fernanda Freitas', 'Duarte'),
  ('ORG11111', 'ORG5689', FALSE, 'Delegacia', 'Ribeiro - ME', '8897', 'Chácara de Aragão', 'Porto do Campo');

UPDATE Orgao_responsavel
SET cod_Org_fiscalizador = 'ORG12345'
WHERE cod_ident = 'ORG8923';

--insert das denuncias
INSERT INTO Denuncia (num_ident, status, cod_ident_org, metodo_analise, relato) VALUES
	('DEN00005', 'Em análise', 'ORG78912', 'Automatizada', 'Há favorecimento claro na distribuição de horas extras, sempre para os mesmos funcionários, sem critérios transparentes.'),
	('DEN00002', 'Em análise', 'ORG45678', 'Automatizada', 'O gerente da unidade central tem tratado os colaboradores com grosseria e constantes ameaças de demissão.'),
	('DEN00003', 'Em análise', 'ORG22222', 'Automatizada', 'Funcionários estão marcando ponto para colegas que chegam atrasados ou sequer comparecem.'),
	('DEN00001', 'Em análise', 'ORG11111', 'Perícia técnica', 'Há indícios de desvio de materiais na obra da filial norte. Funcionários estão retirando itens sem controle de estoque.'),
	('DEN00004', 'Encerrada', 'ORG6791', NULL, 'Foi observado o descarte irregular de resíduos no terreno ao lado da empresa, o que pode gerar problemas ambientais.'),
	('DEN00011', 'Encerrada', 'ORG33333', NULL, 'Após investigação interna, identificou-se que um gerente estaria desviando verbas do setor de compras para contas pessoais, utilizando notas fiscais falsas.'),
	('DEN00006', 'Encerrada', 'ORG22222', NULL, 'Contratos estão sendo assinados sem análise adequada. Suspeita-se que fornecedores estão pagando propina a um supervisor.');

--insert das denuncias usando default
INSERT INTO Denuncia (num_ident, cod_ident_org, metodo_analise, relato) VALUES
	('DEN00007', 'ORG5689', 'Automatizada', 'O supervisor da área administrativa tem cobrado metas inalcançáveis e constrangido publicamente funcionários que não as atingem, gerando forte abalo psicológico.'),
	('DEN00008', 'ORG5689', 'Automatizada', 'Foi constatada a repetida ausência de equipamentos de proteção individual em setores com alto risco, colocando em perigo a integridade física dos trabalhadores.'),
	('DEN00012', 'ORG8923', 'Automatizada', 'Estagiários foram flagrados executando tarefas de risco que deveriam ser realizadas por técnicos capacitados, violando normas de segurança e contrato.'),
	('DEN00009', 'ORG91234', 'Automatizada', 'A empresa terceirizada responsável pela limpeza está retendo parte do salário dos trabalhadores sem justificativa formal.'),
	('DEN00010', 'ORG91234', 'Automatizada', 'Funcionários relataram que não receberam pagamento referente às horas extras trabalhadas nos últimos três meses, apesar dos registros em ponto eletrônico.'),
	('DEN00013', 'ORG12345', 'Perícia técnica', 'Denuncio o colaborador Thomas Martins por práticas reiteradas de assédio moral, com ofensas pessoais, intimidações e humilhações frequentes em reuniões.');

--insert para identificar as denuncias
INSERT INTO Denuncia_identificada (num_ident, cpf_denunciante) VALUES
	('DEN00012', '690.243.518-98'),
	('DEN00007', '089.753.621-59'),
	('DEN00008', '138.964.702-13'),
	('DEN00009', '534.169.027-34'),
	('DEN00010', '290.674.381-03'),
	('DEN00011', '841.926.753-82'),
	('DEN00013', '615.907.432-61');

--insert para as denuncias anonimas
INSERT INTO Denuncia_anonima (num_ident) VALUES
	('DEN00001'),
	('DEN00002'),
	('DEN00003'),
	('DEN00004'),
	('DEN00005'),
	('DEN00006');

--insert das violações
INSERT INTO Violacao (cod_vio, descricao) VALUES
	('VIO00001', 'Corrupção'),
	('VIO00002', 'Desvio de patrimônio'),
	('VIO00003', 'Furto interno'),
	('VIO00004', 'Fraude contra a empresa'),
	('VIO00005', 'Assédio moral no trabalho'),
	('VIO00006', 'Conduta inadequada do gestor'),
	('VIO00007', 'Fraude em registro de ponto'),
	('VIO00008', 'Abuso de confiança'),
	('VIO00009', 'Violação das normas de controle de jornada'),
	('VIO00010', 'Crime ambiental'),
	('VIO00011', 'Poluição'),
	('VIO00012', 'Favorecimento'),
	('VIO00013', 'Falta de transparência'),
	('VIO00014', 'Suborno'),
	('VIO00015', 'Fraude contratual'),
	('VIO00016', 'Falta de compliance'),
	('VIO00017', 'Violação das normas trabalhistas'),
	('VIO00018', 'Descarte irregular de resíduos');

--insert das provas
INSERT INTO Prova (cod_prova, tipo_prova, descricao) VALUES 
	('PRV00001', 'Vídeo', 'Registro de funcionários retirando materiais da obra sem controle de estoque'),
	('PRV00002', 'Áudio', 'Gravação de ameaças do gerente da unidade central aos colaboradores'),
	('PRV00003', 'Vídeo', 'Funcionários marcando ponto para colegas ausentes'),
	('PRV00004', 'Foto', 'Imagem do terreno ao lado da empresa com resíduos visíveis'),
	('PRV00005', 'Documento', 'Planilha com distribuição irregular de horas extras'),
	('PRV00006', 'Áudio', 'Conversa gravada envolvendo suspeita de propina em contratos'),
	('PRV00007', 'Vídeo', 'Vídeo mostrando descarte irregular de resíduos em área ambiental'),
	('PRV00008', 'Áudio', 'Depoimento de colaborador sobre falta de análise contratual'),
	('PRV00009', 'Documento', 'Relatório interno indicando favorecimento e falta de transparência'),
	('PRV00010', 'Vídeo', 'Registro de ponto manual fraudulento'),
	('PRV00011', 'Áudio', 'Gravações com cobranças abusivas e constrangimento'),
	('PRV00012', 'Foto', 'Funcionários em área de risco sem equipamentos de proteção'),
	('PRV00013', 'Documento', 'Comprovantes de pagamento e contracheques com valores divergentes'),
	('PRV00014', 'Documento', 'Folhas de ponto e extrato bancário sem acréscimos por hora extra'),
	('PRV00015', 'Documento', 'Notas fiscais frias e transferências suspeitas'),
	('PRV00016', 'Vídeo', 'Vídeo com estagiário operando maquinário sem supervisão'),
	('PRV00017', 'Áudio', 'Gravação de reunião onde o denunciado ofende diretamente a denunciante.');

--insert das provas nas denuncias
INSERT INTO Denuncia_contem_provas (num_ident, cod_prova) VALUES 
	('DEN00001', 'PRV00001'),--desvio de patrimônio e furto interno
	('DEN00002', 'PRV00002'),--assédio moral no trabalho e conduta inadequada do gestor
	('DEN00003', 'PRV00003'),--fraude em registro de ponto e violação das normas de controle de jornada
	('DEN00004', 'PRV00004'),--crime ambiental e descarte irregular de resíduos
	('DEN00005', 'PRV00005'),--favorecimento e falta de transparência
	('DEN00006', 'PRV00006'),--suborno e fraude contratual
	('DEN00004', 'PRV00007'),
	('DEN00006', 'PRV00008'),
	('DEN00005', 'PRV00009'),
	('DEN00003', 'PRV00010'),
	('DEN00012', 'PRV00016'),
	('DEN00011', 'PRV00015'),
	('DEN00010', 'PRV00014'),
	('DEN00009', 'PRV00013'),
	('DEN00008', 'PRV00012'),
	('DEN00007', 'PRV00011'),
	('DEN00013', 'PRV00017');

--insert das violações nas denuncias
INSERT INTO Denuncia_contem_violacao (num_ident, cod_vio) VALUES 
	('DEN00001', 'VIO00002'),--desvio de patrimônio
	('DEN00001', 'VIO00003'),--furto interno
	('DEN00002', 'VIO00005'),--assédio moral no trabalho
	('DEN00007', 'VIO00005'),--assédio moral no trabalho
	('DEN00002', 'VIO00006'),--conduta inadequada do gestor
	('DEN00003', 'VIO00007'),--fraude em registro de ponto
	('DEN00003', 'VIO00009'),--violação das normas de controle de jornada
	('DEN00004', 'VIO00010'),--crime ambiental
	('DEN00004', 'VIO00018'),--descarte irregular de resíduos
	('DEN00005', 'VIO00012'),--Favorecimento
	('DEN00005', 'VIO00013'),--Falta de transparência
	('DEN00006', 'VIO00014'),--Suborno
	('DEN00006', 'VIO00015'),--Fraude contratual
	('DEN00012', 'VIO00017'),-- Violação das normas trabalhistas
	('DEN00011', 'VIO00002'),-- Desvio de patrimônio
	('DEN00011', 'VIO00004'),-- Fraude contra a empresa
	('DEN00010', 'VIO00017'),-- Violação das normas trabalhistas
	('DEN00009', 'VIO00008'),-- Abuso de confiança
	('DEN00008', 'VIO00017'),-- Violação de normas trabalhistas
	('DEN00013', 'VIO00005');-- Assédio moral no trabalho

--insert das pessoas denunciantes
INSERT INTO Pessoa_denunciante (cpf, num_ident) VALUES
	('615.907.432-61', 'DEN00013'),
	('690.243.518-98', 'DEN00012'),
	('089.753.621-59', 'DEN00007'),
	('138.964.702-13', 'DEN00008'),
	('841.926.753-82', 'DEN00011'),
	('534.169.027-34', 'DEN00009'),
	('290.674.381-03', 'DEN00010');

--insert das pessoas denunciadas
INSERT INTO Pessoa_denunciada (cpf, cod_ident_org, data_comunicado) VALUES
	('089.753.621-59', 'ORG12345', '2025-06-07');

--insert dos advogados que acompanham as denuncias
INSERT INTO Advogado_acompanha_denuncia (num_oab, num_ident) VALUES
	('SP862477', 'DEN00012'),
	('SP175467', 'DEN00007'),
	('RN589822', 'DEN00011');
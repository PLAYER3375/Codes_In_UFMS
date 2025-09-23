--Trabalho de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--SIGVID - Sistema Integrado de Gestão de Violações e Denúncias.

--Autores:
--Matheus Henrique dos Santos Gomes
--Paulo Antonio Blasque Fernandes

--Arquivo para a criação das tabelas:

--Criação da tabela de violações
CREATE TABLE Violacao(
  cod_vio VARCHAR(10) NOT NULL,
  descricao TEXT NOT NULL,
  PRIMARY KEY (cod_vio)
);

--Criação da tabela de provas
CREATE TABLE Prova(
  cod_prova VARCHAR(10) NOT NULL,
  tipo_prova VARCHAR(50) NOT NULL,
  descricao TEXT,
  PRIMARY KEY (cod_prova)
);

--Criação da tabela de pessoas
CREATE TABLE Pessoa(
  cpf CHAR(14) NOT NULL,
  nome VARCHAR(100) NOT NULL,
  idade INTEGER CHECK(idade>0),
  PRIMARY KEY (cpf)
);

--Criação da tabela advogados
CREATE TABLE Advogado(
  num_oab VARCHAR(10) NOT NULL,
  nome VARCHAR(100) NOT NULL,
  area_atua VARCHAR(100) DEFAULT 'Civil',
  PRIMARY KEY (num_oab)
);

--Criação da tabela de contratos
CREATE TABLE Contrato(
  cpf_pes CHAR(14) NOT NULL,
  num_oab VARCHAR(10) NOT NULL,
  valor_contrato DECIMAL(9,2),
  data_contrato DATE,
  PRIMARY KEY (cpf_pes, num_oab),
  FOREIGN KEY (cpf_pes) REFERENCES Pessoa(cpf),
  FOREIGN KEY (num_oab) REFERENCES Advogado(num_oab)
);

--Criação da tabela dos orgãos responsáveis
CREATE TABLE Orgao_responsavel(
  cod_ident VARCHAR(10) NOT NULL,
  cod_Org_fiscalizador VARCHAR(10),
  fiscalizado_anonimamente BOOLEAN DEFAULT FALSE,
  tipo_org VARCHAR(50) NOT NULL,
  nome VARCHAR(100) NOT NULL,
  end_num VARCHAR(10),
  end_logradouro VARCHAR(100),
  end_cidade VARCHAR(50),
  PRIMARY KEY (cod_ident),
  FOREIGN KEY (cod_Org_fiscalizador) REFERENCES Orgao_responsavel(cod_ident)
);

--Criação da tabela da pessoa denunciada
CREATE TABLE Pessoa_denunciada(
  cpf CHAR(14) NOT NULL,
  cod_ident_org VARCHAR(10) NOT NULL,
  data_comunicado DATE,
  PRIMARY KEY (cpf, cod_ident_org),
  FOREIGN KEY (cpf) REFERENCES Pessoa(cpf),
  FOREIGN KEY (cod_ident_org) REFERENCES Orgao_responsavel(cod_ident)
);

--Criação da tabela de denuncia
CREATE TABLE Denuncia(
  num_ident VARCHAR(10) NOT NULL,
  status VARCHAR(20) DEFAULT 'Aberta' CHECK (status IN ('Em análise', 'Encerrada', 'Aberta')),
  cod_ident_org VARCHAR(10) NOT NULL,
  metodo_analise VARCHAR(100) CHECK (metodo_analise IN ('Automatizada', 'Perícia técnica')),
  relato TEXT,
  PRIMARY KEY (num_ident),
  FOREIGN KEY (cod_ident_org) REFERENCES Orgao_responsavel(cod_ident)
);

--Criação da tabela de pessoa denunciante
CREATE TABLE Pessoa_denunciante (
  cpf CHAR(14) NOT NULL,
  relacao_caso VARCHAR(20) DEFAULT 'Vítima' CHECK (relacao_caso IN ('Vítima', 'Testemunha')),
  num_ident VARCHAR(10) NOT NULL,
  PRIMARY KEY (cpf, relacao_caso, num_ident),
  FOREIGN KEY (cpf) REFERENCES Pessoa(cpf),
  FOREIGN KEY (num_ident) REFERENCES Denuncia(num_ident)
);

--Criação da tabela de telefones das pessoas
CREATE TABLE telefonePessoa(
  cpf CHAR(14) NOT NULL,
  telefone VARCHAR(15),
  PRIMARY KEY (cpf, telefone),
  FOREIGN KEY (cpf) REFERENCES Pessoa(cpf)
);

--Criação da tabela de denuncias identificadas
CREATE TABLE Denuncia_identificada(
  num_ident VARCHAR(10) NOT NULL,
  cpf_denunciante CHAR(14) NOT NULL,
  PRIMARY KEY (num_ident),
  FOREIGN KEY (cpf_denunciante) REFERENCES Pessoa(cpf),
  FOREIGN KEY (num_ident) REFERENCES Denuncia(num_ident)
);

--Criação da tabela de denuncias anonimas
CREATE TABLE Denuncia_anonima(
  num_ident VARCHAR(10) NOT NULL,
  PRIMARY KEY (num_ident),
  FOREIGN KEY (num_ident) REFERENCES Denuncia(num_ident)
);

--Criação da tabela que representa o relacionamento do advogado acompanhar uma denuncia
CREATE TABLE Advogado_acompanha_denuncia(
  num_oab VARCHAR(10) NOT NULL,
  num_ident VARCHAR(10) NOT NULL,
  PRIMARY KEY (num_oab, num_ident),
  FOREIGN KEY (num_oab) REFERENCES Advogado(num_oab),
  FOREIGN KEY (num_ident) REFERENCES Denuncia_identificada(num_ident)
);

--Criação da tabela que representa o relacionamento da denuncia conter uma prova
CREATE TABLE Denuncia_contem_provas(
  num_ident VARCHAR(10) NOT NULL,
  cod_prova VARCHAR(10) NOT NULL,
  PRIMARY KEY (num_ident, cod_prova),
  FOREIGN KEY (num_ident) REFERENCES Denuncia(num_ident),
  FOREIGN KEY (cod_prova) REFERENCES Prova(cod_prova)
);

--Criação da tabela que representa o relacionamento da denuncia conter uma violação
CREATE TABLE Denuncia_contem_violacao(
  num_ident VARCHAR(10) NOT NULL,
  cod_vio VARCHAR(10) NOT NULL,
  PRIMARY KEY (num_ident, cod_vio),
  FOREIGN KEY (num_ident) REFERENCES Denuncia(num_ident),
  FOREIGN KEY (cod_vio) REFERENCES Violacao(cod_vio)
);
--Trabalho de Laboratório de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--MarceDB - Sistema de gestão para marcenaria.

--Autor:
--Matheus Henrique dos Santos Gomes

--Arquivo para a criação das tabelas:

CREATE TABLE cliente (
    id_cliente INTEGER PRIMARY KEY,
    cpf VARCHAR(11) UNIQUE NOT NULL,
    nomeCliente VARCHAR(255) NOT NULL
);

CREATE TABLE modulo (
    id_modulo INTEGER PRIMARY KEY,
    complexidade INTEGER DEFAULT 1 CHECK(complexidade>0 OR complexidade<6) --a complexidade será calculada contando o número de peças do módulo
);

CREATE TABLE funcionario (
    id_func INTEGER PRIMARY KEY,
    salario DECIMAL(10, 2) NOT NULL,
    bonus DECIMAL(10, 2) DEFAULT 0,
    id_funcGerente INTEGER,
    FOREIGN KEY (id_funcGerente) REFERENCES funcionario(id_func)
);

CREATE TABLE montador (
    id_funcMontador INTEGER PRIMARY KEY,
    externo BOOLEAN,
    FOREIGN KEY (id_funcMontador) REFERENCES funcionario(id_func)
);

CREATE TABLE operador (
    id_funcOperador INTEGER PRIMARY KEY,
    maquina VARCHAR(100),
    FOREIGN KEY (id_funcOperador) REFERENCES funcionario(id_func)
);

CREATE TABLE vendedor (
    id_funcVendedor INTEGER PRIMARY KEY,
    cidadeAtua VARCHAR(100),
    FOREIGN KEY (id_funcVendedor) REFERENCES funcionario(id_func)
);

CREATE TABLE projeto (
    id_projeto INTEGER PRIMARY KEY,
    finalizado BOOLEAN DEFAULT FALSE,
    ambientes VARCHAR(255),
    valorVenda DECIMAL(10, 2),
    diaVendido DATE,
    garantiaMesVenda INTEGER,
    id_cli INTEGER NOT NULL,
    id_funcVendedor INTEGER NOT NULL,
    FOREIGN KEY (id_cli) REFERENCES cliente(id_cliente),
    FOREIGN KEY (id_funcVendedor) REFERENCES vendedor(id_funcVendedor)
);

CREATE TABLE estoqueChapa (
    id_chapa INTEGER PRIMARY KEY,
    cor VARCHAR(50),
    espessura DECIMAL(5, 2),
    qtd INTEGER
);

CREATE TABLE corte (
    id_corte INTEGER PRIMARY KEY,
    cortado BOOLEAN,
    diaCortado DATE,
    inicio_corte TIME WITHOUT TIME ZONE,
    fim_corte TIME WITHOUT TIME ZONE,
    id_chapaUsar INTEGER NOT NULL,
    id_funcCortou INTEGER,
    id_projOrigem INTEGER NOT NULL,
    FOREIGN KEY (id_chapaUsar) REFERENCES estoqueChapa(id_chapa),
    FOREIGN KEY (id_funcCortou) REFERENCES operador(id_funcOperador),
    FOREIGN KEY (id_projOrigem) REFERENCES projeto(id_projeto)
);

CREATE TABLE peca (
    id_peca INTEGER PRIMARY KEY,
    altura DECIMAL(10, 2),
    espessura DECIMAL(5, 2),
    largura DECIMAL(10, 2),
    id_corteOrigem INTEGER NOT NULL,
    id_moduloDestino INTEGER NOT NULL,
    FOREIGN KEY (id_corteOrigem) REFERENCES corte(id_corte),
    FOREIGN KEY (id_moduloDestino) REFERENCES modulo(id_modulo)
);

CREATE TABLE montaModulo (
    id_modulo INTEGER,
    id_montador INTEGER,
    diaMontado DATE,
    PRIMARY KEY (id_modulo, id_montador),
    FOREIGN KEY (id_modulo) REFERENCES modulo(id_modulo),
    FOREIGN KEY (id_montador) REFERENCES montador(id_funcMontador)
);
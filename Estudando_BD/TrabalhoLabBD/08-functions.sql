--Trabalho de Laboratório de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--MarceDB - Sistema de gestão para marcenaria.

--Autor:
--Matheus Henrique dos Santos Gomes

--Arquivo para a criação das funções:

-- 1 - ordem de compra para chapas que serão cortadas e não estão em estoque
CREATE OR REPLACE FUNCTION ordem_compra()
RETURNS SETOF RECORD AS $$
DECLARE
    reg RECORD;
BEGIN
    FOR reg IN 
        SELECT 
            ec.id_chapa,
            ec.cor,
            ec.espessura,
            ec.qtd AS qtd_estoque,
            cp.qtd_necessaria,
            GREATEST(cp.qtd_necessaria-ec.qtd, 0) AS qtd_comprar
        FROM estoqueChapa as ec
        JOIN(
            SELECT c.id_chapaUsar, COUNT(*) AS qtd_necessaria
            FROM corte as c
            WHERE c.cortado=FALSE
            GROUP BY c.id_chapaUsar) as cp ON ec.id_chapa=cp.id_chapaUsar
        WHERE cp.qtd_necessaria>ec.qtd
        ORDER BY qtd_comprar DESC
    LOOP
        RETURN NEXT reg;
    END LOOP;

    RETURN;
END;
$$ LANGUAGE plpgsql;

--usar:
--SELECT * FROM ordem_compra() AS (
--    id_chapa INTEGER,
--    cor VARCHAR(50),
--   espessura DECIMAL(5,2),
--    qtd_estoque INTEGER,
--    qtd_necessaria INTEGER,
--    qtd_comprar INTEGER
--);

-- 2 - Verificar atividade do cliente nos últimos 12 meses
CREATE OR REPLACE FUNCTION atividade_cliente(p_id_cliente INTEGER)
RETURNS INTEGER AS $$
DECLARE
    compras_recentes INTEGER;
BEGIN
    compras_recentes:=0;

    SELECT COUNT(*)
    INTO compras_recentes
    FROM projeto
    WHERE id_cli=p_id_cliente
        AND diaVendido>=CURRENT_DATE-INTERVAL '12 months';
    
    RETURN compras_recentes;
END;
$$ LANGUAGE 'plpgsql';

--usar select atividade_cliente(1)

-- 3 - Verificar se a garantia está expirada
CREATE OR REPLACE FUNCTION garantia_vencida(p_id_projeto INTEGER)
RETURNS TEXT AS $$
DECLARE
    data_vencimento DATE;
BEGIN
    SELECT (diaVendido + (garantiaMesVenda || ' months')::INTERVAL)::DATE
    INTO data_vencimento
    FROM projeto
    WHERE id_projeto = p_id_projeto;

    IF data_vencimento IS NULL THEN
        RETURN 'Projeto não encontrado';
    END IF;

    IF CURRENT_DATE > data_vencimento THEN
        RETURN 'garantia expirada';
    ELSE
        RETURN 'ainda em garantia';
    END IF;
END;
$$ LANGUAGE 'plpgsql';

--usar select garantia_vencida(1)
--Trabalho de Laboratório de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--MarceDB - Sistema de gestão para marcenaria.

--Autor:
--Matheus Henrique dos Santos Gomes

--Arquivo para a criação das gatilhos:

-- 1 - Atualizar complexidade do módulo automaticamente
CREATE OR REPLACE FUNCTION atualizar_complexidade_modulo()
RETURNS TRIGGER AS $$
BEGIN
    --Atualiza a complexidade baseada na quantidade de peças no módulo
    UPDATE modulo 
    SET complexidade=(
        SELECT 
            CASE 
                WHEN COUNT(*) BETWEEN 1 AND 3 THEN 1
                WHEN COUNT(*) BETWEEN 4 AND 6 THEN 2
                WHEN COUNT(*) BETWEEN 7 AND 9 THEN 3
                WHEN COUNT(*) BETWEEN 10 AND 12 THEN 4
                WHEN COUNT(*) > 12 THEN 5
                ELSE 1
            END
        FROM peca 
        WHERE id_moduloDestino=COALESCE(NEW.id_moduloDestino, OLD.id_moduloDestino)
    )
    WHERE id_modulo=COALESCE(NEW.id_moduloDestino, OLD.id_moduloDestino);
    
    RETURN COALESCE(NEW, OLD);
END;
$$ LANGUAGE 'plpgsql';

CREATE TRIGGER trig_atualizar_complexidade
    AFTER INSERT OR UPDATE OR DELETE ON peca
    FOR EACH ROW
    EXECUTE FUNCTION atualizar_complexidade_modulo();

-- 2 - Validar data de venda do projeto
CREATE OR REPLACE FUNCTION validar_data_venda()
RETURNS TRIGGER AS $$
BEGIN
    -- Não permite data de venda futura
    IF NEW.diaVendido>CURRENT_DATE THEN
        RAISE EXCEPTION 'Data de venda não pode ser futura: %', NEW.diaVendido;
    END IF;
    
    -- Garantia mínima de 3 meses
    IF NEW.garantiaMesVenda<3 THEN
        RAISE EXCEPTION 'Garantia mínima deve ser de 3 meses';
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE 'plpgsql';

CREATE TRIGGER trig_validar_data_venda
    BEFORE INSERT OR UPDATE ON projeto
    FOR EACH ROW
    EXECUTE FUNCTION validar_data_venda();

-- 3 - atualiza estoque após corte
CREATE OR REPLACE FUNCTION atualizar_estoque_apos_corte()
RETURNS TRIGGER AS $$
BEGIN
    -- Quando um corte é marcado como realizado, reduz o estoque
    IF NEW.cortado=TRUE AND (OLD.cortado=FALSE OR OLD.cortado IS NULL) THEN
        UPDATE estoqueChapa 
        SET qtd=qtd-1  
        WHERE id_chapa=NEW.id_chapaUsar
        AND qtd>0;
        
        --estoque mínimo de 5
        IF (SELECT qtd FROM estoqueChapa WHERE id_chapa = NEW.id_chapaUsar)<5 THEN
            RAISE NOTICE 'ALERTA: Estoque da chapa % está abaixo de 5 unidades', NEW.id_chapaUsar;
        END IF;
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE 'plpgsql';

CREATE TRIGGER trig_atualizar_estoque
    AFTER UPDATE ON corte
    FOR EACH ROW
    EXECUTE FUNCTION atualizar_estoque_apos_corte();

-- 4 - Coloca o projeto como finalizado ao fim de todos os cortes.
CREATE OR REPLACE FUNCTION verificar_finalizacao_projeto()
RETURNS TRIGGER AS $$
DECLARE
    total_cortes_projeto INTEGER;
    cortes_concluidos INTEGER;
    projeto_finalizado BOOLEAN;
BEGIN
    SELECT COUNT(*)
    INTO total_cortes_projeto
    FROM corte
    WHERE id_projOrigem = NEW.id_projOrigem;
    
    SELECT COUNT(*)
    INTO cortes_concluidos
    FROM corte
    WHERE id_projOrigem = NEW.id_projOrigem
    AND cortado = TRUE;
    
    projeto_finalizado:=(total_cortes_projeto=cortes_concluidos);
    
    UPDATE projeto 
    SET finalizado=projeto_finalizado
    WHERE id_projeto=NEW.id_projOrigem;
    
    IF projeto_finalizado THEN
        RAISE NOTICE 'Projeto % FINALIZADO!', NEW.id_projOrigem;
    END IF;
    
    RETURN NEW;
END;
$$ LANGUAGE 'plpgsql';

CREATE TRIGGER trig_verificar_finalizacao_projeto
    AFTER UPDATE OF cortado ON corte
    FOR EACH ROW
    EXECUTE FUNCTION verificar_finalizacao_projeto();
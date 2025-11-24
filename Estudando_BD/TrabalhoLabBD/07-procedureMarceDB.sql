--Trabalho de Laboratório de Banco de Dados da Universidade Federal de Mato Grosso do Sul
--Professor(a):
--Ivone Penque Matsuno Yugoshi

--MarceDB - Sistema de gestão para marcenaria.

--Autor:
--Matheus Henrique dos Santos Gomes

--Arquivo para a criação dos procedimentos:

-- 1 - bônus mensal dos funcionarios
CREATE OR REPLACE PROCEDURE calcular_bonus_mensal(p_mes INTEGER, p_ano INTEGER) AS $$
DECLARE
    total_vendas DECIMAL(10,2);
    total_cortes INTEGER;
    bonus_vendedor DECIMAL(10,2);
    bonus_operador DECIMAL(10,2);
    bonus_montador DECIMAL(10,2);
    reg RECORD;
BEGIN
    --bônus de vendedores em 1% das vendas
    FOR reg IN 
        SELECT v.id_funcVendedor, COALESCE(SUM(p.valorVenda), 0) as total_mes
        FROM vendedor as v
        LEFT JOIN projeto as p ON v.id_funcVendedor=p.id_funcVendedor
            AND EXTRACT(MONTH FROM p.diaVendido)=p_mes
            AND EXTRACT(YEAR FROM p.diaVendido)=p_ano
        GROUP BY v.id_funcVendedor
    LOOP
        bonus_vendedor:=reg.total_mes*0.01;
        UPDATE funcionario 
        SET bonus=bonus_vendedor
        WHERE id_func=reg.id_funcVendedor;
        RAISE NOTICE 'Vendedor %: bônus de R$ % calculado sobre vendas de R$ % no mês % do ano %', reg.id_funcVendedor, bonus_vendedor, reg.total_mes, p_mes, p_ano;
    END LOOP;
    
    --bônus para operadores por corte de R$5,00
    FOR reg IN 
        SELECT o.id_funcOperador, COUNT(c.id_corte) as cortes_mes
        FROM operador as o
        LEFT JOIN corte as c ON o.id_funcOperador=c.id_funcCortou
            AND EXTRACT(MONTH FROM c.diaCortado)=p_mes
            AND EXTRACT(YEAR FROM c.diaCortado)=p_ano
            AND c.cortado=TRUE
        GROUP BY o.id_funcOperador
    LOOP
        bonus_operador:=reg.cortes_mes*5.00;
        UPDATE funcionario 
        SET bonus=bonus_operador
        WHERE id_func=reg.id_funcOperador;
        RAISE NOTICE 'Operador %: bônus de R$ % calculado sobre % cortes no mês % do ano %', reg.id_funcOperador, bonus_operador, reg.cortes_mes, p_mes, p_ano;
    END LOOP;
    
    --bônus para montadores pela soma da complexidade de tudo montado por eles
    FOR reg IN 
        SELECT m.id_funcMontador, COALESCE(SUM(md.complexidade), 0) as complexidadeMontados
        FROM montador as m
        LEFT JOIN montamodulo as mm ON m.id_funcMontador=mm.id_montador
            AND EXTRACT(MONTH FROM mm.diaMontado)=p_mes
            AND EXTRACT(YEAR FROM mm.diaMontado)=p_ano
        LEFT JOIN modulo as md ON mm.id_modulo=md.id_modulo
        GROUP BY m.id_funcMontador
    LOOP
        bonus_montador:=reg.complexidadeMontados;
        UPDATE funcionario 
        SET bonus=bonus_montador
        WHERE id_func=reg.id_funcMontador;
        RAISE NOTICE 'Montador %: bônus de R$ % calculado sobre a soma de complexidade dos módulos montados no mês % do ano %', reg.id_funcMontador, bonus_montador, p_mes, p_ano;
    END LOOP;

    --colocar bônus=0 para os funcionários que não tiveram bônus calculado
    UPDATE funcionario 
    SET bonus=0
    WHERE id_func NOT IN (
        SELECT id_funcVendedor FROM vendedor 
        UNION 
        SELECT id_funcOperador FROM operador
        UNION
        SELECT id_funcMontador FROM montador
    );
    
    RAISE NOTICE 'Cálculo de bônus para %/% concluído!', p_mes, p_ano;
END;
$$ LANGUAGE 'plpgsql';
-- Usar: CALL calcular_bonus_mensal(1, 2024)

-- 2 - Finalizar projeto e todos os seus cortes
CREATE OR REPLACE PROCEDURE finalizar_projeto(p_id_projeto INTEGER) AS $$
DECLARE
    v_projeto_exist BOOLEAN;
BEGIN
    --Verificar se projeto existe
    v_projeto_exist:=FALSE;

    SELECT EXISTS(SELECT 1 FROM projeto WHERE id_projeto=p_id_projeto) 
    INTO v_projeto_exist;
    
    IF v_projeto_exist=FALSE THEN
        RAISE EXCEPTION 'Projeto % não encontrado', p_id_projeto;
    END IF;

    --Verificar se já está finalizado
    IF (SELECT finalizado FROM projeto WHERE id_projeto=p_id_projeto) THEN
        RAISE NOTICE 'Projeto % já está finalizado.', p_id_projeto;
        RETURN;
    END IF;
    
    -- Finalizar todos os cortes pendentes
    UPDATE corte 
    SET cortado=TRUE,
        diaCortado=CURRENT_DATE,
        inicio_corte=COALESCE(inicio_corte, '08:00:00'),
        fim_corte=COALESCE(fim_corte, '17:00:00')
    WHERE id_projOrigem=p_id_projeto AND cortado=FALSE;
    
    -- Marcar projeto como finalizado
    UPDATE projeto SET finalizado=TRUE WHERE id_projeto=p_id_projeto;
    
    RAISE NOTICE 'Projeto % finalizado! Os cortes pendentes foram concluídos.', p_id_projeto;
END;
$$ LANGUAGE 'plpgsql';

-- 3 - Relatório mensal
CREATE OR REPLACE PROCEDURE relatorio_mensal(p_mes INTEGER, p_ano INTEGER) AS $$
DECLARE
    reg RECORD;
    projetos_vendidos INTEGER;
    valor_total_vendas DECIMAL(10,2);
    total_cortes INTEGER;
    media_cortes_dia DECIMAL(10,2);
    media_complexidade DECIMAL(10,2);
BEGIN
    RAISE NOTICE '=== RELATÓRIO - %/% ===', p_mes, p_ano;
    RAISE NOTICE '';
    
    --Parte de vendas
    SELECT COUNT(*), COALESCE(SUM(valorVenda), 0)
    INTO projetos_vendidos, valor_total_vendas
    FROM projeto
    WHERE EXTRACT(MONTH FROM diaVendido)=p_mes
        AND EXTRACT(YEAR FROM diaVendido)=p_ano;
    
    RAISE NOTICE 'VENDAS:';
    RAISE NOTICE 'Projetos vendidos: %', projetos_vendidos;
    RAISE NOTICE 'Valor total de vendas: R$ %', valor_total_vendas;
    RAISE NOTICE '';
    
    --Parte de cortes
    SELECT COUNT(*)
    INTO total_cortes
    FROM corte
    WHERE EXTRACT(MONTH FROM diaCortado)=p_mes
        AND EXTRACT(YEAR FROM diaCortado)=p_ano
        AND cortado=TRUE;

    IF total_cortes>0 THEN
        media_cortes_dia:=ROUND(total_cortes/24.0, 2);
    ELSE
        media_cortes_dia:=0;
    END IF;
    
    RAISE NOTICE 'PRODUÇÃO:';
    RAISE NOTICE 'Total de cortes: %', total_cortes;
    RAISE NOTICE 'Média de cortes por dias úteis: %', media_cortes_dia;
    RAISE NOTICE '';
    
    --Parte de montagem
    SELECT COALESCE(AVG(m.complexidade), 0)
    INTO media_complexidade
    FROM modulo as m
    JOIN montaModulo mm ON m.id_modulo=mm.id_modulo
    WHERE EXTRACT(MONTH FROM mm.diaMontado)=p_mes
        AND EXTRACT(YEAR FROM mm.diaMontado)=p_ano;
    
    RAISE NOTICE 'MÓDULOS:';
    RAISE NOTICE 'Média de complexidade dos módulos montados: %', ROUND(media_complexidade, 2);
END;
$$ LANGUAGE 'plpgsql';
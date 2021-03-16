-- 1 cu tabel imbricat
desc employees;
CREATE TABLE emp_stl AS SELECT * FROM employees;
DECLARE
    TYPE tablou_imbricat IS TABLE OF employees%ROWTYPE;
    t tablou_imbricat;
    i NUMBER(6);
BEGIN
    SELECT *
    BULK COLLECT INTO t
    FROM (SELECT *
          FROM emp_stl
          WHERE commission_pct IS NULL
          ORDER BY salary)
    WHERE ROWNUM<=5;
    FOR i IN t.first..t.last LOOP
        DBMS_OUTPUT.PUT_LINE(t(i).employee_id || ' ' || t(i).salary || ' ' || t(i).salary*1.05);
        UPDATE emp_stl
        SET salary = salary*1.05
        WHERE employee_id = t(i).employee_id;
    END LOOP;
END;
/

-- 1 cu vector
DECLARE
    TYPE vectorid IS VARRAY(200) OF employees.employee_id%TYPE;
    TYPE vectorsal IS VARRAY(200) OF employees.salary%TYPE;
    vid vectorid;
    vsal vectorsal;
BEGIN
    SELECT employee_id BULK COLLECT INTO vid
    FROM (SELECT *
          FROM emp_stl
          WHERE commission_pct IS NULL
          ORDER BY salary)
    WHERE ROWNUM<=5;
    
    SELECT salary INTO vsal
    FROM (SELECT *
          FROM emp_stl
          WHERE commission_pct IS NULL
          ORDER BY salary)
    WHERE ROWNUM<=5;
    FOR i IN vid.first..vid.last LOOP
        DBMS_OUTPUT.PUT_LINE(vid(i) || ' ' || vsal(i) || ' ' || vsal(i)*1.05);
        UPDATE emp_stl
        SET salary = salary*1.05
        WHERE employee_id = vid(i);
    END LOOP;
END;
/

--2
CREATE OR REPLACE TYPE tip_orase_stl IS TABLE OF VARCHAR(30);
/
CREATE TABLE excursie_stl(cod_excursie NUMBER(4) PRIMARY KEY, denumire VARCHAR2(20), orase tip_orase_stl, status VARCHAR(20))
NESTED TABLE orase STORE AS tip_orase_stl;
INSERT INTO excursie_stl
VALUES (1, 'Mare', tip_orase_stl('Mamaia','Mangalia'), 'disponibila');
INSERT INTO excursie_stl
VALUES (1, 'Munte', tip_orase_stl('Sinaia','Busteni', 'Predeal'), 'disponibila');
INSERT INTO excursie_stl
VALUES (1, 'Franta', tip_orase_stl('Paris', 'Lyon', 'Marseille', 'Bordeaux'), 'anulata');
INSERT INTO excursie_stl
VALUES (1, 'Germania', tip_orase_stl('Berlin', 'Munich', 'Hamburg'), 'anulata');

--b
--oras la final
DECLARE
    excursie excursie_stl.denumire%TYPE := &p_excursie;
    oras VARCHAR(30) := &p_oras;
    vor tip_orase_stl;
BEGIN
    SELECT orase INTO vor
    FROM excursie_stl
    WHERE UPPER(denumire) = UPPER(excursie);
    
    vor.extend;
    vor(vor.last) := oras;
    
    UPDATE excursie_stl
    SET oras = vor
    WHERE UPPER(denumire) = UPPER(excursie);
END;
/

--oras pe poz 2
DECLARE
    excursie excursie_stl.denumire%TYPE := &p_excursie;
    oras VARCHAR(30) := &p_oras;
    vor tip_orase_stl;
    vaux tip_orase_stl;
BEGIN
    SELECT orase INTO vor
    FROM excursie_stl
    WHERE UPPER(denumire) = UPPER(excursie);
    
    vaux.extend;
    vaux(vaux.first) := vor.first;
    vaux.extend;
    vaux(vaux.last) := oras;
    FOR i IN 3..vor.count LOOP
        vaux.extend;
        vaux(vaux.last) := vor(i);
    END LOOP;
    
    UPDATE excursie_stl
    SET oras = vaux
    WHERE UPPER(denumire) = UPPER(excursie);
END;
/

--inversare ordine
DECLARE
    excursie excursie_stl.denumire%TYPE := &p_excursie;
    oras1 VARCHAR(30) := &p_oras1;
    oras2 VARCHAR(30) := &p_oras2;
    vor tip_orase_stl;
BEGIN
    SELECT orase INTO vor
    FROM excursie_stl
    WHERE UPPER(denumire) = UPPER(excursie);
    
    FOR i in vor.first..vor.last LOOP
        IF(vor(i) = oras1) THEN
            vor(i) := oras2;
        END IF;
        IF(vor(i) = oras2) THEN
            vor(i) := oras1;
        END IF;
    END LOOP;
    
    UPDATE excursie_stl
    SET oras = vor
    WHERE UPPER(denumire) = UPPER(excursie);
END;
/

--eliminare oras dat
DECLARE
    excursie excursie_stl.denumire%TYPE := &p_excursie;
    oras VARCHAR(30) := &p_oras;
    ind NUMBER(3);
    vor tip_orase_stl;
BEGIN
    SELECT orase INTO vor
    FROM excursie_stl
    WHERE UPPER(denumire) = UPPER(excursie);
    
    FOR i in vor.first..vor.last LOOP
        IF(vor(i) = oras) THEN
            ind := i;
        END IF;
    END LOOP;
    
    vor.delete(ind);
    
    UPDATE excursie_stl
    SET oras = vor
    WHERE UPPER(denumire) = UPPER(excursie);
END;
/

--c
DECLARE
    idex excursie_stl.cod_excursie%TYPE := &p_excursie;
    vor tip_orase_stl;
BEGIN
    SELECT orase INTO vor
    FROM excursie_stl
    WHERE idex = cod_excursie;
    DBMS_OUTPUT.PUT_LINE('Nr orase:' || vor.count);
    DBMS_OUTPUT.PUT_LINE('Denumire orase:' || vor.count);
    FOR i in vor.first..vor.last LOOP
        DBMS_OUTPUT.PUT_LINE(vor(i) || ' ');
    END LOOP;
END;
/

--d
DECLARE
    TYPE excursii IS TABLE OF excursie_stl%ROWTYPE;
    exc excursii;
BEGIN
    SELECT * INTO exc
    FROM excursie_stl;
    
    FOR i IN exc.first..exc.last LOOP
        DBMS_OUTPUT.PUT_LINE(exc.orase.count || ' orase in excursia ' || exc.denumire);
        FOR j IN exc.orase.first..exc.orase.second LOOP
            DBMS_OUTPUT.PUT_LINE(exc.orase(j) || ' ');
        END LOOP;
    END LOOP;
END;
/
--e
DECLARE
    TYPE excursii IS TABLE OF excursie_stl%ROWTYPE;
    exc excursii;
    minim NUMBER(6) := 7644286;
BEGIN
    SELECT * INTO exc
    FROM excursie_stl;
    
    FOR i IN exc.first..exc.last LOOP
        IF (exc(i).orase.count < minim) THEN
            minim := exc(i).orase.count;
        END IF;
    END LOOP;
    
    FOR i IN exc.first..exc.last LOOP
        IF (exc(i).orase.count = minim) THEN
            UPDATE excursie_stl
            SET status = 'anulata'
            WHERE exc(i).cod_excursie = cod_excursie;
        END IF;
    END LOOP;
END;
/
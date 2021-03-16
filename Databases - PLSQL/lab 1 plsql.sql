--plsql1 pb1
DECLARE
    numar number(3):=100;
    mesaj1 varchar2(255):='text 1';
    mesaj2 varchar2(255):='text 2';
BEGIN
    DECLARE
        numar number(3):=1;
        mesaj1 varchar2(255):='text 2';
        mesaj2 varchar2(255):='text 3';
    BEGIN
        numar := numar + 1;
        mesaj2 := mesaj2 || ' adaugat in sub-bloc';
        DBMS_OUTPUT.PUT_LINE('valoarea variabilei numar in subbloc: ' || numar);
        DBMS_OUTPUT.PUT_LINE('valoarea variabilei mesaj1 in subbloc: ' || mesaj1);
        DBMS_OUTPUT.PUT_LINE('valoarea variabilei mesaj2 in subbloc: ' || mesaj2);
    END;
    
    numar := numar + 1;
    mesaj1 := mesaj1 || ' adaugat in blocul principal';
    mesaj2 := mesaj2 || ' adaugat in blocul principal';
    DBMS_OUTPUT.PUT_LINE('valoarea variabilei numar in bloc: ' || numar);
    DBMS_OUTPUT.PUT_LINE('valoarea variabilei mesaj1 in bloc: ' || mesaj1);
    DBMS_OUTPUT.PUT_LINE('valoarea variabilei mesaj2 in bloc: ' || mesaj2);
END;
/

--plsql1 pb2
--b
CREATE TABLE octombrie_stl(id number(4), data date);
DECLARE
    contor NUMBER(6) := 1;
    v_data DATE := TO_DATE('2020-10-01', 'YYYY-MM-DD');
BEGIN
    WHILE contor <= 31 LOOP
        INSERT INTO octombrie_stl
        VALUES (contor, v_data);
        v_data := v_data + 1;
        contor := contor + 1;
    END LOOP;
END;
/

SELECT data, COUNT(book_date)
FROM octombrie_stl LEFT JOIN rental ON TO_CHAR(data, 'dd/mm/yyyy') = TO_CHAR(book_date, 'dd/mm/yyyy')
GROUP BY data;

--3

--DESC member;
--desc reservation;
--desc title;
--select title, last_name
--from member m, reservation r, title t
--where m.member_id = r.member_id and r.title_id = t.title_id;
--select * from reservation;
DECLARE
v_nume member.last_name%TYPE := '&p_nume';
v_nrfilme NUMBER(6);
BEGIN
    SELECT COUNT(title_id) into v_nrfilme
    FROM member m JOIN reservation r on m.member_id = r.member_id
    WHERE UPPER(m.last_name) = UPPER(v_nume);
    DBMS_OUTPUT.PUT_LINE('Numarul de filme inchiriate de ' || INITCAP(v_nume) || ' este ' || v_nrfilme);
    EXCEPTION
        WHEN no_data_found THEN
            DBMS_OUTPUT.PUT_LINE('Membrul nu a fost gasit.');
        WHEN too_many_rows THEN
            DBMS_OUTPUT.PUT_LINE('S-au gasit mai multi membri cu acest nume.');
END;
/

--4
DECLARE
v_nume member.last_name%TYPE := '&p_nume';
v_nrfilme NUMBER(6);
v_nrfilmetot NUMBER(6);
BEGIN
    SELECT COUNT(*) into v_nrfilmetot
    FROM title;
    SELECT COUNT(title_id) into v_nrfilme
    FROM member m JOIN reservation r on m.member_id = r.member_id
    WHERE UPPER(m.last_name) = UPPER(v_nume);
    DBMS_OUTPUT.PUT_LINE('Numarul de filme inchiriate de ' || INITCAP(v_nume) || ' este ' || v_nrfilme);
    IF v_nrfilme >= 0.75*v_nrfilmetot THEN
        DBMS_OUTPUT.PUT_LINE('Categoria 1');
    ELSIF v_nrfilme >= 0.5*v_nrfilmetot THEN
        DBMS_OUTPUT.PUT_LINE('Categoria 2');
    ELSIF v_nrfilme >= 0.25*v_nrfilmetot THEN
        DBMS_OUTPUT.PUT_LINE('Categoria 3');
    ELSE
        DBMS_OUTPUT.PUT_LINE('Categoria 4');
    END IF;

END;
/

--5
CREATE TABLE member_stl AS 
    SELECT * FROM member;
commit;
ALTER TABLE member_stl ADD Discount NUMBER(4);
DECLARE
v_nume member.last_name%TYPE := '&p_nume';
v_nrfilme NUMBER(6);
v_nrfilmetot NUMBER(6);
BEGIN
    SELECT COUNT(*) into v_nrfilmetot
    FROM title;
    SELECT COUNT(title_id) into v_nrfilme
    FROM member m JOIN reservation r on m.member_id = r.member_id
    WHERE UPPER(m.last_name) = UPPER(v_nume);
    DBMS_OUTPUT.PUT_LINE('Numarul de filme inchiriate de ' || INITCAP(v_nume) || ' este ' || v_nrfilme);
    IF v_nrfilme >= 0.75*v_nrfilmetot THEN
        UPDATE member_stl
        SET discount = 0.1
        WHERE last_name = v_nume;
        DBMS_OUTPUT.PUT_LINE('Categoria 1. Actualizare produsa cu succes.');
    ELSIF v_nrfilme >= 0.5*v_nrfilmetot THEN
        UPDATE member_stl
        SET discount = 0.05
        WHERE last_name = v_nume;
        DBMS_OUTPUT.PUT_LINE('Categoria 2. Actualizare produsa cu succes.');
    ELSIF v_nrfilme >= 0.25*v_nrfilmetot THEN
        UPDATE member_stl
        SET discount = 0.03
        WHERE last_name = v_nume;
        DBMS_OUTPUT.PUT_LINE('Categoria 3. Actualizare produsa cu succes.');
    ELSE
        UPDATE member_stl
        SET discount = 0
        WHERE last_name = v_nume;
        DBMS_OUTPUT.PUT_LINE('Categoria 4. Actualizare produsa cu succes.');
    END IF;

END;
/


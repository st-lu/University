--1
CREATE TABLE info_stl (utilizator VARCHAR(20),
                        add_date DATE, comanda VARCHAR(20),
                        nr_linii NUMBER(6),
                        eroare VARCHAR(500));

--2
--f2
CREATE OR REPLACE FUNCTION f2_stl
    (v_nume employees.last_name%TYPE DEFAULT 'Bell')
RETURN NUMBER IS
    salariu employees.salary%type;
    nr NUMBER := 0;
    mesaj VARCHAR2(500);
    BEGIN
        SELECT salary INTO salariu
        FROM employees
        WHERE UPPER(last_name) = UPPER(v_nume);
        nr := SQL%ROWCOUNT;
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, 'Nicio eroare');
        
        RETURN salariu;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            nr := SQL%ROWCOUNT;
            INSERT INTO info_stl
            VALUES (USER, SYSDATE, 'SELECT', nr, 'Nu exista angajati cu numele dat');
            RETURN -1;
            --RAISE_APPLICATION_ERROR(-20000, 'Nu exista angajati cu numele dat');
        
        WHEN TOO_MANY_ROWS THEN
            nr := SQL%ROWCOUNT;
            mesaj := SQLCODE || ' ' || SQLERRM;
            DBMS_OUTPUT.PUT_LINE(MESAJ);
            INSERT INTO info_stl
            VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
            RETURN -2;
            --RAISE_APPLICATION_ERROR(-20001, 'Exista mai multi angajati cu numele dat');

        WHEN OTHERS THEN
            mesaj := SQLERRM;
            INSERT INTO info_stl
            VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
            --RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
            RETURN -3;
END f2_stl;
/
ALTER FUNCTION f2_stl COMPILE;
SELECT * FROM INFO_STL;
SELECT * FROM employees;
BEGIN
DBMS_OUTPUT.PUT_LINE('Salariul este '|| f2_stl('Kochhar'));
END;
/

--2
--p4
CREATE OR REPLACE PROCEDURE p4_stl
    (v_nume employees.last_name%TYPE)
IS
    salariu employees.salary%TYPE;
    nr NUMBER := 0;
    mesaj VARCHAR2(500);
BEGIN
    SELECT salary INTO salariu
    FROM employees
    WHERE last_name = v_nume;
    
    nr := SQL%ROWCOUNT;
    mesaj := SQLCODE || ' ' || SQLERRM;
    INSERT INTO info_stl
    VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
    
    COMMIT;
    DBMS_OUTPUT.PUT_LINE('Salariul este '|| salariu);
    
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        nr := SQL%ROWCOUNT;
        mesaj := SQLCODE || ' ' || SQLERRM;
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
        COMMIT;
        DBMS_OUTPUT.PUT_LINE(MESAJ);
    --RAISE_APPLICATION_ERROR(-20000,'Nu exista angajati cu numele dat');
    WHEN TOO_MANY_ROWS THEN
        nr := SQL%ROWCOUNT;
        mesaj := SQLCODE || ' ' || SQLERRM;
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
        COMMIT;
        DBMS_OUTPUT.PUT_LINE(MESAJ);
    --RAISE_APPLICATION_ERROR(-20001,'Exista mai multi angajati cu numele dat');
    WHEN OTHERS THEN
        nr := SQL%ROWCOUNT;
        mesaj := SQLCODE || ' ' || SQLERRM;
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
        COMMIT;
        DBMS_OUTPUT.PUT_LINE(MESAJ);
    --RAISE_APPLICATION_ERROR(-20002,'Alta eroare!');
END p4_stl;
/

--3
SELECT * FROM locations;
SELECT * FROM employees;
SELECT * FROM departments;
SELECT * FROM job_history;
desc job_history;
desc employees;
desc locations;
desc departments;
CREATE OR REPLACE FUNCTION f3_stl
    (v_oras locations.city%TYPE DEFAULT 'Seattle')
RETURN NUMBER IS
    CURSOR c IS SELECT e.employee_id id
                FROM employees e, job_history j
                WHERE e.employee_id = j.employee_id
                GROUP BY e.employee_id
                HAVING COUNT(j.job_id) >= 2;
    v_nrang NUMBER(8);
    aux NUMBER(8);
    suma NUMBER(8) := 0;
    exc  EXCEPTION;
    nr NUMBER := 0;
    mesaj VARCHAR2(500);
BEGIN
    FOR i in c LOOP
        SELECT COUNT(*) into aux
        FROM employees e, departments d, locations l
        WHERE e.department_id = d.department_id
                and d.location_id = l.location_id
                and e.employee_id = i.id
                and city = v_oras;
        suma := suma + aux;
    END LOOP;
    
    nr := SQL%ROWCOUNT;
    mesaj := SQLCODE || ' ' || SQLERRM;
    INSERT INTO info_stl
    VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
    COMMIT;

    IF suma != 0 THEN
        RETURN suma;
    ELSE
        RAISE exc;
    END IF;
    
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        nr := SQL%ROWCOUNT;
        mesaj := SQLCODE || ' ' || SQLERRM;
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
        COMMIT;
        DBMS_OUTPUT.PUT_LINE(MESAJ);
        
    --RAISE_APPLICATION_ERROR(-20000,'Nu exista orasul');
    WHEN exc THEN
        nr := SQL%ROWCOUNT;
        mesaj := 'Nu s-a gasit niciun angajat';
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
        COMMIT;
        DBMS_OUTPUT.PUT_LINE(MESAJ);
    --RAISE_APPLICATION_ERROR(-20000,'Nu s-a gasit niciun angajat');
    WHEN OTHERS THEN
        nr := SQL%ROWCOUNT;
        mesaj := SQLCODE || ' ' || SQLERRM;
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
        COMMIT;
        DBMS_OUTPUT.PUT_LINE(MESAJ);
        
    --RAISE_APPLICATION_ERROR(-20001,'Alta eroare!');
END f3_stl;
/

BEGIN
    DBMS_OUTPUT.PUT_LINE(f3_stl);
END;
/

--4
SELECT * FROM EMPLOYEES;
DESC EMPLOYEES;
CREATE OR REPLACE PROCEDURE p4t_stl
    (v_manid employees.manager_id%TYPE)
IS
    TYPE tid IS TABLE OF NUMBER;
    TYPE tsal IS TABLE OF NUMBER;
    te tid;
    ts tsal;
    nr NUMBER := 0;
    mesaj VARCHAR2(500);
BEGIN
    SELECT e.employee_id, e.salary*1.1 bulk collect into te, ts
    FROM employees e, employees m
    WHERE e.manager_id = m.employee_id and m.employee_id = v_manid;
    FOR i in te.first..te.last LOOP
        UPDATE emp_stl
        SET salary = ts(i)
        WHERE employee_id = te(i);
    END LOOP;
    
    nr := SQL%ROWCOUNT;
    mesaj := SQLCODE || ' ' || SQLERRM;
    INSERT INTO info_stl
    VALUES (USER, SYSDATE, 'UPDATE', nr, mesaj);
    COMMIT;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        nr := SQL%ROWCOUNT;
        mesaj := SQLCODE || ' ' || SQLERRM;
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
        COMMIT;
        DBMS_OUTPUT.PUT_LINE(MESAJ);
    ---RAISE_APPLICATION_ERROR(-20000,'Nu exista manager cu codul dat');
    WHEN OTHERS THEN
        nr := SQL%ROWCOUNT;
        mesaj := SQLCODE || ' ' || SQLERRM;
        INSERT INTO info_stl
        VALUES (USER, SYSDATE, 'SELECT', nr, mesaj);
        COMMIT;
        DBMS_OUTPUT.PUT_LINE(MESAJ);
    --RAISE_APPLICATION_ERROR(-20001,'Alta eroare!');
END p4t_stl;
/



--5
CREATE OR REPLACE FUNCTION f5_stl
RETURN NUMBER IS
    CURSOR c IS SELECT department_name nume, department_id id
                FROM departments;
    v_day VARCHAR(20);
    TYPE ln IS TABLE OF VARCHAR(50);
    TYPE ls IS TABLE OF NUMBER;
    TYPE lv IS TABLE OF NUMBER;
    TYPE d IS TABLE OF VARCHAR(20);
    zile d := d();
    listanum ln := ln();
    listasal ls := ls();
    listavec lv := lv();
    cnt NUMBER(6);
    maxim NUMBER(6);
BEGIN
    FOR i IN c LOOP
        DBMS_OUTPUT.PUT_LINE('Numele departamentului: ' || i.nume);
        SELECT COUNT(last_name) into cnt
        FROM employees e, departments d
        WHERE e.department_id = d.department_id and d.department_id = i.id;
        
        IF cnt = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista angajati in departamentul ' || i.nume);
        ELSE
            zile.extend(); zile(zile.first) := 'Mon';
            zile.extend(); zile(zile.last) := 'Tue';
            zile.extend(); zile(zile.last) := 'Wed';
            zile.extend(); zile(zile.last) := 'Thu';
            zile.extend(); zile(zile.last) := 'Fri';
            zile.extend(); zile(zile.last) := 'Sat';
            zile.extend(); zile(zile.last) := 'Sun';
            maxim := 0;
            FOR j in zile.first..zile.last LOOP
                SELECT COUNT(*) INTO cnt
                FROM emp_stl
                WHERE TO_CHAR(hire_date,'DY') LIKE zile(j) AND department_id = i.id;
                IF cnt = 0 THEN
                    DBMS_OUTPUT.PUT_LINE('Nu s-au facut angajari in ziua ' || zile(j));
                ELSE
                    IF cnt > maxim THEN
                        v_day := zile(j);
                        maxim := cnt;
                    END IF;
                END IF;
            END LOOP;
            DBMS_OUTPUT.PUT_LINE('Ziua in care au fost anagajate cele mai multe persoane: ' || v_day);
            
            SELECT last_name nume, salary salariu, ((SYSDATE - hire_date)/365) vechime
            bulk collect into listanum, listasal, listavec
            FROM employees
            WHERE TO_CHAR(hire_date,'DY') LIKE v_day AND department_id = i.id;
            
            DBMS_OUTPUT.PUT_LINE('Acestea sunt: '); 
            FOR j in listanum.first..listanum.last LOOP
                DBMS_OUTPUT.PUT_LINE(listanum(j) || ' care castiga ' || listasal(j)
                                    || ' si este in firma de ' || listavec(j) || ' ani.');            
            END LOOP;
        END IF;
    END LOOP;
END f5_stl;
/
BEGIN
    DBMS_OUTPUT.PUT_LINE(f5_stl);
END;
/

--6
CREATE OR REPLACE PROCEDURE p6_stl
AS
    CURSOR c IS SELECT department_name nume, department_id id
                FROM departments;
    v_day VARCHAR(20);
    TYPE ln IS TABLE OF VARCHAR(50);
    TYPE ls IS TABLE OF NUMBER;
    TYPE lv IS TABLE OF NUMBER;
    TYPE d IS TABLE OF VARCHAR(20);
    zile d := d();
    listanum ln := ln();
    listasal ls := ls();
    listavec lv := lv();
    cnt NUMBER(6);
    crtvec NUMBER(6);
    maxim NUMBER(6);
BEGIN
    FOR i IN c LOOP
        DBMS_OUTPUT.PUT_LINE('Numele departamentului: ' || i.nume);
        SELECT COUNT(last_name) into cnt
        FROM employees e, departments d
        WHERE e.department_id = d.department_id and d.department_id = i.id;
        
        IF cnt = 0 THEN
            DBMS_OUTPUT.PUT_LINE('Nu exista angajati in departamentul ' || i.nume);
        ELSE
            zile.extend(); zile(zile.first) := 'Mon';
            zile.extend(); zile(zile.last) := 'Tue';
            zile.extend(); zile(zile.last) := 'Wed';
            zile.extend(); zile(zile.last) := 'Thu';
            zile.extend(); zile(zile.last) := 'Fri';
            zile.extend(); zile(zile.last) := 'Sat';
            zile.extend(); zile(zile.last) := 'Sun';
            maxim := 0;
            FOR j in zile.first..zile.last LOOP
                SELECT COUNT(*) INTO cnt
                FROM emp_stl
                WHERE TO_CHAR(hire_date,'DY') LIKE zile(j) AND department_id = i.id;
                IF cnt = 0 THEN
                    DBMS_OUTPUT.PUT_LINE('Nu s-au facut angajari in ziua ' || zile(j));
                ELSE
                    IF cnt > maxim THEN
                        v_day := zile(j);
                        maxim := cnt;
                    END IF;
                END IF;
            END LOOP;
            DBMS_OUTPUT.PUT_LINE('Ziua in care au fost anagajate cele mai multe persoane: ' || v_day);
            
            SELECT last_name nume, salary salariu, ((SYSDATE - hire_date)/365) vechime
            bulk collect into listanum, listasal, listavec
            FROM employees
            WHERE TO_CHAR(hire_date,'DY') LIKE v_day AND department_id = i.id
            ORDER BY (SYSDATE - hire_date) DESC;
                                                                  
            DBMS_OUTPUT.PUT_LINE('Acestea sunt: ');
            cnt := 1;
            crtvec := listavec(listavec.first);
            FOR j in listanum.first..listanum.last LOOP
                IF crtvec != listavec(j) THEN
                    cnt := cnt + 1;
                    crtvec := listavec(j);
                END IF;
                DBMS_OUTPUT.PUT_LINE(cnt || '. ' || listanum(j) || ' care castiga ' || listasal(j)
                                            || ' si este in firma de ' || listavec(j) || ' ani.');
            END LOOP;
        END IF;
    END LOOP;
END p6_stl;
/

SELECT * FROM EMPLOYEES;
SELECT * FROM DEPARTMENTS;
BEGIN
    p6_stl;
END;
/
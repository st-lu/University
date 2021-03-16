--lab3plsql

--1
--a)
DECLARE
v_nume employees.last_name%TYPE;
v_job jobs.job_title%TYPE; 
job_crt jobs.job_title%TYPE;
CURSOR c IS SELECT job_title, last_name
            FROM employees e, jobs j
            WHERE e.job_id = j.job_id
            ORDER BY job_title;
BEGIN
        OPEN c;
        FETCH c INTO v_job, v_nume;
        DBMS_OUTPUT.PUT_LINE('Pe jobul ' || v_job || ' lucreaza angajatii:');
        DBMS_OUTPUT.PUT_LINE(v_nume);
        job_crt := v_job;
        WHILE c%FOUND and v_job = job_crt LOOP
            FETCH c INTO v_job, v_nume;
            IF v_job = job_crt THEN
                DBMS_OUTPUT.PUT_LINE(v_nume);
            ELSE
                DBMS_OUTPUT.PUT_LINE(' ');
                DBMS_OUTPUT.PUT_LINE('Pe jobul ' || v_job || ' lucreaza angajatii:');
                DBMS_OUTPUT.PUT_LINE(v_nume);
                job_crt := v_job;
            END IF;
        END LOOP;
        CLOSE c;
END;
/

--b)
DECLARE
job_crt jobs.job_title%TYPE := '';
CURSOR c IS SELECT job_title job, last_name nume
            FROM employees e, jobs j
            WHERE e.job_id = j.job_id
            ORDER BY job_title;
BEGIN
        FOR i IN c LOOP
            IF i.job = job_crt THEN
                DBMS_OUTPUT.PUT_LINE(i.nume);
            ELSE
                DBMS_OUTPUT.PUT_LINE(' ');
                DBMS_OUTPUT.PUT_LINE('Pe jobul ' || i.job || ' lucreaza angajatii:');
                DBMS_OUTPUT.PUT_LINE(i.nume);
                job_crt := i.job;
            END IF;
        END LOOP;
END;
/

--c)
DECLARE
job_crt jobs.job_title%TYPE := '';
BEGIN
        FOR i IN (SELECT job_title job, last_name nume
                FROM employees e, jobs j
                WHERE e.job_id = j.job_id
                ORDER BY job_title) LOOP
            IF i.job = job_crt THEN
                DBMS_OUTPUT.PUT_LINE(i.nume);
            ELSE
                DBMS_OUTPUT.PUT_LINE(' ');
                DBMS_OUTPUT.PUT_LINE('Pe jobul ' || i.job || ' lucreaza angajatii:');
                DBMS_OUTPUT.PUT_LINE(i.nume);
                job_crt := i.job;
            END IF;
        END LOOP;
END;
/

--d)
DECLARE
TYPE refcursor IS REF CURSOR;
CURSOR c IS SELECT job_title job, CURSOR (SELECT last_name name
                                            FROM employees e
                                            WHERE e.job_id = j.job_id
                                            ORDER BY job_title)
                FROM jobs j;
job_crt jobs.job_title%TYPE := '';
v_cursor refcursor;
v_nume employees.last_name%TYPE;
v_job jobs.job_title%TYPE; 
BEGIN
        OPEN c;
        LOOP
            FETCH c INTO v_job, v_cursor;
            EXIT WHEN c%NOTFOUND;
            DBMS_OUTPUT.PUT_LINE(' ');
            DBMS_OUTPUT.PUT_LINE('Pe jobul ' || v_job || ' lucreaza angajatii:');
            DBMS_OUTPUT.PUT_LINE(' ');
            LOOP
                FETCH v_cursor INTO v_nume;
                EXIT WHEN v_cursor%NOTFOUND;
                DBMS_OUTPUT.PUT_LINE (v_nume);
            END LOOP;
        END LOOP;
END;
/


--2
DECLARE
job_crt jobs.job_title%TYPE := '';
cnt NUMBER(6); -- nr de ordine
CURSOR c IS SELECT job_title job, last_name nume
            FROM employees e, jobs j
            WHERE e.job_id = j.job_id
            ORDER BY job_title;
v_nrang NUMBER(6);
v_sumsal NUMBER(10);

BEGIN
        SELECT COUNT(last_name), SUM(salary) INTO v_nrang, v_sumsal
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id;
        DBMS_OUTPUT.PUT_LINE('Firma are ' || v_nrang || ' angajati. Venitul total al angajatilor: ' || v_sumsal || '. Venitul mediu al angajatilor: ' || v_sumsal/v_nrang);
        FOR i IN c LOOP
            IF i.job = job_crt THEN
                cnt := cnt + 1;
                DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume);
                
            ELSE
                SELECT COUNT(last_name), SUM(salary) INTO v_nrang, v_sumsal
                FROM employees e, jobs j
                WHERE e.job_id = j.job_id and job_title = i.job
                GROUP BY job_title;
                cnt := 1;
                DBMS_OUTPUT.PUT_LINE(' ');
                DBMS_OUTPUT.PUT_LINE('Pe jobul ' || i.job || ' sunt ' || v_nrang || ' angajati. Venit total: ' || v_sumsal || '. Venit mediu: ' || ROUND((v_sumsal/v_nrang),2));
                DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume);
                job_crt := i.job;
            END IF;
        END LOOP;
END;
/

--3
DECLARE
job_crt jobs.job_title%TYPE := '';
cnt NUMBER(6); -- nr de ordine
CURSOR c IS SELECT job_title job, last_name nume, salary
            FROM employees e, jobs j
            WHERE e.job_id = j.job_id
            ORDER BY job_title;
v_nrang NUMBER(6);
v_sumsal NUMBER(10);
v_sumsalcom NUMBER(10);

BEGIN
        SELECT COUNT(last_name), SUM(salary) INTO v_nrang, v_sumsalcom
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id;
        DBMS_OUTPUT.PUT_LINE('Firma are ' || v_nrang || ' angajati. Venitul total al angajatilor: ' || v_sumsalcom || '. Venitul mediu al angajatilor: ' || ROUND(v_sumsalcom/v_nrang,2));
        FOR i IN c LOOP
            IF i.job = job_crt THEN
                cnt := cnt + 1;
                DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume || ' castiga ' || ROUND((i.salary*100)/v_sumsalcom,5) || '%');
                
            ELSE
                SELECT COUNT(last_name), SUM(salary + NVL(commission_pct, 0)*salary) INTO v_nrang, v_sumsal
                FROM employees e, jobs j
                WHERE e.job_id = j.job_id and job_title = i.job
                GROUP BY job_title;
                cnt := 1;
                DBMS_OUTPUT.PUT_LINE(' ');
                DBMS_OUTPUT.PUT_LINE('Pe jobul ' || i.job || ' sunt ' || v_nrang || ' angajati. Venit total: ' || v_sumsal || '. Venit mediu: ' || ROUND((v_sumsal/v_nrang),2));
                DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume || ' castiga ' || ROUND((i.salary*100)/v_sumsalcom,5) || '%');
                job_crt := i.job;
            END IF;
        END LOOP;
END;
/

--4
DESC employees;
SELECT * FROM employees;
DECLARE
job_crt jobs.job_title%TYPE := '';
cnt NUMBER(6); -- nr de ordine
CURSOR c IS SELECT job_title job, last_name nume, salary
            FROM employees e, jobs j
            WHERE e.job_id = j.job_id
            ORDER BY e.job_id, salary;
v_nrang NUMBER(6);
v_sumsal NUMBER(10);
v_sumsalcom NUMBER(10);

BEGIN
        SELECT COUNT(last_name), SUM(salary) INTO v_nrang, v_sumsalcom
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id;
        DBMS_OUTPUT.PUT_LINE('Firma are ' || v_nrang || ' angajati. Venitul total al angajatilor: ' || v_sumsalcom || '. Venitul mediu al angajatilor: ' || ROUND(v_sumsalcom/v_nrang,2));
        FOR i IN c LOOP
            IF i.job = job_crt THEN
                IF cnt < 5 THEN
                    cnt := cnt + 1;
                    DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume || ' castiga ' || ROUND((i.salary*100)/v_sumsalcom,5) || '%');
                ELSE
                    cnt := cnt + 1;
                END IF;
            ELSE
                SELECT COUNT(last_name), SUM(salary + NVL(commission_pct, 0)*salary) INTO v_nrang, v_sumsal
                FROM employees e, jobs j
                WHERE e.job_id = j.job_id and job_title = i.job
                GROUP BY job_title;
                cnt := 1;
                DBMS_OUTPUT.PUT_LINE(' ');
                DBMS_OUTPUT.PUT_LINE('Pe jobul ' || i.job || ' sunt ' || v_nrang || ' angajati. Venit total: ' || v_sumsal || '. Venit mediu: ' || ROUND((v_sumsal/v_nrang),2));
                IF v_nrang < 5 THEN
                    DBMS_OUTPUT.PUT_LINE('Jobul are mai putin de 5 angajati.');
                ELSE
                    DBMS_OUTPUT.PUT_LINE('Top 5 cei mai bine platiti angajati: ');
                END IF;
                DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume || ' castiga ' || ROUND((i.salary*100)/v_sumsalcom,5) || '%');
                job_crt := i.job;
            END IF;
        END LOOP;
END;
/

--5
DESC employees;
SELECT * FROM employees;
DECLARE
job_crt jobs.job_title%TYPE := '';
cnt NUMBER(6); -- nr de ordine
CURSOR c IS SELECT job_title job, last_name nume, salary
            FROM employees e, jobs j
            WHERE e.job_id = j.job_id
            ORDER BY e.job_id ASC, salary DESC;
v_nrang NUMBER(6);
v_sumsal NUMBER(10);
v_sumsalcom NUMBER(10);
lst employees.salary%TYPE;

BEGIN
        SELECT COUNT(last_name), SUM(salary) INTO v_nrang, v_sumsalcom
        FROM employees e, jobs j
        WHERE e.job_id = j.job_id;
        DBMS_OUTPUT.PUT_LINE('Firma are ' || v_nrang || ' angajati. Venitul total al angajatilor: ' || v_sumsalcom || '. Venitul mediu al angajatilor: ' || ROUND(v_sumsalcom/v_nrang,2));
        FOR i IN c LOOP
            IF i.job = job_crt THEN
                IF cnt < 5 THEN
                    IF lst = i.salary THEN
                        DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume || ' castiga ' || ROUND((i.salary*100)/v_sumsalcom,5) || '%');
                    ELSE
                        lst := i.salary;
                        cnt := cnt + 1;
                        DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume || ' castiga ' || ROUND((i.salary*100)/v_sumsalcom,5) || '%');
                    END IF;
                END IF;
            ELSE
                SELECT COUNT(last_name), SUM(salary + NVL(commission_pct, 0)*salary) INTO v_nrang, v_sumsal
                FROM employees e, jobs j
                WHERE e.job_id = j.job_id and job_title = i.job
                GROUP BY job_title;
                cnt := 1;
                lst := i.salary;
                DBMS_OUTPUT.PUT_LINE(' ');
                DBMS_OUTPUT.PUT_LINE('Pe jobul ' || i.job || ' sunt ' || v_nrang || ' angajati. Venit total: ' || v_sumsal || '. Venit mediu: ' || ROUND((v_sumsal/v_nrang),2));
                IF v_nrang < 5 THEN
                    DBMS_OUTPUT.PUT_LINE('Jobul are mai putin de 5 angajati.');
                ELSE
                    DBMS_OUTPUT.PUT_LINE('Top 5 cei mai bine platiti angajati: ');
                END IF;
                DBMS_OUTPUT.PUT_LINE(cnt || '. ' || i.nume || ' castiga ' || ROUND((i.salary*100)/v_sumsalcom,5) || '%');
                job_crt := i.job;
            END IF;
        END LOOP;
END;
/
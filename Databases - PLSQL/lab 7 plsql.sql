--1
CREATE TABLE error_stl (cod NUMBER(20), mesaj VARCHAR(2000));
DECLARE
    v_nr NUMBER(20) := &p_nr;
    err_neg EXCEPTION;
    v_cod NUMBER(20);
    v_mesaj VARCHAR(500);
BEGIN
    IF v_nr < 0 THEN
        RAISE err_neg;
    END IF;
    DBMS_OUTPUT.PUT_LINE(SQRT(v_nr));
EXCEPTION
    WHEN err_neg THEN
        v_cod := -20001;
        v_mesaj := 'Numarul introdus este negativ';
        DBMS_OUTPUT.PUT_LINE(v_mesaj);
        INSERT INTO error_stl
        VALUES (v_cod, v_mesaj);
END;
/

--2
DECLARE
    v_salary NUMBER(20) := &p_salary;
    v_first_name employees.first_name%TYPE;
    v_last_name employees.last_name%TYPE;
    err_neg EXCEPTION;
BEGIN
    SELECT first_name, last_name INTO v_first_name, v_last_name
    FROM employees
    WHERE salary = v_salary;
    DBMS_OUTPUT.PUT_LINE(v_first_name || ' ' || v_last_name);
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista niciun angajat cu acest salariu');
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Exista mai multi angajat cu acest salariu');
END;
/

--3
ALTER TABLE dept_stl
ADD CONSTRAINT c_pr_stl PRIMARY KEY(department_id);
ALTER TABLE emp_stl
ADD CONSTRAINT c_ex_stl FOREIGN KEY (department_id)
REFERENCES dept_stl;

SELECT * FROM dept_stl;
UPDATE dept_stl
SET department_id = 15
WHERE department_id = 90;

DECLARE
    v_old_department_id employees.department_id%TYPE := &p_old_department_id;
    v_new_department_id employees.department_id%TYPE := &p_new_department_id;
    exceptie EXCEPTION;
    PRAGMA EXCEPTION_INIT(exceptie,-02292);
BEGIN
    UPDATE dept_stl
    SET department_id = v_new_department_id
    WHERE department_id = v_old_department_id;
EXCEPTION
    WHEN exceptie THEN
    DBMS_OUTPUT.PUT_LINE ('Nu puteti modifica codul unui departament in care lucreaza salariati');
END;
/

--4
DECLARE
    v_err EXCEPTION;
    v_nr NUMBER(20);
    v_min NUMBER(20) := &p_min;
    v_max NUMBER(20) := &p_max;
    v_department_name departments.department_name%TYPE;
    v_nr_emp NUMBER(20);
BEGIN
    SELECT COUNT(employee_id) INTO v_nr_emp
    FROM employees
    WHERE department_id = 10
    GROUP BY department_id;
    
    IF v_nr_emp <= v_max AND v_nr_emp >= v_min THEN
        SELECT department_name INTO v_department_name
        FROM departments
        WHERE department_id = 10;
        DBMS_OUTPUT.PUT_LINE(v_department_name);
    ELSE
        RAISE v_err;
    END IF;
EXCEPTION
    WHEN v_err THEN
        DBMS_OUTPUT.PUT_LINE('Numarul angajatilor din departamentul 10 nu se afla in intervalul dat');
END;
/

--5
DECLARE
    v_department_id departments.department_id%TYPE := &p_department_id;
    v_new_department_name departments.department_name%TYPE := &p_new_department_name;
    v_err EXCEPTION;
    checker NUMBER(5);
BEGIN
    SELECT COUNT(COUNT(department_id)) INTO checker
    FROM departments
    WHERE department_id = v_department_id
    GROUP BY department_id;
    
    IF checker = 0 THEN
        RAISE_APPLICATION_ERROR(-20001, 'Departamentul nu a fost gasit');
    END IF;

    UPDATE dept_stl
    SET department_name = v_new_department_name
    WHERE department_id = v_department_id;
    
END;
/

--6
SELECT * FROM DEPARTMENTS;
DECLARE
    v_location_id departments.location_id%TYPE := &p_location_id;
    v_department_id departments.department_id%TYPE := &p_department_id;
    v_department_name departments.department_name%TYPE;
    v_department_name2 departments.department_name%TYPE;
    v_localizare NUMBER(5);
BEGIN
    v_localizare := 1;
    SELECT department_name into v_department_name
    FROM departments
    WHERE location_id = v_location_id;
    
    v_localizare := 2;
    SELECT department_name into v_department_name2
    FROM departments
    WHERE department_id = v_department_id;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        dbms_output.put_line('Eroarea se produce la select-ul cu numarul ' || v_localizare);
END;
/

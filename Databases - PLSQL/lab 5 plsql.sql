CREATE OR REPLACE PACKAGE pachetang_stl AS
--1.a
PROCEDURE add_ang(v_first_name emp_stl.first_name%TYPE,
                    v_last_name emp_stl.last_name%TYPE,
                    v_email emp_stl.email%TYPE,
                    v_phone_number emp_stl.phone_number%TYPE:=NULL,
                    v_job_name jobs.job_title%TYPE,
                    v_department_name departments.department_name%TYPE,
                    v_manfn emp_stl.last_name%TYPE,
                    v_manln emp_stl.last_name%TYPE);              
FUNCTION f_idjob(v_job_name jobs.job_title%TYPE)
RETURN VARCHAR;
FUNCTION f_iddep(v_department_name departments.department_name%TYPE)
RETURN NUMBER;
FUNCTION f_minsal(v_job_id jobs.job_id%TYPE,
                    v_department_id departments.department_id%TYPE)
RETURN NUMBER;
FUNCTION f_idman(v_manfn emp_stl.last_name%TYPE,
                    v_manln emp_stl.last_name%TYPE)
RETURN NUMBER;

--1.b
PROCEDURE move_ang(v_first_name emp_stl.first_name%TYPE,
                    v_last_name emp_stl.last_name%TYPE,
                    v_department_name departments.department_name%TYPE,
                    v_job_name jobs.job_title%TYPE,
                    v_manfn emp_stl.last_name%TYPE,
                    v_manln emp_stl.last_name%TYPE);
--1.c
FUNCTION f_subalterni(v_first_name emp_stl.first_name%TYPE,
                    v_last_name emp_stl.last_name%TYPE)
RETURN NUMBER;


--1.d
PROCEDURE p_raise(v_first_name emp_stl.first_name%TYPE,
                    v_last_name emp_stl.last_name%TYPE);
                    
--1.e
PROCEDURE p_sal(v_salary emp_stl.salary%TYPE,
                    v_first_name emp_stl.first_name%TYPE,
                    v_last_name emp_stl.last_name%TYPE);
--1.f
CURSOR c_emp(id NUMBER) RETURN employees%ROWTYPE;

--1.g
CURSOR c_jobs RETURN jobs%ROWTYPE;

--1.h
PROCEDURE p_jobs;
END pachetang_stl;
/

CREATE SEQUENCE seq_pachetang_stl
    START WITH 207
    INCREMENT BY 1;

CREATE OR REPLACE PACKAGE BODY pachetang_stl AS
--1.f
    CURSOR c_emp(id NUMBER) RETURN employees%ROWTYPE
            IS SELECT *
                FROM employees
                WHERE job_id = id;
--1.g
    CURSOR c_jobs RETURN jobs%ROWTYPE
        IS SELECT * FROM jobs;

--1.h
    PROCEDURE p_jobs AS
    BEGIN
        FOR job in pachetang_stl.c_jobs LOOP
            DBMS_OUTPUT.PUT_LINE('Pe job-ul' || job.job_title || 'lucreaza angajatii:');
            FOR emp in pachetang_stl.c_emp(job.job_id) LOOP
                DBMS_OUTPUT.PUT_LINE(emp.first_name || ' ' || emp.last_name);
            END LOOP;
        END LOOP;
    END p_jobs;
        
--1.a functii
    FUNCTION f_idjob(v_job_name jobs.job_title%TYPE)
    RETURN VARCHAR IS
        v_job_id emp_stl.job_id%TYPE;
    BEGIN
        SELECT job_id INTO v_job_id
        FROM jobs
        WHERE job_title = v_job_name;
        
        RETURN v_job_id;
    END f_idjob;
    
    FUNCTION f_iddep(v_department_name departments.department_name%TYPE)
    RETURN NUMBER IS
        v_department_id emp_stl.department_id%TYPE;
    BEGIN
        SELECT department_id INTO v_department_id
        FROM departments
        WHERE department_name = v_department_name;
        
        RETURN v_department_id;
    END f_iddep;
    
    FUNCTION f_minsal(v_job_id jobs.job_id%TYPE,
                    v_department_id departments.department_id%TYPE)
    RETURN NUMBER IS
    v_minsal employees.salary%TYPE;
    BEGIN
        SELECT MIN(salary) INTO v_minsal
        FROM employees
        WHERE v_department_id = department_id AND v_job_id = job_id
        GROUP BY job_id;
        
        RETURN v_minsal;
    END f_minsal;
    
    FUNCTION f_idman(v_manfn emp_stl.last_name%TYPE,
                    v_manln emp_stl.last_name%TYPE)
    RETURN NUMBER IS
    v_manager_id employees.employee_id%TYPE;
    BEGIN
        SELECT employee_id INTO v_manager_id
        FROM employees
        WHERE last_name = v_manln and first_name = v_manfn;
        
        RETURN v_manager_id;
    END f_idman;
    
--1.a proc
    PROCEDURE add_ang (v_first_name emp_stl.first_name%TYPE,
                    v_last_name emp_stl.last_name%TYPE,
                    v_email emp_stl.email%TYPE,
                    v_phone_number emp_stl.phone_number%TYPE:=NULL,
                    v_job_name jobs.job_title%TYPE,
                    v_department_name departments.department_name%TYPE,
                    v_manfn emp_stl.last_name%TYPE,
                    v_manln emp_stl.last_name%TYPE) IS
        v_hire_date emp_stl.hire_date%TYPE;
        v_job_id emp_stl.job_id%TYPE;
        v_department_id emp_stl.department_id%TYPE;
        v_salary emp_stl.salary%TYPE;
        v_manager_id emp_stl.manager_id%TYPE;
        v_commission_pct emp_stl.commission_pct%TYPE := 0;
    BEGIN
        --don't forget employee id
        v_hire_date :=SYSDATE;
        v_job_id := f_idjob(v_job_name);
        v_department_id := f_iddep(v_department_name);
        v_salary := f_minsal(v_job_id, v_department_id);
        v_manager_id := f_idman(v_manfn, v_manln);
        INSERT INTO emp_stl
        VALUES(seq_pachetang_stl.nextval, v_first_name, v_last_name, v_email, v_phone_number,
                v_hire_date, v_job_id, v_salary, v_commission_pct, v_manager_id, v_department_id);
    END add_ang;
    
--1.b
    PROCEDURE move_ang(v_first_name emp_stl.first_name%TYPE,
                    v_last_name emp_stl.last_name%TYPE,
                    v_department_name departments.department_name%TYPE,
                    v_job_name jobs.job_title%TYPE,
                    v_manfn emp_stl.last_name%TYPE,
                    v_manln emp_stl.last_name%TYPE) IS
    v_hire_date emp_stl.hire_date%TYPE := SYSDATE;
    v_job_id emp_stl.job_id%TYPE;
    v_department_id emp_stl.department_id%TYPE;
    v_salary emp_stl.salary%TYPE;
    v_manager_id emp_stl.manager_id%TYPE;
    v_commission_pct emp_stl.commission_pct%TYPE;
    v_old_salary emp_stl.salary%TYPE;
    BEGIN
        v_job_id := f_idjob(v_job_name);
        v_department_id := f_iddep(v_department_name);
        v_salary := f_minsal(v_job_id, v_department_id);
        SELECT salary INTO v_old_salary
        FROM employees
        WHERE last_name = v_last_name and first_name = v_first_name;
        
        IF v_salary < v_old_salary THEN
            v_salary := v_old_salary;
        END IF;
        v_manager_id := f_idman(v_manfn, v_manln);
        SELECT MIN(commission_pct) INTO v_commission_pct
        FROM employees
        WHERE v_department_id = department_id AND v_job_id = job_id
        GROUP BY job_id;
        
        UPDATE emp_stl
        SET hire_date = v_hire_date, department_id = v_department_id, job_id = v_job_id,
            manager_id = v_manager_id, salary = v_salary, commission_pct = v_commission_pct
        WHERE last_name = v_last_name AND first_name = v_first_name;
        
    END move_ang;
    
--1.c
    FUNCTION f_subalterni(v_first_name emp_stl.first_name%TYPE,
                    v_last_name emp_stl.last_name%TYPE)
    RETURN NUMBER IS
    v_nr_subalterni NUMBER(20);
    v_employee_id employees.employee_id%TYPE;
    BEGIN
        SELECT employee_id INTO v_employee_id
        FROM employees
        WHERE last_name = v_last_name and first_name = v_first_name;
        
        SELECT COUNT(employee_id) INTO v_nr_subalterni
        FROM employees e
        WHERE manager_id = v_employee_id
        GROUP BY manager_id;
        
        
        
        RETURN v_nr_subalterni;
    END f_subalterni;

--1.d
    PROCEDURE p_raise(v_first_name emp_stl.first_name%TYPE,
                        v_last_name emp_stl.last_name%TYPE)
    IS
        v_manager_id employees.manager_id%TYPE;
        v_job_id emp_stl.job_id%TYPE;
        v_salary emp_stl.salary%TYPE;
        v_new_manager_id employees.manager_id%TYPE;
        v_old_salary emp_stl.salary%TYPE;
        v_commission_pct emp_stl.commission_pct%TYPE;
        v_department_id emp_stl.department_id%TYPE;
    BEGIN
        SELECT manager_id, department_id INTO v_manager_id, v_department_id
        FROM employees
        WHERE last_name = v_last_name AND first_name = v_first_name;
        
        SELECT job_id, manager_id INTO v_job_id, v_new_manager_id
        FROM employees
        WHERE employee_id = v_manager_id;
        
        SELECT MIN(commission_pct) INTO v_commission_pct
        FROM employees
        WHERE v_department_id = department_id AND v_job_id = job_id
        GROUP BY job_id;
        
        SELECT salary INTO v_old_salary
        FROM employees
        WHERE last_name = v_last_name and first_name = v_first_name;
        
        IF v_salary < v_old_salary THEN
            v_salary := v_old_salary;
        END IF;
        
        UPDATE emp_stl
        SET hire_date = SYSDATE, job_id = v_job_id, manager_id = v_new_manager_id,
            salary = v_salary, commission_pct = v_commission_pct
        WHERE last_name = v_last_name AND first_name = v_first_name;
    END p_raise;

--1.e
    PROCEDURE p_sal(v_salary emp_stl.salary%TYPE,
                        v_first_name emp_stl.first_name%TYPE,
                        v_last_name emp_stl.last_name%TYPE)
    IS
        v_min_salary emp_stl.salary%TYPE;
        v_max_salary emp_stl.salary%TYPE;
    BEGIN
        SELECT min_salary, max_salary INTO v_min_salary, v_max_salary
        FROM employees e, jobs j
        WHERE e.last_name = v_last_name AND e.first_name = v_first_name AND e.job_id = j.job_id;
        
        IF v_salary <= v_max_salary AND v_salary >= v_min_salary THEN
            DBMS_OUTPUT.PUT_LINE('Salariul este valid');
        ELSE
            DBMS_OUTPUT.PUT_LINE('Salariul nu este valid');
        END IF;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Nu exista angajati cu numele dat');
        WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('Exista mai multi angajati '||
        'cu numele dat');
        WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('Alta eroare!');
    END p_sal;

    
END pachetang_stl;
/






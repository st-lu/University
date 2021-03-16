--1
CREATE TABLE DEPT_STL AS SELECT * FROM DEPARTMENTS;
SELECT * FROM DEPT_STL;

CREATE OR REPLACE TRIGGER trig1_stl
    BEFORE INSERT OR UPDATE OR DELETE ON dept_stl
BEGIN
    IF UPPER(USER) NOT LIKE 'SCOTT' THEN
        RAISE_APPLICATION_ERROR(-20001,'tabelul nu poate fi actualizat');
    END IF;
END;
/
DROP TRIGGER trig1_stl;

--2
CREATE OR REPLACE TRIGGER trig2_stl
    BEFORE UPDATE OF commission_pct ON emp_stl
    FOR EACH ROW
BEGIN
    IF(:NEW.commission_pct >= 0.5) THEN
        RAISE_APPLICATION_ERROR(-20001,'tabelul nu poate fi actualizat');
    END IF;
END;
/
DROP TRIGGER trig2_stl;

--3
--a
SELECT * FROM DEPARTMENTS;
CREATE TABLE INFO_DEPT_STL AS SELECT * FROM DEPARTMENTS;
INSERT INTO INFO_DEPT_STL SELECT * FROM DEPARTMENTS;
ALTER TABLE INFO_DEPT_STL
ADD numar NUMBER(20);

SELECT * FROM EMPLOYEES;
SELECT * FROM INFO_DEPT_STL;
CREATE OR REPLACE PROCEDURE p_nr_stl AS
    nr_ang NUMBER(20) :=0;
BEGIN
    FOR i IN (SELECT * FROM DEPARTMENTS) LOOP

        SELECT COUNT(employee_id) INTO nr_ang
        FROM employees e
        WHERE e.department_id = i.department_id
        GROUP BY e.department_id;
        
        UPDATE INFO_DEPT_STL e
        SET numar = nr_ang
        WHERE e.department_id = i.department_id;
    END LOOP;
    COMMIT;
END p_nr_stl;


--b
CREATE OR REPLACE TRIGGER trig3_stl
    AFTER DELETE OR UPDATE OR INSERT ON EMP_STL
    FOR EACH ROW
BEGIN
    p_nr_stl;
END;
/
DROP TRIGGER trig3_stl;

--4
CREATE OR REPLACE TRIGGER trig4_stl
    BEFORE UPDATE OR INSERT OR DELETE ON emp_stl
    FOR EACH ROW
DECLARE
    nr_ang NUMBER(20);
BEGIN
    FOR i IN (SELECT * FROM departments) LOOP
        SELECT COUNT(EMPLOYEE_ID) INTO nr_ang
            FROM emp_stl
            WHERE emp_stl.department_id = i.department_id
            GROUP BY DEPARTMENT_ID;
        IF(nr_ang > 45) THEN
            RAISE_APPLICATION_ERROR(-20001,'tabelul nu poate fi actualizat');
        END IF;
    END LOOP;
END;
/
DROP TRIGGER trig4_stl;

--5
CREATE OR REPLACE TRIGGER trig5_stl
    BEFORE DELETE OR UPDATE ON dept_stl
    FOR EACH ROW
DECLARE
    nr_ang NUMBER(20);
BEGIN
    IF DELETING THEN
        DELETE FROM emp_stl e
        WHERE :OLD.department_id = e.department_id;
    END IF;
    
    IF UPDATING THEN
        UPDATE emp_stl e
        SET e.department_id = :NEW.department_id
        WHERE e.department_id = :OLD.department_id;
    END IF;
END;
/
DROP TRIGGER trig5_stl;

--6
CREATE SEQUENCE seq_err_stl
    START WITH 1
    INCREMENT BY 1;
    
CREATE TABLE errors_stl (error_id NUMBER(20), user_id VARCHAR(50), nume_bd VARCHAR(50),
                            erori VARCHAR(2000), data DATE);
                            
CREATE OR REPLACE TRIGGER trig6_stl
    AFTER SERVERERROR ON DATABASE
BEGIN
    INSERT INTO errors_stl
    VALUES (seq_err_stl.NEXTVAL, SYS.LOGIN_USER, SYS.DATABASE_NAME,
            DBMS_UTILITY.FORMAT_ERROR_STACK, SYSDATE);
END;
/
DROP TRIGGER trig6_stl;
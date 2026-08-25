# Write your MySQL query statement below
select unique_id, name
from Employees
Left JOIN EmployeeUNI
ON EmployeeUNI.id = Employees.id
# Write your MySQL query statement below
select customer_number
from Orders
group by customer_number
order by COUNT(customer_number) DESC
limit 1;

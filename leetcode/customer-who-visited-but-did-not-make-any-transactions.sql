# Write your MySQL query statement below
select customer_id, COUNT(*) AS count_no_trans
from Visits
LEFT JOIN Transactions
ON Visits.visit_id = Transactions.visit_id
where Transactions.transaction_id is NULL
GROUP by customer_id;
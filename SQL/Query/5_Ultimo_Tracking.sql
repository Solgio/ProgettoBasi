SELECT t1.id_pacco, t1.status
FROM tracking t1
INNER JOIN (
    SELECT id_pacco, MAX(data_ora) as max_data_ora
    FROM tracking
    GROUP BY id_pacco
) t2 ON t1.id_pacco = t2.id_pacco AND t1.data_ora = t2.max_data_ora
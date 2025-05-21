SELECT p.corriere, AVG(h.differenza) AS media_corriere
FROM (
  SELECT t1.id_pacco, p1.corriere, MAX(t1.data_ora)-p1.dataora_ordine AS differenza
  FROM tracking AS t1
  JOIN pacco AS p1 ON p1.id =t1.id_pacco
  WHERE t1.status = 'Consegnato'
  GROUP BY t1.id_pacco, p1.dataora_ordine, p1.corriere
) AS h
JOIN pacco as p ON p.id = h.id_pacco
GROUP BY p.corriere
HAVING AVG(h.differenza) > (
  SELECT AVG(differenza)
  FROM (
    SELECT t1.id_pacco, MAX(t1.data_ora)-p2.dataora_ordine AS differenza
    FROM tracking AS t1
    JOIN pacco AS p2 ON p2.id = t1.id_pacco
    WHERE t1.status = 'Consegnato'
    GROUP BY t1.id_pacco, p2.dataora_ordine
  )AS m
) ORDER BY media_corriere DESC3

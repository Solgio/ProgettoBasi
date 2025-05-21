SELECT    corriere, AVG(p.costo) AS costo_medio
FROM    pacco AS p
JOIN    tracking AS t ON t.id_pacco = p.id
JOIN    filiale AS f ON t.città_check_point = f.città AND t.nome_check_point=f.nome
JOIN    corriere AS c ON p.corriere = c.cf
WHERE    f.tipo = 'Locker'    AND c.grado = 'Porter'  
GROUP BY   corriere;
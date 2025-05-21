SELECT cf, count(*) 
FROM corriere as c 
JOIN pacco as p ON p.costo>200 AND p.corriere=cf 
JOIN ( 
      SELECT b.id_bundle, COUNT(*) as n_assicurazione 
      FROM bundle AS b 
      JOIN pacco AS p ON b.id_contenuto = p.id 
      WHERE p.tipo_assicurazione = 'Garanzia per 3 anni'
      GROUP BY b.id_bundle 
) as b ON p.id=b.id_bundle 
GROUP BY cf;
SELECT b.id_bundle, COUNT(*) as n_garanzia_tre_anni
FROM bundle AS b
JOIN pacco AS p ON b.id_contenuto = p.id
WHERE p.tipo_assicurazione = 'Garanzia per 3 anni'
GROUP BY b.id_bundle
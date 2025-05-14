CREATE TABLE SEDE(
  corriere CHAR(16) NOT NULL, 
  sede_nome VARCHAR(20) NOT NULL, 
  sede_città VARCHAR(20) NOT NULL,
  PRIMARY KEY(corriere,sede_nome,sede_città),
  FOREIGN KEY (corriere) REFERENCES corriere(cf),
  FOREIGN KEY (sede_nome,sede_città) REFERENCES filiale(nome,città)
  )
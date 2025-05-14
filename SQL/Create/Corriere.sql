CREATE TABLE CORRIERE(
  cf VARCHAR(16) NOT NULL,
  agenzia VARCHAR (15) NOT NULL, 
  grado grado NOT NULL, 
  disponibilità BOOLEAN NOT NULL, 
  nome_sede VARCHAR(20) NOT NULL,
  città_sede VARCHAR(10) NOT NULL,
  PRIMARY KEY (CF),
  FOREIGN KEY(nome_sede,città_sede) REFERENCES filiale(nome,città)
  
)
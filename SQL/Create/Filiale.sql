CREATE TABLE FILIALE (
  nome VARCHAR(20) NOT NULL,
  città VARCHAR(20) NOT NULL,
  tipo tipo NOT NULL,
  indirizzo VARCHAR(15) NOT NULL,
  PRIMARY KEY (nome,città)
  
)
CREATE TABLE TRACKING (
  id_pacco CHAR(20) NOT NULL, 
  data_ora TIMESTAMP NOT NULL, 
  status status NOT NULL, 
  note VARCHAR(150) NULL, 
  nome_check_point VARCHAR(20) NOT NULL,
  città_check_point VARCHAR(20) NOT NULL,
  PRIMARY KEY(id_pacco,data_ora),
  FOREIGN KEY (id_pacco) REFERENCES pacco(id),
  FOREIGN KEY (nome_check_point,città_check_point) REFERENCES filiale(nome,città)
)
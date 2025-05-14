CREATE TABLE BUNDLE (
  id_bundle CHAR(20)  NOT NULL,
  id_contenuto CHAR(20) NOT NULL,
  quantità INT NOT NULL,
  PRIMARY KEY(id_bundle,id_contenuto),
  FOREIGN KEY (id_bundle) REFERENCES pacco(id),
  FOREIGN KEY (id_contenuto) REFERENCES pacco(id)
)
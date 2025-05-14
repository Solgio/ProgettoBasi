CREATE TABLE PACCO(
    id CHAR(20) PRIMARY KEY, 
    tipologia tipologia NOT NULL, 
    dimensioni INT NOT NULL, 
    costo INT NOT NULL, 
    dataOra_ordine TIMESTAMP NOT NULL,
    dataOra_prevista TIMESTAMP NOT NULL,
    cliente VARCHAR (30) NOT NULL, 
    corriere CHAR (16) NOT NULL, 
    tipo_assicurazione tipo_assicurazione NULL, 
    dedica CHAR (150) NULL, 
    tipo_carta tipo_carta NULL,
    FOREIGN KEY (Cliente) REFERENCES cliente (email),
    FOREIGN KEY (Corriere) REFERENCES corriere (cf)
)
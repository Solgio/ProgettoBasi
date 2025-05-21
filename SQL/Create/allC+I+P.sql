DROP TYPE  IF EXISTS tipo_assicurazione CASCADE;
CREATE TYPE tipo_assicurazione AS ENUM (
   'Reso in 30 giorni',
   'Garanzia per 1 anno',
   'Garanzia per 3 anni'
);

DROP TYPE  IF EXISTS tipo_carta CASCADE;
CREATE TYPE tipo_carta AS ENUM (
    'Carta Regalo',
    'Sacchetto in tela',
    'Scatola Speciale'
);

DROP TYPE  IF EXISTS GRADO CASCADE;
CREATE type Grado as ENUM (
'Porter',
'Skilled Handler',
'Elite Transporter',
'The Great Deliverer'
);

DROP TYPE  IF EXISTS STATUS CASCADE;
CREATE TYPE status AS ENUM(
  'Consegnato',
  'In Consegna',
  'Spedito',
  'Autorizzato',
  'Fase di Controllo'
);

DROP TYPE  IF EXISTS TIPO CASCADE;
CREATE TYPE tipo AS ENUM (
  'Locker',
  'Punto di Controllo',
  'Magazzino'
);

DROP TYPE  IF EXISTS TIPOLOGIA CASCADE;
CREATE TYPE tipologia AS ENUM (
    'Elettronica',
    'Sanitario',
    'Gastronomia',
    'Casa e cucina',
    'CD',
    'Libri',
    'Sport',
    'Cosmetici',
    'Abbigliamento',
    'Cancelleria',
    'Salute e cura della persona'
);

DROP TABLE  IF EXISTS FILIALE CASCADE;
CREATE TABLE FILIALE (
  nome VARCHAR(20) NOT NULL,
  città VARCHAR(20) NOT NULL,
  tipo tipo NOT NULL,
  indirizzo VARCHAR(15) NOT NULL,
  PRIMARY KEY (nome,città)
);

INSERT INTO "public"."filiale" ("nome", "città", "tipo", "indirizzo") VALUES 
('Capital Knot', 'Central Region', 'Magazzino', '122 Bridge Road'), 
('Craftsman Loc', 'Mountain Region', 'Punto di Controllo', '103 Artisan Dr '), 
('Distributor NW', 'Central Region', 'Punto di Controllo', '34 NW Access '),
 ('Doctor Loc', 'Mountain Region', 'Punto di Controllo', '89 Medical Dr '), 
 ('Elder', 'Central Region', 'Locker', '42 Veteran Ave '), 
 ('Engineer Loc', 'East Region', 'Punto di Controllo', '57 Tech Street '), 
 ('Film Direct', 'Central Region', 'Locker', '76 Cinema Way '), 
 ('Geologist Loc', 'Mountain Region', 'Locker', '125 Mineral St'), 
 ('Lake Knot', 'Central Region', 'Magazzino', '47 Lake Avenue '), 
 ('Mountain Knot', 'Mountain Region', 'Magazzino', '62 Peak Road '), 
 ('Port Knot', 'East Region', 'Magazzino', '155 Harbor Way '), 
 ('South Knot', 'Central Region', 'Punto di Controllo', '83 Southern St '), 
 ('Timefall', 'East Region', 'Locker', '29 Rain Drive '), 
 ('Weather Stat', 'East Region', 'Locker', '91 Forecast St '), 
 ('WindFarm', 'Central Region', 'Locker', '18 Turbine Path');

DROP TABLE  IF EXISTS CORRIERE CASCADE;
CREATE TABLE CORRIERE(
  cf VARCHAR(16) NOT NULL,
  agenzia VARCHAR (15) NOT NULL, 
  grado grado NOT NULL, 
  disponibilità BOOLEAN NOT NULL, 
  pacchi_attivi INT NOT NULL,
  PRIMARY KEY (cf)
);

INSERT INTO "public"."corriere" ("cf", "agenzia", "grado", "disponibilità", "pacchi_attivi") VALUES 
('BLFR46D25W783N', 'Bridges', 'Elite Transporter', 'true', '0'), 
('GCDX17P54T329M', 'Fragile', 'The Great Deliverer', 'true', '1'), 
('GRPT89V90K341S', 'Bridges', 'Porter', 'true', '0'), 
('JRTP28N69Q514S', 'Bridges', 'The Great Deliverer', 'true', '1'), 
('KLPT63H45S782F', 'Fragile', 'Skilled Handler', 'false', '0'), 
('MLKH65G09E341C', 'Fragile', 'Elite Transporter', 'true', '2'), 
('NHRD52Y18M673G', 'DieHardman', 'Elite Transporter', 'true', '2'), 
('QKVM92H37S561L', 'DieHardman', 'Skilled Handler', 'false', '2'), 
('SMPB74L28R962D', 'Bridges', 'The Great Deliverer', 'true', '4'), 
('TRGF91D36W125E', 'Bridges', 'Skilled Handler', 'true', '2'), 
('XZPY71C83F419V', 'Fragile', 'Porter', 'true', '2');

DROP TABLE  IF EXISTS SEDE CASCADE;
CREATE TABLE SEDE(
  corriere CHAR(16) NOT NULL, 
  sede_nome VARCHAR(20) NOT NULL, 
  sede_città VARCHAR(20) NOT NULL,
  attuale BOOLEAN NOT NULL,
  PRIMARY KEY(corriere,sede_nome,sede_città),
  FOREIGN KEY (corriere) REFERENCES corriere(cf),
  FOREIGN KEY (sede_nome,sede_città) REFERENCES filiale(nome,città)
);

INSERT INTO "public"."sede" ("corriere", "sede_nome", "sede_città", "attuale") VALUES 
('BLFR46D25W783N  ', 'Craftsman Loc', 'Mountain Region', 'true'), 
('BLFR46D25W783N  ', 'Doctor Loc', 'Mountain Region', 'false'), 
('GCDX17P54T329M  ', 'Film Direct', 'Central Region', 'true'), 
('GCDX17P54T329M  ', 'WindFarm', 'Central Region', 'false'), 
('JRTP28N69Q514S  ', 'Craftsman Loc', 'Mountain Region', 'false'), 
('JRTP28N69Q514S  ', 'Mountain Knot', 'Mountain Region', 'true'), 
('KLPT63H45S782F  ', 'Timefall', 'East Region', 'true'), 
('KLPT63H45S782F  ', 'Weather Stat', 'East Region', 'false'), 
('MLKH65G09E341C  ', 'Lake Knot', 'Central Region', 'true'), 
('MLKH65G09E341C  ', 'South Knot', 'Central Region', 'false'), 
('NHRD52Y18M673G  ', 'Mountain Knot', 'Mountain Region', 'false'), 
('NHRD52Y18M673G  ', 'Port Knot', 'East Region', 'true'),
 ('QKVM92H37S561L  ', 'Engineer Loc', 'East Region', 'false'), 
 ('QKVM92H37S561L  ', 'Weather Stat', 'East Region', 'true'), 
 ('SMPB74L28R962D  ', 'Capital Knot', 'Central Region', 'true'), 
 ('SMPB74L28R962D  ', 'Lake Knot', 'Central Region', 'false'), 
 ('TRGF91D36W125E  ', 'Port Knot', 'East Region', 'false'), 
 ('TRGF91D36W125E  ', 'South Knot', 'Central Region', 'true'), 
 ('XZPY71C83F419V  ', 'Distributor NW', 'Central Region', 'true'), 
 ('XZPY71C83F419V  ', 'Lake Knot', 'Central Region', 'false');

DROP TABLE  IF EXISTS CLIENTE CASCADE;
CREATE TABLE cliente(
  email VARCHAR(20) NOT NULL, 
  nome VARCHAR(20) NOT NULL, 
  cognome VARCHAR(20) NOT NULL, 
  indirizzo VARCHAR(20) NOT NULL, 
  telefono VARCHAR (15) NULL,
  PRIMARY KEY(email)
);

  INSERT INTO "public"."cliente" ("email", "nome", "cognome", "indirizzo", "telefono") VALUES 
('amelie@brid.com', 'Amelie', 'Strand', '22 President Ave', '555-2023 '), 
    ('cliff@bbla.com', 'Cliff', 'Unger', '103 Combat Way', '555-3023 '), 
    ('craftsman@usg.com', 'Craftsman', 'Equipment', '18 Workshop St', '555-3789 '), 
    ('deadman@bbla.com', 'Deadman', 'BB Lab', '83 Corpse Ave', '555-0789 '), 
    ('die@hard.com', 'Die', 'Hardman', '77 Bridges Blvd', '555-2789 '), 
    ('doctor@mount.com', 'Doctor', 'Mountain', '95 Health Ave', '555-4456 '), 
    ('elder@central.com', 'Elder', 'Porter', '32 Veteran St', null), 
    ('engineer@east.com', 'Engineer', 'Bridges', '64 Tech Road', '555-4023 '), 
    ('fragile2@brid.com', 'Fragile', 'Express', '27 Timefall Road', '555-0456 '), 
    ('heartman@lkc.com', 'Heartman', 'Beach', '39 Heart Valley', '555-2456 '), 
    ('higgs@dema.com', 'Higgs', 'Monaghan', '66 Beach Road', '555-1789 '), 
    ('lockne@mount.com', 'Lockne', 'Mountain', '51 Scientist Dr', '555-3456 '), 
    ('mama@brid.com', 'Mama', 'Bridges', '41 Lockdown St', '555-1023 '), 
    ('porter1@kds.com', 'Sam', 'Porter', '55 UCA Street', '555-0123 '), 
    ('sam@brid.com', 'Sam', 'B-Porter', '14 Bridge Link', '555-1456 ');

DROP TABLE  IF EXISTS PACCO CASCADE;
CREATE TABLE PACCO
(id CHAR(20) PRIMARY KEY, 
tipologia tipologia NOT NULL, 
dimensioni VARCHAR(11) NOT NULL, 
costo FLOAT NOT NULL, 
dataOra_ordine TIMESTAMP NOT NULL,
dataOra_prevista TIMESTAMP NOT NULL,
cliente VARCHAR (30) NOT NULL, 
corriere CHAR (16) NOT NULL, 
tipo_assicurazione tipo_assicurazione NULL, 
dedica CHAR (150) NULL, 
tipo_carta tipo_carta NULL,
FOREIGN KEY (Cliente) REFERENCES cliente (email),
FOREIGN KEY (Corriere) REFERENCES corriere (cf),
CHECK (
    (tipo_assicurazione IS NOT NULL AND (dedica IS NULL AND tipo_carta IS NULL))
    OR
    ((dedica IS NOT NULL OR tipo_carta IS NOT NULL) AND tipo_assicurazione IS NULL)
    OR (dedica IS NULL AND tipo_carta IS NULL AND tipo_assicurazione IS NULL)
)
);

INSERT INTO "public"."pacco" ("id", "tipologia", "dimensioni", "costo", "dataora_ordine", "dataora_prevista", "cliente", "corriere", "tipo_assicurazione", "dedica", "tipo_carta") VALUES 
('PC001               ', 'Elettronica', '30x20x15', '59.99', '2025-03-10 08:30:00', '2025-03-15 18:00:00', 'porter1@kds.com', 'SMPB74L28R962D  ', 'Garanzia per 1 anno', null, null), 
('PC002               ', 'Sanitario', '15x10x5', '29.99', '2025-03-10 09:45:00', '2025-03-17 14:00:00', 'fragile2@brid.com', 'MLKH65G09E341C  ', 'Garanzia per 3 anni', null, null), 
('PC003               ', 'Gastronomia', '25x25x10', '39.99', '2025-03-11 10:15:00', '2025-03-14 12:00:00', 'deadman@bbla.com', 'TRGF91D36W125E  ', 'Reso in 30 giorni', null, null), 
('PC004               ', 'Cancelleria', '40x30x20', '129.99', '2025-03-11 14:30:00', '2025-03-18 16:00:00', 'mama@brid.com', 'KLPT63H45S782F  ', null, null, 'Carta Regalo'), 
('PC005               ', 'Cancelleria', '50x40x30', '249.99', '2025-03-12 09:00:00', '2025-03-20 12:00:00', 'sam@brid.com', 'SMPB74L28R962D  ', null, null, null), 
('PC006               ', 'Abbigliamento', '20x15x10', '49.99', '2025-03-12 11:20:00', '2025-03-16 10:00:00', 'higgs@dema.com', 'NHRD52Y18M673G  ', null, null, 'Scatola Speciale'), 
('PC007               ', 'Elettronica', '35x25x15', '89.99', '2025-03-13 13:45:00', '2025-03-19 15:00:00', 'amelie@brid.com', 'MLKH65G09E341C  ', 'Garanzia per 1 anno', null, null), 
('PC008               ', 'Libri', '20x15x5', '19.99', '2025-03-13 15:30:00', '2025-03-15 11:00:00', 'porter1@kds.com', 'SMPB74L28R962D  ', null, null, null), 
('PC009               ', 'Sport', '30x20x15', '39.99', '2025-03-14 08:15:00', '2025-03-18 09:00:00', 'heartman@lkc.com', 'TRGF91D36W125E  ', null, null, 'Sacchetto in tela'), 
('PC010               ', 'Cancelleria', '45x30x25', '159.99', '2025-03-14 10:45:00', '2025-03-21 14:00:00', 'die@hard.com', 'KLPT63H45S782F  ', 'Garanzia per 3 anni', null, null), 
('PC011               ', 'Cancelleria', '60x50x40', '349.99', '2025-03-15 09:30:00', '2025-03-25 16:00:00', 'fragile2@brid.com', 'NHRD52Y18M673G  ', null, null, null), 
('PC012               ', 'Sanitario', '15x10x5', '29.99', '2025-03-15 11:00:00', '2025-03-18 12:00:00', 'cliff@bbla.com', 'SMPB74L28R962D  ', 'Reso in 30 giorni', null, null), 
('PC013               ', 'Elettronica', '25x20x15', '79.99', '2025-03-16 14:20:00', '2025-03-20 18:00:00', 'deadman@bbla.com', 'MLKH65G09E341C  ', null, null, 'Carta Regalo'), 
('PC014               ', 'Gastronomia', '20x20x10', '34.99', '2025-03-16 16:45:00', '2025-03-19 10:00:00', 'mama@brid.com', 'TRGF91D36W125E  ', null, null, null), 
('PC015               ', 'Cancelleria', '55x45x35', '299.99', '2025-03-17 08:30:00', '2025-03-27 14:00:00', 'sam@brid.com', 'KLPT63H45S782F  ', null, null, null), 
('PC016               ', 'Cosmetici', '25x20x20', '89.99', '2025-03-17 11:30:00', '2025-03-22 17:00:00', 'lockne@mount.com', 'JRTP28N69Q514S  ', 'Garanzia per 1 anno', null, null), 
('PC017               ', 'CD', '18x12x10', '119.99', '2025-03-17 14:10:00', '2025-03-21 13:00:00', 'higgs@dema.com', 'XZPY71C83F419V  ', 'Garanzia per 3 anni', null, null), 
('PC018               ', 'Cosmetici', '15x15x15', '239.99', '2025-03-18 09:45:00', '2025-03-23 11:00:00', 'engineer@east.com', 'QKVM92H37S561L  ', null, null, 'Carta Regalo'), 
('PC019               ', 'Sanitario', '10x10x5', '49.99', '2025-03-18 11:30:00', '2025-03-20 14:00:00', 'doctor@mount.com', 'BLFR46D25W783N  ', 'Reso in 30 giorni', null, null), 
('PC020               ', 'Cancelleria', '40x35x30', '199.99', '2025-03-18 15:20:00', '2025-03-24 12:00:00', 'porter1@kds.com', 'GCDX17P54T329M  ', null, null, null), 
('PC021               ', 'Salute e cura della persona', '35x25x20', '159.99', '2025-03-19 08:15:00', '2025-03-23 16:00:00', 'craftsman@usg.com', 'SMPB74L28R962D  ', null, null, 'Scatola Speciale'), 
('PC022               ', 'Elettronica', '30x25x15', '79.99', '2025-03-19 10:40:00', '2025-03-22 18:00:00', 'lockne@mount.com', 'MLKH65G09E341C  ', 'Garanzia per 1 anno', null, null), 
('PC023               ', 'Cancelleria', '45x40x35', '229.99', '2025-03-19 13:25:00', '2025-03-26 14:00:00', 'engineer@east.com', 'TRGF91D36W125E  ', null, null, null), 
('PC024               ', 'CD', '8x8x2', '29.99', '2025-03-20 09:50:00', '2025-03-23 10:00:00', 'mama@brid.com', 'KLPT63H45S782F  ', null, null, 'Sacchetto in tela'), 
('PC025               ', 'Casa e cucina', '30x25x20', '69.99', '2025-03-20 12:15:00', '2025-03-24 15:00:00', 'elder@central.com', 'NHRD52Y18M673G  ', 'Reso in 30 giorni', null, null), 
('PC026               ', 'Libri', '20x15x10', '49.99', '2025-03-20 14:40:00', '2025-03-23 12:00:00', 'deadman@bbla.com', 'JRTP28N69Q514S  ', 'Garanzia per 1 anno', null, null), 
('PC027               ', 'Abbigliamento', '25x20x15', '59.99', '2025-03-21 08:30:00', '2025-03-25 11:00:00', 'amelie@brid.com', 'XZPY71C83F419V  ', null, null, 'Carta Regalo'), 
('PC028               ', 'Cancelleria', '55x50x40', '299.99', '2025-03-21 11:15:00', '2025-03-29 14:00:00', 'higgs@dema.com', 'QKVM92H37S561L  ', null, null, null), 
('PC029               ', 'Gastronomia', '15x15x10', '39.99', '2025-03-21 13:30:00', '2025-03-24 16:00:00', 'craftsman@usg.com', 'BLFR46D25W783N  ', 'Garanzia per 3 anni', null, null), 
('PC030               ', 'Sanitario', '10x10x8', '99.99', '2025-03-21 16:00:00', '2025-03-26 13:00:00', 'doctor@mount.com', 'GCDX17P54T329M  ', null, null, 'Sacchetto in tela');

DROP TABLE  IF EXISTS BUNDLE CASCADE;
CREATE TABLE BUNDLE (
  id_bundle CHAR(20)  NOT NULL,
  id_contenuto CHAR(20) NOT NULL,
  quantità INT NOT NULL,
  PRIMARY KEY(id_bundle,id_contenuto),
  FOREIGN KEY (id_bundle) REFERENCES pacco(id),
  FOREIGN KEY (id_contenuto) REFERENCES pacco(id),
  CHECK (id_bundle!=id_contenuto)
);

INSERT INTO "public"."bundle" ("id_bundle", "id_contenuto", "quantità") VALUES (
    'PC005               ', 'PC001               ', '2'), 
    ('PC005               ', 'PC007               ', '1'), 
    ('PC005               ', 'PC008               ', '3'), 
    ('PC011               ', 'PC002               ', '1'), 
    ('PC011               ', 'PC003               ', '2'), 
    ('PC011               ', 'PC006               ', '1'), 
    ('PC015               ', 'PC009               ', '2'), 
    ('PC015               ', 'PC010               ', '1'), 
    ('PC015               ', 'PC012               ', '3'), 
    ('PC020               ', 'PC013               ', '1'), 
    ('PC020               ', 'PC014               ', '2'), 
    ('PC020               ', 'PC016               ', '1'), 
    ('PC023               ', 'PC017               ', '1'), 
    ('PC023               ', 'PC018               ', '1'), 
    ('PC023               ', 'PC019               ', '2'), 
    ('PC028               ', 'PC021               ', '1'), 
    ('PC028               ', 'PC024               ', '3'), 
    ('PC028               ', 'PC026               ', '2');

DROP TABLE  IF EXISTS TRACKING CASCADE;
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
);

INSERT INTO "public"."tracking" ("id_pacco", "data_ora", "status", "note", "nome_check_point", "città_check_point") VALUES 
('PC001               ', '2025-03-10 08:30:00', 'Autorizzato', 'Prioritario', 'Capital Knot', 'Central Region'), 
('PC001               ', '2025-03-11 10:15:00', 'Spedito', null, 'South Knot', 'Central Region'), 
('PC001               ', '2025-03-13 14:30:00', 'In Consegna', null, 'Lake Knot', 'Central Region'), 
('PC002               ', '2025-03-10 09:45:00', 'Autorizzato', 'Fragile', 'Lake Knot', 'Central Region'), 
('PC002               ', '2025-03-12 11:20:00', 'Spedito', null, 'Port Knot', 'East Region'), 
('PC002               ', '2025-03-14 08:15:00', 'In Consegna', null, 'Timefall', 'East Region'), 
('PC002               ', '2025-03-15 10:30:00', 'Consegnato', null, 'Lake Knot', 'Central Region'), 
('PC003               ', '2025-03-11 10:15:00', 'Autorizzato', 'Refrigerato', 'South Knot', 'Central Region'), 
('PC003               ', '2025-03-13 15:30:00', 'Fase di Controllo', 'Controllo temp', 'Distributor NW', 'Central Region'), 
('PC003               ', '2025-03-15 09:30:00', 'In Consegna', null, 'South Knot', 'Central Region'), 
('PC004               ', '2025-03-11 14:30:00', 'Autorizzato', 'Pesante', 'Lake Knot', 'Central Region'), 
('PC004               ', '2025-03-13 13:45:00', 'Spedito', null, 'Mountain Knot', 'Mountain Region'), 
('PC004               ', '2025-03-15 11:00:00', 'Consegnato', null, 'Mountain Knot', 'Mountain Region'), 
('PC005               ', '2025-03-12 09:00:00', 'Autorizzato', 'Bundle grande', 'Capital Knot', 'Central Region'), 
('PC005               ', '2025-03-14 10:45:00', 'Spedito', null, 'South Knot', 'Central Region'), 
('PC005               ', '2025-03-16 14:20:00', 'In Consegna', null, 'Lake Knot', 'Central Region'), 
('PC006               ', '2025-03-12 11:20:00', 'Autorizzato', 'Leggero', 'Port Knot', 'East Region'), 
('PC006               ', '2025-03-14 08:15:00', 'Fase di Controllo', null, 'Weather Stat', 'East Region'), 
('PC006               ', '2025-03-16 16:45:00', 'In Consegna', null, 'Port Knot', 'East Region'), 
('PC006               ', '2025-03-17 13:30:00', 'Consegnato', null, 'Port Knot', 'East Region'), 
('PC007               ', '2025-03-13 13:45:00', 'Autorizzato', 'Elettronica', 'Capital Knot', 'Central Region'), 
('PC007               ', '2025-03-15 09:30:00', 'Spedito', null, 'Lake Knot', 'Central Region'), 
('PC008               ', '2025-03-13 15:30:00', 'Autorizzato', null, 'Capital Knot', 'Central Region'), 
('PC008               ', '2025-03-15 11:00:00', 'Spedito', null, 'South Knot', 'Central Region'), 
('PC008               ', '2025-03-17 10:15:00', 'Consegnato', null, 'WindFarm', 'Central Region'), 
('PC009               ', '2025-03-14 08:15:00', 'Autorizzato', 'Regalo', 'South Knot', 'Central Region'), 
('PC009               ', '2025-03-16 14:20:00', 'Spedito', null, 'Distributor NW', 'Central Region'), 
('PC009               ', '2025-03-18 09:00:00', 'In Consegna', null, 'Elder', 'Central Region'), 
('PC009               ', '2025-03-19 11:30:00', 'Consegnato', null, 'Elder', 'Central Region'), 
('PC010               ', '2025-03-14 10:45:00', 'Autorizzato', 'Pesante', 'Timefall', 'East Region'), 
('PC010               ', '2025-03-16 16:45:00', 'Fase di Controllo', null, 'Engineer Loc', 'East Region'), 
('PC010               ', '2025-03-18 14:30:00', 'In Consegna', null, 'Timefall', 'East Region'), 
('PC010               ', '2025-03-20 09:15:00', 'Consegnato', null, 'Timefall', 'East Region'), 
('PC011               ', '2025-03-15 09:30:00', 'Autorizzato', 'Bundle grande', 'Port Knot', 'East Region'), 
('PC012               ', '2025-03-15 11:00:00', 'Autorizzato', 'Sanitario', 'Capital Knot', 'Central Region'), 
('PC012               ', '2025-03-17 10:15:00', 'Spedito', null, 'Lake Knot', 'Central Region'), 
('PC012               ', '2025-03-19 13:45:00', 'Fase di Controllo', null, 'South Knot', 'Central Region'), 
('PC013               ', '2025-03-16 14:20:00', 'Autorizzato', 'Regalo', 'Lake Knot', 'Central Region'), 
('PC013               ', '2025-03-18 09:00:00', 'Spedito', null, 'Craftsman Loc', 'Mountain Region'), 
('PC013               ', '2025-03-20 11:20:00', 'In Consegna', null, 'Geologist Loc', 'Mountain Region'), 
('PC014               ', '2025-03-16 16:45:00', 'Autorizzato', 'Refrigerato', 'South Knot', 'Central Region'), 
('PC014               ', '2025-03-18 14:30:00', 'Spedito', null, 'Distributor NW', 'Central Region'), 
('PC014               ', '2025-03-20 15:30:00', 'Consegnato', null, 'Film Direct', 'Central Region'), 
('PC015               ', '2025-03-17 08:30:00', 'Autorizzato', 'Bundle grande', 'Timefall', 'East Region'), 
('PC015               ', '2025-03-19 10:15:00', 'Spedito', null, 'Weather Stat', 'East Region'), 
('PC015               ', '2025-03-21 09:45:00', 'In Consegna', null, 'Port Knot', 'East Region'), 
('PC015               ', '2025-03-23 14:20:00', 'Consegnato', null, 'Timefall', 'East Region'), 
('PC016               ', '2025-03-17 11:30:00', 'Autorizzato', 'Materiali', 'Mountain Knot', 'Mountain Region'), 
('PC016               ', '2025-03-19 13:00:00', 'Spedito', null, 'Craftsman Loc', 'Mountain Region'), 
('PC016               ', '2025-03-21 10:45:00', 'In Consegna', null, 'Geologist Loc', 'Mountain Region'), 
('PC016               ', '2025-03-22 15:30:00', 'Consegnato', null, 'Mountain Knot', 'Mountain Region'), 
('PC017               ', '2025-03-17 14:10:00', 'Autorizzato', 'Sicurezza', 'Distributor NW', 'Central Region'), 
('PC017               ', '2025-03-19 16:30:00', 'Fase di Controllo', 'Verifica cont', 'Lake Knot', 'Central Region'), 
('PC017               ', '2025-03-21 12:15:00', 'Spedito', null, 'Capital Knot', 'Central Region'), 
('PC017               ', '2025-03-23 09:40:00', 'In Consegna', null, 'South Knot', 'Central Region'), 
('PC018               ', '2025-03-18 09:45:00', 'Autorizzato', 'Regalo', 'Engineer Loc', 'East Region'), 
('PC019               ', '2025-03-18 11:30:00', 'Autorizzato', 'Urgente', 'Doctor Loc', 'Mountain Region'), 
('PC019               ', '2025-03-19 14:45:00', 'Spedito', null, 'Mountain Knot', 'Mountain Region'), 
('PC019               ', '2025-03-20 13:20:00', 'Consegnato', null, 'Doctor Loc', 'Mountain Region'),
('PC020               ', '2025-03-18 15:20:00', 'Autorizzato', 'Bundle tech', 'Capital Knot', 'Central Region'), 
('PC020               ', '2025-03-20 17:30:00', 'Spedito', null, 'South Knot', 'Central Region'), 
('PC020               ', '2025-03-24 10:45:00', 'Consegnato', null, 'Capital Knot', 'Central Region'), 
('PC021               ', '2025-03-19 08:15:00', 'Autorizzato', 'Cancelleria', 'Capital Knot', 'Central Region'), 
('PC021               ', '2025-03-21 10:30:00', 'Spedito', null, 'Lake Knot', 'Central Region'), 
('PC021               ', '2025-03-23 15:45:00', 'In Consegna', null, 'Craftsman Loc', 'Mountain Region'), 
('PC022               ', '2025-03-19 10:40:00', 'Autorizzato', 'Tech', 'Lake Knot', 'Central Region'), 
('PC022               ', '2025-03-21 12:15:00', 'Spedito', null, 'Mountain Knot', 'Mountain Region'), 
('PC022               ', '2025-03-22 16:30:00', 'Consegnato', null, 'Mountain Knot', 'Mountain Region'), 
('PC023               ', '2025-03-19 13:25:00', 'Autorizzato', 'Bundle tech', 'South Knot', 'Central Region'), 
('PC024               ', '2025-03-20 09:50:00', 'Autorizzato', 'Dati', 'Lake Knot', 'Central Region'), 
('PC024               ', '2025-03-21 11:45:00', 'Fase di Controllo', 'Verifica cont', 'South Knot', 'Central Region'), 
('PC024               ', '2025-03-22 14:30:00', 'Spedito', null, 'Capital Knot', 'Central Region'), 
('PC024               ', '2025-03-23 10:15:00', 'Consegnato', null, 'Lake Knot', 'Central Region'), 
('PC025               ', '2025-03-20 12:15:00', 'Autorizzato', 'Alimentare', 'South Knot', 'Central Region'), 
('PC025               ', '2025-03-22 09:30:00', 'Spedito', null, 'Distributor NW', 'Central Region'), 
('PC025               ', '2025-03-24 11:45:00', 'In Consegna', null, 'Elder', 'Central Region'), 
('PC026               ', '2025-03-20 14:40:00', 'Autorizzato', 'Carica', 'Capital Knot', 'Central Region'), 
('PC026               ', '2025-03-22 16:15:00', 'Spedito', null, 'Lake Knot', 'Central Region'), 
('PC027               ', '2025-03-21 08:30:00', 'Autorizzato', 'Regalo', 'Lake Knot', 'Central Region'), 
('PC027               ', '2025-03-23 10:45:00', 'Spedito', null, 'Capital Knot', 'Central Region'), 
('PC027               ', '2025-03-25 09:15:00', 'In Consegna', null, 'Film Direct', 'Central Region'), 
('PC028               ', '2025-03-21 11:15:00', 'Autorizzato', 'Bundle tech', 'Timefall', 'East Region'), 
('PC028               ', '2025-03-23 13:30:00', 'Fase di Controllo', 'Verifica cont', 'Engineer Loc', 'East Region'), 
('PC028               ', '2025-03-25 15:45:00', 'Spedito', null, 'Port Knot', 'East Region'), 
('PC028               ', '2025-03-28 10:20:00', 'In Consegna', null, 'Weather Stat', 'East Region'), 
('PC029               ', '2025-03-21 13:30:00', 'Autorizzato', 'Fragile', 'Craftsman Loc', 'Mountain Region'), 
('PC029               ', '2025-03-23 15:45:00', 'Spedito', null, 'Mountain Knot', 'Mountain Region'), 
('PC029               ', '2025-03-24 14:30:00', 'Consegnato', null, 'Craftsman Loc', 'Mountain Region'), 
('PC030               ', '2025-03-21 16:00:00', 'Autorizzato', 'Dati medici', 'Doctor Loc', 'Mountain Region'), 
('PC030               ', '2025-03-24 14:15:00', 'Spedito', null, 'Geologist Loc', 'Mountain Region'), 
('PC030               ', '2025-03-26 11:30:00', 'In Consegna', null, 'Doctor Loc', 'Mountain Region');

DROP INDEX IF EXISTS  idx_id_hash;
CREATE INDEX idx_id_hash ON pacco USING HASH (id);
DROP INDEX IF EXISTS  idx_id_pacco;
CREATE INDEX idx_id_pacco ON tracking USING HASH (id_pacco);

DROP INDEX IF EXISTS  idx_nome_check_point;
CREATE INDEX idx_nome_check_point ON tracking USING HASH (nome_check_point);
DROP INDEX IF EXISTS  idx_città_check_point;
CREATE INDEX idx_città_check_point ON tracking USING HASH (città_check_point);
DROP INDEX IF EXISTS  idx_nome;
CREATE INDEX idx_nome  ON filiale USING HASH (nome);
DROP INDEX IF EXISTS  idx_città;
CREATE INDEX idx_città  ON filiale USING HASH (città);

DROP INDEX IF EXISTS  idx_corriere;
CREATE INDEX idx_corriere  ON pacco USING HASH (corriere);
DROP INDEX IF EXISTS  idx_cf;
CREATE INDEX idx_cf  ON corriere USING HASH (cf);

DROP INDEX IF EXISTS  idx_tipo;
CREATE INDEX idx_tipo ON filiale USING HASH (tipo);
DROP INDEX IF EXISTS  idx_grado;
CREATE INDEX idx_grado ON corriere USING HASH (grado);

DROP INDEX IF EXISTS  pacco_pkey_corriere;
CREATE INDEX pacco_pkey_corriere ON pacco USING BTREE (corriere);


SELECT email,f.nome,f.città, count(*) as n_pacchi_attivi
FROM cliente as c
JOIN pacco as p ON p.cliente=c.email
JOIN tracking as t ON p.id=t.id_pacco
JOIN filiale as f ON t.città_check_point=f.città AND t.nome_check_point=f.nome
WHERE (t.status='Consegnato')
GROUP BY email,f.nome,f.città
HAVING count(*) >=2
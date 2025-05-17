#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dependencies/include/libpq-fe.h"

#define PG_HOST "aws-0-eu-central-1.pooler.supabase.com"
#define PG_USER "postgres.zzqizhzuvvrrupahbgcb"
#define PG_DB "postgres"
#define PG_PASS "iltVoi6uYrskVeSR"
#define PG_PORT 5432

void checkCommand(PGresult *res, PGconn *conn) {
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("Comando fallito: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
}

void checkResults(PGresult *res, PGconn *conn) {
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("Risultati inconsistenti: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
}

int main(int argc, char **argv) {
    char conninfo[250];
    sprintf(conninfo, "user=%s password=%s dbname=%s host=%s port=%d", 
            PG_USER, PG_PASS, PG_DB, PG_HOST, PG_PORT);

    // Eseguo la connessione al database
    PGconn *conn = PQconnectdb(conninfo);

    // Verifico lo stato di connessione
    if (PQstatus(conn) != CONNECTION_OK) {
        printf("Errore di connessione: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }
    printf("Connessione al database %s avvenuta con successo\n", PG_DB);

    // Creazione della vista ultimo_tracking
    const char *createViewSQL = 
        "DROP VIEW IF EXISTS ultimo_tracking CASCADE; "
        "CREATE VIEW ultimo_tracking (id_pacco, status) AS "
        "SELECT t1.id_pacco, t1.status "
        "FROM tracking t1 "
        "INNER JOIN ("
        "    SELECT id_pacco, MAX(data_ora) as max_data_ora "
        "    FROM tracking "
        "    GROUP BY id_pacco"
        ") t2 ON t1.id_pacco = t2.id_pacco AND t1.data_ora = t2.max_data_ora;";
    
    PGresult *res = PQexec(conn, createViewSQL);
    checkCommand(res, conn);
    PQclear(res);
    printf("Vista ultimo_tracking creata con successo\n");

    // Query per selezionare i dati dalla vista
    const char *selectSQL = "SELECT id_pacco, status FROM ultimo_tracking ORDER BY id_pacco;";
    res = PQexec(conn, selectSQL);
    checkResults(res, conn);

    // Stampa i risultati
    int rows = PQntuples(res);
    int cols = PQnfields(res);
    
    printf("\nRisultati della vista ultimo_tracking:\n");
    printf("ID Pacco\tStatus\n");
    printf("--------\t------\n");
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%s\t\t", PQgetvalue(res, i, j));
        }
        printf("\n");
    }

    // Pulizia e chiusura
    PQclear(res);
    PQfinish(conn);

    return 0;
}
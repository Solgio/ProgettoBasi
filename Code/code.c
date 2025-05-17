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

printf("                                 .______    _______ .__   __. ____    ____  _______ .__   __.  __    __  .___________.  ______                                                   \n");
printf("                                 |   _  \\  |   ____||  \\ |  | \\   \\  /   / |   ____||  \\ |  | |  |  |  | |           | /  __  \\                                                  \n");
printf("                                 |  |_)  | |  |__   |   \\|  |  \\   \\/   /  |  |__   |   \\|  | |  |  |  | `---|  |----`|  |  |  |                                                 \n");
printf("                                 |   _  <  |   __|  |  . `  |   \\      /   |   __|  |  . `  | |  |  |  |     |  |     |  |  |  |                                                 \n");
printf("                                 |  |_)  | |  |____ |  |\\   |    \\    /    |  |____ |  |\\   | |  `--'  |     |  |     |  `--'  |                                                 \n");
printf("                                 |______/  |_______||__| \\__|     \\__/     |_______||__| \\__|  \\______/      |__|      \\______/                                                  \n");
printf("                       ___       __       __       __  __  .__   __. .___________. _______ .______       _______    ___       ______   ______  __       ___                      \n");
printf("                      /   \\     |  |     |  |     (_ )|  | |  \\ |  | |           ||   ____||   _  \\     |   ____|  /   \\     /      | /      ||  |     /   \\                     \n");
printf("                     /  ^  \\    |  |     |  |      |/ |  | |   \\|  | `---|  |----`|  |__   |  |_)  |    |  |__    /  ^  \\   |  ,----'|  ,----'|  |    /  ^  \\                    \n");
printf("                    /  /_\\  \\   |  |     |  |         |  | |  . `  |     |  |     |   __|  |      /     |   __|  /  /_\\  \\  |  |     |  |     |  |   /  /_\\  \\                   \n");
printf("                   /  _____  \\  |  `----.|  `----.    |  | |  |\\   |     |  |     |  |____ |  |\\  \\----.|  |    /  _____  \\ |  `----.|  `----.|  |  /  _____  \\                  \n");
printf("                  /__/     \\__\\ |_______||_______|    |__| |__| \\__|     |__|     |_______|| _| `._____||__|   /__/     \\__\\ \\______| \\______||__| /__/     \\__\\                 \n");
printf("    _______   __       _______  _______      _______..___________. __    ______   .__   __.  _______     _______   __     .______      ___       ______   ______  __    __   __  \n");
printf("   |       \\ |  |     /  _____||   ____|    /       ||           ||  |  /  __  \\  |  \\ |  | |   ____|   |       \\ |  |    |   _  \\    /   \\     /      | /      ||  |  |  | |  | \n");
printf("   |  .--.  ||  |    |  |  __  |  |__      |   (----``---|  |----`|  | |  |  |  | |   \\|  | |  |__      |  .--.  ||  |    |  |_)  |  /  ^  \\   |  ,----'|  ,----'|  |__|  | |  | \n");
printf("   |  |  |  ||  |    |  | |_ | |   __|      \\   \\        |  |     |  | |  |  |  | |  . `  | |   __|     |  |  |  ||  |    |   ___/  /  /_\\  \\  |  |     |  |     |   __   | |  | \n");
printf("   |  '--'  ||  |    |  |__| | |  |____ .----)   |       |  |     |  | |  `--'  | |  |\\   | |  |____    |  '--'  ||  |    |  |     /  _____  \\ |  `----.|  `----.|  |  |  | |  | \n");
printf("   |_______/ |__|     \\______| |_______||_______/        |__|     |__|  \\______/  |__| \\__| |_______|   |_______/ |__|    | _|    /__/     \\__\\ \\______| \\______||__|  |__| |__| \n");
    
printf("Pronto a partire?\n");
int end=0;
while(end!=1){
printf("Premi invio per continuare...\n");
getchar();
int scelta;
printf("Che query vuoi eseguire?\n A tua disposizione abbiamo queste 5 opzioni:\n");
printf("\t1. Elenco dei pacchi Consegnati\n\t2. Numero pacchi per bundle con garanzia 3 anni\n\t3. Clienti con più di 2 pacchi consegnati per filiale\n\t4. Status attuale dei pacchi\n");
printf("Qual'è la tua scelta? (1-4): ");
scanf("%d", &scelta);
while(scelta < 1 || scelta > 4){
    printf("\tHai scelto molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
    printf("Le scelte sono 4, riprova: ");
    scanf("%d", &scelta);
}
printf("\tHai scelto molto bene!  (cit)\n\n");
if(scelta == 4){// Creazione della vista ultimo_tracking
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
        printf("ID Pacco\t\t\tStatus\n");
        printf("--------\t\t\t------\n");
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("%s\t\t", PQgetvalue(res, i, j));
            }
            printf("\n");
        }
        PQclear(res);
    }
    
    printf("Vuoi continuare? (0=si, 1=no): ");
    scanf("%d", &end);
}
printf("Grazie per aver usato il mio programma! Che l'algebra relazionale sia con te\n");
    // Pulizia e chiusura
    PQfinish(conn);

    return 0;
}
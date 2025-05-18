#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dependencies/include/libpq-fe.h"

#define PG_HOST "aws-0-eu-central-1.pooler.supabase.com"
#define PG_USER "postgres.zzqizhzuvvrrupahbgcb"
#define PG_DB "postgres"
#define PG_PASS "iltVoi6uYrskVeSR"
#define PG_PORT 5432

const char *GRADO_CORRIERE[] = {
    "Porter",
    "Skilled Handler",
    "Elite Transporter",
    "The Great Deliverer"};

const char *TIPO_FILIALE[] = {
    "Locker",
    "Punto di Controllo",
    "Magazzino"};

const char *TIPO_ASSICURAZIONE[] = {
    "Reso in 30 giorni",
    "Garanzia per 1 anno",
    "Garanzia per 3 anni"};

const char *TIPO_CARTA[] = {
    "Carta Regalo",
    "Sacchetto in tela",
    "Scatola Speciale"};

const char *STATUS[] = {
    "Consegnato",
    "In Consegna",
    "Spedito",
    "Autorizzato",
    "Fase di Controllo"};

void checkCommand(PGresult *res, PGconn *conn)
{
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Comando fallito: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
}

void checkResults(PGresult *res, PGconn *conn)
{
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        printf("Risultati inconsistenti: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
}

void printResult(int rows, int cols, PGresult *res)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%s\t\t", PQgetvalue(res, i, j));
        }
        printf("\n");
    }
}

int main(int argc, char **argv)
{
    char conninfo[250];
    sprintf(conninfo, "user=%s password=%s dbname=%s host=%s port=%d",
            PG_USER, PG_PASS, PG_DB, PG_HOST, PG_PORT);

    // Eseguo la connessione al database
    PGconn *conn = PQconnectdb(conninfo);

    // Verifico lo stato di connessione
    if (PQstatus(conn) != CONNECTION_OK)
    {
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
    int end = 0;
    while (end != 1)
    {
        printf("Premi invio per continuare...\n");
        getchar();

        int scelta;
        printf("Che query vuoi eseguire?\n A tua disposizione abbiamo queste 5 opzioni:\n");
        printf("\t1. Media del costo dei pacchi di un corriere di un certo grado che sono passati per una filiale di un certo tipo\n\t2. Numero pacchi per bundle con un determinato tipo di assicurazione\n\t3. Clienti con più di 2 pacchi consegnati per filiale\n\t4. Corrieri con bundle con pacchi con garanzia a 3 anni e costo maggiore di 300\n\t5. Status attuale dei pacchi\n");
        printf("Qual'è la tua scelta? (1-5): ");
        scanf("%d", &scelta);
        while (scelta < 1 || scelta > 5)
        {
            printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
            printf("Le scelte sono 5, riprova: ");
            scanf("%d", &scelta);
        }
        printf("\tHai scelto molto bene!  (cit)\n\n");
        PGresult *res;

        if (scelta == 1)
        {
            const char *query1 = "SELECT corriere, AVG(p.costo) AS costo_medio "
                                 "FROM pacco AS p "
                                 "JOIN tracking AS t ON t.id_pacco = p.id "
                                 "JOIN filiale AS f ON t.città_check_point = f.città AND t.nome_check_point=f.nome "
                                 "JOIN corriere AS c ON p.corriere = c.cf "
                                 "WHERE f.tipo = $1 AND c.grado = $2 "
                                 "GROUP BY corriere;";
            res = PQprepare(conn, "query1", query1, 2, NULL);
            if (PQresultStatus(res) != PGRES_COMMAND_OK)
            {
                fprintf(stderr, "Prepare failed: %s", PQerrorMessage(conn));
                PQclear(res);
                // Handle error appropriately
            }
            PQclear(res);

            int grado;
            int tipo_filiale;
            printf("Scegli il Tipo di Filiale. Le opzioni sono:\n");
            for (int i = 0; i < 3; i++)
            {
                printf("\t%d. %s\n", i + 1, TIPO_FILIALE[i]);
            }
            printf("Quale tipo vuoi? (1-3): ");
            scanf("%d", &tipo_filiale);
            while (tipo_filiale < 1 || tipo_filiale > 3)
            {
                printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                printf("Quale grado vuoi? (1-4): ");
                scanf("%d", &tipo_filiale);
            }

            printf("Scegli il Grado del Corriere. Le opzioni sono:\n");
            for (int i = 0; i < 4; i++)
            {
                printf("\t%d. %s\n", i + 1, GRADO_CORRIERE[i]);
            }
            printf("Quale grado vuoi? (1-4): ");
            scanf("%d", &grado);
            while (grado < 1 || grado > 4)
            {
                printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                printf("Quale grado vuoi? (1-4): ");
                scanf("%d", &grado);
            }

            const char *paramValues[2] = {
                TIPO_FILIALE[tipo_filiale - 1],
                GRADO_CORRIERE[grado - 1]};

            res = PQexecPrepared(conn, "query1", 2, paramValues, NULL, NULL, 0);
            checkResults(res, conn);

            // Stampa i risultati
            int rows = PQntuples(res);
            int cols = PQnfields(res);

            printf("\n\t\tMedia del costo dei pacchi di un corriere %s che sono passati per una filiale %s:\n", GRADO_CORRIERE[grado - 1], TIPO_FILIALE[tipo_filiale - 1]);
            printf("ID Corriere\t\t\tCosto Medio\n");
            printf("-----------\t\t\t-----------\n");
            printResult(rows, cols, res);
            PQclear(res);
        }

        if (scelta == 2)
        {
            const char *query2 = "SELECT b.id_bundle, COUNT(*) as n_garanzia_tre_anni "
                                 "FROM bundle AS b "
                                 "JOIN pacco AS p ON b.id_contenuto = p.id "
                                 "WHERE p.tipo_assicurazione = $1 "
                                 "GROUP BY b.id_bundle";
            res = PQprepare(conn, "query2", query2, 1, NULL);

            int assicurazione;
            printf("Scegli il tipo di assicurazione. Le opzioni sono:\n");
            for (int i = 0; i < 3; i++)
            {
                printf("\t%d. %s\n", i + 1, TIPO_ASSICURAZIONE[i]);
            }
            printf("Quale tipo vuoi? (1-3): ");
            scanf("%d", &assicurazione);
            while (assicurazione < 1 || assicurazione > 3)
            {
                printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                printf("Quale grado vuoi? (1-3): ");
                scanf("%d", &assicurazione);
            }

            const char *paramValue = TIPO_ASSICURAZIONE[assicurazione - 1];
            res = PQexecPrepared(conn, "query2", 1, &paramValue, NULL, NULL, 0);
            checkResults(res, conn);

            // Stampa i risultati
            int rows = PQntuples(res);
            int cols = PQnfields(res);

            printf("\nNumero pacchi per bundle con %s:\n", TIPO_ASSICURAZIONE[assicurazione - 1]);
            printf("ID Bundle\t\t\tNumero pacchi Assicurati\n");
            printf("---------\t\t\t------------------------\n");
            printResult(rows, cols, res);
            PQclear(res);
        }

        if (scelta == 3)
        {
            // Query per selezionare i dati dalla vista
            const char *query3 = "SELECT email,f.nome,f.città, count(*) as n_pacchi_attivi "
                                 "FROM cliente as c "
                                 "JOIN pacco as p ON p.cliente=c.email "
                                 "JOIN tracking as t ON p.id=t.id_pacco "
                                 "JOIN filiale as f ON t.città_check_point=f.città AND t.nome_check_point=f.nome "
                                 "WHERE (t.status=$1) "
                                 "GROUP BY email,f.nome,f.città "
                                 "HAVING count(*) >=$2";
            res = PQprepare(conn, "query3", query3, 2, NULL);

            int status;
            printf("Scegli il tipo di status per il pacco. Le opzioni sono:\n");
            for (int i = 0; i < 5; i++)
            {
                printf("\t%d. %s\n", i + 1, STATUS[i]);
            }
            printf("Quale tipo vuoi? (1-5): ");
            scanf("%d", &status);
            while (status < 1 || status > 5)
            {
                printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                printf("Quale grado vuoi? (1-5): ");
                scanf("%d", &status);
            }

            int numero_pacchi_per_filiale;
            printf("Scegli quanti pacchi vuole per filiale:\n");
            scanf("%d", &numero_pacchi_per_filiale);

            char num_pacchi_str[12]; // Buffer for 32-bit integer
            snprintf(num_pacchi_str, sizeof(num_pacchi_str), "%d", numero_pacchi_per_filiale);

            const char *paramValues[2] = {
                STATUS[status - 1],
                num_pacchi_str};

            res = PQexecPrepared(conn, "query3", 2, paramValues, NULL, NULL, 0);
            checkResults(res, conn);

            // Stampa i risultati
            int rows = PQntuples(res);
            int cols = PQnfields(res);

            printf("\n3. Clienti con più di %d pacchi %s per filiale", numero_pacchi_per_filiale, STATUS[status - 1]);
            printf("Cliente\t\t\tNumero pacchi\n");
            printf("--------\t\t\t------\n");
            printResult(rows, cols, res);
            PQclear(res);
        }

        if (scelta == 4)
        {
            int costo;
            printf("Scegli il costo per il filtraggio dei risultati: ");
            scanf("%d", &costo);
            char costo_str[12];
            snprintf(costo_str, sizeof(costo_str), "%d", costo);

            int filtro;
            printf("Vuoi filtrare per pacchi assicurati o regalo?    (0=assicurati, 1=regalo): ");
            scanf("%d", &filtro);
            while (filtro < 0 || filtro > 1)
            {
                printf("\n Input non valido, riprova: ");
                printf("Vuoi filtrare per pacchi assicurati o regalo?    (0=assicurati, 1=regalo): ");
                scanf("%d", &filtro);
            }
            if (filtro == 0)
            {
                const char *query4 = "SELECT cf, count(*) "
                                     "FROM corriere as c "
                                     "JOIN pacco as p ON p.costo>$1 AND p.corriere=cf "
                                     "JOIN ( "
                                     "      SELECT b.id_bundle, COUNT(*) as n_garanzia_tre_anni "
                                     "      FROM bundle AS b "
                                     "      JOIN pacco AS p ON b.id_contenuto = p.id "
                                     "      WHERE p.tipo_assicurazione = $2"
                                     "      GROUP BY b.id_bundle "
                                     ") as b ON p.id=b.id_bundle "
                                     "GROUP BY cf";
                res = PQprepare(conn, "query4", query4, 2, NULL);
                int assicurazione;

                printf("Scegli il tipo di assicurazione. Le opzioni sono:\n");
                for (int i = 0; i < 3; i++)
                {
                    printf("\t%d. %s\n", i + 1, TIPO_ASSICURAZIONE[i]);
                }
                printf("Quale tipo vuoi? (1-3): ");
                scanf("%d", &assicurazione);
                while (assicurazione < 1 || assicurazione > 3)
                {
                    printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                    printf("Quale grado vuoi? (1-3): ");
                    scanf("%d", &assicurazione);
                }

                const char *paramValues[2] = {
                    costo_str,
                    TIPO_ASSICURAZIONE[assicurazione - 1]};
                res = PQexecPrepared(conn, "query4", 2, paramValues, NULL, NULL, 0);
            }
            else
            {
                int caso;
                printf("Cosa vuoi dalla query:\n\t1. Solo tipo carta\n\t2. Solo dedica\n\t3. Entrambi\n Cosa preferisci? (1-3): ");
                scanf("%d", &caso);
                while (caso < 1 || caso > 3)
                {
                    printf("\n Input non valido, riprova: ");
                    printf("Cosa vuoi dalla query:\n\t1. Solo tipo carta\n\t2. Solo dedica\n\t3. Entrambi\n Cosa preferisci? (1-3): ");
                    scanf("%d", &filtro);
                }

                if (caso == 1)
                {
                    const char *query4a = "SELECT cf, count(*) "
                                          "FROM corriere as c "
                                          "JOIN pacco as p ON p.costo>$1 AND p.corriere=cf "
                                          "JOIN ( "
                                          "      SELECT b.id_bundle, COUNT(*) as n_garanzia_tre_anni "
                                          "      FROM bundle AS b "
                                          "      JOIN pacco AS p ON b.id_contenuto = p.id "
                                          "      WHERE p.tipo_carta = $2"
                                          "      GROUP BY b.id_bundle "
                                          ") as b ON p.id=b.id_bundle "
                                          "GROUP BY cf";
                    res = PQprepare(conn, "query4a", query4a, 2, NULL);
                    int assicurazione;

                    int carta;
                    printf("Scegli il tipo di carta. Le opzioni sono:\n");
                    for (int i = 0; i < 3; i++)
                    {
                        printf("\t%d. %s\n", i + 1, TIPO_CARTA[i]);
                    }
                    printf("Quale tipo vuoi? (1-3): ");
                    scanf("%d", &carta);
                    while (carta < 0 || carta > 3)
                    {
                        printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                        printf("Quale carta vuoi? (1-3): ");
                        scanf("%d", &carta);
                    }

                    const char *paramValues[2] = {
                        costo_str,
                        TIPO_CARTA[carta - 1]};
                    res = PQexecPrepared(conn, "query4a", 2, paramValues, NULL, NULL, 0);
                }

                else if (caso == 2)
                {
                    const char *query4b = "SELECT cf, count(*) "
                                          "FROM corriere as c "
                                          "JOIN pacco as p ON p.costo>$1 AND p.corriere=cf "
                                          "JOIN ( "
                                          "      SELECT b.id_bundle, COUNT(*) as n_garanzia_tre_anni "
                                          "      FROM bundle AS b "
                                          "      JOIN pacco AS p ON b.id_contenuto = p.id "
                                          "      WHERE p.dedica = $2"
                                          "      GROUP BY b.id_bundle "
                                          ") as b ON p.id=b.id_bundle "
                                          "GROUP BY cf";
                    res = PQprepare(conn, "query4b", query4b, 2, NULL);

                    char dedica[100];
                    printf("Inserisci la dedica: ");
                    scanf("%99s", dedica);

                    const char *paramValues[2] = {
                        costo_str,
                        dedica};
                    res = PQexecPrepared(conn, "query4b", 2, paramValues, NULL, NULL, 0);
                }

                else
                {
                    const char *query4c = "SELECT cf, count(*) "
                                          "FROM corriere as c "
                                          "JOIN pacco as p ON p.costo>$1 AND p.corriere=cf "
                                          "JOIN ( "
                                          "      SELECT b.id_bundle, COUNT(*) as n_garanzia_tre_anni "
                                          "      FROM bundle AS b "
                                          "      JOIN pacco AS p ON b.id_contenuto = p.id "
                                          "      WHERE p.tipo_carta = $2 AND p.dedica = $3"
                                          "      GROUP BY b.id_bundle "
                                          ") as b ON p.id=b.id_bundle "
                                          "GROUP BY cf";
                    res = PQprepare(conn, "query4c", query4c, 3, NULL);

                    int carta;
                    printf("Scegli il tipo di carta. Le opzioni sono:\n");
                    for (int i = 0; i < 3; i++)
                    {
                        printf("\t%d. %s\n", i + 1, TIPO_CARTA[i]);
                    }
                    printf("Quale tipo vuoi? (1-3): ");
                    scanf("%d", &carta);
                    while (carta < 0 || carta > 3)
                    {
                        printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                        printf("Quale carta vuoi? (1-3): ");
                        scanf("%d", &carta);
                    }

                    char dedica[100];
                    printf("Inserisci la dedica: ");
                    scanf("%99s", dedica);

                    const char *paramValues[3] = {
                        costo_str,
                        TIPO_CARTA[carta - 1],
                        dedica};
                    res = PQexecPrepared(conn, "query4c", 3, paramValues, NULL, NULL, 0);
                }
            }

            checkResults(res, conn);

            // Stampa i risultati
            int rows = PQntuples(res);
            int cols = PQnfields(res);
            printf("Corriere\t\t\tNumero pacchi\n");
            printf("--------\t\t\t------\n");

            // printf("\nCorrieri con bundle con pacchi con %s e costo maggiore di %d", TIPO_ASSICURAZIONE[assicurazione - 1], costo);
            printResult(rows, cols, res);
            PQclear(res);
        }

        if (scelta == 5)
        {

            const char *selectSQL = "SELECT t1.id_pacco, t1.status "
                                    "FROM tracking t1 "
                                    "INNER JOIN ("
                                    "    SELECT id_pacco, MAX(data_ora) as max_data_ora "
                                    "    FROM tracking "
                                    "    GROUP BY id_pacco"
                                    ") t2 ON t1.id_pacco = t2.id_pacco AND t1.data_ora = t2.max_data_ora;";
            PGresult *res = PQexec(conn, selectSQL);
            checkResults(res, conn);

            // Stampa i risultati
            int rows = PQntuples(res);
            int cols = PQnfields(res);

            printf("\nRisultati della vista ultimo_tracking:\n");
            printf("ID Pacco\t\t\tStatus\n");
            printf("--------\t\t\t------\n");

            printResult(rows, cols, res);
            PQclear(res);
        }

        printf("\n\nVuoi continuare? (0=si, 1=no): ");
        scanf("%d", &end);
    }
    printf("Grazie per aver usato il mio programma! Che l'algebra relazionale sia con te\n");
    // Pulizia e chiusura
    PQfinish(conn);

    return 0;
}
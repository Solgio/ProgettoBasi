#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dependencies/include/libpq-fe.h"

#define PG_HOST "aws-0-eu-central-1.pooler.supabase.com"
#define PG_USER "postgres.zzqizhzuvvrrupahbgcb"
#define PG_DB "postgres"
#define PG_PASS "iltVoi6uYrskVeSR"
#define PG_PORT 5432

//! ENUM PER LIMITARE LE SCELTE (SICUREZZA E COMPATIBILITA' CON L'INFRASTRUTTURA)
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

//! FUNZIONI PER LA GESTIONE DEGLI ERRORI
void checkCommand(PGresult *res, PGconn *conn)
{
    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        fprintf(stderr, "Comando fallito: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
}

void checkResults(PGresult *res, PGconn *conn)
{
    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        fprintf(stderr, "Risultati inconsistenti: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }
}

//! FUNZIONE PER STAMPARE I RISULTATI
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

//! FUNZIONE PER PULIZIA DELLO SCHERMO e TITOLO
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");

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

#endif
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
        fprintf(stderr, "Errore di connessione: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }
    printf("Connessione al database %s avvenuta con successo\n", PG_DB);

    clearScreen(); // Clears screen and prints title once at the beginning

    printf("Pronto a partire?\n");
    int end = 0;
    //! Ciclo che permette di eseguire più query
    while (end != 1)
    {
        printf("Premi invio per continuare...\n");
        getchar(); // Consume the newline character from previous scanf

        clearScreen(); // Clear the screen before showing the menu again

        int scelta;
        printf("Che query vuoi eseguire?\n A tua disposizione abbiamo queste 5 opzioni:\n");
        printf("\t1. Media del costo dei pacchi di un corriere di un certo grado che sono passati per una filiale di un certo tipo\n\t2. Numero pacchi per bundle con un determinato tipo di assicurazione\n\t3. Corrieri con tempi di consegna maggiori alla media\n\t4. Corrieri con bundle con pacchi assicurati o regalo e costo specifici\n\t5. Status attuale dei pacchi\n");
        printf("Qual'è la tua scelta? (1-5): ");
        scanf("%d", &scelta);
        // Consume the newline character after scanf
        while (getchar() != '\n');

        //! Controllo che la scelta sia valida (presente anche in seguito ma non ripetuto)
        while (scelta < 1 || scelta > 5)
        {
            printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
            printf("Le scelte sono 5, riprova: ");
            scanf("%d", &scelta);
            while (getchar() != '\n'); // Consume the newline
        }
        printf("\tHai scelto molto bene!  (cit)\n\n");
        PGresult *res;
        //! Scelta della query da eseguire
        switch (scelta) // Using switch statement
        {
            case 1: //! QUERY 1 (PARAMETRIZZABILE)
            {
                const char *query1 = "SELECT corriere, AVG(p.costo) AS costo_medio "
                                     "FROM pacco AS p "
                                     "JOIN tracking AS t ON t.id_pacco = p.id "
                                     "JOIN filiale AS f ON t.città_check_point = f.città AND t.nome_check_point=f.nome "
                                     "JOIN corriere AS c ON p.corriere = c.cf "
                                     "WHERE f.tipo = $1 AND c.grado = $2 "
                                     "GROUP BY corriere;";

                int grado;
                int tipo_filiale;
                printf("Scegli il Tipo di Filiale. Le opzioni sono:\n");
                for (int i = 0; i < 3; i++)
                {
                    printf("\t%d. %s\n", i + 1, TIPO_FILIALE[i]);
                }
                printf("Quale tipo vuoi? (1-3): ");
                scanf("%d", &tipo_filiale);
                while (getchar() != '\n'); // Consume the newline
                while (tipo_filiale < 1 || tipo_filiale > 3)
                {
                    printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                    printf("Quale tipo vuoi? (1-3): ");
                    scanf("%d", &tipo_filiale);
                    while (getchar() != '\n'); // Consume the newline
                }

                printf("Scegli il Grado del Corriere. Le opzioni sono:\n");
                for (int i = 0; i < 4; i++)
                {
                    printf("\t%d. %s\n", i + 1, GRADO_CORRIERE[i]);
                }
                printf("Quale grado vuoi? (1-4): ");
                scanf("%d", &grado);
                while (getchar() != '\n'); // Consume the newline
                while (grado < 1 || grado > 4)
                {
                    printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                    printf("Quale grado vuoi? (1-4): ");
                    scanf("%d", &grado);
                    while (getchar() != '\n'); // Consume the newline
                }

                const char *paramValues[2] = {
                    TIPO_FILIALE[tipo_filiale - 1],
                    GRADO_CORRIERE[grado - 1]};

                res = PQexecParams(conn, query1, 2, NULL, paramValues, NULL, NULL, 0);
                checkResults(res, conn);

                // Stampa i risultati
                int rows = PQntuples(res);
                int cols = PQnfields(res);

                printf("\n\t\tMedia del costo dei pacchi di un corriere %s che sono passati per una filiale %s:\n", GRADO_CORRIERE[grado - 1], TIPO_FILIALE[tipo_filiale - 1]);
                printf("ID Corriere\t\t\tCosto Medio\n");
                printf("-----------\t\t\t-----------\n");
                printResult(rows, cols, res);
                PQclear(res);
                break; // Don't forget break;
            }

            case 2: //! QUERY 2 (PARAMETRIZZABILE)
            {
                const char *query2 = "SELECT b.id_bundle, COUNT(*) as n_bundle "
                                     "FROM bundle AS b "
                                     "JOIN pacco AS p ON b.id_contenuto = p.id "
                                     "WHERE p.tipo_assicurazione = $1 "
                                     "GROUP BY b.id_bundle";

                int assicurazione;
                printf("Scegli il tipo di assicurazione. Le opzioni sono:\n");
                for (int i = 0; i < 3; i++)
                {
                    printf("\t%d. %s\n", i + 1, TIPO_ASSICURAZIONE[i]);
                }
                printf("Quale tipo vuoi? (1-3): ");
                scanf("%d", &assicurazione);
                while (getchar() != '\n'); // Consume the newline
                while (assicurazione < 1 || assicurazione > 3)
                {
                    printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                    printf("Quale tipo vuoi? (1-3): ");
                    scanf("%d", &assicurazione);
                    while (getchar() != '\n'); // Consume the newline
                }

                const char *paramValue = TIPO_ASSICURAZIONE[assicurazione - 1];
                res = PQexecParams(conn, query2, 1, NULL, &paramValue, NULL, NULL, 0);
                checkResults(res, conn);

                // Stampa i risultati
                int rows = PQntuples(res);
                int cols = PQnfields(res);

                printf("\nNumero pacchi per bundle con %s:\n", TIPO_ASSICURAZIONE[assicurazione - 1]);
                printf("ID Bundle\t\t\tNumero pacchi Assicurati\n");
                printf("---------\t\t\t------------------------\n");
                printResult(rows, cols, res);
                PQclear(res);
                break;
            }

            case 3: //! QUERY 3 (NON PARAMETRIZZABILE)
            {
                const char *query3 = "SELECT p.corriere, AVG(h.differenza) AS media_corriere "
                                     "FROM ( "
                                     "    SELECT t1.id_pacco, p1.corriere, MAX(t1.data_ora) - p1.dataora_ordine AS differenza "
                                     "    FROM "
                                     "        tracking AS t1 "
                                                                         "    JOIN pacco AS p1 ON p1.id = t1.id_pacco "
                                     "    WHERE t1.status = 'Consegnato' "
                                     "    GROUP BY t1.id_pacco, p1.dataora_ordine, p1.corriere "
                                     ") AS h "
                                     "JOIN pacco AS p ON p.id = h.id_pacco "
                                     "GROUP BY p.corriere "
                                     "HAVING AVG(h.differenza) > ( "
                                     "    SELECT AVG(differenza) "
                                     "    FROM ( "
                                     "        SELECT t1.id_pacco, MAX(t1.data_ora) - p2.dataora_ordine AS differenza "
                                     "        FROM tracking AS t1 "
                                     "        JOIN pacco AS p2 ON p2.id = t1.id_pacco "
                                     "        WHERE t1.status = 'Consegnato' "
                                     "        GROUP BY t1.id_pacco, p2.dataora_ordine "
                                     "    ) AS m "
                                     ") "
                                     "ORDER BY media_corriere DESC;";
                res = PQexec(conn, query3);
                checkResults(res, conn);

                // Stampa i risultati
                int rows = PQntuples(res);
                int cols = PQnfields(res);

                printf("\nCorrieri più lenti del tempo medio di consegna:\n");
                printf("ID Corriere\t\t\tTempo di consegna medio\n");
                printf("-----------\t\t\t-----------------------\n");

                printResult(rows, cols, res);
                PQclear(res);
                break;
            }

            case 4: //! QUERY 4 (SUPER-PARAMETRIZZABILE)
            {
                int costo;
                printf("Scegli il costo per il filtraggio dei risultati: ");
                scanf("%d", &costo);
                while (getchar() != '\n');
                char costo_str[12];
                snprintf(costo_str, sizeof(costo_str), "%d", costo);

                int filtro;
                printf("Vuoi filtrare per pacchi assicurati o regalo?    (0=assicurati, 1=regalo): ");
                scanf("%d", &filtro);
                while (getchar() != '\n');
                while (filtro < 0 || filtro > 1)
                {
                    printf("\n Input non valido, riprova: ");
                    printf("Vuoi filtrare per pacchi assicurati o regalo?    (0=assicurati, 1=regalo): ");
                    scanf("%d", &filtro);
                    while (getchar() != '\n');
                }
                //! FILTRO X PACCHI ASSICURATI
                if (filtro == 0)
                {
                    const char *query4_assured = "SELECT cf, count(*) "
                                                 "FROM corriere as c "
                                                 "JOIN pacco as p ON p.costo>$1 AND p.corriere=cf "
                                                 "JOIN ( "
                                                 "      SELECT b.id_bundle, COUNT(*) as n_assicurazione "
                                                 "      FROM bundle AS b "
                                                 "      JOIN pacco AS p ON b.id_contenuto = p.id "
                                                 "      WHERE p.tipo_assicurazione = $2"
                                                 "      GROUP BY b.id_bundle "
                                                 ") as b ON p.id=b.id_bundle "
                                                 "GROUP BY cf";

                    int assicurazione;

                    printf("Scegli il tipo di assicurazione. Le opzioni sono:\n");
                    for (int i = 0; i < 3; i++)
                    {
                        printf("\t%d. %s\n", i + 1, TIPO_ASSICURAZIONE[i]);
                    }
                    printf("Quale tipo vuoi? (1-3): ");
                    scanf("%d", &assicurazione);
                    while (getchar() != '\n');
                    while (assicurazione < 1 || assicurazione > 3)
                    {
                        printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                        printf("Quale tipo di assicurazione vuoi? (1-3): ");
                        scanf("%d", &assicurazione);
                        while (getchar() != '\n');
                    }

                    const char *paramValues[2] = {
                        costo_str,
                        TIPO_ASSICURAZIONE[assicurazione - 1]};
                    res = PQexecParams(conn, query4_assured, 2, NULL, paramValues, NULL, NULL, 0);
                }
                //! FILTRO X PACCHI REGALO
                else
                {
                    //! SCELTA DEI PARAMETRI DA INSERIRE NELLA QUERY
                    int caso;
                    printf("Cosa vuoi dalla query:\n\t1. Solo tipo carta\n\t2. Solo dedica\n\t3. Entrambi\n Cosa preferisci? (1-3): ");
                    scanf("%d", &caso);
                    while (getchar() != '\n');
                    while (caso < 1 || caso > 3)
                    {
                        printf("\n Input non valido, riprova: ");
                        printf("Cosa vuoi dalla query:\n\t1. Solo tipo carta\n\t2. Solo dedica\n\t3. Entrambi\n Cosa preferisci? (1-3): ");
                        scanf("%d", &caso);
                        while (getchar() != '\n');
                    }
                    //! SOLO TIPO CARTA
                    if (caso == 1)
                    {
                        const char *query4_gift_card = "SELECT cf, count(*) "
                                              "FROM corriere as c "
                                              "JOIN pacco as p ON p.costo>$1 AND p.corriere=cf "
                                              "JOIN ( "
                                              "      SELECT b.id_bundle, COUNT(*) as n_regali "
                                              "      FROM bundle AS b "
                                              "      JOIN pacco AS p ON b.id_contenuto = p.id "
                                              "      WHERE p.tipo_carta = $2"
                                              "      GROUP BY b.id_bundle "
                                              ") as b ON p.id=b.id_bundle "
                                              "GROUP BY cf";

                        int carta;
                        printf("Scegli il tipo di carta. Le opzioni sono:\n");
                        for (int i = 0; i < 3; i++)
                        {
                            printf("\t%d. %s\n", i + 1, TIPO_CARTA[i]);
                        }
                        printf("Quale tipo vuoi? (1-3): ");
                        scanf("%d", &carta);
                        while (getchar() != '\n');
                        while (carta < 1 || carta > 3)
                        {
                            printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                            printf("Quale carta vuoi? (1-3): ");
                            scanf("%d", &carta);
                            while (getchar() != '\n');
                        }

                        const char *paramValues[2] = {
                            costo_str,
                            TIPO_CARTA[carta - 1]};
                        res = PQexecParams(conn, query4_gift_card, 2, NULL, paramValues, NULL, NULL, 0);
                    }

                    //! SOLO DEDICA
                    else if (caso == 2)
                    {
                        const char *query4_gift_dedica = "SELECT cf, count(*) "
                                              "FROM corriere as c "
                                              "JOIN pacco as p ON p.costo>$1 AND p.corriere=cf "
                                              "JOIN ( "
                                              "      SELECT b.id_bundle, COUNT(*) as n_regali "
                                              "      FROM bundle AS b "
                                              "      JOIN pacco AS p ON b.id_contenuto = p.id "
                                              "      WHERE p.dedica = $2"
                                              "      GROUP BY b.id_bundle "
                                              ") as b ON p.id=b.id_bundle "
                                              "GROUP BY cf";

                        char dedica[100];
                        printf("Inserisci la dedica: ");
                        fgets(dedica, sizeof(dedica), stdin);
                        dedica[strcspn(dedica, "\n")] = 0;

                        const char *paramValues[2] = {
                            costo_str,
                            dedica};
                        res = PQexecParams(conn, query4_gift_dedica, 2, NULL, paramValues, NULL, NULL, 0);
                    }

                    //! ENTRAMBI
                    else
                    {
                        const char *query4_gift_both = "SELECT cf, count(*) "
                                              "FROM corriere as c "
                                              "JOIN pacco as p ON p.costo>$1 AND p.corriere=cf "
                                              "JOIN ( "
                                              "      SELECT b.id_bundle, COUNT(*) as n_regali "
                                              "      FROM bundle AS b "
                                              "      JOIN pacco AS p ON b.id_contenuto = p.id "
                                              "      WHERE p.tipo_carta = $2 AND p.dedica = $3"
                                              "      GROUP BY b.id_bundle "
                                              ") as b ON p.id=b.id_bundle "
                                              "GROUP BY cf";

                        int carta;
                        printf("Scegli il tipo di carta. Le opzioni sono:\n");
                        for (int i = 0; i < 3; i++)
                        {
                            printf("\t%d. %s\n", i + 1, TIPO_CARTA[i]);
                        }
                        printf("Quale tipo vuoi? (1-3): ");
                        scanf("%d", &carta);
                        while (getchar() != '\n');
                        while (carta < 1 || carta > 3)
                        {
                            printf("\tHai scelto... molto MALE!\n\tTrovo insopportabile la sua mancanza di Input corretto\n");
                            printf("Quale carta vuoi? (1-3): ");
                            scanf("%d", &carta);
                            while (getchar() != '\n');
                        }

                        char dedica[100];
                        printf("Inserisci la dedica: ");
                        fgets(dedica, sizeof(dedica), stdin);
                        dedica[strcspn(dedica, "\n")] = 0;

                        const char *paramValues[3] = {
                            costo_str,
                            TIPO_CARTA[carta - 1],
                            dedica};
                        res = PQexecParams(conn, query4_gift_both, 3, NULL, paramValues, NULL, NULL, 0);
                    }
                }

                checkResults(res, conn);

                // Stampa i risultati
                int rows = PQntuples(res);
                int cols = PQnfields(res);
                printf("Corriere\t\tNumero pacchi\n");
                printf("--------\t\t------\n");

                printResult(rows, cols, res);
                PQclear(res);
                break;
            }

            case 5: //! QUERY 5 (NON PARAMETRIZZABILE)
            {
                const char *query5 = "SELECT t1.id_pacco, t1.status "
                                        "FROM tracking t1 "
                                        "INNER JOIN ("
                                        "    SELECT id_pacco, MAX(data_ora) as max_data_ora "
                                        "    FROM tracking "
                                        "    GROUP BY id_pacco"
                                        ") t2 ON t1.id_pacco = t2.id_pacco AND t1.data_ora = t2.max_data_ora;";
                res = PQexec(conn, query5);
                checkResults(res, conn);

                // Stampa i risultati
                int rows = PQntuples(res);
                int cols = PQnfields(res);

                printf("\nRisultati della vista ultimo_tracking:\n");
                printf("ID Pacco\t\t\tStatus\n");
                printf("--------\t\t\t------\n");

                printResult(rows, cols, res);
                PQclear(res);
                break;
            }

            default:
            {
                // This case should ideally not be reached if input validation is strict,
                // but it's good practice to have a default case for unexpected values.
                printf("Scelta non valida. Si prega di selezionare un'opzione tra 1 e 5.\n");
                break;
            }
        }
        do{
            printf("\n\nVuoi continuare? (0=si, 1=no): ");
            scanf("%d", &end);
            while (getchar() != '\n');
        } while (end < 0 || end > 1); 
    }
    printf("Grazie per aver usato il mio programma! Che l'algebra relazionale sia con te\n");
    // Pulizia e chiusura
    PQfinish(conn);

    return 0;
}
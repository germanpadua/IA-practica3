# include "AIPlayer.h"
# include "Parchis.h"

const double masinf = 9999999999.0, menosinf = -9999999999.0;
const double gana = masinf - 1, pierde = menosinf + 1;
const int num_pieces = 4;
const int PROFUNDIDAD_MINIMAX = 4;  // Umbral maximo de profundidad para el metodo MiniMax
const int PROFUNDIDAD_ALFABETA = 6; // Umbral maximo de profundidad para la poda Alfa_Beta

bool AIPlayer::move(){
    cout << "Realizo un movimiento automatico" << endl;
    
    color c_piece;
    int id_piece;
    int dice;
    think(c_piece, id_piece, dice);

    cout << "Movimiento elegido: " << str(c_piece) << " " << id_piece << " " << dice << endl;

    actual->movePiece(c_piece, id_piece, dice);
    return true;
}

void AIPlayer::think(color & c_piece, int & id_piece, int & dice) const{
    switch (id)
    {
    case 0:
        thinkPodaAlfaBeta(c_piece, id_piece, dice);
        break;
    case 4:
        thinkAleatorio(c_piece, id_piece, dice);
        break;
    case 1:
        thinkAleatorioMasInteligente(c_piece, id_piece, dice);
        break;
    case 2:
        thinkFichaMasAdelantada(c_piece, id_piece, dice);
        break;
    case 3:
        thinkMejorOpcion(c_piece, id_piece, dice);
        break;
    }
}

void AIPlayer::thinkAleatorio(color &c_piece, int &id_piece, int &dice) const
{
    // IMPLEMENTACIÓN INICIAL DEL AGENTE
    // Esta implementación realiza un movimiento aleatorio.
    // Se proporciona como ejemplo, pero se debe cambiar por una que realice un movimiento inteligente
    // como lo que se muestran al final de la función.

    // OBJETIVO: Asignar a las variables c_piece, id_piece, dice (pasadas por referencia) los valores,
    // respectivamente, de:
    // - color de ficha a mover
    // - identificador de la ficha que se va a mover
    // - valor del dado con el que se va a mover la ficha.

    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden mover para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento
    current_dices = actual->getAvailableDices(c_piece);
    // Elijo un dado de forma aleatoria.
    dice = current_dices[rand() % current_dices.size()];

    // Se obtiene el vector de fichas que se pueden mover para el dado elegido
    current_pieces = actual->getAvailablePieces(c_piece, dice);

    // Si tengo fichas para el dado elegido muevo una al azar.
    if (current_pieces.size() > 0)
    {
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
    else
    {
        // Si no tengo fichas para el dado elegido, pasa turno (la macro SKIP_TURN me permite no mover).
        id_piece = SKIP_TURN;
    }
}

void AIPlayer::thinkAleatorioMasInteligente(color &c_piece, int &id_piece, int &dice) const
{
    // El color de ficha que se va a mover
    c_piece = actual->getCurrentColor();

    // Vector que almacenará los dados que se pueden usar para el movimiento.
    vector<int> current_dices;
    // Vector que almacenará los ids de las fichas que se pueden movel para el dado elegido.
    vector<int> current_pieces;

    // Se obtiene el vector de dados que se pueden usar para el movimiento.
    current_dices = actual->getAvailableDices(c_piece);

    // En vez de elegir un dado al azar, miro primero cuáles tienen fichas que se puedan mover.
    vector<int> current_dices_que_pueden_mover_ficha;
    for (int i = 0; i < current_dices.size(); i++)
    {
        // Se obtiene el vector de fichas que se pueden mover para el dado elegido.
        current_pieces = actual->getAvailablePieces(c_piece, current_dices[i]);

        // Si se pueden mover fichas para el dado actual, lo añado al vector de dados que pueden mover fichas.
        if (current_pieces.size() > 0)
        {
            current_dices_que_pueden_mover_ficha.push_back(current_dices[i]);
        }
    }

    // Si no tengo ningún dado que pueda mover fichas, paso turno con un dado al azar ( la macro SKIP_TURN me permite no mover ).
    if (current_dices_que_pueden_mover_ficha.size() == 0)
    {
        dice = current_dices[rand() % current_dices.size()];

        id_piece = SKIP_TURN;
    }

    // En caso contrario, elijo un dado de forma aleatoria de entre los que pueden mover ficha.
    else
    {
        dice = current_dices_que_pueden_mover_ficha[rand() % current_dices_que_pueden_mover_ficha.size()];
        // Se obtiene el vector de fichas que se pueden mover para el dado elegido.
        current_pieces = actual->getAvailablePieces(c_piece, dice);
        // Muevo una ficha al azar de entre las que se pueden mover.
        id_piece = current_pieces[rand() % current_pieces.size()];
    }
}

void AIPlayer::thinkFichaMasAdelantada(color &c_piece, int &id_piece, int &dice) const
{
    // Elijo el dado haciendo lo mismo que el jugador anterior.
    thinkAleatorioMasInteligente(c_piece, id_piece, dice);
    // Tras llamar a esta función, ya tengo en dice el número de dado que quiero usar.
    // Ahora, en vez de mover una ficha al azar, voy a mover la que esté más adelantada
    // (equivalentemenete, la más cercana a la meta).

    vector<int> current_pieces = actual->getAvailablePieces(c_piece, dice);

    int id_ficha_mas_adelantada = -1;
    int min_distancia_meta = 9999;
    for (int i = 0; i < current_pieces.size(); i++)
    {
        // distanceToGoal(color, id) devuelve la disancia a la meta de la ficha [id] del color que le indique.
        int distancia_meta = actual->distanceToGoal(c_piece, current_pieces[i]);
        if (distancia_meta < min_distancia_meta)
        {
            min_distancia_meta = distancia_meta;
            id_ficha_mas_adelantada = current_pieces[i];
        }
    }

    // Si no he encontrado ninguna ficha, paso turno.
    if (id_ficha_mas_adelantada == -1)
    {
        id_piece == SKIP_TURN;
    }
    // En caso contrario, moveré la ficha más adelantada.
    else
    {
        id_piece = id_ficha_mas_adelantada;
    }
}

void AIPlayer::thinkMejorOpcion(color &c_piece, int &id_piece, int &dice) const
{
    // Vamos a mirar todos los posibles movimientos del jugador actual accediendo a los hijos del estado actual.

    // generateNextMove va iterando sobre cada hijo. Le paso la acción del último movimiento sobre
    // el que he iterado y me devolverá el siguiente. Inicialmente, cuando aún no he hecho ningún
    // movimiento, lo inicializo así.
    color last_c_piece = none; // El color de la última ficha que se movió
    int last_id_piece = -1;    // El id de la última ficha que se movió.
    int last_dice = -1;        // El dado que se usó en el último movimiento.

    // Cuando ya he recorrido todos los hijos, la función devuelve el estado actual. De esta forma puedo saber
    // cuándo paro de iterar.

    Parchis siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);

    bool me_quedo_con_esta_accion = false;

    while (!(siguiente_hijo == *actual) && !me_quedo_con_esta_accion)
    {
        if (siguiente_hijo.isEatingMove() or                                            // Si con este movimiento como ficha, o
            siguiente_hijo.isGoalMove() or                                              // Si con este movimiento llego a la meta, o
            (siguiente_hijo.gameOver() and siguiente_hijo.getWinner() == this->jugador) // Si con este movimiento gano la partida.
        )
        {
            // Me quedo con la acción actual (se almacenó en last_c_piece, last_id_piece, last_dice al llamar a generateNextMove).
            me_quedo_con_esta_accion = true;
        }
        else
        {
            // Genero el siguiente hijo.
            siguiente_hijo = actual->generateNextMove(last_c_piece, last_id_piece, last_dice);
        }
    }

    // Si he encontrado una acción que me interesa, la guardo en las variables pasadas por referencia.
    if (me_quedo_con_esta_accion)
    {
        c_piece = last_c_piece;
        id_piece = last_id_piece;
        dice = last_dice;
    }
    // Si no, muevo la ficha más adelantada como antes.
    else
    {
        thinkFichaMasAdelantada(c_piece, id_piece, dice);
    }
}

void AIPlayer::thinkPodaAlfaBeta(color &c_piece, int &id_piece, int &dice) const
{

    Poda_AlfaBeta(*actual, this->id, 0, PROFUNDIDAD_ALFABETA, c_piece, id_piece, dice, INT16_MIN, INT16_MAX, heuristica2);
}

double AIPlayer::Poda_AlfaBeta(const Parchis &actual, int jugador, int profundidad, int profundidad_max, color &c_piece, int &id_piece, int &dice, double alpha, double beta, double (*heuristic)(const Parchis &, int)) const
{

    double aux = 0;
    color last_c_piece = none; // El color de la última ficha que se movió
    int last_id_piece = -1;    // El id de la última ficha que se movió.
    int last_dice = -1;        // El dado que se usó en el último movimiento.

    if (actual.gameOver() || profundidad == profundidad_max)
    {
        return heuristic(actual, jugador);
    }

    Parchis siguiente_hijo = actual.generateNextMoveDescending(last_c_piece, last_id_piece, last_dice);

    if (jugador == actual.getCurrentPlayerId())
    {
        while (!(siguiente_hijo == actual))
        {
            aux = Poda_AlfaBeta(siguiente_hijo, actual.getCurrentPlayerId(), profundidad + 1, profundidad_max, last_c_piece, last_id_piece, last_dice, alpha, beta, heuristic);
            if (aux > alpha)
            {
                alpha = aux;
                //cout << "Actualizar ALFA" << endl;
                if (profundidad == 0)
                {
                    //cout << "NODO PADRE" << endl;
                    c_piece = last_c_piece;
                    id_piece = last_id_piece;
                    dice = last_dice;
                    break;
                }

            }

            if (beta <= alpha)
            {
                //cout << "PODA" << endl;
                break;
            }

            siguiente_hijo = actual.generateNextMoveDescending(last_c_piece, last_id_piece, last_dice);
        }
    }
    else
    {
        while (!(siguiente_hijo == actual))
        {
            aux = Poda_AlfaBeta(actual, actual.getCurrentPlayerId(), profundidad + 1, profundidad_max, last_c_piece, last_id_piece, last_dice, alpha, beta, heuristic);
            
            if (aux < beta)
            {
                beta = aux;
            }

            if (beta <= alpha)
            {
                //cout << "PODA" << endl;
                break;
            }
            siguiente_hijo = actual.generateNextMoveDescending(last_c_piece, last_id_piece, last_dice);
        }
    }

    if (jugador == actual.getCurrentPlayerId())
    {
        return alpha;
    }
    else
    {
        return beta;
    }
}

double AIPlayer::heuristica1(const Parchis &estado, int jugador){
    
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];

            
            // Reco./bin/Parchis --p1 AI 0 Random --p2 AI 1 "Random listo"rro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 10;
                }

                puntuacion_jugador = puntuacion_jugador - estado.distanceToGoal(c, j);

                if(hayFichaDistintaDetras(estado, c, estado.getBoard().getPiece(c, j))){
                    puntuacion_jugador = puntuacion_jugador - 200;
                }
            }

            puntuacion_jugador = puntuacion_jugador - estado.piecesAtHome(c)*100;

        
            if(estado.isEatingMove()){
                puntuacion_jugador += 5;
            }else if(estado.isGoalMove()){
                puntuacion_jugador += 10;
            }

            
            
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }

                puntuacion_oponente = puntuacion_oponente - estado.distanceToGoal(c, j);

                if(hayFichaDistintaDetras(estado, c, estado.getBoard().getPiece(c, j))){
                    puntuacion_oponente = puntuacion_oponente - 10;
                }
            }

            puntuacion_oponente = puntuacion_oponente - estado.piecesAtHome(c)*100;
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }

}

double AIPlayer::heuristica2(const Parchis &estado, int jugador){
    
    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];

            
            for (int j = 0; j < num_pieces; j++)
            {            
                puntuacion_jugador = puntuacion_jugador - estado.distanceToGoal(c, j);

                if(hayFichaDistintaDetras(estado, c, estado.getBoard().getPiece(c, j))){
                    puntuacion_jugador = puntuacion_jugador - 5;
                }
            }

            puntuacion_jugador = puntuacion_jugador - estado.piecesAtHome(c)*10;
            
        }

        return puntuacion_jugador;
    }

}

bool AIPlayer::hayFichaDistintaDetras(const Parchis &estado, color c, Box b){
    vector<color> colores = {red, green, yellow, blue};

    for(int i=0; i<4; i++){
        if(colores[i] != c){
            
            for(int j=0; j<estado.getBoard().getPieces(colores[i]).size(); j++){
                if(estado.getBoard().getPieces(colores[i])[j].type == normal){
                    if(estado.getBoard().getPieces(colores[i])[j].num >= (b.num - 5) && estado.getBoard().getPieces(colores[i])[j].num < (b.num))
                        return true;
                }
            }

        }
    }

    return false;


}

double AIPlayer::ValoracionTest(const Parchis &estado, int jugador)
{
    // Heurística de prueba proporcionada para validar el funcionamiento del algoritmo de búsqueda.


    int ganador = estado.getWinner();
    int oponente = (jugador + 1) % 2;

    // Si hay un ganador, devuelvo más/menos infinito, según si he ganado yo o el oponente.
    if (ganador == jugador)
    {
        return gana;
    }
    else if (ganador == oponente)
    {
        return pierde;
    }
    else
    {
        // Colores que juega mi jugador y colores del oponente
        vector<color> my_colors = estado.getPlayerColors(jugador);
        vector<color> op_colors = estado.getPlayerColors(oponente);

        // Recorro todas las fichas de mi jugador
        int puntuacion_jugador = 0;
        // Recorro colores de mi jugador.
        for (int i = 0; i < my_colors.size(); i++)
        {
            color c = my_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                // Valoro positivamente que la ficha esté en casilla segura o meta.
                if (estado.isSafePiece(c, j))
                {
                    puntuacion_jugador++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_jugador += 5;
                }
            }
        }

        // Recorro todas las fichas del oponente
        int puntuacion_oponente = 0;
        // Recorro colores del oponente.
        for (int i = 0; i < op_colors.size(); i++)
        {
            color c = op_colors[i];
            // Recorro las fichas de ese color.
            for (int j = 0; j < num_pieces; j++)
            {
                if (estado.isSafePiece(c, j))
                {
                    // Valoro negativamente que la ficha esté en casilla segura o meta.
                    puntuacion_oponente++;
                }
                else if (estado.getBoard().getPiece(c, j).type == goal)
                {
                    puntuacion_oponente += 5;
                }
            }
        }

        // Devuelvo la puntuación de mi jugador menos la puntuación del oponente.
        return puntuacion_jugador - puntuacion_oponente;
    }
}


package es.ucm.moviles.logica;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Random;
import java.util.Stack;

public class Board implements Cloneable
{
    private Tile[] _board;
    private Stack<Tile[]> _moves;
    private final int _size;

    static Random rnd = new Random();
    private static final Tile OUT_OF_BOUNDS_TILE = new Tile(-1, -1 , Tile.Kind.WALL);

    //Variables para el %

    public Board(int size)
    {
        this._size = size;
        this._board = new Tile[_size*_size];
        for (int i = 0; i < _board.length; i++)
            _board[i] = new Tile(i / _size, i % _size, Tile.Kind.UNKNOWN);

        _moves = new Stack<>();

    }
    public int getSize() { return _size;}
    public int getTilesCount() { return _size*_size;}
    public void pushMove()
    {
        Tile[] copy = new Tile[_board.length];
        for (int i = 0; i < copy.length; i++) {
            copy[i] = (Tile)_board[i].clone();
        }
        _moves.push(copy);
    }
    public void popMove()
    {
        if(_moves.empty())
        {
            //System.out.println("No hay movimentos para deshacer");
            return;
        }

        Tile[] tiles = _moves.pop();
        System.arraycopy(tiles, 0, _board, 0, tiles.length);
    }

    /**
     * Returns a string representation of the object. In general, the
     * {@code toString} method returns a string that
     * "textually represents" this object. The result should
     * be a concise but informative representation that is easy for a
     * person to read.
     * It is recommended that all subclasses override this method.
     * <p>
     * The {@code toString} method for class {@code Object}
     * returns a string consisting of the name of the class of which the
     * object is an instance, the at-sign character `{@code @}', and
     * the unsigned hexadecimal representation of the hash code of the
     * object. In other words, this method returns a string equal to the
     * value of:
     * <blockquote>
     * <pre>
     * getClass().getName() + '@' + Integer.toHexString(hashCode())
     * </pre></blockquote>
     *
     * @return a string representation of the object.
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder(_size*_size* + _size);
        for(int r = 0; r < _size; r++)
        {
            sb.append('|');
            for (int c = 0; c < _size; c++)
            {
                Tile tile = getTile(r, c);
                char x = 'E';
                switch (tile.getKind())
                {
                    case TILE: x = tile.isNumber() ? (char)('0' + tile.getNumber()) : 'O'; break;
                    case WALL:    x = 'X'; break;
                    case UNKNOWN: x = ' '; break;
                }
                sb.append(x);
                sb.append('|');
            }
            sb.append('\n');
        }

        return sb.toString();
    }

    /**
     * Genera una nueva instancia con los mismos valores que la actual
     * @return nueva instancia
     */
    @Override
    public Object clone(){

        Board copy = new Board(this._size);
        copy._board = this._board.clone();
        copy._moves = (Stack<Tile[]>) this._moves.clone();
        for(int i =0;i< this._board.length;i++){
            copy._board[i] = (Tile) this._board[i].clone();
        }
        return copy;
    }

    /**
     * Comprueba si las coordenadas dadas se encuentan dentro del tablero de juego
     * @param row La fila
     * @param col La columna
     * @return true si están dentro del tablero, false si no
     */
    private boolean inBounds(int row, int col){
        return row >= 0 && row < _size
            && col >= 0 && col < _size;
    }

    /**
     * Devuelve una tile por sus coordenadas.
     * Si las coordenadas caen fuera del tablero (<ref>inBounds</ref>)
     * se devuelve <seealso>OUT_OF_BOUNDS_TILE</seealso>
     * @param row La fila
     * @param col La columna
     * @return La tile perteneciente a las coordenadas.
     */
    Tile getTile(int row, int col)
    {
        if(!inBounds(row, col))
            return OUT_OF_BOUNDS_TILE;
        return _board[row * _size + col];
    }

    /**
     * Devuelve una Tile por su índice en en el tablero.
     * El ínice crece de izquierda a derecha, de arriba a abajo, empezando en 0
     * @param index el índice [0, this.getTilesCount())
     * @return La tile si dentro del tablero, {@code OUT_OF_BOUNDS_TILE} si no
     */
    Tile getTile(int index)
    {
        if(index < 0 || index >= _board.length)
            return OUT_OF_BOUNDS_TILE;
        return _board[index];
    }

    /**
     * Devuelve una Tile por sus coordenadas
     * @param coord Las coordenadas
     * @return La tile si dentro del tablero, {@code OUT_OF_BOUNDS_TILE} si no
     */
    Tile getTile(Coordinate coord)
    {
        //if(coord == null) throw new IllegalArgumentException();
        return getTile(coord.getRow(), coord.getCol());
    }

    /**
     * Cambia el tile a una number.
     * @param row Fila del Tile
     * @param col Columna del Tile
     * @param number el valor del number
     */
    void setTile(int row, int col, int number)
    {
        Tile tile = getTile(row, col);
        if(tile != OUT_OF_BOUNDS_TILE)
            tile.setAsTile(number);
    }

    /**
     * Cambia el tile a un tipo dado
     * @param row la fila del tile
     * @param col la columna del tile
     * @param kind El nuevo tipo del tile
     */
    void setTile(int row, int col, Tile.Kind kind)
    {
        Tile tile = getTile(row, col);
        if(tile != OUT_OF_BOUNDS_TILE)
            tile.setKind(kind);
    }

    /**
     * Cambia el tile a un tipo dado
     * @param coord Las coordenadas del tile
     * @param kind el nuevo tipo del tile
     */
    void setTile(Coordinate coord, Tile.Kind kind)
    {
        if(coord == null) throw new IllegalArgumentException();
        setTile(coord.getCol(), coord.getRow(), kind);
    }

    /**
     * Busca la siguiente Tile en una dirección
     * @param tile Tile de origen
     * @param dir La dirección en la que moverse
     * @return La siguiente Tile en la dirección {@<code>dir</code>}
     */
    Tile getNextTile(Tile tile, Coordinate dir)
    {
        return getTile(Coordinate.add(tile.getCoord(), dir));
    }

    /**
     * Devuelve la próxima Tile de un determinado tipo en una determinada dirección
     * @param tile La tile origen
     * @param dir La dirección a mirar
     * @param kind El Kind a buscar
     * @return Tile si se encuentra
     */
    Tile getNextTile(Tile tile, Coordinate dir, Tile.Kind kind)
    {
        //for(Tile aux = getNextTile(tile, dir); (aux != null) && (aux.getKind() != kind); tile = aux);
        tile =getNextTile(tile, dir);
        while( tile != null && tile.getKind() != kind){
            tile = getNextTile(tile,dir);
        }
        return tile;

    }

    /**
     * Comprueba si es estado actual del tablero representa un tablero resuelto
     * @return true si es tablero es una solución válida, false en otro caso
     */
    public boolean isSolution()
    {
        for(Tile tile : _board)
        {
            // Si queda algún undefined el tablero
            if(tile.isUndefined()) return false;
            // Si queda algún número que no vea todos sus tiles
            if(tile.isNumber() && countTiles(tile) != tile.getNumber())
                return false;
            // Si hay algún dot encerrado
            if(tile.isTile() && !tile.isNumber() && countVisibles(tile) == 0)
                return false;
        }
        return true;
    }


    /**
     * Cuenta en número de celdas que se pueden recorrer desde la celda dada
     * hasta dar con un WALL o salirse del tablero.
     * ATENCIÓN: este método cuenta la celda inicial si ésta cumple los requisitos.
     *
     * @param t La celda inicial
     * @param countTile Si el recorrido debe continuar al pasar por una celda TILE
     * @param countUndefined Si el recorrido debe continuar al pasar por una celda UNDEFINED
     * @return El número de celdas visitadas.
     */
    int count(Tile t, boolean countTile, boolean countUndefined)
    {
        return count(t.getCoord(), countTile, countUndefined);
    }
    /**
     * Cuenta en número de celdas que se pueden recorrer desde la celda dada
     * hasta dar con un WALL o salirse del tablero.
     *
     * @param c La coordenada de la celda inicial
     * @param doCountTile Si el recorrido debe continuar al pasar por una celda TILE
     * @param doCountUndefined Si el recorrido debe continuar al pasar por una celda UNDEFINED
     * @return El número de celdas visitadas.
     */
    int count(Coordinate c, boolean doCountTile, boolean doCountUndefined)
    {
        Tile tile = getTile(c);
        if(tile == null || tile.isWall()) return 0;

        return count(c,    Coordinate.UP, doCountTile, doCountUndefined)
             + count(c,  Coordinate.DOWN, doCountTile, doCountUndefined)
             + count(c, Coordinate.RIGHT, doCountTile, doCountUndefined)
             + count(c,  Coordinate.LEFT, doCountTile, doCountUndefined);
    }

    /**
     * Cuenta en número de celdas que se pueden recorrer desde la celda dada
     * hasta dar con un WALL en la dirección dada.
     *
     * @param t La Tile inicial
     * @param dir La dirección en la que contar
     * @param doCountTile Si el recorrido debe continuar al pasar por una celda TILE
     * @param doCountUndefined Si el recorrido debe continuar al pasar por una celda UNDEFINED
     * @return El número de celdas visitadas.
     */
    int count(Tile t, Coordinate dir, boolean doCountTile, boolean doCountUndefined)
    {
        return count(t.getCoord(), dir, doCountTile, doCountUndefined);
    }

    /**
     * Cuenta en número de celdas que se pueden recorrer desde la celda dada
     * hasta dar con un WALL en la dirección dada.
     *
     * @param c La coordenada de la celda inicial
     * @param dir La Dirección en la que contar
     * @param doCountTile Si el recorrido debe continuar al pasar por una celda TILE
     * @param doCountUndefined Si el recorrido debe continuar al pasar por una celda UNDEFINED
     * @return El número de celdas visitadas.
     */
    int count(Coordinate c, Coordinate dir, boolean doCountTile, boolean doCountUndefined)
    {
        Tile tile = getTile(c);
        if(tile == null || tile.isWall()) return 0;

        int counter = 0;
        for(tile = getNextTile(tile, dir); tile != null && !tile.isWall(); tile = getNextTile(tile, dir))
            if((doCountTile && tile.isTile())
            || (doCountUndefined && tile.isUndefined()))
                counter++;
        return counter;
    }

    /**
     * Cuenta el número de Tiles visibles desde la Tile dada en una dirección dada
     * @param t La Tile inicial
     * @param dir La dirección en la que mirar
     * @return El número de tiles visibles
     */
    int countTiles(Tile t, Coordinate dir){return countTiles(t.getCoord(), dir);}
    /**
     * Cuenta el número de Tiles visibles desde la Tile dada en una dirección dada
     * @param c La coordenada de la Tile inicial
     * @param dir La dirección en la que mirar
     * @return El número de tiles visibles
     */
    int countTiles(Coordinate c, Coordinate dir)
    {
        return count(c, dir, true, false);
    }
    /**
     * Cuenta el número de Tiles visibles desde la Tile dada
     * @param tile La Tile inicial
     * @return El número de tiles visibles
     */
    int countTiles(Tile tile){ return countTiles(tile.getCoord());}
    /**
     * Cuenta el número de Tiles visibles desde la Tile dada
     * @param c La coordenada de la Tile inicial
     * @return El número de tiles visibles
     */
    int countTiles(Coordinate c)
    {
        return count(c, true, false);
    }

    /**
     * Cuenta el numero de celdas visibles desde una tile en una dirección dada.
     * Cuenta UNDEFINED, TILES y NUMBERS
     * @param t la tile de origen
     * @param dir la dirección en la que mirar
     * @return el número de celdas visibles
     */
    int countVisibles(Tile t, Coordinate dir) { return countVisibles(t.getCoord(), dir);}
    /**
     * Cuenta el numero de celdas visibles desde una tile en una dirección dada.
     * Cuenta UNDEFINED, TILES y NUMBERS
     * @param c La coordenada de la tile de origen
     * @param dir la dirección en la que mirar
     * @return el número de celdas visibles
     */
    int countVisibles(Coordinate c, Coordinate dir)
    {
        return count(c, dir,true, true);
    }
    /**
     * Cuenta el numero de celdas visibles desde una tile.
     * Cuenta UNDEFINED, TILES y NUMBERS
     * @param tile la tile de origen
     * @return el número de celdas visibles
     */
    int countVisibles(Tile tile) {return countVisibles(tile.getCoord());}
    /**
     * Cuenta el numero de celdas visibles desde una tile.
     * Cuenta UNDEFINED, TILES y NUMBERS
     * @param c las coordenadas de la tile de origen
     * @return el número de celdas visibles
     */
    int countVisibles(Coordinate c)
    {
        return count(c, true, true);
    }

    /**
     * Cuenta en número de celdas del tipo dado contiguas a la celda inical en una dirección dada
     * @param tile El tile inicial
     * @param kind el tipo de las celdas
     * @param dir la direccion en la que contar
     * @return el número de celdas de tipo dado contiguas a {@code tile}
     */
    int countContiguous(Tile tile, Tile.Kind kind, Coordinate dir)
    {
        int counter = 0;
        for(tile = getNextTile(tile, dir); tile.getKind() == kind; tile = getNextTile(tile, dir))
            counter++;
        return counter;
    }

    /**
     * Cuenta en número de celdas del tipo dado contiguas a la celda inical
     * @param tile El tile inicial
     * @param kind el tipo de las celdas
     * @return el número de celdas de tipo dado contiguas a {@code tile}
     */
    int countContiguous(Tile tile, Tile.Kind kind)
    {
        int n = 0;
        for(Coordinate dir : Coordinate.DIRECTIONS)
            n += countContiguous(tile, kind, dir);
        return n;
    }

    /**
     * Devuele las últimas celdas no tile desde una coordenada en cada dirección
     * @param c La coordenada desde la que mirar
     * @return
     */
    Tile[] getEdges(Coordinate c)
    {
        Tile[] edges = new Tile[4];
        for(int i = 0; i < 4; i++)
        {
            Tile tile = getTile(c);
            while(tile.isTile())
                tile = getNextTile(tile, Coordinate.DIRECTIONS[i]);
            edges[i] = tile;
        }
        return edges;
    }


    /**
     * Comprueba si una tile dada se puede cerrar (Pista 1)
     * @param tile la tile sobre la que mirar
     * @return true si la tile se puede cerrar, false si no
     */
    boolean canBeClosed(Tile tile)
    {
        if(tile == null) throw new IllegalArgumentException();
        if(!tile.isNumber()) return false;

        Coordinate c = tile.getCoord();
        boolean isCandidate = tile.getNumber() == countContiguous(tile, Tile.Kind.TILE);

        if(isCandidate)
        {
            for (Tile edge: getEdges(c))
            {
                if(edge != null && edge.isUndefined())
                    return true;
            }
        }
        return false;
    }

    /**
     * Comprueba si una tile debe ser muro (Pista 2)
     * @param tile La Tile a comprobrar
     * @return La tile que debe ser muro
     */
    Tile mustBeWall(Tile tile)
    {
        if(tile == null) throw new IllegalArgumentException();
        if(!tile.isUndefined()) return null;

        Tile res = null;

        tile.setAsTile();
        for(Tile t : _board)
            if(t.isTile() && t.isNumber() && countTiles(t) > t.getNumber())
            {
                res = t;
                break;
            }
        tile.setAsUndefined();
        return res;
    }

    /**
     * Buscamos si encontramos un UNDEFINED que deba ser TILE
     * @param tile una tile tipo Numero
     * @return el Tile que cumpla la condicion, null si no se encuentra
     */
    Tile mustBeTile(final Tile tile)
    {
        if(tile == null) throw new IllegalArgumentException();
        if(!tile.isNumber()) return null;

        class Count
        {
            Count(int v, int t)
            {
                visibles = v;
                tiles = t;
                undefined = v - t;
            }

            final int visibles;
            final int tiles;
            final int undefined;
        }
        Count[] counts = new Count[Coordinate.DIRECTIONS.length];
        int n = tile.getNumber();

        for (int i = 0; i < Coordinate.DIRECTIONS.length; i++) {
            counts[i] = new Count(
                countVisibles(tile, Coordinate.DIRECTIONS[i]),
                countTiles   (tile, Coordinate.DIRECTIONS[i])
            );
            n -= counts[i].tiles;
        }

        Coordinate dir = Coordinate.ZERO;

        for (int i = 0; i < Coordinate.DIRECTIONS.length; i++)
        {
            int sum = counts[(i + 1) % Coordinate.DIRECTIONS.length].undefined
                    + counts[(i + 2) % Coordinate.DIRECTIONS.length].undefined
                    + counts[(i + 3) % Coordinate.DIRECTIONS.length].undefined;
            if(counts[i].undefined > 0 && sum <= n)
            {
                dir = Coordinate.DIRECTIONS[i];
            }
        }

        if(!dir.equals(Coordinate.ZERO))
        {
            Coordinate c = Coordinate.add(tile.getCoord(), dir);
            while(!getTile(c).isUndefined()) c.add(dir);
            return getTile(c);

        }

        return null;
    }

    /**
     * Comprueba si una tile está cerrada
     * @param tile La tile a comprobar
     * @return true si está cerrada, false si no
     */
    boolean isClosed(Tile tile)
    {
        for(Coordinate dir : Coordinate.DIRECTIONS)
        {
            while(!(tile = getNextTile(tile, dir)).isWall())
                if(tile.isUndefined()) return false;
        }
        return true;
    }


    /**
     * Comprueba si la tile ve demasiados dots
     * @param tile la tile a comprobar
     * @return true si ve demasiados, false si no
     */
    boolean errorTooManyTiles(Tile tile)
    {
        if(tile == null) throw new IllegalArgumentException();
        if(!tile.isNumber()) return false;

        int v = countContiguous(tile, Tile.Kind.TILE);
        return v > tile.getNumber();
    }

    /**
     * Comproeba si la tile no ve suficientes tiles
     * @param tile La tile a comprobar
     * @return true si la tile no ve suficientes, false si no
     */
    boolean errorNotEnoughTiles(Tile tile)
    {
        if(tile == null) throw new IllegalArgumentException();
        if(!tile.isNumber()) return false;

        int v = countVisibles(tile);
        return v < tile.getNumber();
    }

    /**
     * Comprueba si una tile que está cerrada debería ser un muro
     * @param tile La tile a comprobar
     * @return true si la tile tile que está cerrada debería ser un muro, false si no
     */
    boolean closedMustBeWall(Tile tile)
    {
        if(tile == null) throw new IllegalArgumentException();
        if(tile.isWall() || tile.isNumber()) return false;

        Coordinate c = tile.getCoord();
        Tile u = getTile(Coordinate.add(c, Coordinate.UP));
        Tile d = getTile(Coordinate.add(c, Coordinate.DOWN));
        Tile r = getTile(Coordinate.add(c, Coordinate.RIGHT));
        Tile l = getTile(Coordinate.add(c, Coordinate.LEFT));

        return  (u == null || u.isWall())
            &&  (d == null || d.isWall())
            &&  (r == null || r.isWall())
            &&  (l == null || l.isWall());
    }

    /**
     * Ejecuta una pista sobre el tablero actual
     * @param tip La pista a ejecutar
     */
    void execute(Tip tip)
    {
        if(tip == null) return;
        Tile tile = tip.getTile();

        switch (tip.getKind()) {
            case CAN_BE_CLOSED:
                closeTile(tile);
                break;
            case MUST_BE_WALL:
                for(Tile t : getEdges(tile.getCoord())){
                    if(t.isUndefined()){
                        t.setAsTile();
                        int visibles = countVisibles(tile);
                        if(visibles > tile.getNumber()){
                            t.setAsWall();
                            break;
                        }
                    }
                }
                tile.setAsWall();
                break;
            case MUST_BE_TILE:
                tile.setAsTile();
                break;
            case CLOSED_MUST_BE_WALL:
                tile.setAsWall();
            // El ejecutor no pude cometer errores
            case ERROR_TOO_MANY_TILES:
            case ERROR_NOT_ENOUGH_TILES_BUT_CLOSED:
            case ERROR_NOT_ENOUGH_TILES_BUT_OPEN:
                break;
        }

    }

    /**
     * Busca todas las psitas posibles sobre el tablero actual
     * @return La lista de posibles pistas. La lsita puede estar vacía.
     */
    List<Tip> getTips()
    {
        List<Tip> tips = new ArrayList<>();
        for(Tile tile : _board)
        {
            Tile arg;
            /**/ if(canBeClosed(tile)) // #1
                tips.add(new Tip(Tip.Kind.CAN_BE_CLOSED, tile));
            else if((arg = mustBeWall(tile)) != null) // #2
                tips.add(new Tip(Tip.Kind.MUST_BE_WALL, arg));
            else if((arg = mustBeTile(tile)) != null) // #3
                tips.add(new Tip(Tip.Kind.MUST_BE_TILE, arg));
            else if(closedMustBeWall(tile)) //
                tips.add(new Tip(Tip.Kind.CLOSED_MUST_BE_WALL, tile));
            else if(errorTooManyTiles(tile)) // #4
                tips.add(new Tip(Tip.Kind.ERROR_TOO_MANY_TILES, tile));
            else if(errorNotEnoughTiles(tile))
            {
                if(isClosed(tile))
                    tips.add(new Tip(Tip.Kind.ERROR_NOT_ENOUGH_TILES_BUT_CLOSED, tile));
                else tips.add(new Tip(Tip.Kind.ERROR_NOT_ENOUGH_TILES_BUT_OPEN, tile));
            }

        }
        //MAYBE: limpiar Tips repetidas (¿?)

        return tips;
    }

    /**
     * Selecciona una pista aleatoria sobre todas las posibles sobre el tablero actual
     * @return Un pista aleatoria, null si no hay ninguna
     */
    public Tip pickTip()
    {
        List<Tip> tips = getTips();
        if(tips.size()== 0)
            return null;
        return tips.get(new Random().nextInt(tips.size()));
    }

    /**
     * Cierra una tile en una dirección
     * @param tile La tile a cerrar
     * @param dir la dirección a cerrar
     */
    private void closeTile(Tile tile, Coordinate dir)
    {
        Tile t = getNextTile(tile, dir);
        while(!t.isUndefined())
            t = getNextTile(tile, dir);
        t.setAsWall();
    }

    /**
     * Cierra una tile
     * @param tile la tile a cerrar
     */
    private void closeTile(Tile tile)
    {
        Tile[] edges = getEdges(tile.getCoord());
        for (Tile edge : edges) {
            if(edge != null)
                edge.setAsWall();
        }
    }

    /**
     * Genera un nuevo tablero puzzle
     * @param size el tamaño del tablero cuadrado (size * size)
     * @return Un nuevo tablero solución
     */
    static Board generate(int size)
    {
        //System.out.println("Generando tablero");
        //Random rnd = new Random(69);
        Board board = new Board(size);
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                // Al principio todas se ven entre si
                board.setTile(i, j, 2* (size-1));


        int rr = rnd.nextInt(board.getSize());
        int rc = rnd.nextInt(board.getSize());

        board.setTile(rr, rc, Tile.Kind.WALL);


        int max = -1;
        Tile maxView = board.getTile(0,0);
        for(Tile tile : board._board)
        {
            if(tile.getKind() != Tile.Kind.WALL) {
                int visibles = board.countVisibles(tile);
                tile.setAsTile(visibles);
                if (max < visibles) {
                    max = visibles;
                    maxView = tile;
                }
            }
        }

        //System.out.println("El primer max es: " + maxView.getCoord());

        int iteration = 1;
        while(max > size)
        {
            //System.out.printf("%d.============================= (max = %d)\n", iteration++, max);

            List<Coordinate> possibleDirection = new ArrayList<>(4);
            for(Coordinate dir : Coordinate.DIRECTIONS)
            {
                Tile t = board.getTile(Coordinate.add(dir, maxView.getCoord()));
                if(t != null && !t.isWall())
                    possibleDirection.add(dir);
            }
            //System.out.println("Direcciones posibles: " + possibleDirection.size());

            int visiblesInDir = Integer.MAX_VALUE;
            Coordinate dir = Coordinate.ZERO;
            do
            {
                dir = possibleDirection.get(rnd.nextInt(possibleDirection.size()));
                visiblesInDir = board.countVisibles(maxView, dir);
                possibleDirection.remove(dir);
            }while(visiblesInDir <= 0);

            int distance = visiblesInDir == 1 ? 1 : 1 + rnd.nextInt(visiblesInDir -1);
            Coordinate newWallCoord = Coordinate.add(maxView.getCoord(), Coordinate.mult(dir, distance));

            /*System.out.printf("Direccion escogida: %s\nPosicion escogida %s%n",
                    dir.toString(),
                    newWallCoord.toString());
            */
            Tile newWall = board.getTile(newWallCoord);
            newWall.setAsWall();

            //System.out.println("Buscando nuevo máximo");
            max = -1;
            for(Tile tile : board._board)
            {
                if(tile.getKind() != Tile.Kind.WALL) {
                    int visibles = board.countVisibles(tile);
                    tile.setAsTile(visibles);
                    if (max < visibles) {
                        max = visibles;
                        maxView = tile;
                    }
                }
            }
            //System.out.printf("Nuevo máximo: %s (%d)\n", maxView.toString(), max);
            //System.out.flush();
            //System.out.println("Estado del tablero:\n" + board.toString());
            //System.out.flush();
        }


        board.removeDots();
        board = breakdownBoard(board);

        // Lock all undefined for presenting puzzle to the user
        for(Tile tile : board._board)
            if(!tile.isUndefined())
                tile.lock();
        return board;
    }

    /**
     * Transforma todos los tiles que no sean Number en Wall
     */
    private void removeDots(){
        for(Tile tile : _board) {
            if(tile.isTile() && !tile.isNumber())
                tile.setAsWall();
        }
    }

    /**
     * Coloca Tiles de tipo UNDEFINED sobre un tablero solución para transformarmo en un tablero puzzle
     * @param board el tablero solución
     * @return Una instancia de Board con un tablero puzzle
     */
    static private Board breakdownBoard(Board board) {

        Board solutionBoard =(Board) board.clone();
        //BoardStack stack = new BoardStack();
        Stack<Board> stack = new Stack<>();
        List<Tip> tips = new ArrayList();
        float minWallsPerc = 0.4f;
        float minTilesPerc = 0.4f;
        int tiles =0;
        int walls =0;


        List<Integer> indexes = new ArrayList<>(board._board.length);
        for (int i = 0; i < board._board.length; i++) indexes.add(i);

        //Shuffle indexes
        for (int i = 0; i < indexes.size(); i++)
        {
            Tile tile = board.getTile(i);
            if(tile.isTile()) tiles++;
            else walls++;

            int j = rnd.nextInt(indexes.size());

            int aux = indexes.get(i);
            indexes.set(i, indexes.get(j));
            indexes.set(j, aux);
        }

        int minWalls = (int)(((float)walls) * minWallsPerc);
        int minTiles = (int)(((float)tiles) * minTilesPerc);

        int attemps = 0;
        while(indexes.size() > 0 && attemps++ < 99)
        {
            stack.push((Board) board.clone());

            Tile tile = board.getTile(indexes.get(0));
            indexes.remove(0);
            boolean isWall = tile.isWall();
            boolean isTile = tile.isTile();


            if((isWall && walls <= minWalls) ^ (isTile && tiles <= minTiles))
                continue;
            if (walls <= minWalls && tiles <= minTiles)
                break;

            tile.setAsUndefined();
            stack.push((Board) board.clone());
            //boolean hasSolution = board.solve();
            boolean hasSolution = board.trySolve();
            boolean isSameSolution = hasSolution && solutionBoard.similarSolution(board);
            board = stack.pop();

            if(isSameSolution)
            {
                if(isWall) walls--;
                if(isTile) tiles--;
                //tips.add(tip);
                //stack.pop(board);
            }
            else
            {
                board = stack.pop();
            }


            //System.out.printf("Breaking board: %d\n", attemps);
            //System.out.printf("MinWalls: %d Walls: %d\n", minWalls, walls);
            //System.out.printf("MinTiles: %d Tiles: %d\n", minTiles, tiles);
            //System.out.println(board);
            //System.out.flush();
        }

        return board;
    }

    /**
     * Indicates whether some other object is "equal to" this one.
     * <p>
     * The {@code equals} method implements an equivalence relation
     * on non-null object references:
     * <ul>
     * <li>It is <i>reflexive</i>: for any non-null reference value
     *     {@code x}, {@code x.equals(x)} should return
     *     {@code true}.
     * <li>It is <i>symmetric</i>: for any non-null reference values
     *     {@code x} and {@code y}, {@code x.equals(y)}
     *     should return {@code true} if and only if
     *     {@code y.equals(x)} returns {@code true}.
     * <li>It is <i>transitive</i>: for any non-null reference values
     *     {@code x}, {@code y}, and {@code z}, if
     *     {@code x.equals(y)} returns {@code true} and
     *     {@code y.equals(z)} returns {@code true}, then
     *     {@code x.equals(z)} should return {@code true}.
     * <li>It is <i>consistent</i>: for any non-null reference values
     *     {@code x} and {@code y}, multiple invocations of
     *     {@code x.equals(y)} consistently return {@code true}
     *     or consistently return {@code false}, provided no
     *     information used in {@code equals} comparisons on the
     *     objects is modified.
     * <li>For any non-null reference value {@code x},
     *     {@code x.equals(null)} should return {@code false}.
     * </ul>
     * <p>
     * The {@code equals} method for class {@code Object} implements
     * the most discriminating possible equivalence relation on objects;
     * that is, for any non-null reference values {@code x} and
     * {@code y}, this method returns {@code true} if and only
     * if {@code x} and {@code y} refer to the same object
     * ({@code x == y} has the value {@code true}).
     * <p>
     * Note that it is generally necessary to override the {@code hashCode}
     * method whenever this method is overridden, so as to maintain the
     * general contract for the {@code hashCode} method, which states
     * that equal objects must have equal hash codes.
     *
     * @param obj the reference object with which to compare.
     * @return {@code true} if this object is the same as the obj
     * argument; {@code false} otherwise.
     * @see #hashCode()
     * @see HashMap
     */
    @Override
    public boolean equals(Object obj) {
        if(obj == null) return false;
        if(obj.getClass() != this.getClass()) return false;
        return equals((Board)obj);
    }

    /**
     * Equality comparator
     * @param other Another instance
     * @return true if they are exactly equals, false of not
     */
    public boolean equals(Board other)
    {
        if(this._size != other._size) return false;
        for(int i = 0; i < this._board.length; i++)
        {
            if(!this._board[i].equals(other._board[i]))
                return false;
        }
        return true;
    }

    /**
     * Comprueba que un tablero sea equivalente a otro, esto es:
     * Solamente teniendo en cuenta que las tiles sean del mismo Tile.Kind
     * @param other Otra instancia
     * @return true si son equivalentes, false si no
     */
    public boolean similarSolution(Board other){
        if(this._size != other._size) return false;
        for(int i = 0; i < this._board.length; i++)
        {
            if(this._board[i].getKind() != other._board[i].getKind())
                return false;
        }
        return true;
    }

    public boolean trySolve()
    {
        int attemps = 0;
        int maxAttemps = (int)Math.pow(_size, 4);
        boolean isSolved = false;
        while(!isSolved && attemps++ < maxAttemps)
        {
            List<Tip> tips = getTips();
            List<Tip> toRemove = new ArrayList<>();
            for(Tip tip : tips)
                if(tip.isError())
                    toRemove.add(tip);
            for(Tip tip : toRemove)
                tips.remove(tip);

            if(tips.size() == 0)return false;
            Tip tip = tips.get(rnd.nextInt(tips.size()));
            execute(tip);
            isSolved = isSolution();

            //System.out.printf("Attemp %d: Tip: %s is solution: %s\n", attemps, tip, isSolved);
            //System.out.println(this);
        }
        return isSolved;
    }
}

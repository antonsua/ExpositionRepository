package es.ucm.moviles.logica;

import java.util.ArrayList;
import java.util.List;

import es.ucm.moviles.engineinterface.GraphicsInterface;
import es.ucm.moviles.engineinterface.Position;
import es.ucm.moviles.engineinterface.TouchEvent;

public class BoardObj extends GameObject
{
    public interface BoardObserver{
        void onTileClicked(Tile tile);
        void onTileChanged(Tile tile);

    }

    Board _board;
    List<TileObj> _tiles;
    List<BoardObserver> _observers;
    static final int BOARD_WIDTH  = 400;
    static final int BOARD_HEIGHT = 600;
    static final float CIRCLE_MARGIN_PERCENTAGE = 0.9f;
    static final int BOARD_OFFSET_V = 110;
    static final int BOARD_OFFSET_H = 10;
    static final float TILE_CHANGE_COLOR_DURATION = 0.3f;

    float tileSize;
    //Necesario para quitar el texto de las pistas en GameplayScene
    boolean unselectedTileButNotNoticed = false;
    //Necesario para el % de completado
    int undefinedAtStart;
    int currentUndefined;



    public BoardObj(int boardSize)
    {

        float w = ((float)BOARD_WIDTH*0.95f)/(float) boardSize;
        int tileW = (int)Math.floor(w);
        int tileR = (int)Math.floor(w *0.5f * CIRCLE_MARGIN_PERCENTAGE);

        tileSize = ((float)tileW * 0.9f);
        undefinedAtStart =0;
        currentUndefined =0;
        _board = Board.generate(boardSize);
        _tiles = new ArrayList<>(boardSize*boardSize);
        for (int r = 0; r < boardSize; r++) {
            for (int c = 0; c < boardSize; c++) {

                Position pos = new Position
                (
                    (tileW * c + (tileW / 2)) + BOARD_OFFSET_H,
                    (tileW * r + (tileW / 2)) + BOARD_OFFSET_V
                );
                Tile t = _board.getTile(r,c);
                if(t.getKind() == Tile.Kind.UNKNOWN)
                    undefinedAtStart++;
                _tiles.add(new TileObj(this, t, pos, tileW, tileR, TILE_CHANGE_COLOR_DURATION));
            }
        }
        currentUndefined = undefinedAtStart;
    }



    public void undoMove()
    {
        int aux =0;
        _board.popMove();
        for(int i = 0; i < _board.getTilesCount(); i++)
        {
            TileObj tile = _tiles.get(i);
            tile.setTile(_board.getTile(i));
            if(tile.isUndefined()) aux++;

        }
        currentUndefined= aux;
    }

    public void selectTile(Tile tile)
    {
        for(TileObj tileObj : _tiles)
            if(tileObj._tile.equals(tile))
                tileObj.setSelected(true);
    }

    public void unselectTiles()
    {
        for(TileObj tileObj : _tiles)
            tileObj.setSelected(false);
    }

    @Override
    public void update(float deltaTime)
    {
        for (TileObj tile : _tiles)
            tile.update(deltaTime);
    }

    @Override
    public void render(GraphicsInterface g)
    {
        g.setFontSize(tileSize);
        for(TileObj tile : _tiles)
            tile.render(g);

    }

    @Override
    void handleEvent(TouchEvent e) {
        for(TileObj tile : _tiles)
            tile.handleEvent(e);
    }

    public Tip getTip()
    {
        return _board.pickTip();
    }

    public boolean isSolved()
    {
        boolean anyTileAnimating = false;
        for(TileObj tile : _tiles)
            if(tile.animationPlaying())
            {
                anyTileAnimating = true;
                break;
            }
        return !anyTileAnimating && _board.isSolution();
    }

    public void onTileChanged(Tile t){
        if(t.isUndefined())
            currentUndefined++;
        else if(t.isTile())
            currentUndefined--;

        for(BoardObserver obs : _observers)
            obs.onTileChanged(t);

    }
    public void onTileClicked(TileObj tile)
    {
        if(tile.isLocked())
        {
            if(tile.isWall())
            {
                for (TileObj t : _tiles) {
                    if(t.isLocked() && t.isWall())
                        t.beginTwitchAnimation();
                }
            }
            else
            {
                tile.beginTwitchAnimation();
            }
        }
        else
        {
            _board.pushMove();
            tile.beginTransitionAnimation();
        }

        //System.out.println("Tile clicked");
        //Necesario para quitar texto de pistas
        if(tile.getSelected())
            unselectedTileButNotNoticed = true;
        unselectTiles();

        for(BoardObserver obs : _observers){
            obs.onTileClicked(tile._tile);
        }

    }
    public void addObserver(BoardObserver obs){
        assert obs != null;
        if(_observers== null)
            _observers = new ArrayList<>();

        _observers.add(obs);
    }


}

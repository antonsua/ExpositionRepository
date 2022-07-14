package es.ucm.moviles.logica;

import java.util.Stack;

public class BoardStack
{
    private final Stack<int[]> _stack;

    private static final int WALL = -2;
    private static final int UNKNOWN = -1;
    private static final int DOT = 0;


    public BoardStack()
    {
        _stack = new Stack<>();
    }
    public void push(Board board)
    {
        int size = board.getSize();
        int[] values = new int[size* size];
        for(int r = 0; r < size; r++)
            for(int c = 0; c < size; c++)
            {
                Tile tile = board.getTile(r, c);
                int index = r * size + c;
                switch (tile.getKind())
                {
                    case UNKNOWN:
                    values[index] = UNKNOWN;
                        break;
                    case WALL:
                    values[index] = WALL;
                        break;
                    case TILE:
                    values[index] = tile.isNumber() ? tile.getNumber() : DOT;
                    break;
                }

            }
        _stack.push(values);
    }
    public boolean pop(Board board)
    {
        int size = board.getSize();
        if(_stack.empty()) return false;
        int[] values = _stack.pop();
        for(int r = 0; r < size; r++)
            for(int c = 0; c < size; c++)
            {
                int v = values[r * size + c];
                switch (v){
                    case WALL: board.setTile(r, c, Tile.Kind.WALL); break;
                    case UNKNOWN: board.setTile(r, c, Tile.Kind.UNKNOWN); break;
                    case DOT: board.setTile(r, c, Tile.Kind.TILE);
                    default /*NUMBER*/: board.setTile(r, c, v); break;

                }
            }
        return true;
    }
}

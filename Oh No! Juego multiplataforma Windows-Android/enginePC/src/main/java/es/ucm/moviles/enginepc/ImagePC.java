package es.ucm.moviles.enginepc;


// Import de metodos de carga de archivos e imagenes
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

// Import de la clase que almacenará la imagen
import java.awt.image.BufferedImage;

// Import de la interfaz
import es.ucm.moviles.engineinterface.ImageInterface;

public class ImagePC implements ImageInterface
{
    // Variables internas
    BufferedImage _img;

    /**
     * Constructora
     */
    void ImagePC(){}

    /* -------------------------------------
     * Getters
     * -------------------------------------
     */
    /**
     * Metodo para obtener la imagen en formato adecuado para el graphicsPC.
     * Llamado en exclusiva desde la parte implentada en PC.
     * @return BufferedImage
     */
    public BufferedImage getBuffImage()
    {
        return _img;
    }

    /* -------------------------------------
     * Metodos Heredados
     * -------------------------------------
     */
    /**
     * Devuelve el ancho de la imagen en int (pixeles)
     */
    @Override
    public int getWidth() {
        return _img.getWidth();
    }

    /**
     * Devuelve el alto de la imagen en int (pixeles)
     */
    @Override
    public int getHeight() {
        return _img.getHeight();
    }

    /**
     * Carga en memoria una imagen desde un archivo.
     * Este metodo no debería devolver nada, la lógica no tiene por que
     * utilizar las imagenes como tal, ya se encargará el motor de pintado de
     * hacer con ella lo que necesite.
     * @param filePath
     */
    public void loadImageFile(String filePath) {
        //System.out.println("ImagePC::loadImageFile() Cargando: " + filePath);
        try
        {
            _img = ImageIO.read(new File(filePath));
        }
        catch (IOException e)
        {
            System.err.println("ImagePC::loadImageFile() ERROR - La imagen " + filePath + " no ha podido ser cargada.");
        }
    }
}

package es.ucm.moviles.androidEngine;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.Image;

import java.io.IOException;
import java.io.InputStream;

import es.ucm.moviles.engineinterface.ImageInterface;

public class ImageAndroid implements ImageInterface
{
    // Agregar el tipo de variable que maneja imagenes en Android

    Bitmap _bmImg;
    // Meter un getter de la variable de imagen de Android para el motor

    public Bitmap getBitmapImage()
    {
        return _bmImg;
    }


    public void loadAndroidImage(String fi1eName, Context c){
        try (InputStream is = c.getAssets().open(fi1eName))
        {
            _bmImg = BitmapFactory.decodeStream(is);
        }
        catch (IOException e)
        {
            android.util.Log.e("MainActivity", "Error leyendo la imagen");
        }
    }
    @Override
    public int getWidth() {
        return _bmImg.getWidth();
    }

    @Override
    public int getHeight() {
        return _bmImg.getHeight();
    }

}

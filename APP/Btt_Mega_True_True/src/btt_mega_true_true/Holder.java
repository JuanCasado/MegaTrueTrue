/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

import static java.lang.Thread.NORM_PRIORITY;
import java.util.concurrent.LinkedBlockingQueue;
import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.geom.Rectangle;

/**
 *
 * @author mr.blissfulgrin
 */
public class Holder extends Scene implements Clickable{
    public static enum MODO {FULL,HD,HI,Q1,Q2,Q3,Q4};
    public static enum TIPO {Botonera,Colector,Grafica,Display,Void};
    private Rectangle background;
    private final float margenX = Size.Xp*20;
    private final float margenY = Size.Yp*20;
    private final MODO modo;
    private TIPO tipo;
    private final Bluetooth bluetooth;
    private int finalSize;
    
    private final LinkedBlockingQueue <Button> botonera;
    private final LinkedBlockingQueue <Button> colector;
    private final LinkedBlockingQueue <DatoGrafico> graficos;
    private final LinkedBlockingQueue <Label> label;
    
    
    public Holder (MODO modo, Bluetooth bluetooth){
        super(STATE.ON,0);
        this.modo = modo;
        this.tipo = TIPO.Void;
        botonera = new LinkedBlockingQueue<>();
        colector = new LinkedBlockingQueue<>();
        graficos = new LinkedBlockingQueue<>();
        label = new LinkedBlockingQueue<>();
        this.bluetooth = bluetooth;
    }
    @Override
    public String toString() {
        return "Holder "+modo.toString()+" "+tipo.toString();
    }

    @Override
    public void Render(GameContainer gc, Graphics g) throws SlickException {
        g.setColor(Color.cyan);
        if (background != null)
            g.fill(background);
    }

    @Override
    public void Update(GameContainer gc, float t) throws SlickException {
    }

    @Override
    public void init(GameContainer gc) throws SlickException {
        switch (modo){
            case FULL:
                background = new Rectangle(margenX,margenY*3,Size.X-margenX*2,Size.Y-margenY*5);
                break;
            case HI:
                background = new Rectangle(margenX,margenY*3,Size.X/2-margenX*2,Size.Y-margenY*5);
                break;
            case HD:
                background = new Rectangle(Size.X/2+margenX,margenY*3,Size.X/2-margenX*2,Size.Y-margenY*5);
                break;
            case Q1:
                background = new Rectangle(margenX,margenY*3,Size.X/2-margenX*2,Size.Y/2-margenY*5);
                break;
            case Q2:
                background = new Rectangle(Size.X/2+margenX,margenY*3,Size.X/2-margenX*2,Size.Y/2-margenY*5);
                break;
            case Q3:
                background = new Rectangle(margenX,Size.Y/2+margenY,Size.X/2-margenX*2,Size.Y/2-margenY*3);
                break;
            case Q4:
                background = new Rectangle(Size.X/2+margenX,Size.Y/2+margenY,Size.X/2-margenX*2,Size.Y/2-margenY*3);
                break;
        }
    }
    @Override
    public void click(float x, float y) {
        if(background.contains(x, y)){
            switch(tipo){
                case Botonera:
                    botonera.forEach((boton)->{
                        boton.click(x, y);
                    });
                    break;
                case Colector:
                    colector.forEach((colect)->{
                        colect.click(x, y);
                    });
                    break;
            }
        }
    }

    @Override
    public void release(float x, float y) {
        if(background.contains(x, y)){
            switch(tipo){
                case Botonera:
                    botonera.forEach((boton)->{
                        boton.release(x, y);
                    });
                    break;
                case Colector:
                    colector.forEach((colect)->{
                        colect.release(x, y);
                    });
                    break;
            }
        }
    }
    public void setTipo(TIPO tipo, int finalSize){
        this.tipo = tipo;
        this.finalSize = finalSize;
    }
    public void add(String id, String data){
        switch(tipo){
            case Botonera:
                if (botonera.size()<finalSize){
                    Button b = new Button(bluetooth,id,data,
                            ((botonera.size()%2)==0?background.getMinX():(background.getWidth()/2)+Size.Xp*20)+Size.Xp*10,
                            background.getMinY()+Size.Yp*10+(background.getHeight()/((finalSize+1)/2))*(botonera.size()/2),
                            background.getWidth()/2-Size.Xp*20,
                            background.getHeight()/((finalSize+1)/2)-Size.Yp*20);
                    botonera.add(b);
                    Scenes.add(b);
                }
                break;
            case Colector:
                
                break;
            case Grafica:
                
                break;
            case Display:
                
                break;
        }
    }
    public void end(){
        botonera.forEach((boton)->{
            Scenes.remove(boton);
        });
        Scenes.remove(this);
    }
}

/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

import java.awt.Font;
import java.util.concurrent.atomic.AtomicBoolean;
import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.TrueTypeFont;
import org.newdawn.slick.geom.Rectangle;

/**
 *
 * @author mr.blissfulgrin
 */
public class Button extends Scene implements Clickable{
    private final Rectangle btt;
    private final String id;
    private final String toSend;
    private final Font fuente;
    private TrueTypeFont tFuente;
    private final AtomicBoolean clicked;
    private final Bluetooth bluetooth;
    
    public Button (Bluetooth bluetooth, String id, String toSend,float x,float y,float w,float h){
        super (Scene.STATE.ON,0);
        this.id = id;
        this.toSend = toSend;
        btt = new Rectangle(x,y,w,h);
        clicked = new AtomicBoolean(false);
        this.bluetooth = bluetooth;
        fuente = new Font("Impact", Font.BOLD, 35);
    }

    @Override
    public void click(float x, float y) {
        if (btt.contains(x, y)){
            clicked.set(true);
        }
    }

    @Override
    public void release(float x, float y) {
        if (btt.contains(x, y)){
            clicked.set(false);
            bluetooth.send(toSend);
        }
    }   

    @Override
    public String toString() {
        return "Boton "+id+" "+toSend;
    }

    @Override
    public void Render(GameContainer gc, Graphics g) throws SlickException {
        if (tFuente == null)
            tFuente = new TrueTypeFont(fuente,false);
        if(clicked.get())
            g.setColor(Color.black);
        else
            g.setColor(Color.blue);
        g.fill(btt);
        if(clicked.get())
            g.setColor(Color.lightGray);
        else
            g.setColor(Color.white);
        g.drawString(id, btt.getCenterX()-tFuente.getWidth(id)/2, btt.getCenterY()-tFuente.getHeight(id)/2);
    }

    @Override
    public void Update(GameContainer gc, float t) throws SlickException {
        
    }

    @Override
    public void init(GameContainer gc) throws SlickException {
    }
}

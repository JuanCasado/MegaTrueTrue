/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

import java.awt.Font;
import java.util.concurrent.atomic.AtomicBoolean;
import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.Input;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.TrueTypeFont;
import org.newdawn.slick.command.BasicCommand;
import org.newdawn.slick.command.Command;
import org.newdawn.slick.command.Control;
import org.newdawn.slick.command.InputProvider;
import org.newdawn.slick.command.InputProviderListener;
import org.newdawn.slick.command.MouseButtonControl;
import org.newdawn.slick.geom.Line;
import org.newdawn.slick.geom.Polygon;
import org.newdawn.slick.geom.Rectangle;

/**
 *
 * @author mr.blissfulgrin
 */
public class HUD extends Scene implements InputProviderListener{
    private Rectangle salir;
    private Line salirl1;
    private Line salirl2;
    private Rectangle back;
    private Line backL;
    private Polygon backT;
    private final Bluetooth btt;
    private final Command click;
    private InputProvider provider;
    private final Control mouse = new MouseButtonControl(0);
    private float xMouse;
    private float yMouse;
    private Input input;
    private String menu;
    private final AtomicBoolean cSalir;
    private final AtomicBoolean cBack;
    private final Font fuente;
    private final TrueTypeFont tFuente;
    
    public HUD (Bluetooth btt){
        super(STATE.ON,0);
        this.btt = btt;
        click = new BasicCommand("click");
        menu = "Mega True True";
        cSalir = new AtomicBoolean (false);
        cBack = new AtomicBoolean (false);
                fuente = new Font("Impact", Font.BOLD, 50);
        tFuente = new TrueTypeFont(fuente,false);
    }

    @Override
    public String toString() {
        return "HUD";
    }

    @Override
    public synchronized void Render(GameContainer gc, Graphics g) throws SlickException {
        g.setBackground(Color.blue);
        if (cSalir.get())
            g.setColor(Color.black);
        else
            g.setColor(Color.red);
        g.setLineWidth(20);
        g.fill(salir);
        g.setColor(Color.white);
        g.draw(salirl1);
        g.draw(salirl2);
        g.setFont(tFuente);
        g.drawString(menu, Size.X/2 - tFuente.getWidth(menu)/2, Size.Yp);
        if (cBack.get())
            g.setColor(Color.black);
        else
            g.setColor(Color.orange);
        g.fill(back);
        g.setColor(Color.white);
        g.draw(backL);
        g.fill(backT);
    }

    @Override
    public synchronized void Update(GameContainer gc, float t) throws SlickException {
    }

    @Override
    public synchronized void init(GameContainer gc) throws SlickException {
        this.salir = new Rectangle((Size.X-Size.Xp*40)-Size.Xp*5,Size.Yp*5,Size.Xp*40,Size.Yp*40);
        this.salirl1 = new Line(salir.getMinX()+Size.Xp*5,salir.getMinY()+Size.Xp*5,salir.getMaxX()-Size.Xp*5,salir.getMaxY()-Size.Xp*5);
        this.salirl2 = new Line(salir.getMaxX()-Size.Xp*5,salir.getMinY()+Size.Xp*5,salir.getMinX()+Size.Xp*5,salir.getMaxY()-Size.Xp*5);
        this.back = new Rectangle(Size.Xp*5,Size.Yp*5,Size.Xp*40,Size.Yp*40);
        this.backL = new Line (back.getMinX()+Size.Xp*14,back.getCenterY(),back.getMaxX()-Size.Xp*5,back.getCenterY());
        this.backT = new Polygon ();
        this.backT.addPoint(back.getMinX()+Size.Xp*5, back.getCenterY());
        this.backT.addPoint(back.getMinX()+Size.Xp*15, back.getCenterY()+Size.Yp*10);
        this.backT.addPoint(back.getMinX()+Size.Xp*15, back.getCenterY()-Size.Yp*10);
        input = gc.getInput(); 
        provider = new InputProvider(gc.getInput());
        provider.addListener(this);       
        provider.bindCommand(mouse, click);
    }

    @Override
    public void controlPressed(Command cmnd) {
        if (cmnd.equals(click))
        {
            xMouse = input.getMouseX();
            yMouse = input.getMouseY();
            if (salir.contains(xMouse, yMouse)){
                
            }else if (back.contains(xMouse, yMouse)){
                
            }else{
                btt.click(xMouse, yMouse);
            }
        }
    }
    @Override
    public void controlReleased(Command cmnd) {
       if (cmnd.equals(click))
        {
            if (salir.contains(xMouse, yMouse)){
                cSalir.set(true);
                btt.close();
                System.exit(0);                
            }else if (back.contains(xMouse, yMouse)){
                cBack.set(false);
                btt.send("X");
            }else{
                btt.release(xMouse, yMouse);
            }
        }
    }
    public synchronized void setTextMenu (String txt){
        menu = txt;
    }
}

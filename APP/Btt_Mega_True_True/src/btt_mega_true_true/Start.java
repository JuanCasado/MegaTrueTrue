/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

import org.newdawn.slick.Color;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;
import org.newdawn.slick.geom.Circle;
import org.newdawn.slick.geom.Line;

/**
 *
 * @author mr.blissfulgrin
 */
public class Start extends Scene{
    private Circle circle;
    private Circle onda;
    private Circle vuelta;
    private Line top;
    private Line botom;
    private final Bluetooth bluetooth;
    public Start (){
        super (STATE.ON,0);
        bluetooth = new Bluetooth();
        bluetooth.start();
    }
    @Override
    public String toString() {
        return "Starter Animation";
    }

    @Override
    public void Render(GameContainer gc, Graphics g) throws SlickException {
        g.setBackground(Color.white);
        g.setColor(Color.blue);
        g.setLineWidth(30);
        g.draw(circle);
        if (onda.contains(top)&&onda.contains(botom)){
            g.fill(onda);
            if (onda.radius > circle.radius){
                if (vuelta.radius>(-Size.Yp*150)){
                    g.setColor(Color.white);
                    g.draw(vuelta);
                }else{
                    g.fill(vuelta);
                }
            }
        }else{
            g.draw(top);
            g.draw(botom);
        }
    }

    @Override
    public void Update(GameContainer gc, float t) throws SlickException {
        if (onda.contains(top)&&onda.contains(botom)){
            if (onda.radius > circle.radius){
                vuelta.setRadius(vuelta.radius-t*2);
                vuelta.setCenterX(Size.X/2);
                vuelta.setCenterY(Size.Y/2);
                if (vuelta.radius < -300){
                    vuelta.setRadius(vuelta.radius-t*4);
                    if (vuelta.radius < -1000){
                        if (bluetooth.isConnected()){
                            Scenes.remove(this);
                        }else{
                            this.bluetooth.close();
                            System.exit(0);
                        }
                    }
                }
            }else{
                onda.setRadius(onda.radius+t*3);
                onda.setCenterX(Size.X/2);
                onda.setCenterY(Size.Y/2);
            }
        }else{
            botom.set(
                    botom.getCenterX(), 
                    botom.getMinY()<(circle.getCenterY()-Size.Yp*4)?botom.getMinY()+t:botom.getMinY(), 
                    botom.getCenterX(), 
                    botom.getMaxY()>(circle.getCenterY()-Size.Yp*4)?botom.getMaxY()-t*1.2f:botom.getMaxY()
            );
            top.set(top.getMinX()+t,botom.getMinY(), top.getMaxX()-t, botom.getMinY());
        }
    }

    @Override
    public void init(GameContainer gc) throws SlickException {
        circle = new Circle(Size.X/2,Size.Y/2,Size.Yp*150);
        onda = new Circle(Size.X/2,Size.Y/2,Size.Yp*20);
        vuelta = new Circle(Size.X/2,Size.Y/2,Size.Yp*150);
        top = new Line(Size.X/2-Size.Yp*130,Size.Y/2-Size.Yp*75,Size.X/2+Size.Yp*130,Size.Y/2-Size.Yp*75);
        botom = new Line(Size.X/2,Size.Y/2-Size.Yp*75,Size.X/2,Size.Y/2+Size.Yp*150);
    }
    
}

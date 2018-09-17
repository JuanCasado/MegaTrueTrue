/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;


public abstract class Scene implements Comparable<Scene>
{
    // ESTADOS DE LA ESCENA
    public enum STATE {ON, FREEZE ,OFF};
    private STATE state;
    private int prio; 

    public Scene (STATE state, int prio)
    {
        this.state = state;
        this.prio = prio;
        Scenes.sort();
    }

    public void setPriority ( int p )
    {
        prio = p;
        Scenes.sort();
    }

    public int getPriority ()
    {
        return prio;
    }

    @Override
    public int compareTo(Scene compareObject)
    {
        if (getPriority() < compareObject.getPriority())
            return -1;
        else if (getPriority() == compareObject.getPriority())
            return 0;
        else
            return 1;
    }

    public void setState( STATE s )
    {
        state = s;
    }
    
    public STATE getState(){
        return this.state;
    }
    
    @Override
    public abstract String toString ();
    public abstract void Render(GameContainer gc, Graphics g) throws SlickException;
    public abstract void Update(GameContainer gc, float t) throws SlickException;
    public abstract void init(GameContainer gc) throws SlickException;
}

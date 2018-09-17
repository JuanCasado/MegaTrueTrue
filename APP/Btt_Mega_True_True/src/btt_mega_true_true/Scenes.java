/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

import java.util.ArrayList;
import java.util.Collections;
import org.newdawn.slick.BasicGame;
import org.newdawn.slick.GameContainer;
import org.newdawn.slick.Graphics;
import org.newdawn.slick.SlickException;

/**
 *
 * @author mr.blissfulgrin
 */
public class Scenes extends BasicGame{
    private static ArrayList <Scene> scene;
    private static GameContainer gc;
    public Scenes (String gamename){
        super(gamename);
        scene = new ArrayList <>(); 
    }
    public synchronized void setGc(GameContainer gc){
        Scenes.gc = gc;
    }
    @Override
    public synchronized void render(GameContainer gc, Graphics g) throws SlickException 
    {
        g.setAntiAlias(true);
        for (int x = 0; x < scene.size(); x++){
            if(scene.get(x).getState() != Scene.STATE.OFF)
            {
                try{
                    scene.get(x).Render(gc, g);
                }catch (SlickException e){}
            }
        }
    }

    @Override
    public synchronized void update(GameContainer gc, int i) throws SlickException {
        float t = i*0.1f;
        for (int x = 0; x < scene.size(); x++){
            if(scene.get(x).getState() == Scene.STATE.ON)
            {
                try{
                    scene.get(x).Update(gc, t);
                }catch (SlickException e){}
            }
        }
    }
    
    public static synchronized void clear (){
        scene.clear();
    }
    
    @Override
    public synchronized void init(GameContainer gc) throws SlickException{
        Start start = new Start();
        scene.add(start);
        for (int x = 0; x < scene.size(); x++){
            if(scene.get(x).getState() == Scene.STATE.ON)
            {
                try{
                    scene.get(x).init(gc);
                }catch (SlickException e){}
            }
        }
    }
    public synchronized static void sort (){
        Collections.sort(scene);
    }
    public synchronized static void add (Scene sc){
        try 
        {
            scene.add(sc);
            sc.init(gc);
        } 
        catch (SlickException e) 
        {
            System.out.println("ERROR DE ESCENA " + e.toString());
        }
        Collections.sort(scene);
    }
    public synchronized static void remove (Scene sc){
        scene.remove(sc);
        Collections.sort(scene);
    }
}

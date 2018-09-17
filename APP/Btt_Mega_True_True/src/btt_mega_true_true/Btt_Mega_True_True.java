/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

import org.newdawn.slick.AppGameContainer;
import org.newdawn.slick.SlickException;

/**
 *
 * @author mr.blissfulgrin
 */
public class Btt_Mega_True_True {
    //java -Djava.library.path=./lib/slick -jar ./dist/Btt_Mega_True_True.jar
    public static void main(String[] args) {
        AppGameContainer app;
        try{
            Scenes scenes = new Scenes ("Mega True TRue");
            app = new AppGameContainer(scenes);
            scenes.setGc(app);
            app.setDisplayMode(app.getScreenWidth(),app.getScreenHeight(), true);
            app.setShowFPS(false);
            app.setTargetFrameRate(45);
            app.setIcon("./media/icon.png");
            Size.setSize(app.getScreenWidth(), app.getScreenHeight());
            app.start();
        }catch (SlickException s){}
    }
}

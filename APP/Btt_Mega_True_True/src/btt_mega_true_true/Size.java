/*
 * Mr.BlissfulGrin
 */
package btt_mega_true_true;

/**
 *
 * @author mr.blissfulgrin
 */
public class Size {
    public static float X;
    public static float Y;
    public static float Xp;
    public static float Yp;
    public static void setSize (float X,float Y){
        Size.X = X;
        Size.Y = Y;
        Size.Xp = X/1000;
        Size.Yp = Y/1000;
    }
    private Size (){}
}
